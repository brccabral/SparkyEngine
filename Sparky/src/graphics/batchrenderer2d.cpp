#include "batchrenderer2d.h"

namespace sparky
{
	namespace graphics
	{
		using namespace maths;

		BatchRenderer2D::BatchRenderer2D()
			: m_IndexCount(0)
		{
			init();
		};

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
			glDeleteVertexArrays(1, &m_VAO);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			// get the vertex position based on VertexData
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_MID_INDEX);
			// get the color position based on VertexData
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, uv)));
			glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, mask_uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, tid)));
			glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, mid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0); // bind and unbind costs a lot

			// create triangle indices
			// t1 = 0,1,2, 2,3,0
			// t2 = 4,5,6, 6,7,4
			GLuint *indices = new GLuint[RENDERER_INDICES_SIZE]; // moving to HEAP we can load more sprites on Windows
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
			glBindVertexArray(0);

		#ifdef SPARKY_PLATFORM_WEB
			m_BufferBase = new VertexData[RENDERER_MAX_TEXTURES * 4];
		#endif
		};

		float BatchRenderer2D::submitTexture(const Texture *texture)
		{
			uint id = texture->getID();

			float result = 0.0f;
			bool found = false;
			if (id > 0)
			{
				for (uint i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i] == id)
					{
						result = (float)(i + 1);
						found = true;
						break;
					}
				}
				if (!found)
				{
					// openGL has a limit to hold 32 textures
					// if we have more than that, flush (draw)
					// what we have in memory and add more starting from 0
					if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES)
					{
						end();
						flush();
						begin();
					}
					m_TextureSlots.push_back(id);
					result = (float)(m_TextureSlots.size());
				}
			}
			return result;
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		#ifdef SPARKY_PLATFORM_WEB
			m_Buffer = m_BufferBase;
		#else
			m_Buffer = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		#endif
		};

		// submit will create a rectangle
		void BatchRenderer2D::submit(const Renderable2D *renderable)
		{
			// indices 0,1,2, 2,3,0
			const vec3 &position = renderable->getPosition();
			const vec2 &size = renderable->getSize();
			const uint color = renderable->getColor();
			const std::vector<vec2> &uv = renderable->getUV();
			const GLuint tid = renderable->getTID();

			float ts = 0.0f;
			if(tid > 0)
				ts = submitTexture(renderable->getTexture());

			mat4 maskTransform = mat4::identity();
			const GLuint mid = m_Mask ? m_Mask->texture->getID() : 0;
			float ms = 0.0f; // mask slot

			if (m_Mask != nullptr)
			{
				maskTransform = mat4::invert(m_Mask->transform);
				ms = submitTexture(m_Mask->texture);
			}

			vec3 vertex = *m_TransformationBack * position;
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[0];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(position.x, position.y + size.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[1];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[2];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			vertex = *m_TransformationBack * vec3(position.x + size.x, position.y, position.z);
			m_Buffer->vertex = vertex;
			m_Buffer->uv = uv[3];
			m_Buffer->mask_uv = maskTransform * vertex;
			m_Buffer->tid = ts;
			m_Buffer->mid = ms;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		};

		void BatchRenderer2D::end()
		{
		#ifdef SPARKY_PLATFORM_WEB
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, (m_Buffer - m_BufferBase) * RENDERER_VERTEX_SIZE, m_BufferBase);
			m_Buffer = m_BufferBase;
		#else
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		#endif
	};

		void BatchRenderer2D::flush()
		{
			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);
			m_IndexCount = 0;

			m_TextureSlots.clear();
		}

		void BatchRenderer2D::drawString(const std::string &text, vec3 position, const Font &font, uint color)
		{
			float ts = 0.0f;

			bool found = false;
			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == font.getID())
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found)
			{
				// openGL has a limit to hold 32 textures
				// if we have more than that, flush (draw)
				// what we have in memory and add more starting from 0
				if (m_TextureSlots.size() >= 32)
				{
					end();
					flush();
					begin();
				}
				m_TextureSlots.push_back(font.getID());
				ts = (float)(m_TextureSlots.size());
			}

			// scale to the size of our window
			const vec2 &scale = font.getScale();

			// position is const, we need separated variable to move chars
			float x = position.x;

			for (byte i = 0; i < text.length(); i++)
			{
				char c = text.at(i);
				ftgl::texture_glyph_t *glyph = ftgl::texture_font_get_glyph(font.getFTGLFont(), c);
				if (glyph != NULL)
				{
					// space between chars
					if (i > 0)
					{
						float kerning = ftgl::texture_glyph_get_kerning(glyph, text.at(i - 1));
						x += kerning / scale.x;
					}

					// get char position on screen x/y/u/v
					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					// add to buffer
					m_Buffer->vertex = *m_TransformationBack * vec3(x0, y0, 0.0f);
					m_Buffer->uv = vec2(u0, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * vec3(x0, y1, 0.0f);
					m_Buffer->uv = vec2(u0, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * vec3(x1, y1, 0.0f);
					m_Buffer->uv = vec2(u1, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * vec3(x1, y0, 0.0f);
					m_Buffer->uv = vec2(u1, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_IndexCount += 6;

					// move to next char position.
					x += glyph->advance_x / scale.x;
				}
			}
		};

}
}
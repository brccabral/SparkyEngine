#include "PostEffectsPass.h"

namespace sparky
{
	namespace graphics
	{

		PostEffectsPass::PostEffectsPass(Shader *shader)
			: m_Shader(shader)
		{
			m_Shader->Bind();
			m_Shader->SetUniform("tex", 0);
			m_Shader->Unbind();
		}

		PostEffectsPass::~PostEffectsPass()
		{}

		void PostEffectsPass::RenderPass(Framebuffer *target)
		{
			m_Shader->Bind();
			m_Shader->SetUniform("pr_matrix", maths::mat4::Orthographic(0.0f, (float)target->GetWidth(), (float)target->GetHeight(), 0.0f, -1.0f, 1.0f));
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
			m_Shader->Unbind();
		}

	}
}
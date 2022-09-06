#pragma once

#include <iostream>
#include <string>
#include <utils/Log.h> // needs to be before GL, redefinition of APIENTRY
#include <sparkygl.h>
#include <utils/imageload.h>

namespace sparky
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_Name, m_FileName;
			GLuint m_TID;
			GLsizei m_Width, m_Height;
			unsigned int m_Bits;
		public:
			Texture(const std::string &name, const std::string &filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() const { return m_Width; };
			inline const unsigned int getHeight() const { return m_Height; };
			inline const unsigned int getID() const { return m_TID; };
			inline const std::string &getName() const { return m_Name; };
		private:
			GLuint load();
		};
	}
}
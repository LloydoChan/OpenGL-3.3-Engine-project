//TexturedShader.h
#pragma once
#include "Includes.h"
#include "Shader.h"

namespace OpenGL_3_3Engine
{
	class TexturedShader
	{
		public:
			TexturedShader(){};
			~TexturedShader(){};

			bool Init();
			GLuint GetHandle()const {return textureShader.GetHandle();}

			void UpdateUniforms(glm::mat4& MVPMatrix);

			Shader textureShader; 		
	};
};
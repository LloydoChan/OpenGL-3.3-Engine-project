//CubeMapShader.h - interface for cubemap prebuilt shader
#pragma once
#include "Includes.h"
#include "Shader.h"

namespace OpenGL_3_3Engine
{
	class CubeMapShader
	{
		public:
			CubeMapShader(){};
			~CubeMapShader(){};

			bool Init();
			GLuint GetHandle()const {return cubemap.GetHandle();}

			void UpdateUniforms(glm::mat4& MVPMatrix,int texture);

			Shader cubemap; 			
	};
};
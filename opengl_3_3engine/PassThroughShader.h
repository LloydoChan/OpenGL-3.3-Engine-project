//PassThroughShader.h
//last update: 20/07/2012
#pragma once

#include "Shader.h"

namespace OpenGL_3_3Engine
{
	class PassThroughShader
	{
		public:
			PassThroughShader(){};
			~PassThroughShader(){};

			bool Init();
			GLuint GetHandle()const {return passthrough.GetHandle();}

			void UpdateUniforms(glm::mat4& MVPMatrix);

			Shader passthrough; 			
	};
};
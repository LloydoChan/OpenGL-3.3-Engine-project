//FiveLightVertexShader.h - vertex shading, faster version of FiveLightFragmentShader
//last update 26/07/2012
#pragma once
#include "Includes.h"

#include "Shader.h"
#include "LightsAndMaterials.h"

namespace OpenGL_3_3Engine
{
	

	class FiveLightVertexShader
	{
		public:
			FiveLightVertexShader(){};
			~FiveLightVertexShader(){};

			bool Init();
			GLuint GetHandle()const {return fiveLight.GetHandle();}

			void UpdateUniforms(glm::mat4& MVPMatrix,glm::mat4& projectionMatrix,glm::mat4& modelViewMatrix,
								PointLightStruct* lights,MaterialStruct& mat,int numLights = 1,bool spec = false);

			void UpdateUniforms(glm::mat4& MVPMatrix,glm::mat4& projectionMatrix,glm::mat4& modelViewMatrix,
								PointLightStruct* lights,int numLights = 1,bool spec = false);

			void UpdateUniforms(MaterialStruct& mat);

			Shader fiveLight; 			
	};
}

//LightsAndMaterials.h - interface/declaration of light and material structs
//for use in lighting and passing to shaders etc
//last update 26/07/2012

#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	struct PointLightStruct
	{
		glm::vec3 pos;
		glm::vec3 color;
		float attenuation1;
		float attenuation2;
		float attenuation3;
	};

	struct DirectionalLightStruct
	{
		glm::vec3 direction;
		glm::vec3 color;
	};

	struct SpotLightStruct
	{
		glm::vec3 direction;
		glm::vec3 color;
		glm::vec3 position;
		float exponent;
		float cutoff;
	};

	struct MaterialStruct
	{
		glm::vec3 amb;
		glm::vec3 diff;
		glm::vec3 spec;
		float shininess;
	};
};
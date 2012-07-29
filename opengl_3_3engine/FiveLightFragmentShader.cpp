//FiveLightShader.cpp
//Last update 25/07/2012
#include "FiveLightFragmentShader.h"

namespace OpenGL_3_3Engine
{
	const char* lightVert = //texture.vp
		"#version 330 \n"
		"in vec3 vertexPosition;\n"
		"in vec3 vertexNormal; \n"
		"in vec2 textureCoord; \n"

		"out     vec3 position; \n"
		"out     vec3 normal;   \n"

		"uniform mat4 modelViewMatrix; \n"
		"uniform mat3 normalMatrix; \n"
		"uniform mat4 projectionMatrix; \n"
		"uniform mat4 MVPMatrix; \n"

		"void main() \n"
		"{ \n"
		"  normal = normalize(normalMatrix * vertexNormal); \n"
		"  position = vec3 (modelViewMatrix * vec4(vertexPosition,1.0f)); \n"
		"  gl_Position = MVPMatrix * vec4(vertexPosition,1.0f); \n"
		"} \n";

	const char* lightFrag = 
		"#version 330 \n"
		"in vec3 position; \n"
		"in vec3 normal; \n"

		"uniform vec3 lightPos[5]; \n"
		"uniform vec3 lightIntensity[5]; \n"
		"uniform int numLights; \n"


		"uniform vec3 Ka; // Ambient reflectivity \n"
		"uniform vec3 Kd; // Diffuse reflectivity \n"
		"uniform vec3 Ks; // Specular reflectivity \n"
		"uniform float shininess; // Specular shininess factor \n"

		"vec3 phongModel(vec3 normal,vec3 lightPos,vec3 lightIntensity) \n"
		"{ \n"
		"	vec3 n = normalize(normal); \n"
		"	vec3 s = normalize(lightPos.xyz - position); \n"
		"	vec3 v = normalize(-position); \n"
		"	vec3 h = normalize(v+s); \n"
		"	vec3 ambient = lightIntensity * Ka; \n"
		"	float sDotN = max( dot(s,n), 0.0 ); \n"
		"	vec3 spec,diffuse = vec3(0.0);	\n"
		"	spec = lightIntensity * Ks * pow( max( dot(h,n), 0.0 ), shininess ); \n"
		"	diffuse = lightIntensity * Kd * sDotN; \n"
		"	return ambient + diffuse + spec; \n"
		"} \n"

		"out vec4 FragColor; \n"

		"void main() \n"
		"{ \n"
		"   vec3 lightColor = vec3(0.0); \n"
		"   for(int l = 0; l < 5; l++)\n"
		"   { \n"
		"		lightColor += phongModel(normal,lightPos[l],lightIntensity[l]);\n"
		"   } \n"
		"   \n"
		"   FragColor = vec4(lightColor,1.0f); \n"
		"} ";

	bool FiveLightFragmentShader::Init()
	{
		return fiveLight.InitShaderProgramFromString(lightVert,lightFrag,2,"vertexPosition","vertexNormal");
	}


	void FiveLightFragmentShader::UpdateUniforms(glm::mat4& MVPMatrix,glm::mat4& projectionMatrix,glm::mat4& modelViewMatrix,
								PointLightStruct* lights,MaterialStruct& mat,int numLights,bool spec)
	{
		fiveLight.SetUniform("MVPMatrix",MVPMatrix);
		fiveLight.SetUniform("projectionMatrix",projectionMatrix);
		fiveLight.SetUniform("modelViewMatrix",modelViewMatrix);
		fiveLight.SetUniform("normalMatrix",glm::transpose(glm::mat3x3(modelViewMatrix)));

		fiveLight.SetUniform("numLights",numLights);

		fiveLight.SetUniform("Ka",mat.amb);
		fiveLight.SetUniform("Ks",mat.spec);
		fiveLight.SetUniform("Kd",mat.diff);
		fiveLight.SetUniform("shininess",mat.shininess);

		char buf[18]; // a char buffer to concatenate c strings with integers

		for(int light = 0; light < numLights; light++)
		{
			sprintf(buf,"lightPos[%d]",light);
			fiveLight.SetUniform(buf,lights[light].pos);

			sprintf(buf,"lightIntensity[%d]",light);
			fiveLight.SetUniform(buf,lights[light].color);
		}

	}

	void FiveLightFragmentShader::UpdateUniforms(glm::mat4& MVPMatrix,glm::mat4& projectionMatrix,glm::mat4& modelViewMatrix,
										PointLightStruct* lights,int numLights,bool spec)
	{
		fiveLight.SetUniform("MVPMatrix",MVPMatrix);
		fiveLight.SetUniform("projectionMatrix",projectionMatrix);
		fiveLight.SetUniform("modelViewMatrix",modelViewMatrix);
		fiveLight.SetUniform("normalMatrix",glm::transpose(glm::mat3x3(modelViewMatrix)));

		fiveLight.SetUniform("numLights",numLights);


		char buf[18]; // a char buffer to concatenate c strings with integers

		for(int light = 0; light < numLights; light++)
		{
			sprintf(buf,"lightPos[%d]",light);
			fiveLight.SetUniform(buf,lights[light].pos);

			sprintf(buf,"lightIntensity[%d]",light);
			fiveLight.SetUniform(buf,lights[light].color);
		}
	}

	void FiveLightFragmentShader::UpdateUniforms(MaterialStruct& mat)
	{
		fiveLight.SetUniform("Ka",mat.amb);
		fiveLight.SetUniform("Ks",mat.spec);
		fiveLight.SetUniform("Kd",mat.diff);
		fiveLight.SetUniform("shininess",mat.shininess);
	}
};

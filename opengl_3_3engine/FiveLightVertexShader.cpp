//FiveLightVertexShader.cpp
//Last update 25/07/2012
#include "FiveLightVertexShader.h"

namespace OpenGL_3_3Engine
{
	const char* lightVert2 = //texture.vp
		"#version 330 \n"
		"in vec3 vertexPosition;\n"
		"in vec3 vertexNormal; \n"
		"in vec2 textureCoord; \n"

		"out vec3 color; \n"
		"out vec2 texCoord; \n"

		"uniform mat4 modelViewMatrix; \n"
		"uniform mat3 normalMatrix; \n"
		"uniform mat4 projectionMatrix; \n"
		"uniform mat4 MVPMatrix; \n"

		"uniform vec3 lightPos[5]; \n"
		"uniform vec3 lightIntensity[5]; \n"
		"uniform int numLights; \n"


		"uniform vec3 Ka; // Ambient reflectivity \n"
		"uniform vec3 Kd; // Diffuse reflectivity \n"
		"uniform vec3 Ks; // Specular reflectivity \n"
		"uniform float shininess; // Specular shininess factor \n"

		"vec3 phongModel(vec3 normal,vec3 lightPos,vec3 lightIntensity,vec3 position) \n"
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

		"void main() \n"
		"{ \n"
		"  texCoord = textureCoord; \n"
		"  vec3 normal   = normalize(normalMatrix * vertexNormal); \n"
		"  vec3 position = vec3 (modelViewMatrix * vec4(vertexPosition,1.0f)); \n"
		"  for(int i = 0; i < 5; i++) \n"
		"       color += phongModel(normal,lightPos[i],lightIntensity[i],position); \n"
		"  gl_Position = MVPMatrix * vec4(vertexPosition,1.0f); \n"
		"} \n";

	const char* lightFrag2 = 
		"#version 330 \n"
		"in vec3 color;\n"
		"in vec2 texCoord; \n"

		"uniform sampler2D meshTexture; \n"

		"out vec4 FragColor; \n"

		"void main() \n"
		"{ \n"
		"   vec4 texCol = texture2D(meshTexture,texCoord); \n"
		"   FragColor = vec4(texCol.xyz * color,1.0f); \n"
		"} ";

	bool FiveLightVertexShader::Init()
	{
		return fiveLight.InitShaderProgramFromString(lightVert2,lightFrag2,3,"vertexPosition","vertexNormal","textureCoord");
	}


	void FiveLightVertexShader::UpdateUniforms(glm::mat4& MVPMatrix,glm::mat4& projectionMatrix,glm::mat4& modelViewMatrix,
								PointLightStruct* lights,MaterialStruct& mat,int numLights,bool spec)
	{
		fiveLight.SetUniform("MVPMatrix",MVPMatrix);
		fiveLight.SetUniform("projectionMatrix",projectionMatrix);
		fiveLight.SetUniform("modelViewMatrix",modelViewMatrix);
		fiveLight.SetUniform("normalMatrix",glm::transpose(glm::mat3x3(modelViewMatrix)));

		fiveLight.SetUniform("numLights",numLights);

		fiveLight.SetUniform("meshTexture",0);

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

	void FiveLightVertexShader::UpdateUniforms(glm::mat4& MVPMatrix,glm::mat4& projectionMatrix,glm::mat4& modelViewMatrix,
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

	void FiveLightVertexShader::UpdateUniforms(MaterialStruct& mat)
	{
		fiveLight.SetUniform("Ka",mat.amb);
		fiveLight.SetUniform("Ks",mat.spec);
		fiveLight.SetUniform("Kd",mat.diff);
		fiveLight.SetUniform("shininess",mat.shininess);
	}
};

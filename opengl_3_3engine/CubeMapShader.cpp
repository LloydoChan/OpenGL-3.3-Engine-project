//CubeMapShader.cpp
#include "CubeMapShader.h"

namespace OpenGL_3_3Engine
{
	const char* cubeVert = 
		
	"#version 330 \n"

	"in vec3 position; \n"
	"in vec3 color; \n"
	"in vec3 texture; \n"

	"varying vec3 ray; \n"

	"uniform mat4 MVPMatrix; \n"

	"void main() \n"
	"{ \n"
		"ray = normalize(position); \n"
		"gl_Position = MVPMatrix * vec4(position,1.0f); \n"
	"}";


	const char* cubeFrag = 

	"#version 330 \n"
	"varying vec3 ray;\n"

	"uniform samplerCube CubeMapTex;\n"

	"out vec4 FragColor; \n"

	"void main() \n"
	"{\n"
		"FragColor = texture(CubeMapTex,ray); \n"
	"}\n";

	bool CubeMapShader::Init()
	{
		return cubemap.InitShaderProgramFromString(cubeVert,cubeFrag,2,"position","color");
	}

	void CubeMapShader::UpdateUniforms(glm::mat4& MVPMatrix,int texture)
	{
		cubemap.SetUniform("MVPMatrix",MVPMatrix);
		cubemap.SetUniform("CubeMapTex",texture);
	}

}
//PassThroughShader.cpp
//last update 20/07/2012
#include "PassThroughShader.h"

namespace OpenGL_3_3Engine
{
	const char* passVert = "#version 330 \n"

	"in vec3 position; \n"
	"in vec3 color; \n"

	"uniform mat4 MVPMatrix; \n"


	"out vec3 fragColor; \n"

	"void main() \n"
	"{ \n"
	"  fragColor = color; \n"
	"  gl_Position = MVPMatrix * vec4(position,1.0f); \n"

	"}";


	const char* passFrag = "#version 330 \n"

	"in vec3 fragColor;\n"

	"out vec4 col;\n"

	"void main()\n"
	"{\n"
	"  col = vec4(fragColor,1.0f);\n"
	"}";

	bool PassThroughShader::Init()
	{
		return passthrough.InitShaderProgramFromString(passVert,passFrag,2,"position","color");
	}

	void PassThroughShader::UpdateUniforms(glm::mat4& MVPMatrix)
	{
		passthrough.SetUniform("MVPMatrix",MVPMatrix);
	}

}
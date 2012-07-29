//TexturedShader.cpp - implementation of texture shader
#pragma once

#include "TexturedShader.h"

namespace OpenGL_3_3Engine
{
	const char* texVert = //texture.vp
		"#version 330 core \n"

		"in vec3 position; \n"
		"in vec2 textureCoord;\n"
		"out vec2 UV; \n"

		"uniform mat4 MVPMatrix; \n"

		"void main(){ \n"
		"	gl_Position =  MVPMatrix * vec4(position,1); \n"
		"	UV = textureCoord; \n"
		"} \n";

	const char* texFrag = 
		"#version 330 \n"

		"in vec2 UV; \n"

		"out vec4 col; \n"

		"uniform sampler2D texture; \n"

		"void main() \n"
		"{ \n"
		"  vec3 texCol = texture(texture,UV).xyz; \n"
		"  col = vec4(texCol,1.0f);\n"
		"}";
	
	

	bool TexturedShader::Init()
	{
		return textureShader.InitShaderProgramFromString(texVert,texFrag,2,"position","textureCoord");
	}


	void TexturedShader::UpdateUniforms(glm::mat4& MVPMatrix)
	{
		textureShader.SetUniform("MVPMatrix",MVPMatrix);
		glActiveTexture(GL_TEXTURE0);
		textureShader.SetUniform("texture",0);
	}
 		
	
};
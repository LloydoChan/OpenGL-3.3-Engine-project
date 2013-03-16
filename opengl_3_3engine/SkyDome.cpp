//SkyDome.cm_latSlicesm_latSlices

#include "SkyDome.h"

using glm::vec3;
using glm::vec2;

namespace OpenGL_3_3Engine{

bool	SkyDome::Init(const std::string& textureName,ResourceManager<Shader>* shaderMan,ResourceManager<Texture>* texMan,
	                   ResourceManager<StaticMesh>* meshMan){
	meshMan->Add("sphere.obj","sphere\\");
	m_skyMesh = meshMan->GetElement("sphere.obj","sphere\\");
	m_skyMesh->Init(texMan,shaderMan);

	shaderMan->Add("skyShader","shaders\\");
	m_shader = shaderMan->GetElement("skyShader","shaders\\");

	glActiveTexture(GL_TEXTURE0);
	m_skyTexture = new CubeMap();
	m_skyTexture->Init("textures\\sand");

	return true;

}

void	SkyDome::Render(const glm::mat4x4& MVPMatrix){

	glFrontFace(GL_CW);
	glUseProgram(m_shader->GetProgramHandle());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,m_skyTexture->GetHandle());
		m_shader->SetUniform("MVPMatrix",MVPMatrix * glm::scale(6.0f,6.0f,6.0f));
		m_shader->SetUniform("cubemap",0);
		m_skyMesh->Render();
	glUseProgram(0);
	glFrontFace(GL_CCW);
}

void	SkyDome::Destroy(){
	
	if(m_shader){
		delete m_shader;
		m_shader = NULL;
	}

	if(m_skyMesh){
		delete m_skyMesh;
		m_skyMesh = NULL;
	}

	if(m_skyTexture){
		delete m_skyTexture;
	}
}

}
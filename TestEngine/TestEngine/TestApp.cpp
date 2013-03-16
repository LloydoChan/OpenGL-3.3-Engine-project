//TestApp.cpp
#include "TestApp.h"
#include <time.h>


TestApp::TestApp()
{
	

}

bool TestApp::Init()
{
	/*if(!object->Init(indices,3,positionData,3,textureData,3))
		return false;*/

	glClearColor(1.0f,0.0f,0.0f,1.0f);

	unsigned int indices[] = {0,1,2};
	float vertices[] = {-0.4f,-0.4f,0.0f,
	                    0.8f,-0.8f,0.0f,
	                    0.0f,0.8f,0.0};

	m_objBuffer = new ObjectData(1,1);
	m_objBuffer->Init(indices,3,vertices,NULL,NULL);

	m_shaderMan = new ResourceManager<Shader>(CreateShaderWithVertsNormsTextures);
	m_texMan    = new ResourceManager<Texture>(CreateTexture);
	m_meshMan   = new ResourceManager<StaticMesh>(CreateStaticMesh);


	//m_shaderHandle = m_shaderMan->Add("texture","");
	m_shaderHandle = m_shaderMan->Add("texture","");
	m_meshHandle = m_meshMan->Add("PartyGirl\\","PartyGirl.obj");

	StaticMesh* mesh = m_meshMan->GetElement(m_meshHandle);
	mesh->Init(m_texMan,m_shaderMan);
	return true;
}

void TestApp::Render()
{
	static float time = 0.0f;
	Shader* shader = m_shaderMan->GetElement(m_shaderHandle);
	StaticMesh* mesh = m_meshMan->GetElement(m_meshHandle);
	glUseProgram(shader->GetProgramHandle());
	  mesh->Render();
	glUseProgram(0);
	
	time += 0.001f;
}

void TestApp::ReadInput()
{
	
}

void TestApp::Shutdown()
{

	delete m_objBuffer;
	delete m_shaderMan;
	delete m_meshMan;
	delete m_texMan;
}
//SkyDome.h
//last modified 16/01/2013

#pragma once
#include "Includes.h"
#include "ObjectData.h"
#include"CubeMap.h"
#include "Shader.h"
#include "StaticMesh.h"

using glm::mat4x4;

namespace OpenGL_3_3Engine{

class SkyDome{

	public:
		SkyDome(float radius):m_radius(radius),m_skyTexture(NULL),m_skyMesh(NULL),m_shader(NULL){};
		~SkyDome() {Destroy();}

		bool			Init(const std::string& textureName,ResourceManager<Shader>* shaderMan,ResourceManager<Texture>* texMan,ResourceManager<StaticMesh>* meshMan);
		void			Render(const glm::mat4x4& MVPMatrix);
		void			Destroy();
	private:
		float				m_radius;
		StaticMesh*         m_skyMesh;
		CubeMap*			m_skyTexture;
		Shader*             m_shader;
		mat4x4              m_transform;
};

}
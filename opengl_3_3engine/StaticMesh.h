//StaticMesh.h - this class uses assimp to load models and is used to represent all the data in a mesh
//through assimp's supported classes it can store many kinds of file type
//last updata 22/01/2013 - deleted pointer to texture manager

#pragma once
#include "Includes.h"
#include "ObjectData.h"
#include "Texture.h"
#include "Shader.h"
#include "LightsAndMaterials.h"
#include "ResourceManager.h"

struct aiScene;
struct aiNode;
struct aiMatrix4x4;
struct aiMaterial;

namespace OpenGL_3_3Engine{




struct MeshComponent{
	ObjectData* m_meshData;
	MaterialStruct* m_material;
	bool m_hasTexture;
	Texture* m_texture;

	MeshComponent() : m_hasTexture(false) { m_meshData = NULL; m_material = NULL; m_texture = NULL;}
	~MeshComponent() {delete m_meshData; delete m_material;}};



class StaticMesh : public Uncopyable, public Resource{
	public:
		StaticMesh(const unsigned int handle,const string& name,const string& path): Resource(handle,name,path) {;}
		~StaticMesh();

		bool				Init(ResourceManager<Texture>* texMan, ResourceManager<Shader>* shaderMan);
		int					GetNumMeshes()const {return m_numMeshes;}
		int					GetNumMaterials()const {return m_numMaterials;}
		void				Render();

		void				SetTextureManager(ResourceManager<Texture>* texMan){ m_texMan = texMan;}
		void				SetShaderManager(ResourceManager<Shader>* shaderMan){ m_shaderMan = shaderMan;}
	
	protected:
		//support functions for use by Init();
		void				GetBoundingBox(glm::vec3& min,glm::vec3& max,const aiScene* scene);
		void				GetBoundingBoxForNode(const aiNode* node,glm::vec3& min,glm::vec3& max,aiMatrix4x4& trafo,const aiScene* scene);
		MaterialStruct*		LoadMaterials(const aiScene* scene,aiMaterial* materials);
		Texture*			LoadTextures(const char* directory,const  aiScene* scene,aiMaterial* material);

		std::vector<MeshComponent*> m_meshData;
		glm::vec3					m_boundingBoxMin;
		glm::vec3					m_boundingBoxMax;
		unsigned int				m_numMaterials;
		unsigned int				m_numMeshes;
		Texture*					m_texture;
		ResourceManager<Texture>*   m_texMan;
	    ResourceManager<Shader>*    m_shaderMan;};

inline void StaticMesh::Render()
{
	for(unsigned int meshNum = 0; meshNum < m_numMeshes; meshNum++){
		
		if(m_meshData[meshNum]->m_hasTexture){
			glBindTexture(GL_TEXTURE_2D,m_meshData[meshNum]->m_texture->GetHandle());
		}

		glBindVertexArray(m_meshData[meshNum]->m_meshData->GetVAO());
		glDrawElements(GL_TRIANGLES,m_meshData[meshNum]->m_meshData->GetNumFaces() * 3,GL_UNSIGNED_INT,0);}

}

void CreateStaticMesh(StaticMesh** mesh,const unsigned int handle,const std::string& path,const std::string& name);

};

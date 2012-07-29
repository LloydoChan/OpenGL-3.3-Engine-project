//StaticMesh.h - this class uses assimp to load models and is used to represent all the data in a mesh
//through assimp's supported classes it can store many kinds of file type
//last updata 26/07/2012

#pragma once
#include "Includes.h"
#include "ObjectData.h"
#include "Texture.h"
#include "Shader.h"
#include "LightsAndMaterials.h"
#include "Texture.h"

struct aiScene;
struct aiNode;
struct aiMatrix4x4;
struct aiMaterial;

namespace OpenGL_3_3Engine
{
	struct MeshComponent
	{
		ObjectData* m_meshData;
		MaterialStruct* m_material;
		bool m_hasTexture;
		Texture* m_texture;

		MeshComponent() : m_hasTexture(false) { m_meshData = NULL; m_material = NULL; m_texture = NULL;}
		~MeshComponent() {delete m_meshData; delete m_material; delete m_texture;}
	};

	class StaticMesh
	{
		public:
			StaticMesh(){}
			~StaticMesh();

			bool Init(const char* filename,const char* directory);

			void Render(int meshNum);

			glm::mat4x4 m_transform,m_scale;
			std::vector<MeshComponent*> m_meshData;

			float m_scaleFactor;
			glm::vec3 m_boundingBoxMin,m_boundingBoxMax;
			int m_numMaterials;
			int m_numMeshes;
		private:
			//support functions for use by Init();
			void GetBoundingBox(glm::vec3& min,glm::vec3& max,const aiScene* scene);
			void GetBoundingBoxForNode(const aiNode* node,glm::vec3& min,glm::vec3& max,aiMatrix4x4& trafo,
				                       const aiScene* scene);
			MaterialStruct* LoadMaterials(const aiScene* scene,aiMaterial* materials);
			Texture*        LoadTextures(const char* directory,const  aiScene* scene,aiMaterial* material);
			//void RecursiveRender(const aiScene* scene,const aiNode* node);


	};

	inline void StaticMesh::Render(int meshNum)
	{
		if(m_meshData[meshNum]->m_hasTexture)
		{
			glBindTexture(GL_TEXTURE_2D,m_meshData[meshNum]->m_texture->m_handle);
		}

		glBindVertexArray(m_meshData[meshNum]->m_meshData->GetVAO());
		glDrawElements(GL_TRIANGLES,m_meshData[meshNum]->m_meshData->GetNumFaces() * 3,GL_UNSIGNED_INT,0);

	}
};
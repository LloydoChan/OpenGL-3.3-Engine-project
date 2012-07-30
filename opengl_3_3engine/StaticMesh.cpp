//StaticMesh.cpp - implementation of loading meshes, initialising vertex buffer data etc
// http://www.lighthouse3d.com/cg-topics/code-samples/importing-3d-models-with-assimp/ was a great reference in building 
//this

//last update 26/07/2012


#include "StaticMesh.h"
#include <Assimp/aiScene.h>
#include <Assimp/aiPostProcess.h>
#include <Assimp/aiMesh.h>
#include <Assimp/assimp.hpp>
#include <Assimp/assimp.h>

namespace OpenGL_3_3Engine
{
	StaticMesh::~StaticMesh()
	{
		for(std::vector<MeshComponent*>::iterator meshData = m_meshData.begin(); meshData != m_meshData.end(); meshData++)
		{
			delete *meshData;
		}

		m_meshData.clear();
	}

	bool StaticMesh::Init(const char* filename,const char* directory)
	{
		//check if file exists
		char buf[40];
		sprintf(buf,"%s//%s",directory,filename);
		std::ifstream fin(buf);

		if(!fin.fail())
		{
			fin.close();
		}
		else
		{
			std::cout << "Couldn't open file "<< buf <<" it doesn't exist!" << std::endl;
			return false;
		}

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(buf,aiProcess_Triangulate | aiProcess_GenSmoothNormals);

		if(!scene)
		{
			std::cout <<"couldn't load scene! Reason: "<< importer.GetErrorString() <<std::endl;
			return false;
		}


		GetBoundingBox(m_boundingBoxMin,m_boundingBoxMax,scene);

		float biggestDifferenceAxis = 0.0f;
		biggestDifferenceAxis = m_boundingBoxMax.x - m_boundingBoxMin.x; 

		if(m_boundingBoxMax.y - m_boundingBoxMin.y > biggestDifferenceAxis )
			biggestDifferenceAxis = m_boundingBoxMax.y - m_boundingBoxMin.y;

		if(m_boundingBoxMax.z - m_boundingBoxMin.z > biggestDifferenceAxis )
			biggestDifferenceAxis = m_boundingBoxMax.z - m_boundingBoxMin.z;

		m_scaleFactor = 1.0f/biggestDifferenceAxis;

		m_scale = glm::scale(m_scaleFactor,m_scaleFactor,m_scaleFactor);

		std::cout<<"number of meshes in Init: "<< scene->mNumMeshes << std::endl;

		//determine number of meshes
		m_numMeshes = scene->mNumMeshes;

		m_meshData.reserve(m_numMeshes);

		

		//now init vaos and buffers...
		
		//find out if this mesh has positions, normals, textures
		for(unsigned int mesh = 0; mesh < m_numMeshes; mesh++)
		{
			int numAttribs = 0;

			const aiMesh* thisMesh = scene->mMeshes[mesh];


			unsigned int numFaces = thisMesh->mNumFaces;

			
			
			//copy the mesh's face data

			unsigned int *indices = new unsigned int[numFaces * 3];

			for(unsigned int face = 0, vertexIndex = 0; face < numFaces; face++, vertexIndex += 3)
			{
				const struct aiFace* meshFace = &thisMesh->mFaces[face];
				memcpy(&indices[vertexIndex],meshFace->mIndices,sizeof(unsigned int) * 3);
			}

			//create a new objectdata to store the mesh data on the gfx card
			ObjectData* newObject = NULL;

			MeshComponent* newComp = new MeshComponent;
			
			//here is a slightly messy way of allocating object data....
			//generate vertex array for this mesh using objectData

			if(thisMesh->HasPositions() && thisMesh->HasNormals() && thisMesh->HasTextureCoords(0))
			{
				//create a new objectdata to store the mesh data on the gfx card
				newObject = new ObjectData(3,numFaces);

				//in a assimp file the textures are stored as 3 components, this is a waste of a whole 4 bytes on 
				//the graphics card PER TEXTURED VERTEX! so will need to copy and 'condense' these elems

				float *texCoords = new float[thisMesh->mNumVertices * 2];

				int destIndex   = 0;

				for(unsigned int vertex = 0; vertex < thisMesh->mNumVertices;vertex++)
				{
					memcpy(&texCoords[destIndex],&thisMesh->mTextureCoords[0][vertex],sizeof(float) * 2);
					destIndex   += 2;
				}

				newObject->Init(indices,thisMesh->mNumVertices,thisMesh->mVertices,3,thisMesh->mNormals,3,
								texCoords,2);

				delete [] texCoords;

			}
			else if(thisMesh->HasPositions() && thisMesh->HasNormals())
			{
				//create a new objectdata to store the mesh data on the gfx card
				newObject = new ObjectData(2,numFaces);
				newObject->Init(indices,thisMesh->mNumVertices,thisMesh->mVertices,3,thisMesh->mNormals,3);
			}
			else 
			{
				//create a new objectdata to store the mesh data on the gfx card
				newObject = new ObjectData(1,numFaces);
				newObject->Init(indices,thisMesh->mNumVertices,thisMesh->mVertices,3);
			}

			//push this info into a vector of objectdatas for rendering later
			

			delete [] indices;

			newComp->m_meshData = newObject;

			MaterialStruct* newMat = NULL;
			GLuint          newTex = 0;

			//load materials
			newMat = LoadMaterials(scene,scene->mMaterials[thisMesh->mMaterialIndex]);
			newTex = LoadTextures(directory,scene,scene->mMaterials[thisMesh->mMaterialIndex]);

			newComp->m_material = newMat;

			if(newTex != 0)
			{
				newComp->m_hasTexture = true;
				newComp->m_textureHandle = newTex;
			}

			m_meshData.push_back(newComp);
		}

		

		return true;
	}



	void StaticMesh::GetBoundingBox(glm::vec3& min,glm::vec3& max,const aiScene* scene)
	{
	  aiMatrix4x4 trafo;
      aiIdentityMatrix4(&trafo);

      min.x = min.y = min.z =  1e10f;
      max.x = max.y = max.z = -1e10f;
      GetBoundingBoxForNode(scene->mRootNode,min,max,trafo,scene);
	}

	void StaticMesh::GetBoundingBoxForNode(const aiNode* node,glm::vec3& min,glm::vec3& max,aiMatrix4x4& trafo,
				                           const aiScene* scene)
	{
		aiMatrix4x4 prev;

		prev = trafo;
		aiMultiplyMatrix4(&trafo,&node->mTransformation);

	    for (unsigned int n = 0; n < node->mNumMeshes; ++n) 
		{
            const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];
            
			for (unsigned int t = 0; t < mesh->mNumVertices; ++t) 
			{

                  struct aiVector3D tmp = mesh->mVertices[t];
                  aiTransformVecByMatrix4(&tmp,&trafo);

                  min.x = glm::min(min.x,tmp.x);
                  min.y = glm::min(min.y,tmp.y);
                  min.z = glm::min(min.z,tmp.z);

                  max.x = glm::max(max.x,tmp.x);
                  max.y = glm::max(max.y,tmp.y);
                  max.z = glm::max(max.z,tmp.z);
            }
      }

      for (unsigned int n = 0; n < node->mNumChildren; n++) 
	  {
            GetBoundingBoxForNode(node->mChildren[n],min,max,trafo,scene);
      }

      trafo = prev;
	}

	MaterialStruct* StaticMesh::LoadMaterials(const aiScene* scene,aiMaterial* material)
	{
		MaterialStruct* mat = new MaterialStruct;

		float c[4] = {0.8f, 0.8f, 0.8f, 1.0f};

        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
			memcpy(&mat->diff,&diffuse, sizeof(diffuse));
		else
			memcpy(&mat->diff,c, sizeof(c));
 
		c[0] = 0.2f;
		c[1] = 0.2f; 
		c[2] = 0.2f;
		c[3] = 1.0f;

        aiColor4D ambient;
        if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient))
            memcpy(&mat->amb, &ambient, sizeof(ambient));
		else
			memcpy(&mat->amb,c, sizeof(c));
 
		c[0] = 0.0f;
		c[1] = 0.0f; 
		c[2] = 0.0f;
		c[3] = 1.0f;
      
        aiColor4D specular;
        if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular))
             memcpy(&mat->spec, &specular, sizeof(specular));
		else
			memcpy(&mat->spec, c, sizeof(c));
 
 
        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max);
        mat->shininess = shininess;

		return mat;
	}

	GLuint StaticMesh::LoadTextures(const char* directory,const aiScene* scene,aiMaterial* material)
	{
		
		int texIndex = 0;
		aiString path;  // filename

		std::vector<char*> texNames;

		aiReturn texFound = material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path, NULL, NULL, NULL,NULL,NULL);

		while (texFound == AI_SUCCESS) 
		{
			//fill map with textures, OpenGL image ids set to 0
			char buf[50];
			sprintf(buf,"%s//%s",directory,path.data);
			texNames.push_back(buf);

			// more textures?
			texIndex++;
			texFound = material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		}


		int numTextures = texNames.size();
		//std::cout << numTextures << std::endl;

		if(numTextures != 0)
		{
			//Texture* meshTexture = new Texture;

			//meshTexture->Init(texNames[0],GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT);
			//return meshTexture;

			//load the texture using the textureManager
			return m_texMan->GetRecord(std::string(texNames[0]));

		}
		else
		{
			return NULL;
		}

			
		
	}

};
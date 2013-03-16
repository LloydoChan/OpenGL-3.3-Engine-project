//Shader.h - interface for a shader wrapper class
//Last update: 20/07/2012
#pragma once
#include "Includes.h"
#include "Resource.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using std::string;



class Shader : public Uncopyable, public Resource
{
	public:
		Shader(const unsigned int handle,const string& name,const string& path): Resource(handle,name,path),
																				m_shaderHandle(0){};
		~Shader();

		
		bool				InitShaderProgramFromFile(int numAttribs, ... );

		void				SetUniform(const char *name,float x,float y,float z);
		void				SetUniform(const char *name, const vec2 & v);
		void				SetUniform(const char *name, const vec3 & v);
		void				SetUniform(const char *name, const vec4 & v);
		void				SetUniform(const char *name, const mat4 & m);
		void				SetUniform(const char *name, const mat3 & m);
		void				SetUniform(const char *name, float val );
		void				SetUniform(const char *name, int val );
		void				SetUniform(const char *name, bool val );
		void				PrintActiveUniforms();
		void				PrintActiveAttribs();

		GLuint				GetProgramHandle()const {return m_shaderHandle;}
			

	private:
		//private funcs used by initialisation
		inline void InitAttribs(std::vector<char*>& m_attribs,GLuint program);
		inline bool LinkProgram(GLuint program);
		std::string ReadFile(const std::string& filename);
		GLuint CreateShader(GLenum eShaderType,const std::string& shaderFile,bool fromFile = true);
		GLuint CreateProgram(GLuint vertShader,GLuint fragShader,std::vector<char*>& attribs);

		GLuint m_shaderHandle;

};

void CreateShaderWithVerts(Shader** shader,const unsigned int handle,const std::string& path,const std::string& name);
void CreateShaderWithVertsNorms(Shader** shader,const unsigned int handle,const std::string& path,const std::string& name);
void CreateShaderWithVertsNormsTextures(Shader** shader,const unsigned int handle,const std::string& path,const std::string& name);

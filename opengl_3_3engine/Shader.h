//Shader.h - interface for a shader wrapper class
//Last update: 20/07/2012
#pragma once
#include "Includes.h"

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

namespace OpenGL_3_3Engine
{
	class Shader
	{
		public:
			Shader():m_handle(0){};
			~Shader();

			bool InitShaderProgramFromFile(const char* vert,const char* frag,int numAttribs, ... );
			bool InitShaderProgramFromString(const char* vert,const char* frag,int numAttribs, ... );

			void SetUniform(const char *name,float x,float y,float z);
			void SetUniform(const char *name, const vec3 & v);
			void SetUniform(const char *name, const vec4 & v);
			void SetUniform(const char *name, const mat4 & m);
			void SetUniform(const char *name, const mat3 & m);
			void SetUniform(const char *name, float val );
			void SetUniform(const char *name, int val );
			void SetUniform(const char *name, bool val );
			void PrintActiveUniforms();
			void PrintActiveAttribs();

			GLuint GetHandle()const {return m_handle;}
			

		private:
			Shader& operator=(const Shader& shader){};
			Shader(const Shader& shader){};
			inline void InitAttribs(std::vector<char*>& m_attribs,GLuint program);
			inline bool LinkProgram(GLuint program);
			std::string ReadFile(const char* filename);
			
			GLuint m_handle;
			
			GLuint CreateShader(GLenum eShaderType,const char*shaderFile,bool fromFile = true);
			GLuint CreateProgram(GLuint vertShader,GLuint fragShader,std::vector<char*>& attribs);

	};
};
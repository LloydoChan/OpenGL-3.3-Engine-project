//Shader.cpp - implementation of shader wrapper class
//Last Update: 20/07/2012
#include "Shader.h"



namespace OpenGL_3_3Engine
{

	Shader::~Shader()
	{
		glDeleteProgram(m_handle);
	}

	bool Shader::InitShaderProgramFromFile(const char* vert,const char* frag,int numAttribs, ... )
	{
		
		std::vector<char*> m_attribs;

		va_list attribList;
		va_start(attribList,numAttribs);

		for(int a = 0; a < numAttribs; a++)
		{
			char* attrib = va_arg(attribList,char*);
			m_attribs.push_back(attrib);
		}

		GLuint vertHandle = CreateShader(GL_VERTEX_SHADER,vert);

		if(vertHandle == NULL)
		{
			return false;
		}

		GLuint fragHandle = CreateShader(GL_FRAGMENT_SHADER,frag);

		if(fragHandle == NULL)
		{
			return false;
		}

		m_handle = CreateProgram(vertHandle,fragHandle,m_attribs);

		glDeleteShader(vertHandle);
		glDeleteShader(fragHandle);

		if(m_handle==NULL)
		{
			return false;
		}
		
		return true;

	}

	bool Shader::InitShaderProgramFromString(const char* vert,const char* frag,int numAttribs, ... )
	{
		
		std::vector<char*> m_attribs;

		va_list attribList;
		va_start(attribList,numAttribs);

		for(int a = 0; a < numAttribs; a++)
		{
			char* attrib = va_arg(attribList,char*);
			m_attribs.push_back(attrib);
		}

		GLuint vertHandle = CreateShader(GL_VERTEX_SHADER,vert,false);

		if(vertHandle == NULL)
		{
			return false;
		}

		GLuint fragHandle = CreateShader(GL_FRAGMENT_SHADER,frag,false);

		if(fragHandle == NULL)
		{
			return false;
		}

		m_handle = CreateProgram(vertHandle,fragHandle,m_attribs);

		glDeleteShader(vertHandle);
		glDeleteShader(fragHandle);

		if(m_handle==NULL)
		{
			return false;
		}
		
		return true;

	}

	GLuint Shader::CreateShader(GLenum eShaderType,const char* shaderFile,bool fromFile)
	{
		GLuint shader = glCreateShader(eShaderType);

		if(fromFile)
		{
			std::string strFileData = ReadFile(shaderFile);

			const char* file = strFileData.c_str();
			glShaderSource(shader,1,&file,NULL);
		}
		else
		{
			const char* file = shaderFile;
			glShaderSource(shader,1,&file,NULL);
		}


		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader,GL_COMPILE_STATUS,&status);

		if(status==GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLogLength);

			GLchar* strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader,infoLogLength,NULL,strInfoLog);

			const char* strShaderType = NULL;

			switch(eShaderType)
			{
				case GL_VERTEX_SHADER: 
					strShaderType = "vertex";
					break;
				case GL_FRAGMENT_SHADER:
					strShaderType = "fragment";
					break;

			}

			fprintf(stderr,"Compile failure in %s shader: \n %s \n",strShaderType,strInfoLog);
			delete[] strInfoLog;

			return NULL;
		}

		return shader;
	}

	GLuint Shader::CreateProgram(GLuint vertShader,GLuint fragShader,std::vector<char*>& attribs)
	{
		GLuint program = glCreateProgram();

		glAttachShader(program,vertShader);
		glAttachShader(program,fragShader);
		

		for(int iLoop = 0; iLoop < attribs.size();iLoop++)
		{
			glBindAttribLocation(program,iLoop,attribs[iLoop]);
		}


		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program,GL_LINK_STATUS,&status);

		if(status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;

			return NULL;
		}

		
		glDetachShader(program,vertShader);
		glDetachShader(program,fragShader);

		return program;
	}

	void Shader::SetUniform(const char *name,float x,float y,float z)
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniform3f(uniform,x,y,z);
	}

	void Shader::SetUniform(const char *name, const vec3 & v)
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniform3fv(uniform,1,&v[0]);
	}

	void Shader::SetUniform(const char *name, const vec4 & v)
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniform4fv(uniform,1,&v[0]);
	}

	void Shader::SetUniform(const char *name, const mat4 & m)
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniformMatrix4fv(uniform,1,GL_FALSE,&m[0][0]);
	}

	void Shader::SetUniform(const char *name, const mat3 & m)
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniformMatrix3fv(uniform,1,GL_FALSE,&m[0][0]);
	}

	void Shader::SetUniform(const char *name, float val )
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniform1f(uniform,val);
	}

	void Shader::SetUniform(const char *name, int val )
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniform1i(uniform,val);
	}

	void Shader::SetUniform(const char *name, bool val )
	{
		GLuint uniform = glGetUniformLocation(m_handle,name);
		glUniform1i(uniform,val);
	}

	void Shader::PrintActiveUniforms()
	{
		
		GLint activeUniforms,length;
		GLsizei size;
		glGetProgramiv(m_handle,GL_ACTIVE_UNIFORMS,&activeUniforms);

		for(GLuint index = 0; index < activeUniforms; index++)
		{
			char* uniformName = new char[50];
			glGetActiveUniformName(m_handle,index,50,&length,uniformName);
			printf(uniformName);
			delete [] uniformName;
		}
	}

	void Shader::PrintActiveAttribs()
	{
		GLint maxLength, nAttribs,location,written, size;
		glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTES,&nAttribs);
		glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,&maxLength);

		
		GLenum type;

		for(int index = 0; index < nAttribs; index++)
		{
			char* name;
			glGetActiveAttrib( m_handle, index, maxLength, &written,&size, &type, name );
			location = glGetAttribLocation(m_handle, name);
			printf(" %-5d | %s\n",location, name);
		}
	}


	std::string Shader::ReadFile(const char* filename)
    {
        std::ifstream fileIn(filename);

        if (!fileIn.good())
        {
			std::cerr << "Could not load shader: " << filename << std::endl;
			return std::string();
        }

        std::string stringBuffer(std::istreambuf_iterator<char>(fileIn), (std::istreambuf_iterator<char>()));
		return stringBuffer;
    }


};
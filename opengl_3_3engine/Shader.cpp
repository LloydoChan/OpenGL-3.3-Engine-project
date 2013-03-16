//Shader.cpp - implementation of shader wrapper class
//Last Update: 6/01/2012
#include "Shader.h"



Shader::~Shader(){
	glDeleteProgram(m_shaderHandle);
}

//bool Shader::InitShaderProgramFromFile(const char* vert,const char* frag,int numAttribs, ... )
//initialisation function that takes a variable number of arguments, depending on the number of attributes
//desired for the shader. It initialises from a saved shader text file with a .vp or .fp extension

bool Shader::InitShaderProgramFromFile(int numAttribs, ... ){
		
	std::vector<char*> m_attribs;
	va_list attribList;
	va_start(attribList,numAttribs);

	for(int a = 0; a < numAttribs; a++){
		char* attrib = va_arg(attribList,char*);
		m_attribs.push_back(attrib);
	}
	GLuint vertHandle = CreateShader(GL_VERTEX_SHADER,GetFileName() + ".vp");

	if(vertHandle == NULL){
		return false;
	}
	GLuint fragHandle = CreateShader(GL_FRAGMENT_SHADER,GetFileName() + ".fp");

	if(fragHandle == NULL){
		return false;
	}
	m_shaderHandle = CreateProgram(vertHandle,fragHandle,m_attribs);

	glDeleteShader(vertHandle);
	glDeleteShader(fragHandle);

	if(m_shaderHandle==NULL){
		return false;
	}
		
	return true;
}



GLuint Shader::CreateShader(GLenum eShaderType,const std::string& shaderFile,bool fromFile){
	GLuint shader = glCreateShader(eShaderType);

	if(fromFile){
		std::string strFileData = ReadFile(shaderFile);

		const char* file = strFileData.c_str();
		glShaderSource(shader,1,&file,NULL);
	}else{
		const char* file = shaderFile.c_str();
		glShaderSource(shader,1,&file,NULL);
	}


	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);

	if(status==GL_FALSE){
		GLint infoLogLength;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader,infoLogLength,NULL,strInfoLog);

		const char* strShaderType = NULL;

		switch(eShaderType){
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


GLuint Shader::CreateProgram(GLuint vertShader,GLuint fragShader,std::vector<char*>& attribs){
	GLuint program = glCreateProgram();

	glAttachShader(program,vertShader);
	glAttachShader(program,fragShader);
		

	for(unsigned int iLoop = 0; iLoop < attribs.size();iLoop++){
		glBindAttribLocation(program,iLoop,attribs[iLoop]);
	}


	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program,GL_LINK_STATUS,&status);

	if(status == GL_FALSE){
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

void Shader::SetUniform(const char *name,float x,float y,float z){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniform3f(uniform,x,y,z);
}

void Shader::SetUniform(const char *name, const vec2 & v){
  GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
  glUniform2fv(uniform,1,&v[0]);
}

void Shader::SetUniform(const char *name, const vec3 & v){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniform3fv(uniform,1,&v[0]);
}

void Shader::SetUniform(const char *name, const vec4 & v){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniform4fv(uniform,1,&v[0]);
}

void Shader::SetUniform(const char *name, const mat4 & m){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniformMatrix4fv(uniform,1,GL_FALSE,&m[0][0]);
}

void Shader::SetUniform(const char *name, const mat3 & m){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniformMatrix3fv(uniform,1,GL_FALSE,&m[0][0]);
}

void Shader::SetUniform(const char *name, float val ){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniform1f(uniform,val);
}

void Shader::SetUniform(const char *name, int val ){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniform1i(uniform,val);
}

void Shader::SetUniform(const char *name, bool val ){
	GLuint uniform = glGetUniformLocation(m_shaderHandle,name);
	glUniform1i(uniform,val);
}


void Shader::PrintActiveUniforms(){
		
	GLint activeUniforms,length;
	glGetProgramiv(m_shaderHandle,GL_ACTIVE_UNIFORMS,&activeUniforms);

	for(int index = 0; index < activeUniforms; index++){
		char* uniformName = new char[50];
		glGetActiveUniformName(m_shaderHandle,index,50,&length,uniformName);
		printf(uniformName);
		delete [] uniformName;
	}
}


void Shader::PrintActiveAttribs(){
	GLint maxLength, nAttribs,location,written, size;
	glGetProgramiv(m_shaderHandle, GL_ACTIVE_ATTRIBUTES,&nAttribs);
	glGetProgramiv(m_shaderHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,&maxLength);

	GLenum type;

	for(int index = 0; index < nAttribs; index++){
		char* name = new char[50];
		glGetActiveAttrib( m_shaderHandle, index, maxLength, &written,&size, &type, name );
		location = glGetAttribLocation(m_shaderHandle, name);
		printf(" %-5d | %s\n",location, name);
		delete [] name;
	}
}


std::string Shader::ReadFile(const std::string& filename){
    std::ifstream fileIn(filename);

    if (!fileIn.good()){
		std::cerr << "Could not load shader: " << filename << std::endl;
		return std::string();
    }

    std::string stringBuffer(std::istreambuf_iterator<char>(fileIn), (std::istreambuf_iterator<char>()));
	return stringBuffer;
}

void CreateShaderWithVerts(Shader** shader,const unsigned int handle,const std::string& path,const std::string& name){
	*shader = new Shader(handle,path,name); 
	(*shader)->InitShaderProgramFromFile(1,"inCoords");
}

void CreateShaderWithVertsNorms(Shader** shader,const unsigned int handle,const std::string& path,const std::string& name){
	*shader = new Shader(handle,path,name); 
	(*shader)->InitShaderProgramFromFile(2,"inCoords","inNormals");
}

void CreateShaderWithVertsNormsTextures(Shader** shader,const unsigned int handle,const std::string& path,const std::string& name){
	*shader = new Shader(handle,path,name); 
	(*shader)->InitShaderProgramFromFile(3,"inCoords","inNormals","inTexCoords");
}



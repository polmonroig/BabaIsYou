#ifndef SHADER_MANAGER_H 
#define SHADER_MANAGER_H 


#include <vector>
#include <string>
#include <iostream>

#include "Shader.h"
#include "ShaderProgram.h"


class ShaderManager {

public:

	static int TILE_PROGRAM;
	static int BACKGROUND_PROGRAM;

	void init();
	
	void use(int id);

	GLint bindVertexAttribute(string const& attribName, GLint size, GLsizei stride, GLvoid* firstPointer);
	void setUniform(std::string const& uniformName, float v0, float v1);
	void setUniform(std::string const& uniformName, float v0, float v1, float v2);
	void setUniform(std::string const& uniformName, float v0, float v1, float v2, float v3);
	void setUniform(std::string const& uniformName, glm::mat4& mat);
	

private:

	

	void checkShaderErrors(Shader const& shader);
	int addProgram(std::string const& vertex_file_name, std::string const& fragment_file_name);

	void linkProgram();
	int currentProgram;
	std::vector<ShaderProgram> programs;


};


#endif 
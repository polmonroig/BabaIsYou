#ifndef SHADER_MANAGER_H 
#define SHADER_MANAGER_H 


#include <vector>
#include <string>
#include <iostream>

#include "Shader.h"
#include "ShaderProgram.h"


class ShaderManager {

public:


	int addProgram(std::string const& vertex_file_name, std::string const& fragment_file_name);
	ShaderProgram& getProgram(int id);
	ShaderProgram& getProgram();
	void use(int id);
	void use();

	GLint bindVertexAttribute(int id, string const& attribName, GLint size, GLsizei stride, GLvoid* firstPointer);
	void setUniform(int id, std::string const& uniformName, float v0, float v1);
	void setUniform(int id, std::string const& uniformName, float v0, float v1, float v2);
	void setUniform(int id, std::string const& uniformName, float v0, float v1, float v2, float v3);
	void setUniform(int id, std::string const& uniformName, glm::mat4& mat);
	void checkShaderErrors(Shader const& shader);

private:

	void linkProgram();

	std::vector<ShaderProgram> programs;


};


#endif 
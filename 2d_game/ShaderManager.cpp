#include "ShaderManager.h"


int ShaderManager::addProgram(std::string const& vertex_file_name, std::string const& fragment_file_name) {

	Shader vShader, fShader;
	ShaderProgram program;

	vShader.initFromFile(VERTEX_SHADER, vertex_file_name);
	checkShaderErrors(vShader);
	fShader.initFromFile(FRAGMENT_SHADER, fragment_file_name);
	checkShaderErrors(fShader);

	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	programs.push_back(program);
	linkProgram();

	vShader.free();
	fShader.free();

	return programs.size() - 1;
}

ShaderProgram& ShaderManager::getProgram(int id) {
	return programs[id];
}

ShaderProgram& ShaderManager::getProgram() {
	return programs[programs.size() - 1];
}

void ShaderManager::use(int id) {
	programs[id].use();
}


void ShaderManager::use() {
	programs[programs.size() - 1].use();
}

void ShaderManager::linkProgram() {
	int id = programs.size() - 1;
	programs[id].link();

	if (!programs[id].isLinked()){
		std::cerr << "Shader Linking Error" << std::endl;
		std::cerr << "" << programs[id].log() << std::endl << std::endl;
	}

}

GLint ShaderManager::bindVertexAttribute(int id, string const& attribName, GLint size, GLsizei stride, GLvoid* firstPointer) {
	return programs[id].bindVertexAttribute(attribName, size, stride, firstPointer);
}


void ShaderManager::setUniform(int id, std::string const& uniformName, float v0, float v1) {
	programs[id].setUniform2f(uniformName, v0, v1);
}

void ShaderManager::setUniform(int id, std::string const& uniformName, float v0, float v1, float v2) {
	programs[id].setUniform3f(uniformName, v0, v1, v2);
}

void ShaderManager::setUniform(int id, std::string const& uniformName, float v0, float v1, float v2, float v3) {
	programs[id].setUniform4f(uniformName, v0, v1, v2, v3);
}

void ShaderManager::setUniform(int id, std::string const& uniformName, glm::mat4& mat) {
	programs[id].setUniformMatrix4f(uniformName, mat);
}




void ShaderManager::checkShaderErrors(Shader const& shader) {
	if (!shader.isCompiled()){
		std::cerr << "Shader Error" << std::endl;
		std::cerr << "" << shader.log() << std::endl << std::endl;
	}
}
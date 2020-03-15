#include "Text.h"


bool Text::bLibInit = false;
FT_Library Text::library;

void Text::initLibrary() {
	/*if (!bLibInit) {
		if (FT_Init_FreeType(&library))
			std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		else bLibInit = true;
	}*/
}


void Text::initFont(std::string const& fileName) {
	/*if (FT_New_Face(library, fileName.c_str(), 0, &face)) {
		std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	else {
		FT_Set_Pixel_Sizes(face, ATLAS_FONT_SIZE, ATLAS_FONT_SIZE);
	}*/
	
}

void Text::init(std::string const& fileName) {
	initLibrary();
	initFont(fileName);
	
}

void Text::render(std::string const& str, const glm::vec2& pixel, int size, const glm::vec4& color){
	int vp[4];
	glm::mat4 projection, modelview;
	glm::vec2 minTexCoord, maxTexCoord, pos = pixel;
	auto shaderProgram = ServiceLocator::getShaderManager();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glGetIntegerv(GL_VIEWPORT, vp);;
	projection = glm::ortho(0.f, float(vp[2] - 1), float(vp[3] - 1), 0.f);
	shaderProgram->setUniform("projection", projection);
	shaderProgram->setUniform("color", color.r, color.g, color.b, color.a);

	for (unsigned int i = 0; i < str.length(); i++)
	{
		modelview = glm::mat4(1.0f);

		//	modelview = glm::translate(modelview, glm::vec3(pos.x + (float(size) / fontSize) * chars[str[i] - 32].bl, pos.y - (float(size) / fontSize) * chars[str[i] - 32].bt, 0.f));
			//modelview = glm::scale(modelview, (float(size) / fontSize) * glm::vec3(chars[str[i] - 32].sx, chars[str[i] - 32].sy, 0.f));
		shaderProgram->setUniform("modelview", modelview);
		//	minTexCoord = glm::vec2(float(chars[str[i] - 32].tx) / textureSize, float(chars[str[i] - 32].ty) / textureSize);
			//maxTexCoord = glm::vec2(float(chars[str[i] - 32].tx + chars[str[i] - 32].sx) / textureSize, float(chars[str[i] - 32].ty + chars[str[i] - 32].sy) / textureSize);
		shaderProgram->setUniform("minTexCoord", minTexCoord.s, minTexCoord.t);
		shaderProgram->setUniform("maxTexCoord", maxTexCoord.s, maxTexCoord.t);
		//quad->render(textureAtlas);
	//	pos.x += (float(size) / fontSize) * chars[str[i] - 32].ax;
	}
}
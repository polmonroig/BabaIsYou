#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H 



class Text{

public:

private:

	int fontSize, textureSize, maxCharWidth, maxCharHeight;
	FT_Face face;

	static bool bLibInit;
	static FT_Library library;
	
};


#endif 

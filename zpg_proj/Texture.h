#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <GL/glew.h>
#include <stdio.h>
#include "stb_image.h"
class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);
	bool LoadTexture(const char* fileName);
	bool LoadTextureA();
	void UseTexture();
	void ClearTexture();
	~Texture();

private:
	GLuint textureID;
	int height, width, bitDepth;

};
#endif
#include"Texture.h"
#include <SFML/Graphics.hpp>

Texture::Texture(const char* path) :_id(0)
{
	init(path);
}
Texture::~Texture() 
{
	glDeleteTextures(1, &_id);
}

void Texture::bind() 
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::init(const char* path) 
{
	sf::Image i;
	if (!i.loadFromFile(path)) {
		char s[256];
		sprintf_s(s, "Unable to load BasicTexture: %s", path);
		throw std::runtime_error(s);
	}
	glGenTextures(1, &_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr());

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
}
#include"SkyTexture.h"
#include <SFML/Graphics.hpp>

SkyTexture::SkyTexture() :_id(0)
{
}

SkyTexture::~SkyTexture()
{
	glDeleteTextures(1, &_id);
}

void SkyTexture::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}

void SkyTexture::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyTexture::init(std::vector<const char*> path)
{
	glGenTextures(1, &_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

	for (int i = 0; i < 6; i++) {
		auto& str = path[i];
		sf::Image image;
		if (!image.loadFromFile(str)) {
			throw std::runtime_error("Unable to load CubeTexture Part");
		}

		auto param = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		auto width = image.getSize().x;
		auto height = image.getSize().y;

		glTexImage2D(param, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, image.getPixelsPtr());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
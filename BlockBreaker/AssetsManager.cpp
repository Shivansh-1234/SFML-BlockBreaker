#include "AssetsManager.h"
#include <SFML/Graphics.hpp>

void AssetsManager::LoadTexture(std::string name, std::string filename)
{
	sf::Texture texture;

	if (texture.loadFromFile(filename))
	{
		this->_textures[name] = texture;
	}
}

sf::Texture& AssetsManager::GetTexture(std::string name)
{
	return this->_textures.at(name);
}

void AssetsManager::LoadFont(std::string name, std::string filename)
{
	sf::Font font;

	if (font.loadFromFile(filename))
	{
		this->_fonts[name] = font;
	}

}

sf::Font& AssetsManager::GetFont(std::string name)
{
	return this->_fonts.at(name);
}

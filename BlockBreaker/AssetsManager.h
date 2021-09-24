#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class AssetsManager
{
private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
public:
	AssetsManager() {}
	~AssetsManager() {}

	void LoadTexture(std::string name , std::string filename);
	sf::Texture& GetTexture(std::string name);

	void LoadFont(std::string name , std::string filename);
	sf::Font& GetFont(std::string name);
};


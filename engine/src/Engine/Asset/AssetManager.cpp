#include "AssetManager.hpp"

namespace Engine { namespace Asset {

	void AssetManager::LoadTexture(const std::string t_name, const std::string t_filename)
	{
		sf::Texture tex;
		
		if (tex.loadFromFile(t_filename))
			m_textures[t_name] = tex;
	}

	void AssetManager::LoadFont(const std::string t_name, const std::string t_filename)
	{
		sf::Font font;
		
		if (font.loadFromFile(t_filename))
			m_fonts[t_name] = font;
	}

} }
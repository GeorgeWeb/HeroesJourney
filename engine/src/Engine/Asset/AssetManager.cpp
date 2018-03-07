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

	void AssetManager::LoadSound(const std::string t_name, const std::string t_filename)
	{
		sf::SoundBuffer buffer;
		sf::Sound sound;

		if (buffer.loadFromFile(t_filename))
		{
			sound.setBuffer(buffer);
			m_sounds[t_name] = sound;
		}
	}

	void AssetManager::LoadMusic(const std::string t_name, const std::string t_filename)
	{
		auto musicPtr = std::make_unique<sf::Music>();

		if (musicPtr->openFromFile(t_filename))
			m_themes[t_name] = std::move(musicPtr);
	}

} }
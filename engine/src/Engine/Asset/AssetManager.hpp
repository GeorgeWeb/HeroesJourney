#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <memory>

namespace Engine { namespace Asset {

	class AssetManager final
	{
		public:
			AssetManager() = default;
			~AssetManager() = default;

			void LoadTexture(const std::string t_name, const std::string t_filename);
			inline sf::Texture& GetTexture(const std::string t_name) { return m_textures[t_name]; }

			void LoadFont(const std::string t_name, const std::string t_filename);
			inline sf::Font& GetFont(const std::string t_name) { return m_fonts[t_name]; }

			void LoadSound(const std::string t_name, const std::string t_filename);
			inline sf::Sound& GetSound(const std::string t_name) { return m_sounds[t_name]; }

			void LoadMusic(const std::string t_name, const std::string t_filename);
			inline sf::Music& GetMusic(const std::string t_name) { return *m_themes[t_name]; }

		private:
			std::map<std::string, sf::Texture> m_textures;
			std::map<std::string, sf::Font> m_fonts;
			std::map<std::string, sf::Sound> m_sounds;
			std::map<std::string, std::unique_ptr<sf::Music>> m_themes;
	};

} }

#endif // !ASSET_MANAGER_H
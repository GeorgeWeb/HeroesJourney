#ifndef FILE_IO_H
#define FILE_IO_H

#include <iostream>
#include <fstream>
#include <vector>

namespace Engine { namespace Utils {

	enum class DATA_TYPE : int
	{
		GAME_SETTINGS = 0,
		GAME_DATA = 1
	};

	class FileIO final
	{
		private:
			std::string m_gameDataPath = "save_data/game_data.txt";
			std::string m_gameSettingsPath = "save_data/game_settings.txt";
		
		public:
			FileIO() = default;

			bool IsEmpty(DATA_TYPE t_fileType)
			{
				if (t_fileType == DATA_TYPE::GAME_DATA)
				{
					std::ifstream file(m_gameDataPath, std::ios::in);
					return file.peek() == std::ifstream::traits_type::eof();
				}
				else if (t_fileType == DATA_TYPE::GAME_SETTINGS)
				{
					std::ifstream file(m_gameSettingsPath, std::ios::in);
					return file.peek() == std::ifstream::traits_type::eof();
				}
			}

			template <class T>
			void Load(std::vector<T*> t_data, DATA_TYPE t_type)
			{
				try
				{
					std::ifstream file;
					if (t_type == DATA_TYPE::GAME_DATA)
						file.open(m_gameDataPath, std::ios::in);
					else if (t_type == DATA_TYPE::GAME_SETTINGS)
						file.open(m_gameSettingsPath, std::ios::in);

					if (file.good())
					{
						std::cout << "Opening load file...\n";
						// READ DATA FROM FILE AND INPUT IT IN THE GAME DATA VECTOR
						for (auto d : t_data)
						{
							file >> *d;
						}

						std::cout << "Data was saved. Closing save file...\n";
					}
				}
				catch (std::exception ex)
				{
					std::cout << "\n\tFile Error! Unable to SAVE data.\n";
				}
			}

			template <class T>
			void Save(std::vector<T> t_data, DATA_TYPE t_type)
			{
				std::cout << "Opening save file...\n";
				try
				{
					std::ofstream file;
					if (t_type == DATA_TYPE::GAME_DATA)
						file.open(m_gameDataPath, std::ios::out);
					else if (t_type == DATA_TYPE::GAME_SETTINGS)
						file.open(m_gameSettingsPath, std::ios::out);

					std::cout << "Saving...\n";

					// WRITE GAME DATA TO FILE
					for (auto d : t_data)
					{
						file << d << "\n";
					}
					std::cout << "Data was saved. Closing save file...\n";
					file.close();
				}
				catch (std::exception ex)
				{
					std::cout << "\n\tFile Error! Unable to LOAD data.\n";
				}
			}
	};

} }

#endif // !FILE_IO_H
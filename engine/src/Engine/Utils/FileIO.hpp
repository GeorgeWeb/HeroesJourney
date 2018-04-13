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
			// game progress data file
			std::string m_gameDataPath = "save_data/game_data.txt";
			// game settings data file
			std::string m_settingsPath = "save_data/game_settings.txt";
		
		public:
			FileIO() = default;

			template <class T>
			void Load(std::vector<T*> t_data, DATA_TYPE t_type)
			{
				try
				{
					std::ifstream file;
					if (t_type == DATA_TYPE::GAME_DATA)
						file.open(m_gameDataPath);
					else if (t_type == DATA_TYPE::GAME_SETTINGS)
						file.open(m_settingsPath);

					if (file.good())
					{
						// READ DATA FROM FILE AND INPUT IT IN THE GAME DATA VECTOR
						for (auto d : t_data)
						{
							file >> *d;
						}
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
				try
				{
					std::ofstream file;
					if (t_type == DATA_TYPE::GAME_DATA)
						file.open(m_gameDataPath, std::ios::trunc);
					else if (t_type == DATA_TYPE::GAME_SETTINGS)
						file.open(m_settingsPath, std::ios::trunc);

					// WRITE GAME DATA TO FILE
					for (auto d : t_data)
					{
						file << d << "\n";
					}
					file.close();
				}
				catch (std::exception ex)
				{
					std::cout << "\n\tFile Error! Unable to LOAD data.\n";
				}
			}

			bool IsEmpty(DATA_TYPE t_fileType)
			{
				if (t_fileType == DATA_TYPE::GAME_DATA)
				{
					std::ifstream file(m_gameDataPath);
					return file.peek() == std::ifstream::traits_type::eof();
				}
				else if (t_fileType == DATA_TYPE::GAME_SETTINGS)
				{
					std::ifstream file(m_settingsPath);
					return file.peek() == std::ifstream::traits_type::eof();
				}
			}
	};

} }

#endif // !FILE_IO_H
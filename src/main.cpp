#include "Game.hpp"
#include <Windows.h>
#include <iostream>

std::shared_ptr<HJ::Game> LinkStart(const std::string&);

auto main(void) -> int
{
	/*
	#ifdef NDEBUG
	// Hide console
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
	#endif
	*/
	auto HeroesJourney = LinkStart("Heroes Journey");
    // Happy game playing! :)
	return EXIT_SUCCESS;
}

std::shared_ptr<HJ::Game> LinkStart(const std::string& t_title)
{
	auto game = std::make_shared<HJ::Game>(1366, 768, t_title, Engine::System::SCREEN_MODE::WINDOWED);
	return std::move(game);
}
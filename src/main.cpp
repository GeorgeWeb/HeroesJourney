#include "Game.hpp"

#include <iostream>

std::shared_ptr<HJ::Game> LinkStart(const std::string&);

auto main(void) -> int
{
	auto HeroesJourney = LinkStart("Heroes Journey");
    // Happy game playing! :)
	return EXIT_SUCCESS;
}

std::shared_ptr<HJ::Game> LinkStart(const std::string& t_title)
{
	auto game = std::make_shared<HJ::Game>(SCREEN_WIDTH, SCREEN_HEIGHT, t_title);
	return std::move(game);
}
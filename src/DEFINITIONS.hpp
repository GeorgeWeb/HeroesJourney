#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// HD Dimensions by default
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

// Initial/Splash state global definitions
#define SPLASH_STATE_SHOW_TIME 1.0
#define SPLASH_SCENE_BACKGROUND "res/img/splash-bg.png"

// MainMenu state global definitions
#define MAINMENU_SCENE_BACKGROUND "res/img/main-menu-bg.png"
// menu title
#define MAINMENU_TITLE_FONT "res/font/lady_radical.ttf"
// menu buttons
#define MAINMENU_STARTGAME_BUTTON "res/img/main_menu/start_btn.png"
#define MAINMENU_QUITGAME_BUTTON "res/img/main_menu/quit_btn.png"

// Main Game state global definitions
#define MAIN_GAME_SCENE_BACKGROUND "res/img/main-game-map-bg.jpg"

// Global gameplay defs
#define STATE_PLAYING 98
#define	STATE_PAUSED 97
#define STATE_WON_ENCOUNTER 96
#define STATE_LOST_ENCOUNTER 95
#define STATE_DRAW 94

#endif // !DEFINITIONS_H

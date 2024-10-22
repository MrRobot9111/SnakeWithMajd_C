#pragma once
#include "GameStatesEnum.h"
class GameStatesManager
{
public:
	GameStatesEnum currentGameState = GameStatesEnum::MainMenu;
public:
	void SetState(GameStatesEnum gameState);
};


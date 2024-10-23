#include "GameStatesEnum.h"
#include "GameStatesManager.h"

void GameStatesManager::SetState(GameStatesEnum gameState) 
{
	currentGameState = gameState;
}
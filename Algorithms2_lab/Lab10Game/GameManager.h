#pragma once
#define MAX_LEVEL_LENGTH 100
#include <stdio.h>
#include <Windows.h>


#define GameDebug 1

#define PLAYABLE_LEVELS_COUNT 0
#define DEBUGGING_LEVELS_COUNT 2

const char* mlevelPaths[];
HBRUSH brushesForObjects[];

enum EPlayerMovementDirection
{
	Up, Down, Left, Right
};

enum ELevelObjects
{
	Empty = 1, Player, Wall, Explosive, LevelEnd
};

enum EGameConditions
{
	NotStarted, InProcess, LostDueExplosion, WonCurrentLevel, WonAllLevels
};

enum EMovementResult
{
	NotMovedDueWall, MovedOnEmptyCell, MovedOnBomb, MovedOnLevelEnd
};

typedef struct Position
{
	int row, column;
} Position;

class CGameManager
{
public:
	void LoadLevel(int levelNumber, const char* levelFilePath);
	
	// Changes player position on map
	int MovePlayer(int movementDirection);
	
	// Checks if player can move in given movementDirection(checks for obsticales and so on)
	bool ValidateMovement(int movementDirection) const;

	int** GetLevelMatrixPointer();

	int GetRowsCount() const;
	int GetColumnsCount() const;
	
	void ChangeGameState(int newState);

	void NextLevel();

	void ReloadCurrentLevel();

private:
	int GetLevelObjectAtPosition(const Position& pos) const;
	Position CalculatePossiblePositionAfterMovement(int movementDirection) const;

	

private:

	// Data about current level
	int m_CurrentLevelNumber = 1;
	int m_CurrentLevelMapRows;
	int m_CurrentLevelMapColumns;
	int** m_CurrentLevelMapMatrix;
	
	// Player start position on current level
	Position m_LevelPlayerStartPosition;
	
	// Current player position
	Position m_CurrentPlayerPosition;

	// Levels Count
#if GameDebug 1
	int m_LevelsCount = PLAYABLE_LEVELS_COUNT + DEBUGGING_LEVELS_COUNT;
#else
	int m_LevelsCount = PLAYABLE_LEVELS_COUNT;
#endif
	
	// Game conditions: 
	// 0 - Game aint started yet
	// 1 - Nothing (neither won or lost)
	// 2 - Player Lost because of stepping on the bomb
	// 3 - Player won current level
	// 4 - Player won all levels
	int m_CurrentGameState = 0;

};


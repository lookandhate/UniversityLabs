#pragma once
#define MAX_LEVEL_LENGTH 100
#include <stdio.h>
#include <Windows.h>


#ifdef _DEBUG
#define GAME_DEBUG 1
#define INCLUDE_DEBUG_LEVELS 0
#endif

#ifdef _GAMEPLAY_DEBUG
#define GAME_DEBUG 1
#define INCLUDE_DEBUG_LEVELS 1
#endif

#define PLAYABLE_LEVELS_COUNT 2
#define DEBUGGING_LEVELS_COUNT 5

const char* pathsToLevelTextFiles[];
HBRUSH brushesForObjects[];

enum EPlayerMovementDirection
{
	Up, Down, Left, Right
};

enum ELevelObjects
{
	Empty = 1, Player, Wall, Explosive, LevelEnd, ExplosiveSpawner
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
	const char* GetLevelFilePath();

private:
	int GetLevelObjectAtPosition(const Position& pos) const;
	Position CalculatePossiblePositionAfterMovement(int movementDirection) const;
	void SpawnBomb(const Position& pos);
	

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

	// Path to level txt file
	const char* m_levelTextFilePath;

	// Levels Count
#if INCLUDE_DEBUG_LEVELS 1
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


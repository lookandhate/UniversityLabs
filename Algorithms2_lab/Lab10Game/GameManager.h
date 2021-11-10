#pragma once
#define MAX_LEVEL_LENGTH 100
#include <stdio.h>

enum PlayerMovementDirection
{
	Up, Down, Left, Right
};

enum LevelObjects
{
	Empty, Player, Wall, Explosive, LevelEnd
};

typedef struct Position
{
	int row, column;
} Position;

class GameManager
{
public:
	void LoadLevel(int levelNumber, char* levelFilePath);
	
	// Changes player position on map
	void MovePlayer(int direction);
	
	// Checks if player can move in given direction(checks for obsticales and so on)
	bool ValidateMovement(int direction) const;

private:
	int GetLevelObjectAtPosition(const Position& pos) const;

private:

	// Data about current level
	int m_CurrentLevelNumber = 1;
	int m_CurrentLevelMapRows;
	int m_CurrentLevelMapColumns;
	int m_CurrentLevelMapMatrix[MAX_LEVEL_LENGTH][MAX_LEVEL_LENGTH];
	
	// Player start position on current level
	Position m_LevelPlayerStartPosition;
	
	// Current player position
	Position m_CurrentPlayerPosition;

	// Levels Count
	int m_LevelsCount = 1;

	
	// Game conditions: 
	// 0 - Game aint started yet
	// 1 - Nothing (neither won or lost)
	// 2 - Player Lost because of stepping on the bomb
	// 3 - Player won current level
	// 4 - Player won all levels
	int m_CurrentGameCondition = 0;






};


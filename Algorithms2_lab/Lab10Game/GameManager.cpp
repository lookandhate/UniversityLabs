#include "GameManager.h"
#include <Windows.h>


const char* mlevelPaths[] = {

#if GameDebug 1
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevel.txt",
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevelEmpty.txt"
#endif
};

//  Brushes for coloring each of gameObject
HBRUSH brushesForObjects[] = {
	CreateSolidBrush(RGB(255,255,255)), // Empty - White
	CreateSolidBrush(RGB(0,255,0)), // Player - Green
	CreateSolidBrush(RGB(58,58,58)), // Wall - Gray
	CreateSolidBrush(RGB(255,0,0)), // Explosive - Red
	CreateSolidBrush(RGB(255,255,0)), // LevelEnd - Yellow
};

void GameManager::LoadLevel(int levelNumber, const char* levelFilePath)
{
	// LEVEL FILE FORMAT
	// ROWS, COLUMNS - 2 VARIABLES
	// PLAYER START POSITION ON CURRENT MAP - 2 VARIABLES (ROW, COLUMN)
	// ROWS * COLUMNS DIGITS REPRESENTING EACH OBJECT ON MAP


	FILE* levelFilePtr;
	int openningError = fopen_s(&levelFilePtr, levelFilePath, "rt");
	if (openningError)
	{
		exit(0);
		// TODO: handle file openning error
	}
	// Read rows and columns count on current level
	fscanf_s(levelFilePtr, "%d%d", &m_CurrentLevelMapRows, &m_CurrentLevelMapColumns);
	
	// Read player start position
	fscanf_s(levelFilePtr, "%d%d", &m_LevelPlayerStartPosition.row, &m_LevelPlayerStartPosition.column);

	// Allocating memory for level matrix

	// Here allocation memory for pointers to array of pointers
	m_CurrentLevelMapMatrix = (int**)malloc(m_CurrentLevelMapRows * sizeof(int*));

	for (int row = 0; row < m_CurrentLevelMapRows; row++)
	{
		// Allocation memory for column
		m_CurrentLevelMapMatrix[row] = (int*)malloc(m_CurrentLevelMapColumns * sizeof(int));
		for (int column = 0; column < m_CurrentLevelMapColumns; column++)
		{
			fscanf_s(levelFilePtr, "%d", &m_CurrentLevelMapMatrix[row][column]);
		}
	}
	m_CurrentPlayerPosition = m_LevelPlayerStartPosition;

	// Close file after loading level information
	fclose(levelFilePtr);

}

// Getters for internal fields
int GameManager::GetRowsCount() const
{
	return m_CurrentLevelMapRows;
}

int GameManager::GetColumnsCount() const
{
	return m_CurrentLevelMapColumns;
}

int GameManager::GetLevelObjectAtPosition(const Position& pos) const
{
	if (pos.row == 0 || pos.column == 0)
		return LevelObjects::Wall;
	return m_CurrentLevelMapMatrix[pos.row - 1][pos.column - 1];
}

int** GameManager::GetLevelMatrixPointer()
{
	return m_CurrentLevelMapMatrix;
}

// Movement functionallity
void GameManager::MovePlayer(int movementDirection)
{
	if (!ValidateMovement(movementDirection))
		return;

	// Getting new player position
	Position newPosition = CalculatePossiblePositionAfterMovement(movementDirection);
	m_CurrentLevelMapMatrix[newPosition.row - 1][newPosition.column - 1] = LevelObjects::Player;
	m_CurrentLevelMapMatrix[m_CurrentPlayerPosition.row - 1][m_CurrentPlayerPosition.column - 1] = LevelObjects::Empty;
	m_CurrentPlayerPosition = newPosition;

}

bool GameManager::ValidateMovement(int direction) const
{
	// First of all we cant move outside of level boundaries even if there no any wall.
	// For example, we cant move up, if current player row 0 or maximum row
	if (
		(m_CurrentPlayerPosition.row == 0 && direction == PlayerMovementDirection::Up)
		|| (m_CurrentPlayerPosition.row == m_CurrentLevelMapRows && direction == PlayerMovementDirection::Down)
		)
		return false;

	// In the same way handle side-movements
	if (
		(m_CurrentPlayerPosition.column == 0 && direction == PlayerMovementDirection::Left)
		|| (m_CurrentPlayerPosition.column == m_CurrentLevelMapRows && direction == PlayerMovementDirection::Right)
		)
		return false;

	// Now, we have to check if we moving at wall. If so - return false
	if (GetLevelObjectAtPosition(CalculatePossiblePositionAfterMovement(direction)) == LevelObjects::Wall)
	{
		return false;
	}

	// All checks are passed
	return true;
}

Position GameManager::CalculatePossiblePositionAfterMovement(int movementDirection) const
{
	Position possibleNewPosition = m_CurrentPlayerPosition;
	switch (movementDirection)
	{
	case PlayerMovementDirection::Down:
		possibleNewPosition.row += 1;
		break;
	case PlayerMovementDirection::Up:
		possibleNewPosition.row -= 1;
		break;
	case PlayerMovementDirection::Right:
		possibleNewPosition.column += 1;
		break;
	case PlayerMovementDirection::Left:
		possibleNewPosition.column -= 1;
		break;

	}
	return possibleNewPosition;
}

// GameCycle methods
void GameManager::NextLevel()
{
	m_CurrentLevelNumber = (m_CurrentLevelNumber) % m_LevelsCount;
	LoadLevel(m_CurrentLevelNumber, mlevelPaths[m_CurrentLevelNumber]);
}

void GameManager::ReloadCurrentLevel()
{
	LoadLevel(m_CurrentLevelNumber, mlevelPaths[m_CurrentLevelNumber]);
}

void GameManager::ChangeGameState(int newState)
{
	m_CurrentGameState = newState;
}


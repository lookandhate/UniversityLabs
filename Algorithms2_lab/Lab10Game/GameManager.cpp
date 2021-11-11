#include "GameManager.h"
#include <Windows.h>


const char* pathsToLevelTextFiles[] = {

#if INCLUDE_DEBUG_LEVELS 1
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevel.txt",
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevelEmpty.txt",
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevelBomb.txt",
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevelBombNextLevel.txt",
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\debugLevelBombSpawners.txt",
#endif
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\playableLevel1.txt",
	"C:\\Users\\root\\Desktop\\labs\\testTextFiles\\Lab10\\playableLevel2.txt"
};

//  Brushes for coloring each of gameObject
HBRUSH brushesForObjects[] = {
	CreateSolidBrush(RGB(255,255,255)), // Empty - White
	CreateSolidBrush(RGB(0,255,0)), // Player - Green
	CreateSolidBrush(RGB(58,58,58)), // Wall - Gray
	CreateSolidBrush(RGB(255,0,0)), // Explosive - Red
	CreateSolidBrush(RGB(255,255,0)), // LevelEnd - Yellow
	CreateSolidBrush(RGB(0,255,255)) // Bomb Spawner - Cyan
};

void CGameManager::LoadLevel(int levelNumber, const char* levelFilePath)
{
	// LEVEL FILE FORMAT
	// ROWS, COLUMNS - 2 VARIABLES
	// PLAYER START POSITION ON CURRENT MAP - 2 VARIABLES (ROW, COLUMN)
	// ROWS * COLUMNS DIGITS REPRESENTING EACH OBJECT ON MAP


	FILE* levelFilePtr;
	int openningError = fopen_s(&levelFilePtr, levelFilePath, "rt");
	if (openningError)
	{
		exit(0x1337);
		// TODO: handle file openning error
	}
	m_levelTextFilePath = levelFilePath;
	// Read rows and columns count on current level
	fscanf_s(levelFilePtr, "%d%d", &m_CurrentLevelMapRows, &m_CurrentLevelMapColumns);
	
	// Read player start position
	fscanf_s(levelFilePtr, "%d%d", &m_LevelPlayerStartPosition.row, &m_LevelPlayerStartPosition.column);

	// Before allocation: check if memory was already allocated and free it
	if (m_CurrentLevelMapMatrix)
	{
		for (int row = 0; row < m_CurrentLevelMapRows; row++)
		{
			if (m_CurrentLevelMapMatrix[row])
				free(m_CurrentLevelMapMatrix[row]);
		}
		free(m_CurrentLevelMapMatrix);

	}

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
int CGameManager::GetRowsCount() const
{
	return m_CurrentLevelMapRows;
}

int CGameManager::GetColumnsCount() const
{
	return m_CurrentLevelMapColumns;
}

int CGameManager::GetLevelObjectAtPosition(const Position& pos) const
{
	if (pos.row == 0 || pos.column == 0)
		return ELevelObjects::Wall;
	return m_CurrentLevelMapMatrix[pos.row - 1][pos.column - 1];
}

int** CGameManager::GetLevelMatrixPointer()
{
	return m_CurrentLevelMapMatrix;
}

// Movement functionallity
int CGameManager::MovePlayer(int movementDirection)
{
	if (!ValidateMovement(movementDirection))
		return EMovementResult::NotMovedDueWall;


	// Getting new player position
	Position newPosition = CalculatePossiblePositionAfterMovement(movementDirection);
	int objectOnNewPosition = GetLevelObjectAtPosition(newPosition);
	m_CurrentLevelMapMatrix[newPosition.row - 1][newPosition.column - 1] = ELevelObjects::Player;
	m_CurrentLevelMapMatrix[m_CurrentPlayerPosition.row - 1][m_CurrentPlayerPosition.column - 1] = ELevelObjects::Empty;
	m_CurrentPlayerPosition = newPosition;

	int movementResult = EMovementResult::MovedOnEmptyCell;

	switch (objectOnNewPosition)
	{
	case ELevelObjects::Empty:
		break;
	case ELevelObjects::Explosive:
		movementResult = EMovementResult::MovedOnBomb;
		break;
	case ELevelObjects::LevelEnd:
		movementResult = EMovementResult::MovedOnLevelEnd;
		break;
	case ELevelObjects::ExplosiveSpawner:
		// cell next to cell player moved on
		Position possibleBombPosition = CalculatePossiblePositionAfterMovement(movementDirection);
		// Spawn bomb on possibleBombPosition if it's cooirdinates in boundaries of current level
		
		if (
			possibleBombPosition.row >= 0 && possibleBombPosition.row <= m_CurrentLevelMapRows
			&&
			possibleBombPosition.column >= 0 && possibleBombPosition.column <= m_CurrentLevelMapColumns
			)
		{
			SpawnBomb(possibleBombPosition);
		}
		break;

	}
	return movementResult;


}

bool CGameManager::ValidateMovement(int direction) const
{
	// First of all we cant move outside of level boundaries even if there no any wall.
	// For example, we cant move up, if current player row 0 or maximum row
	if (
		(m_CurrentPlayerPosition.row == 0 && direction == EPlayerMovementDirection::Up)
		|| (m_CurrentPlayerPosition.row == m_CurrentLevelMapRows && direction == EPlayerMovementDirection::Down)
		)
		return false;

	// In the same way handle side-movements
	if (
		(m_CurrentPlayerPosition.column == 0 && direction == EPlayerMovementDirection::Left)
		|| (m_CurrentPlayerPosition.column == m_CurrentLevelMapColumns && direction == EPlayerMovementDirection::Right)
		)
		return false;

	// Now, we have to check if we moving at wall. If so - return false
	if (GetLevelObjectAtPosition(CalculatePossiblePositionAfterMovement(direction)) == ELevelObjects::Wall)
	{
		return false;
	}

	// All checks are passed
	return true;
}

Position CGameManager::CalculatePossiblePositionAfterMovement(int movementDirection) const
{
	Position possibleNewPosition = m_CurrentPlayerPosition;
	switch (movementDirection)
	{
	case EPlayerMovementDirection::Down:
		possibleNewPosition.row += 1;
		break;
	case EPlayerMovementDirection::Up:
		possibleNewPosition.row -= 1;
		break;
	case EPlayerMovementDirection::Right:
		possibleNewPosition.column += 1;
		break;
	case EPlayerMovementDirection::Left:
		possibleNewPosition.column -= 1;
		break;

	}
	return possibleNewPosition;
}

void CGameManager::SpawnBomb(const Position& pos)
{
	m_CurrentLevelMapMatrix[pos.row - 1][pos.column - 1] = ELevelObjects::Explosive;
}

// GameCycle methods
void CGameManager::NextLevel()
{
	//m_CurrentLevelNumber = (m_CurrentLevelNumber + 1) % m_LevelsCount + 1;
	m_CurrentLevelNumber = (m_CurrentLevelNumber + 1 <= m_LevelsCount) ? m_CurrentLevelNumber + 1 : (m_CurrentLevelNumber + 1) % m_LevelsCount;

	LoadLevel(m_CurrentLevelNumber, pathsToLevelTextFiles[m_CurrentLevelNumber - 1]);
}

void CGameManager::ReloadCurrentLevel()
{
	LoadLevel(m_CurrentLevelNumber, pathsToLevelTextFiles[m_CurrentLevelNumber - 1]);
}

const char* CGameManager::GetLevelFilePath()
{
	return m_levelTextFilePath;
}

void CGameManager::ChangeGameState(int newState)
{
	m_CurrentGameState = newState;
	if (m_CurrentGameState == EGameConditions::LostDueExplosion)
	{
		ReloadCurrentLevel();
	}

	if (m_CurrentGameState == EGameConditions::WonCurrentLevel)
	{
		NextLevel();
	}
}


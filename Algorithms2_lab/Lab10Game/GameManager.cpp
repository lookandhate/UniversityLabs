#include "GameManager.h"

void GameManager::LoadLevel(int levelNumber, char* levelFilePath)
{
	// LEVEL FILE FORMAT
	// ROWS, COLUMNS - 2 VARIABLES
	// PLAYER START POSITION ON CURRENT MAP - 2 VARIABLES (ROW, COLUMN)
	// ROWS * COLUMNS DIGITS REPRESENTING EACH OBJECT ON MAP


	FILE* levelFilePtr;
	int openningError = fopen_s(&levelFilePtr, levelFilePath, "rt");
	if (openningError)
	{
		// TODO: handle file openning error
	}
	// Read rows and columns count on current level
	fscanf_s(levelFilePtr, "%d%d", &m_CurrentLevelMapRows, &m_CurrentLevelMapColumns);
	
	// Read player start position
	fscanf_s(levelFilePtr, "%d%d", &m_LevelPlayerStartPosition.row, &m_LevelPlayerStartPosition.column);

	for (int row = 0; row < m_CurrentLevelMapRows; row++)
	{
		for (int column = 0; column < m_CurrentLevelMapColumns; column++)
		{
			fscanf_s(levelFilePtr, "%d", &m_CurrentLevelMapMatrix[row][column]);
		}
	}

	// Close file after loading level information
	fclose(levelFilePtr);

}

bool GameManager::ValidateMovement(int direction) const
{
	// First of all we cant move outside of level boundaries even if there no any wall.
	// For example, we cant move up, if current player row 0 or maximum row
	if (
		(m_CurrentPlayerPosition.row == 0 && direction == PlayerMovementDirection::Up)
		|| (m_CurrentPlayerPosition.row + 1 == m_CurrentLevelMapRows && PlayerMovementDirection::Down)
		)
		return false;

	// In the same way handle side-movements
	if (
		(m_CurrentPlayerPosition.column == 0 && direction == PlayerMovementDirection::Left)
		|| (m_CurrentPlayerPosition.column + 1 == m_CurrentLevelMapRows && PlayerMovementDirection::Right)
		)
		return false;

	// Now, we have to check if we moving at wall. If so - return false
	if(GetLevelObjectAtPosition)

}

int GameManager::GetLevelObjectAtPosition(const Position& pos) const
{
	return 0;
}

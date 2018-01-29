#include "stdafx.h"
#include "GameBoard.h"
#include <stdlib.h>
#include <time.h> 
#include <string>

GameBoard::GameBoard(void)
{
	m_arrBoard = {};
	m_nColumns = 16;
	m_nRows = 30;
	m_nHeight= 20;
	m_nWidth = 20;
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(0, 0, 255);
	m_arrColors[2] = RGB(255, 0, 0);
}

GameBoard::~GameBoard(void)
{
	Sleep(100);
	DeleteBoard();
}


void GameBoard::SetupBoard(void)
{
	if (m_arrBoard.empty())
		CreateBoard();
}

COLORREF GameBoard::GetBoardSpace(int row, int col)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return m_arrColors[0];
	return m_arrColors[m_arrBoard[row][col]];
}

void GameBoard::DeleteBoard(void)
{
	m_arrBoard = {};
}

void GameBoard::NewPiece(void) {
	srand(time(NULL));
	int Pos = (rand() % m_nColumns - 1) + 1;
	srand(time(NULL));
	int Type = (rand() % 7);
	if (Type == 0) {
		PiecePos[0] = { 2,Pos };
		PiecePos[1] = { 3,Pos };
		PiecePos[2] = { 1,Pos };
		PiecePos[3] = { 0,Pos };
	}
	else if (Type == 1) {
		if (Pos == 0) {
			Pos++;
		}
		if (Pos == m_nColumns - 1) {
			Pos--;
		}
		PiecePos[0] = { 1,Pos };
		PiecePos[1] = { 1,Pos - 1 };
		PiecePos[2] = { 1,Pos + 1 };
		PiecePos[3] = { 0,Pos };
	}
	else if (Type == 2) {
		if (Pos == 0) {
			Pos++;
		}
		if (Pos == m_nColumns - 1) {
			Pos--;
		}
		PiecePos[0] = { 1,Pos };
		PiecePos[1] = { 1,Pos + 1 };
		PiecePos[2] = { 0,Pos + 1 };
		PiecePos[3] = { 0,Pos };
	}
	else if (Type == 3) {
		if (Pos == 0) {
			Pos++;
		}
		if (Pos == m_nColumns - 1) {
			Pos--;
		}
		PiecePos[0] = { 1,Pos };
		PiecePos[1] = { 1,Pos + 1 };
		PiecePos[2] = { 0,Pos };
		PiecePos[3] = { 0,Pos - 1 };
	}
	else if (Type == 4) {
		if (Pos == 0) {
			Pos++;
		}
		if (Pos == m_nColumns - 1) {
			Pos--;
		}
		PiecePos[0] = { 1,Pos };
		PiecePos[1] = { 1,Pos - 1 };
		PiecePos[2] = { 0,Pos };
		PiecePos[3] = { 0,Pos + 1 };
	}
	else if (Type == 5) {
		if (Pos == m_nColumns - 1) {
			Pos = Pos - 2;
		}
		PiecePos[0] = { 1,Pos };
		PiecePos[1] = { 1,Pos + 1 };
		PiecePos[2] = { 1,Pos + 2 };
		PiecePos[3] = { 0,Pos };
	}
	else {
		if (Pos == 0) {
			Pos = Pos + 2;
		}
		PiecePos[0] = { 1,Pos };
		PiecePos[1] = { 1,Pos - 1 };
		PiecePos[2] = { 1,Pos - 2 };
		PiecePos[3] = { 0,Pos };
	}
	PiecePos[4] = { Type , 0 };
	PosChange(2);
}

void GameBoard::PosChange(int io) {
	if (io > 2) {
		io = 2;
	}
	if (io < 0) {
		io = 0;
	}
	if (!m_arrBoard.empty())
	{
		m_arrBoard[PiecePos[0][0]][PiecePos[0][1]] = io;
		m_arrBoard[PiecePos[1][0]][PiecePos[1][1]] = io;
		m_arrBoard[PiecePos[2][0]][PiecePos[2][1]] = io;
		m_arrBoard[PiecePos[3][0]][PiecePos[3][1]] = io;
	}
}

void GameBoard::MovePiece(int Direction = 0) {
	if (m_arrBoard.empty())
	{
		return;
	}
	if (PiecePos[0][0] == -1) {
		NewPiece();
	}
	else {
		std::vector<std::vector<int>> NewPos = PiecePos;
		if (Direction == 0) {
			//ALAS
			if (PiecePos[0][0] > m_nRows - 2 ||
				PiecePos[1][0] > m_nRows - 2 ||
				PiecePos[2][0] > m_nRows - 2 || 
				PiecePos[3][0] > m_nRows - 2) {
				PosChange(1);
				CheckBoard();
				NewPiece();
				return;
			}
			else {
				NewPos[0][0] = PiecePos[0][0] + 1;
				NewPos[1][0] = PiecePos[1][0] + 1;
				NewPos[2][0] = PiecePos[2][0] + 1;
				NewPos[3][0] = PiecePos[3][0] + 1;
			}
		}
		else if (Direction == 1) {
			//VASEMMALLE
			if (PiecePos[0][1] <= 0 ||
				PiecePos[1][1] <= 0 ||
				PiecePos[2][1] <= 0 || 
				PiecePos[3][1] <= 0) {
				return;
			}
			else {
				NewPos[0][1] = PiecePos[0][1] - 1;
				NewPos[1][1] = PiecePos[1][1] - 1;
				NewPos[2][1] = PiecePos[2][1] - 1;
				NewPos[3][1] = PiecePos[3][1] - 1;
			}
		}
		else if (Direction == 2) {
			//OIKEALLE
			if (PiecePos[0][1] > m_nColumns - 2 ||
				PiecePos[1][1] > m_nColumns - 2 ||
				PiecePos[2][1] > m_nColumns - 2 ||
				PiecePos[3][1] > m_nColumns - 2) {
				return;
			}
			else {
				NewPos[0][1] = PiecePos[0][1] + 1;
				NewPos[1][1] = PiecePos[1][1] + 1;
				NewPos[2][1] = PiecePos[2][1] + 1;
				NewPos[3][1] = PiecePos[3][1] + 1;
			}
		}
		else {
			//KÄÄNTÄMINEN
			if (PiecePos[4][0] == 0) {
				if (PiecePos[4][1] == 0) {
					NewPos[1] = { PiecePos[0][0], PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] + 2 };
				}
				else if (PiecePos[4][1] == 1) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0] - 2, PiecePos[0][1] };
				}
				else if (PiecePos[4][1] == 2) {
					NewPos[1] = { PiecePos[0][0], PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] + 2 };
				}
				else if (PiecePos[4][1] == 4) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0] - 2, PiecePos[0][1] };
				}
			} 
			else if (PiecePos[4][0] == 1) {
				if (PiecePos[4][1] == 0) {
					NewPos[1] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 1) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] + 1 };
					NewPos[2] = { PiecePos[0][0] , PiecePos[0][1] - 1 };
					NewPos[3] = { PiecePos[0][0] + 1, PiecePos[0][1] };
				}
				else if (PiecePos[4][1] == 2) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] - 1 };
				}
				else if (PiecePos[4][1] == 4) {
					NewPos[1] = { PiecePos[0][0], PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] };
				}
			}
			else if (PiecePos[4][0] == 2) {
				return;
			}
			else if (PiecePos[4][0] == 3) {
				if (PiecePos[4][1] == 0) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 1) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] + 1 };
					NewPos[2] = { PiecePos[0][0] - 1 , PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] - 1 };
				}
				else if (PiecePos[4][1] == 2) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 4) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] + 1 };
					NewPos[2] = { PiecePos[0][0] - 1 , PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] - 1 };
				}
			}
			else if (PiecePos[4][0] == 4) {
				if (PiecePos[4][1] == 0) {
					NewPos[1] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0] + 1, PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 1) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0] - 1 , PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 2) {
					NewPos[1] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[3] = { PiecePos[0][0] + 1, PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 4) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0] - 1 , PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] + 1 };
				}
			}
			else if (PiecePos[4][0] == 5) {
				if (PiecePos[4][1] == 0) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] + 2, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 1) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0] , PiecePos[0][1] - 2 };
					NewPos[3] = { PiecePos[0][0] + 1, PiecePos[0][1] };
				}
				else if (PiecePos[4][1] == 2) {
					NewPos[1] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] - 2, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] - 1 };
				}
				else if (PiecePos[4][1] == 4) {
					NewPos[1] = { PiecePos[0][0], PiecePos[0][1] + 1 };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] + 2 };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] };
				}
			}
			else {
				if (PiecePos[4][1] == 0) {
					NewPos[1] = { PiecePos[0][0] - 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] - 2, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] + 1 };
				}
				else if (PiecePos[4][1] == 1) {
					NewPos[1] = { PiecePos[0][0] , PiecePos[0][1] + 1 };
					NewPos[2] = { PiecePos[0][0] , PiecePos[0][1] + 2 };
					NewPos[3] = { PiecePos[0][0] + 1, PiecePos[0][1] };
				}
				else if (PiecePos[4][1] == 2) {
					NewPos[1] = { PiecePos[0][0] + 1, PiecePos[0][1] };
					NewPos[2] = { PiecePos[0][0] + 2, PiecePos[0][1] };
					NewPos[3] = { PiecePos[0][0], PiecePos[0][1] - 1 };
				}
				else if (PiecePos[4][1] == 4) {
					NewPos[1] = { PiecePos[0][0], PiecePos[0][1] - 1 };
					NewPos[2] = { PiecePos[0][0], PiecePos[0][1] - 2 };
					NewPos[3] = { PiecePos[0][0] - 1, PiecePos[0][1] };
				}
			}
			if (PiecePos[4][1] == 4) {
				NewPos[4][1] = 0;
			}
			else {
				NewPos[4][1] = PiecePos[4][1] + 1;
			}
			if (NewPos[0][1] < 0 ||
				NewPos[1][1] < 0 ||
				NewPos[2][1] < 0 ||
				NewPos[3][1] < 0 || 
				NewPos[0][1] > m_nColumns - 1 ||
				NewPos[1][1] > m_nColumns - 1 ||
				NewPos[2][1] > m_nColumns - 1 ||
				NewPos[3][1] > m_nColumns - 1 ||
				NewPos[0][0] > m_nRows - 2 ||
				NewPos[1][0] > m_nRows - 2 ||
				NewPos[2][0] > m_nRows - 2 ||
				NewPos[3][0] > m_nRows - 2) {
				return;
			}
		}
		if (m_arrBoard[NewPos[0][0]][NewPos[0][1]] == 1 ||
			m_arrBoard[NewPos[1][0]][NewPos[1][1]] == 1 ||
			m_arrBoard[NewPos[2][0]][NewPos[2][1]] == 1 ||
			m_arrBoard[NewPos[3][0]][NewPos[3][1]] == 1
			) {
			if (Direction == 0) {
				if (NewPos[0][0] == 1 ||
					NewPos[1][0] == 1 ||
					NewPos[2][0] == 1 ||
					NewPos[3][0] == 1
					) {
					GameLost();
					return;
				}
				PosChange(1);
				CheckBoard();
				GamePoints = GamePoints + 50;
				NewPiece();
				return;
			}
			else {
				return;
			}
		}
		PosChange(0);
		PiecePos = NewPos;
		PosChange(2);
		GamePoints++;
	}
}
void GameBoard::GameLost(void) {
	std::wstring GameLostStr = L"The game has ended with ";
	std::wstring GamePointsStr = std::to_wstring(GamePoints);
	GameLostStr = GameLostStr + GamePointsStr + L" points.";
	MessageBox(NULL, GameLostStr.c_str() , L"Game lost!", MB_OK);
	Sleep(1000);
	CreateBoard();
}
void GameBoard::CheckBoard(void)
{
	if (m_arrBoard.empty())
	{
		return;
	}
	std::vector<int> ToDrop;
	for (int i = 0; i < m_nRows; i++) {
		bool Drop = true;
		for (int j = 0; j < m_nColumns; j++) {
			if (m_arrBoard[i][j] != 1) {
				Drop = false;
				break;
			}
		}
		if (Drop) {
			ToDrop.push_back(i);
		}
	}
	if (!ToDrop.empty()) {
		DropBoard(ToDrop);
	}
}
void GameBoard::DropBoard(std::vector<int> ToDrop)
{
	if (m_arrBoard.empty())
	{
		return;
	}
	int HighestRow = m_nRows;
	int RowAmount = ToDrop.size();
	int PointMultiplier = pow(RowAmount, 1.4);
	GamePoints = GamePoints + PointMultiplier * 1000;
	for (int i = 0; i < RowAmount; i++) {
		if (ToDrop[i] < HighestRow) {
			HighestRow = ToDrop[i];
		}
		for (int j = 0; j < m_nColumns; j++) {
			m_arrBoard[ToDrop[i]][j] = 0;
		}
	}
	for (int i = HighestRow - 1; i > -RowAmount; i--) {
		for (int j = 0; j < m_nColumns; j++) {
			if (i < 0) {
				m_arrBoard[i + RowAmount][j] = 0;
			}
			else {
				m_arrBoard[i + RowAmount][j] = m_arrBoard[i][j];
			}
		}
	}
}
void GameBoard::CreateBoard(void)
{
	if (!m_arrBoard.empty());
		DeleteBoard();
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard.push_back({});
		for (int col = 0; col < m_nColumns; col++) {
			m_arrBoard[row].push_back(0);
		}
	}
	PiecePos = { { -1,-1 },{ -1,-1 },{ -1,-1 },{ -1,-1 },{ -1,-1 } };
	GamePoints = 0;
}
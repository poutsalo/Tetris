#pragma once
#include <vector>

class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	std::vector<std::vector<int>> PiecePos;
	void SetupBoard(void);
	void NewPiece(void);
	void MovePiece(int Direction);
	COLORREF GetBoardSpace(int row, int col);
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }
	int GetPoints(void) { return GamePoints; }
	void DeleteBoard(void);
	void PosChange(int color);
	void CheckBoard(void);
	void DropBoard(std::vector<int> ToDrop);
	void GameLost(void);
private:
	int GamePoints;
	void CreateBoard(void);
	std::vector<std::vector<int>> m_arrBoard;
	COLORREF m_arrColors[3];
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
};

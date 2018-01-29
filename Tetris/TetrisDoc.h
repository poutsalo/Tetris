
// TetrisDoc.h : interface of the CTetrisDoc class
//


#pragma once

#include "GameBoard.h"

class CTetrisDoc : public CDocument
{
protected: // create from serialization only
	CTetrisDoc();
	DECLARE_DYNCREATE(CTetrisDoc)

// Attributes
public:
	
private:

// Operations
public:
	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{
		return TetrisBoard.GetBoardSpace(row, col);
	}
	void MovePiece(int Direction = 0) { TetrisBoard.MovePiece(Direction); }
	void SetupBoard(void) { TetrisBoard.SetupBoard(); }
	int GetWidth(void) { return TetrisBoard.GetWidth(); }
	int GetHeight(void) { return TetrisBoard.GetHeight(); }
	int GetColumns(void) { return TetrisBoard.GetColumns(); }
	int GetRows(void) { return TetrisBoard.GetRows(); }
	int GetPoints(void) { return TetrisBoard.GetPoints(); }
	void DeleteBoard(void) { TetrisBoard.DeleteBoard(); }
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CTetrisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GameBoard TetrisBoard;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:

};

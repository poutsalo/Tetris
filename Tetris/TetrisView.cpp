
// TetrisView.cpp : implementation of the CTetrisView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"
#include <chrono>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CTetrisView
#define CM_UB (WM_APP+1)

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	ON_MESSAGE(CM_UB,UpdateBoard)
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CTetrisView construction/destruction

long long int EpochTime() {
	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	long long int time_int = time.time_since_epoch().count() / 10000;
	return time_int;
}

CTetrisView::CTetrisView()
{
	// TODO: add construction code here
}

CTetrisView::~CTetrisView()
{
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTetrisView drawing

void CTetrisView::OnDraw(CDC* pDC) // MFC will comment out the argument name by default; uncomment it
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int nDCSave = pDC->SaveDC();
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	pDC->FillSolidRect(&rcClient, clr);
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Draw the squares
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			clr = pDoc->GetBoardSpace(row, col);
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			pDC->FillSolidRect(&rcBlock, clr);
			pDC->Rectangle(&rcBlock);
		}
	}
	//Draw points
	std::wstring Points = std::to_wstring(pDoc->GetPoints());
	std::wstring PointStr = Points + L" points";
	clr = RGB(255, 255, 255);
	pDC->FillSolidRect(0, 0, 0, 0, 0);
	pDC->SetTextColor(clr);
	pDC->TextOut(5, 2, PointStr.c_str(), PointStr.size());
	br.DeleteObject();
	pDC->RestoreDC(nDCSave);
}

// CTetrisView diagnostics

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}


void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView message handlers

UINT CTetrisView::Worker(LPVOID pParam) {
	CTetrisView* self = (CTetrisView*)pParam;
	while (self->RunProgram) {
		long long int Runtime = EpochTime();
		if ((Runtime - self->LastUpdate) > self->Speed) {
			self->SendMessage(CM_UB);
			self->LastUpdate = Runtime;
		}
		Sleep(5);
	}
	return 0;
}
LRESULT CTetrisView::UpdateBoard(WPARAM wparam,LPARAM lparam) {
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->MovePiece();
	Invalidate();
	UpdateWindow();
	return 0;
}

void CTetrisView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	ResizeWindow();
	RunProgram = true;
	AfxBeginThread(Worker, this);
	// TODO: Add your specialized code here and/or call the base class
}

void CTetrisView::ResizeWindow() {
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	GetParentFrame()->MoveWindow(&rcWindow);
}

BOOL CTetrisView::OnEraseBkgnd(CDC* pDC) {
	return 1;
}

void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (RunProgram) {
		CTetrisDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (nChar == VK_DOWN) {
			pDoc->MovePiece(0);
		}
		else if (nChar == VK_LEFT) {
			pDoc->MovePiece(1);
		}
		else if (nChar == VK_RIGHT) {
			pDoc->MovePiece(2);
		}
		else if (nChar == VK_UP) {
			pDoc->MovePiece(3);
		}
		else {
			return;
		}
		Invalidate();
		UpdateWindow();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTetrisView::OnDestroy()
{
	RunProgram = false;
	Sleep(50);
	CView::OnDestroy();
	// TODO: Add your message handler code here
}


void CTetrisView::OnClose()
{
	RunProgram = false;
	Sleep(50);
	// TODO: Add your message handler code here and/or call default
	CView::OnClose();
}

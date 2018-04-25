// pplgameView.cpp : implementation of the CPplgameView class
//

#include "stdafx.h"
#include "pplgame.h"

#include "pplgameDoc.h"
#include "pplgameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPplgameView

IMPLEMENT_DYNCREATE(CPplgameView, CView)

BEGIN_MESSAGE_MAP(CPplgameView, CView)
	//{{AFX_MSG_MAP(CPplgameView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPplgameView construction/destruction

CPplgameView::CPplgameView()
{
	// TODO: add construction code here
	game=new CGame();
}

CPplgameView::~CPplgameView()
{
}

BOOL CPplgameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPplgameView drawing

void CPplgameView::OnDraw(CDC* pDC)
{
	CPplgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	static int i=0;
	if(i==0)
	{
		game->InitImg(pDC);
		i = 1;
		game->GetRand();
		game->GetNextRand();
		gpDC = new CClientDC(this);
	}
//	game->Draw(pDC);
	
}

/////////////////////////////////////////////////////////////////////////////
// CPplgameView printing

BOOL CPplgameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPplgameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPplgameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPplgameView diagnostics

#ifdef _DEBUG
void CPplgameView::AssertValid() const
{
	CView::AssertValid();
}

void CPplgameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPplgameDoc* CPplgameView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPplgameDoc)));
	return (CPplgameDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPplgameView message handlers

void CPplgameView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!game->GetGameflag())
	{
	game->SetCurrent(point);
	}
	else
	{
		game->GetRand();
		game->GetNextRand();
		game->SetGameoverflag();
		game->PointsClear();
	}
	CView::OnLButtonDown(nFlags, point);

}

void CPplgameView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	game->GetPoint(point);
	CView::OnMouseMove(nFlags, point);
	
}

void CPplgameView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	game->Draw(gpDC);
	CView::OnTimer(nIDEvent);
}

int CPplgameView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(1,17,NULL);
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CPplgameView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

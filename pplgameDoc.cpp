// pplgameDoc.cpp : implementation of the CPplgameDoc class
//

#include "stdafx.h"
#include "pplgame.h"

#include "pplgameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPplgameDoc

IMPLEMENT_DYNCREATE(CPplgameDoc, CDocument)

BEGIN_MESSAGE_MAP(CPplgameDoc, CDocument)
	//{{AFX_MSG_MAP(CPplgameDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPplgameDoc construction/destruction

CPplgameDoc::CPplgameDoc()
{
	// TODO: add one-time construction code here

}

CPplgameDoc::~CPplgameDoc()
{
}

BOOL CPplgameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPplgameDoc serialization

void CPplgameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPplgameDoc diagnostics

#ifdef _DEBUG
void CPplgameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPplgameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPplgameDoc commands

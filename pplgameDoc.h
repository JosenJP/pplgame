// pplgameDoc.h : interface of the CPplgameDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPLGAMEDOC_H__10E67861_070F_4BF7_9809_050D22A8BA0D__INCLUDED_)
#define AFX_PPLGAMEDOC_H__10E67861_070F_4BF7_9809_050D22A8BA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPplgameDoc : public CDocument
{
protected: // create from serialization only
	CPplgameDoc();
	DECLARE_DYNCREATE(CPplgameDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPplgameDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPplgameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPplgameDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPLGAMEDOC_H__10E67861_070F_4BF7_9809_050D22A8BA0D__INCLUDED_)

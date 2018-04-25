// pplgame.h : main header file for the PPLGAME application
//

#if !defined(AFX_PPLGAME_H__6BBA5670_EE0E_46B5_9153_F5167E0054F8__INCLUDED_)
#define AFX_PPLGAME_H__6BBA5670_EE0E_46B5_9153_F5167E0054F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPplgameApp:
// See pplgame.cpp for the implementation of this class
//

class CPplgameApp : public CWinApp
{
public:
	CPplgameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPplgameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPplgameApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPLGAME_H__6BBA5670_EE0E_46B5_9153_F5167E0054F8__INCLUDED_)

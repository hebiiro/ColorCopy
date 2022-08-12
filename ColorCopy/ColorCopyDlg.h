#pragma once

class CColorCopyDlg : public CDialog
{
public:

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORCOPY_DIALOG };
#endif

	COLORREF m_color = CLR_NONE;
	CBrush m_brush;
	BOOL m_isPicking = FALSE;

	CStatic m_pick;
	int m_type;
	CString m_text;

public:

	CColorCopyDlg(CWnd* pParent = nullptr);
	COLORREF pickColor();
	CString getText(COLORREF color);
	void drag();
	void copy();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
};

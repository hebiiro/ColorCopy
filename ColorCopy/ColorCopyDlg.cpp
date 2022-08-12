#include "pch.h"
#include "framework.h"
#include "ColorCopy.h"
#include "ColorCopyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CColorCopyDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

CColorCopyDlg::CColorCopyDlg(CWnd* pParent)
	: CDialog(IDD_COLORCOPY_DIALOG, pParent)
	, m_type(0)
	, m_text(_T(""))
{
}

COLORREF CColorCopyDlg::pickColor()
{
	POINT point; ::GetCursorPos(&point);
//	::LogicalToPhysicalPointForPerMonitorDPI(0, &point);
	HDC dc = ::GetDC(0);
	COLORREF color = ::GetPixel(dc, point.x, point.y);
	::ReleaseDC(0, dc);
	return color;
}

CString CColorCopyDlg::getText(COLORREF color)
{
	CString text;

	switch (m_type)
	{
	case 0:
		{
			text.Format(_T("#%02x%02x%02x"),
				GetRValue(color),
				GetGValue(color),
				GetBValue(color));

			break;
		}
	case 1:
		{
			text.Format(_T("%d,%d,%d"),
				GetRValue(color),
				GetGValue(color),
				GetBValue(color));

			break;
		}
	case 2:
		{
			text.Format(_T("%3d,%3d,%3d"),
				GetRValue(color),
				GetGValue(color),
				GetBValue(color));

			break;
		}
	}

	return text;
}

void CColorCopyDlg::drag()
{
	static int n = 0; n++;

	m_color = pickColor();
	TRACE(_T("%d, m_color = 0x%08X\n"), n, m_color);

	if ((HBRUSH)m_brush) m_brush.DeleteObject();
	m_brush.CreateSolidBrush(m_color);
	m_pick.Invalidate(TRUE);

	m_text = getText(m_color);
	TRACE(_T("m_text = %s\n"), m_text);

	UpdateData(FALSE);
}

void CColorCopyDlg::copy()
{
	TRACE(_T("CColorCopyDlg::copy()\n"));

	CEdit* edit = (CEdit*)GetDlgItem(IDC_TEXT);
	edit->SetSel(0, -1);
	edit->Copy();
}

void CColorCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PICK, m_pick);
	DDX_Radio(pDX, IDC_HEX, m_type);
	DDX_Text(pDX, IDC_TEXT, m_text);
}

BOOL CColorCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return TRUE;
}

void CColorCopyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	TRACE(_T("CColorCopyDlg::OnLButtonDown()\n"));

	m_isPicking = TRUE;
	SetCapture();
	UpdateData(TRUE);

	CDialog::OnLButtonDown(nFlags, point);
}

void CColorCopyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isPicking && GetCapture() == this)
	{
		drag();
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CColorCopyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	TRACE(_T("CColorCopyDlg::OnLButtonUp()\n"));

	if (m_isPicking && GetCapture() == this)
	{
		m_isPicking = FALSE;
		ReleaseCapture();

		drag();
		copy();
	}

	CDialog::OnLButtonUp(nFlags, point);
}

HBRUSH CColorCopyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH brush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (*pWnd == m_pick)
		return m_brush;

	return brush;
}

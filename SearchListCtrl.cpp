#include "StdAfx.h"
#include "SearchListCtrl.h"


CSearchListCtrl::CSearchListCtrl(void)
{
	 pavi=NULL;
}


CSearchListCtrl::~CSearchListCtrl(void)
{
}
BEGIN_MESSAGE_MAP(CSearchListCtrl, CListCtrl)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CSearchListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	pDC->SetBkMode(TRANSPARENT);
	HBRUSH hb=CreateSolidBrush(RGB(255,255,255));
	pDC->SetBkColor(RGB(255,255,255));
	return hb;
	
}


// topcoderDlg.h : ͷ�ļ�
//

#pragma once

#include "user.h"

// CtopcoderDlg �Ի���
class CtopcoderDlg : public CDialogEx
{
// ����
public:
	CtopcoderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOPCODER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CUser *ReadCard(void);
	afx_msg void OnBnClickedButton1();
	int ConvertPict(const CString &path);
	// �������ݷ���
	void SendImage(BYTE* Bitmap, DWORD count);
};

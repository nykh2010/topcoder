
// topcoderDlg.h : 头文件
//

#pragma once

#include "user.h"

// CtopcoderDlg 对话框
class CtopcoderDlg : public CDialogEx
{
// 构造
public:
	CtopcoderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOPCODER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 串口数据发送
	void SendImage(BYTE* Bitmap, DWORD count);
	afx_msg void OnStnClickedStatic4();
};

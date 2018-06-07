
// topcoderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "topcoder.h"
#include "topcoderDlg.h"
#include "afxdialogex.h"
#include "termb.h"
#include "resource.h"

#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <Windows.h>

using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CUser currentUser;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtopcoderDlg 对话框




CtopcoderDlg::CtopcoderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtopcoderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtopcoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtopcoderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CtopcoderDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CtopcoderDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CtopcoderDlg 消息处理程序

BOOL CtopcoderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtopcoderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtopcoderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtopcoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//连接/断开身份证阅读器
void CtopcoderDlg::OnBnClickedButton2()
{
	int status;
	CString error_msg;
	CString button_current_state;
	// TODO: 在此添加控件通知处理程序代码
	CButton *pConnectButton = (CButton *)GetDlgItem(IDC_BUTTON2);
	pConnectButton->GetWindowTextW(button_current_state);
	if (button_current_state == _T("断开")) {
		status = CloseComm();
		if (status != 1) {
			AfxMessageBox(_T("CloseComm Failed\n"));
			return;
		}
		AfxMessageBox(_T("CloseComm Success\n"));
		pConnectButton->SetWindowTextW(_T("连接"));
	}
	else {
		int nPort = InitCommExt();
		if (nPort > 0) {
			//error_msg.Format(_T("InitComm success, port=%d!\n"), nPort);
			//AfxMessageBox(error_msg);
			pConnectButton->SetWindowTextW(_T("断开"));
			this->SetTimer(0,500,NULL);
		}
		else {
			AfxMessageBox(_T("InitComm Failed!\n"));
		}
	}
}

void CtopcoderDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int status;
	switch (nIDEvent) {
	case 0:
		//500ms定时器
		status = Authenticate();
		if (status == 1) {
			this->KillTimer(nIDEvent);
			this->ReadCard();
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

CString exact_info(CString attribute, const CByteArray &content) {
	CString Error = _T("Failed");
	int index;
	int length;
	if (attribute == _T("name")) {
		CString name;
		wchar_t *pstr = name.GetBufferSetLength(15);
		memcpy(pstr,content.GetData(),30);
		index = name.Find(_T("\x0020"),0);
		if (index < 0){
			name.SetAt(15,'\0');
		}
		else {
			name.SetAt(index,'\0');
		}
		//length = name.GetLength();
		return name.Left(index);
	}
	else if (attribute == _T("sex")) {
		CString sex;
		memcpy(sex.GetBuffer(),&content.GetData()[30],2);
		return sex;
	}
	else if (attribute == _T("id")) {
		CString id;
		memcpy(id.GetBufferSetLength(18),&content.GetData()[122],36);
		//id.SetAt(18,'\0');
		length = id.GetLength();
		return id;
	}
	return Error;
}

CUser *CtopcoderDlg::ReadCard(void)
{
	int status;
	
	status = Read_Content(1);
	if (status != 1) {
		AfxMessageBox(_T("读卡失败！\n"));
		return NULL;
	}
	GetBmpPhoto("../Debug/xp.wlt");									//生成bmp图片 zp.bmp
	CFile content;
	if (!content.Open(_T("../Debug/wz.txt"),CFile::modeRead | CFile::typeBinary, NULL)) {
		return NULL;
	}
	CByteArray content_byte;
	content_byte.SetSize(256);
	content.Read(content_byte.GetData(), 256);
	currentUser.name = exact_info(_T("name"),content_byte);			//获取姓名
	currentUser.id = exact_info(_T("id"),content_byte);				//获取身份证号
	UpdateData(true);
	CEdit *pName = (CEdit *)GetDlgItem(IDC_EDIT1);					//将姓名显示在控件上
	pName->SetWindowTextW(currentUser.name);
	if (!PathIsDirectory(currentUser.id)) {
		CreateDirectory(currentUser.id,NULL);						//创建一个以身份证号命名的文件夹
	}
	CFile newFile;
	CString newPath = _T(".\\")+currentUser.id+_T("\\")+currentUser.name;
	if (!newFile.Open(_T(".\\")+currentUser.id+'\\'+currentUser.name,CFile::modeCreate | CFile::modeWrite, NULL)) {
		return NULL;
	}
	newFile.Write(currentUser.name+_T("\r\n"),(currentUser.name.GetLength()+2)*2);		//生成新的信息文件
	newFile.Write(currentUser.id+_T("\r\n"),(currentUser.id.GetLength()+2)*2);
	
	CStatic *imgctl = (CStatic *)GetDlgItem(IDC_STATIC);
	CRect rc;
	imgctl->GetWindowRect(&rc);
	//获取背景图片
	Mat photo = imread("../Debug/zp.bmp");
	Mat photo_scale;
	Size dsize(rc.Width(),rc.Height());
	resize(photo,photo_scale,dsize);				//改变图像尺寸
	imwrite("../Debug/zp_scale.bmp",photo_scale);

	CImage photo_bitmap;
	photo_bitmap.Load(_T("../Debug/zp_scale.bmp"));			//载入背景	
	CBitmap bitmap;
	bitmap.DeleteObject();
	bitmap.Attach((HBITMAP)photo_bitmap.operator HBITMAP());
	CDC ImageDC;
	ImageDC.CreateCompatibleDC(NULL);
	ImageDC.SelectObject(&bitmap);
	imgctl->GetDC()->StretchBlt(0,0,rc.Width(),rc.Height(),&ImageDC,0,0,rc.Width(),rc.Height(),SRCCOPY);
	ReleaseDC(&ImageDC);

	content.Close();
	newFile.Close();
	UpdateData(false);

	photo_bitmap.Destroy();
	//DeleteFile(_T("../Debug/zp_scale.bmp"));				//删除转换之后的图片

	return NULL;
}


void CtopcoderDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFile newFile;
	UpdateData(true);
	CEdit *pCorp = (CEdit *)GetDlgItem(IDC_EDIT2);
	pCorp->GetWindowTextW(currentUser.corporation);
	UpdateData(false);
	if (!newFile.Open(_T(".\\")+currentUser.id+'\\'+currentUser.name, CFile::modeNoTruncate | CFile::modeWrite, NULL)) {
		return ;
	}
	newFile.SeekToEnd();
	newFile.Write(currentUser.corporation+_T("\r\n"),(currentUser.corporation.GetLength()+2)*2);
	newFile.Close();
	this->ConvertPict(_T("../Debug/zp.bmp"));
	return;
}


int CtopcoderDlg::ConvertPict(const CString &path)
{
	BYTE readbuf[4096];
	HBITMAP hBmp;
	int count,status;
	CString dst_path = _T(".\\")+currentUser.id+'\\'+currentUser.name+_T(".bmp");
	CString dst_folder = _T(".\\")+currentUser.id+'\\';
	CFile srcFile,dstFile;
	//GetBmpPhoto("../Debug/xp.wlt");
	//创建新的身份证照片
	if (!srcFile.Open(path,CFile::modeRead | CFile::typeBinary)) {
		return -1;
	}
	if (!dstFile.Open(dst_path, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary)) {
		return -1;
	}
	while(true) {
		count = srcFile.Read(readbuf,4096);
		if (count <= 0) {
			break;
		}
		dstFile.Write(readbuf,count);
	}
	srcFile.Close();
	dstFile.Close();


	CImage userImage;
	userImage.Load(dst_path);
	if (!userImage.IsNull()) {
		hBmp = userImage.Detach();
	}
	
	//创建空白背景
	Scalar s(255,255,255);
	Mat background(128,296,CV_8UC3,s);
	USES_CONVERSION;
	char *file_path = T2A(dst_path);
	//char file_path[] = "C:\\Users\\xulingfeng\\Documents\\Visual Studio 2010\\Projects\\test\\test\\徐凌峰.bmp";
	Mat img = imread(file_path);
	if (img.empty()) {
		AfxMessageBox(_T("图片打开失败!"));
		return -1;
	}
	Mat background_roi(background,Rect(0,0,102,126));		//获取照片位置
	img.copyTo(background_roi);								//插入照片
	//imshow("show",background);
	//waitKey();
	CString background_path = dst_folder+'\\'+currentUser.name+_T("background.bmp");
	imwrite(T2A(background_path),background);				//保存背景图片


	//创建一个空白bmp文件，大小为296*128
	int background_width = 296;
	int background_height = 128;
	//创建内存DC
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);

	CImage photo;
	//photo.Create(102,126,24,0);
	photo.Load(background_path);			//载入背景	
	CBitmap bitmap;
	bitmap.DeleteObject();
	bitmap.Attach((HBITMAP)photo.operator HBITMAP());
	memDC.SelectObject(&bitmap);

	CFont font;								//创建文字
	int nHeight = 30;
	int nWidth = 0;
	int nEscapement = 0;
	int nOrientation = 0;
	int fnWeight = 18;
	DWORD fdwltalic = 0;
	DWORD fdwUnderline = 0;
	DWORD fdwStrikeOut = 0;
	DWORD fdwCharSet = GB2312_CHARSET;
	DWORD fdwOutputPrecision = OUT_DEFAULT_PRECIS;
	DWORD fdwClipPrecision = CLIP_DEFAULT_PRECIS;
	DWORD fdwQuality = DEFAULT_QUALITY;
	DWORD fdwPitchAndFamily = FF_DONTCARE;
	LPCTSTR lpszFace = _T("华文行楷");
	font.CreateFontW(nHeight,nWidth,nEscapement,nOrientation,fnWeight,fdwltalic,fdwUnderline,fdwStrikeOut,fdwCharSet,fdwOutputPrecision,fdwClipPrecision,fdwQuality,
		fdwPitchAndFamily,lpszFace);			//初始化字体

	memDC.SelectObject(&font);			//选择字体

	CRect rectName(102,18,296,54);					//设定文字区
	UpdateData(true);
	CString name;
	CEdit *pName = (CEdit *)GetDlgItem(IDC_EDIT1);
	pName->GetWindowTextW(name);
	memDC.DrawTextW(name, &rectName, DT_CENTER);		//写入姓名
	CString corp;
	CEdit *pCorp = (CEdit *)GetDlgItem(IDC_EDIT2);
	pName->GetWindowTextW(name);
	CRect rectCorp(102,72,296,108);
	memDC.DrawTextW(corp,&rectCorp,DT_CENTER | DT_CALCRECT);		//写入单位
	UpdateData(false);

	UpdateData(true);
	CStatic *hint = (CStatic *)GetDlgItem(IDC_STATIC4);				//提示符
	hint->SetWindowTextW(_T("正在刷屏，请稍等..."));
	UpdateData(false);

	CImage outImage;							//创建结果
	outImage.Create(296,128,24,0);
	CDC::FromHandle(outImage.GetDC())->BitBlt(0,0,296,128,&memDC,0,0,SRCCOPY);
	outImage.Save(background_path);				//保存背景

	Mat convert = imread(T2A(background_path));
	Mat convert_gray(128,296,CV_8UC1);
	cvtColor(convert,convert_gray,CV_BGR2GRAY);		//转灰度图
	threshold(convert_gray,convert_gray,144,255,THRESH_BINARY_INV);			//转二值反图

	BYTE *buf = (BYTE *)calloc(1,296*128/8);		//转为E-ink屏识别的格式
	uchar *p = convert_gray.data;
	int i,j;
	for (i=0;i<296*128/8;i++) {
		for (j=0;j<8;j++) {
			buf[i] <<= 1;
			if (*p != 0xff) {
				buf[i] |= 0x01;
			}
			p++;
		}
	}
	DWORD sendcount = 296*128/8;
	this->SendImage(buf, &sendcount);

	UpdateData(true);
	hint->SetWindowTextW(_T("已就绪"));
	UpdateData(false);

	//资源回收
	free(buf);
	outImage.ReleaseDC();
	ReleaseDC(&memDC);
	photo.Destroy();
	outImage.Destroy();

	return 0;
}


// 串口数据发送
void CtopcoderDlg::SendImage(BYTE* Bitmap, DWORD * count)
{
	CString com = _T("COM2");
	//打开串口
	HANDLE hCom;
	hCom = CreateFile(com,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if (hCom == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("open com failed\n"));
		return;
	}
	//初始化配置
	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate = 19200;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = 1;
	SetCommState(hCom,&dcb);
	PurgeComm(hCom,PURGE_TXCLEAR);

	DWORD per_send_count = 1024;
	DWORD length = 0;
	while(*count > 0) {
		WriteFile(hCom, Bitmap, per_send_count, &length, NULL);
		*count = *count - length;
		per_send_count = *count < per_send_count? *count : 1024;
	}
	
	CloseHandle(hCom);		//关闭串口
	this->SetTimer(0,500,NULL);		//继续读卡
}

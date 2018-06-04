
// topcoderDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtopcoderDlg �Ի���




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


// CtopcoderDlg ��Ϣ�������

BOOL CtopcoderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtopcoderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtopcoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//����/�Ͽ����֤�Ķ���
void CtopcoderDlg::OnBnClickedButton2()
{
	int status;
	CString error_msg;
	CString button_current_state;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pConnectButton = (CButton *)GetDlgItem(IDC_BUTTON2);
	pConnectButton->GetWindowTextW(button_current_state);
	if (button_current_state == _T("�Ͽ�")) {
		status = CloseComm();
		if (status != 1) {
			AfxMessageBox(_T("CloseComm Failed\n"));
			return;
		}
		AfxMessageBox(_T("CloseComm Success\n"));
		pConnectButton->SetWindowTextW(_T("����"));
	}
	else {
		int nPort = InitCommExt();
		if (nPort > 0) {
			//error_msg.Format(_T("InitComm success, port=%d!\n"), nPort);
			//AfxMessageBox(error_msg);
			pConnectButton->SetWindowTextW(_T("�Ͽ�"));
			this->SetTimer(0,500,NULL);
		}
		else {
			AfxMessageBox(_T("InitComm Failed!\n"));
		}
	}
}

void CtopcoderDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int status;
	switch (nIDEvent) {
	case 0:
		//500ms��ʱ��
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
		AfxMessageBox(_T("����ʧ�ܣ�\n"));
		return NULL;
	}
	GetBmpPhoto("../Debug/xp.wlt");									//����bmpͼƬ zp.bmp
	CFile content;
	if (!content.Open(_T("../Debug/wz.txt"),CFile::modeRead | CFile::typeBinary, NULL)) {
		return NULL;
	}
	CByteArray content_byte;
	content_byte.SetSize(256);
	content.Read(content_byte.GetData(), 256);
	currentUser.name = exact_info(_T("name"),content_byte);			//��ȡ����
	currentUser.id = exact_info(_T("id"),content_byte);				//��ȡ���֤��
	UpdateData(true);
	CEdit *pName = (CEdit *)GetDlgItem(IDC_EDIT1);					//��������ʾ�ڿؼ���
	pName->SetWindowTextW(currentUser.name);
	if (!PathIsDirectory(currentUser.id)) {
		CreateDirectory(currentUser.id,NULL);						//����һ�������֤���������ļ���
	}
	CFile newFile;
	CString newPath = _T(".\\")+currentUser.id+_T("\\")+currentUser.name;
	if (!newFile.Open(_T(".\\")+currentUser.id+'\\'+currentUser.name,CFile::modeCreate | CFile::modeWrite, NULL)) {
		return NULL;
	}
	newFile.Write(currentUser.name+_T("\r\n"),(currentUser.name.GetLength()+2)*2);		//�����µ���Ϣ�ļ�
	newFile.Write(currentUser.id+_T("\r\n"),(currentUser.id.GetLength()+2)*2);
	
	CStatic *imgctl = (CStatic *)GetDlgItem(IDC_STATIC);
	CRect rc;
	imgctl->GetWindowRect(&rc);
	//��ȡ����ͼƬ
	Mat photo = imread("../Debug/zp.bmp");
	Mat photo_scale;
	Size dsize(rc.Width(),rc.Height());
	resize(photo,photo_scale,dsize);				//�ı�ͼ��ߴ�
	imwrite("../Debug/zp_scale.bmp",photo_scale);

	CImage photo_bitmap;
	photo_bitmap.Load(_T("../Debug/zp_scale.bmp"));			//���뱳��	
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
	//DeleteFile(_T("../Debug/zp_scale.bmp"));				//ɾ��ת��֮���ͼƬ

	return NULL;
}


void CtopcoderDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//�����µ����֤��Ƭ
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
	
	//�����հױ���
	Scalar s(255,255,255);
	Mat background(128,296,CV_8UC3,s);
	USES_CONVERSION;
	char *file_path = T2A(dst_path);
	//char file_path[] = "C:\\Users\\xulingfeng\\Documents\\Visual Studio 2010\\Projects\\test\\test\\�����.bmp";
	Mat img = imread(file_path);
	if (img.empty()) {
		AfxMessageBox(_T("ͼƬ��ʧ��!"));
		return -1;
	}
	Mat background_roi(background,Rect(0,0,102,126));		//��ȡ��Ƭλ��
	img.copyTo(background_roi);								//������Ƭ
	//imshow("show",background);
	//waitKey();
	CString background_path = dst_folder+'\\'+currentUser.name+_T("background.bmp");
	imwrite(T2A(background_path),background);				//���汳��ͼƬ


	//����һ���հ�bmp�ļ�����СΪ296*128
	int background_width = 296;
	int background_height = 128;
	//�����ڴ�DC
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);

	CImage photo;
	//photo.Create(102,126,24,0);
	photo.Load(background_path);			//���뱳��	
	CBitmap bitmap;
	bitmap.DeleteObject();
	bitmap.Attach((HBITMAP)photo.operator HBITMAP());
	memDC.SelectObject(&bitmap);

	CFont font;								//��������
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
	LPCTSTR lpszFace = _T("�����п�");
	font.CreateFontW(nHeight,nWidth,nEscapement,nOrientation,fnWeight,fdwltalic,fdwUnderline,fdwStrikeOut,fdwCharSet,fdwOutputPrecision,fdwClipPrecision,fdwQuality,
		fdwPitchAndFamily,lpszFace);			//��ʼ������

	memDC.SelectObject(&font);			//ѡ������

	CRect rectName(102,18,296,54);					//�趨������
	UpdateData(true);
	CString name;
	CEdit *pName = (CEdit *)GetDlgItem(IDC_EDIT1);
	pName->GetWindowTextW(name);
	memDC.DrawTextW(name, &rectName, DT_CENTER);		//д������
	CString corp;
	CEdit *pCorp = (CEdit *)GetDlgItem(IDC_EDIT2);
	pName->GetWindowTextW(name);
	CRect rectCorp(102,72,296,108);
	memDC.DrawTextW(corp,&rectCorp,DT_CENTER | DT_CALCRECT);		//д�뵥λ
	UpdateData(false);

	UpdateData(true);
	CStatic *hint = (CStatic *)GetDlgItem(IDC_STATIC4);				//��ʾ��
	hint->SetWindowTextW(_T("����ˢ�������Ե�..."));
	UpdateData(false);

	CImage outImage;							//�������
	outImage.Create(296,128,24,0);
	CDC::FromHandle(outImage.GetDC())->BitBlt(0,0,296,128,&memDC,0,0,SRCCOPY);
	outImage.Save(background_path);				//���汳��

	Mat convert = imread(T2A(background_path));
	Mat convert_gray(128,296,CV_8UC1);
	cvtColor(convert,convert_gray,CV_BGR2GRAY);		//ת�Ҷ�ͼ
	threshold(convert_gray,convert_gray,144,255,THRESH_BINARY_INV);			//ת��ֵ��ͼ

	BYTE *buf = (BYTE *)calloc(1,296*128/8);		//תΪE-ink��ʶ��ĸ�ʽ
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
	hint->SetWindowTextW(_T("�Ѿ���"));
	UpdateData(false);

	//��Դ����
	free(buf);
	outImage.ReleaseDC();
	ReleaseDC(&memDC);
	photo.Destroy();
	outImage.Destroy();

	return 0;
}


// �������ݷ���
void CtopcoderDlg::SendImage(BYTE* Bitmap, DWORD * count)
{
	CString com = _T("COM2");
	//�򿪴���
	HANDLE hCom;
	hCom = CreateFile(com,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if (hCom == INVALID_HANDLE_VALUE) {
		AfxMessageBox(_T("open com failed\n"));
		return;
	}
	//��ʼ������
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
	
	CloseHandle(hCom);		//�رմ���
	this->SetTimer(0,500,NULL);		//��������
}

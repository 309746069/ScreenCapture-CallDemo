// CaptureTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CaptureTest.h"
#include "CaptureTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4482)
#pragma warning(disable:4311)
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCaptureTestDlg �Ի���

typedef int (*FnStartScreenCapture)(const char* szAuth, const char* szDefaultSavePath, void* pCallBack, unsigned long hWndNotice, unsigned int noticeMsg);
FnStartScreenCapture gl_StartScreenCapture = NULL;
typedef int (*FnInitScreenCapture)(unsigned long trackerColor, unsigned long editBorderColor, int nTransparent, int flag);
FnInitScreenCapture gl_InitCapture = NULL;

typedef int (*FnInitCaptureParam)(int flag, unsigned long flagvalue);
FnInitCaptureParam gl_InitCaptureParam = NULL;

//�˽ӿ����� 
typedef int (*FnSetExtendFlag)(int flag, int flagvalue);
FnSetExtendFlag gl_SetExtendFlag = NULL;

typedef enum ExtendFlagTypeEnum
{
	emPensize = 1,		//���û��ʴ�С
	emDrawType,			//��������Ѷ�����360���
	emTrackColor,		//�Զ�ʶ��ı߿����ɫ
	emEditBorderColor,	//�ı�����ı߿���ɫ
	emTransparent,		//��������͸����
	emWindowAware,		//�����Ƿ��������DPI�Ŵ�
	emDetectSubWindowRect,	//�Ƿ��Զ�����Ӵ��ڣ���ʱ���� 
	emSetSaveName,		//���ñ���ʱ�Ŀ�ʼ����
	emSetMagnifierBkColor, //���÷Ŵ󾵵ı���ɫ����������͸��
	emSetMagnifierLogoText, //���÷Ŵ��ϵ�LOGO�ַ�������ʾ��ݼ����磺 ţţ��ͼ(CTRL + SHIFT + A)
};

CCaptureTestDlg::CCaptureTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureTestDlg::IDD, pParent)
{
	//���ؽ�ͼ�ؼ�
	m_hModule = LoadLibrary("NiuniuCapture.dll");
	gl_StartScreenCapture = (FnStartScreenCapture)GetProcAddress(m_hModule, "StartScreenCapture");
	gl_InitCapture = (FnInitScreenCapture)GetProcAddress(m_hModule, "InitScreenCapture");
	gl_InitCaptureParam = (FnInitCaptureParam)GetProcAddress(m_hModule, "InitCaptureParam");


	//���ý�ͼ�߿����ʽ��Ϊ�����ϰ汾���°汾�ɲ��������� ��  
	//gl_InitCapture(RGB(255, 0, 0), RGB(0, 174, 255), 230, 2);	//���һ���������û����߿�

	
	gl_InitCaptureParam(ExtendFlagTypeEnum::emPensize, 2);	//�����߿�
	gl_InitCaptureParam(ExtendFlagTypeEnum::emDrawType, 0);	//���÷Ŵ󾵷��0�� ��Ѷ���   1�� 360��� 
	gl_InitCaptureParam(ExtendFlagTypeEnum::emTrackColor, RGB(255, 0, 0));	//�Զ�ʶ��ı߿���ɫ
	gl_InitCaptureParam(ExtendFlagTypeEnum::emEditBorderColor, RGB(0, 174, 255));	//���ֱ༭��߿���ɫ
	gl_InitCaptureParam(ExtendFlagTypeEnum::emTransparent, 240); //���ù���������͸����

	const char* szSavePath = "ţţ��ͼ";
	gl_InitCaptureParam(ExtendFlagTypeEnum::emSetSaveName, (unsigned long)szSavePath); //���ñ���ʱ�Ŀ�ʼ����
	gl_InitCaptureParam(ExtendFlagTypeEnum::emSetMagnifierBkColor, RGB(255, 255, 255)); //���÷Ŵ󾵵ı���ɫ����������͸��
	
	//���¿������÷Ŵ��ϵ�LOGO���֣���������ã�Ĭ����ʾ��ţţ��ͼ�� 
	//gl_InitCaptureParam(ExtendFlagTypeEnum::emSetMagnifierLogoText, (unsigned long)"ţţ��ͼ(Ctrl+Shift+A)");
	gl_InitCaptureParam(ExtendFlagTypeEnum::emSetMagnifierLogoText, (unsigned long)"  ��ͨ���ӿ���������");
	
	gl_InitCaptureParam(ExtendFlagTypeEnum::emWindowAware, 1); //�˺������贰�ڴ���ǰ���ã����ͬ�����´���
	//ͨ����δ�����ú�Ӧ�ó��򽫲���DPI���зŴ���������DPI�Ŵ�Ļ����ϣ���Ҫ���ô�API�� һ��Ҫ�ڴ��ڴ���ǰ���е��ã��������Ӧ�ó����ʼ��ʼ���ĵط� 
	/*
	HINSTANCE hUser32 = LoadLibrary( "user32.dll" );
	if( hUser32 )
	{
		typedef BOOL ( WINAPI* LPSetProcessDPIAware )( void );
		LPSetProcessDPIAware pSetProcessDPIAware = ( LPSetProcessDPIAware )GetProcAddress(hUser32,
			"SetProcessDPIAware" );
		if( pSetProcessDPIAware )
		{
			pSetProcessDPIAware();
		}
		FreeLibrary( hUser32 );
	}
	*/

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
}

void CCaptureTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCaptureTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER + 1111,OnCaptureFinish)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCaptureTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CCaptureTestDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CCaptureTestDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()



// CCaptureTestDlg ��Ϣ�������

BOOL CCaptureTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	CenterWindow();
	ShowWindow(SW_SHOW);

	CButton* btn = (CButton*)GetDlgItem(IDC_RADIO1);
	btn->SetCheck(TRUE);
	
	

	SetWindowText("ţţ��ͼ");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCaptureTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCaptureTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CCaptureTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HWND gl_hWnd = NULL;
void CaptureNotice(int nType)
{
	::PostMessage(gl_hWnd, WM_USER + 1111, 1, 1);
}

void CCaptureTestDlg::OnBnClickedOk()
{
	SetDlgItemText(IDC_STATIC_NOTICE, "");

	/*
	����1�Ķ������� 
	typedef enum ExtendFlagTypeEnum
	{
	emPensize = 1,
	emDrawType,	
	};
	*/
	CButton* btn = (CButton*)GetDlgItem(IDC_RADIO2);
	BOOL bCheck = btn->GetCheck();

	gl_InitCaptureParam(2, bCheck);	//����2�����壬0�� ��Ѷ���   1�� 360��� 

	//ͨ���ص�������֪ͨ��ͼ����¼�
	gl_hWnd = m_hWnd;
	gl_StartScreenCapture("niuniu", "", CaptureNotice, 0, 0);

	//ͨ�� WINDOWS ��Ϣ��֪ͨ��ͼ����¼�
	//gl_StartScreenCapture("niuniu", "", NULL, (unsigned long)m_hWnd, WM_USER + 1111);
}


LRESULT CCaptureTestDlg::OnCaptureFinish(WPARAM wParam,LPARAM lParam)
{
	if (wParam == lParam && wParam == 1)
	{
		SetDlgItemText(IDC_STATIC_NOTICE, "��ͼ���");
	}	
	return 0;
}

void CCaptureTestDlg::OnBnClickedRadio1()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_RADIO1);
	btn->SetCheck(TRUE);

	btn = (CButton*)GetDlgItem(IDC_RADIO2);
	btn->SetCheck(FALSE);
}

void CCaptureTestDlg::OnBnClickedRadio2()
{
	CButton* btn = (CButton*)GetDlgItem(IDC_RADIO1);
	btn->SetCheck(FALSE);

	btn = (CButton*)GetDlgItem(IDC_RADIO2);
	btn->SetCheck(TRUE);
}


// CDCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CDC.h"
#include "CDCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCDCDlg 对话框



CCDCDlg::CCDCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDERX, Sliderx);
	DDX_Control(pDX, IDC_SLIDERY, Slidery);

}

BEGIN_MESSAGE_MAP(CCDCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_YELLW, &CCDCDlg::OnBnClickedRadioYellw)
	ON_BN_CLICKED(IDC_RADIO_GREEN, &CCDCDlg::OnBnClickedRadioGreen)
	ON_BN_CLICKED(IDC_RADIO_RED, &CCDCDlg::OnBnClickedRadioRed)
	ON_BN_CLICKED(IDC_RADIO_DARKBULE, &CCDCDlg::OnBnClickedRadioDarkbule)
	ON_BN_CLICKED(IDC_RADIO_LIGHTBULE, &CCDCDlg::OnBnClickedRadioLightbule)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CCDCDlg 消息处理程序

BOOL CCDCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	UpdateStaticText();

	// 设置时钟频率 每秒更新一次时间
	SetTimer(1, 1000, NULL);
	// 初始化坐标
	x1 = 20;	x2 = 20;	x3 = 20;	x4 = 20;	x5 = 20;
	y1 = 20;	y2 = 20;	y3 = 20;	y4 = 20;	y5 = 20;
	Sliderx.SetRange(0, 100); // 设置 X 轴的范围
	Sliderx.SetRange(0, 100); // 设置 Y 轴的范围
	Sliderx.SetPos(20);
	Slidery.SetPos(20);
	pointx = Sliderx.GetPos();
	pointy = Slidery.GetPos();
	
	// 设置字体
	myFont.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"宋体");
	GetDlgItem(IDC_STATIC_YEAR)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC_MONTH)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC_DAY)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&myFont);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCDCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCDCDlg::OnPaint()
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
		CWnd* pWnd = GetDlgItem(IDC_STATIC_DRAW);
		CDC* dc = pWnd->GetDC();
		pWnd->Invalidate();
		pWnd->UpdateWindow();

		CRect rectView;
		CRgn rgn;
		GetDlgItem(IDC_STATIC_DRAW)->GetWindowRect(&rectView);
		ScreenToClient(&rectView);
		rgn.CreateRectRgn(rectView.left, rectView.top, rectView.right, rectView.bottom);
		dc->SelectClipRgn(&rgn);

		CPaintDC newdc(this);
		newdc.SelectClipRgn(&rgn);

		CPen pNewPen(PS_SOLID, 4, RGB(0, 0, 0));
		CBrush yellowBrush(RGB(255, 255, 0));//选中新笔
		CPen* pOldPen = newdc.SelectObject(&pNewPen);//选中新画刷

		// 绘制黄色圆形
		CBrush* pOldBrush = newdc.SelectObject(&yellowBrush);
		CRect yellowEclipse(rectView);
		yellowEclipse.left += x1;
		yellowEclipse.top += y1;
		yellowEclipse.right += x1;
		yellowEclipse.bottom += y1;
		newdc.Ellipse(yellowEclipse);
		newdc.SelectObject(pOldPen);
		newdc.SelectObject(pOldBrush);

		// 绘制红色矩形
		pOldPen = newdc.SelectObject(&pNewPen);
		CBrush redBrush(RGB(255, 0, 0));
		pOldBrush = newdc.SelectObject(&redBrush);
		CRect redRect(rectView);
		redRect.left += x2 + 80;
		redRect.top += y2 + 80;
		redRect.right += x2 - 80;
		redRect.bottom += y2 - 80;
		newdc.Rectangle(redRect);
		newdc.SelectObject(pOldBrush);

		// 绘制绿色矩形
		pOldPen = newdc.SelectObject(&pNewPen);
		CBrush greeBrush(RGB(0, 255, 0));
		pOldBrush = newdc.SelectObject(&greeBrush);
		CRect greeRect(rectView);
		greeRect.left += x3 + 100;
		greeRect.top += y3 + 100;
		greeRect.right += x3 - 100;
		greeRect.bottom += y3 - 100;
		newdc.Rectangle(greeRect);
		newdc.SelectObject(pOldBrush);

		// 绘制深蓝色矩形
		 pOldPen = newdc.SelectObject(&pNewPen);
		CBrush navyblueBrush(RGB(0, 0, 255));
		pOldBrush = newdc.SelectObject(&navyblueBrush);
		CRect navyblueRect(rectView);
		navyblueRect.left += x4 + 120;
		navyblueRect.top += y4 + 120;
		navyblueRect.right += x4 - 120;
		navyblueRect.bottom += y4 - 120;
		newdc.Rectangle(navyblueRect);
		newdc.SelectObject(pOldBrush);

		// 绘制浅蓝色圆形
		CBrush lightbrueBrush(RGB(0, 255, 255));
		pOldBrush = newdc.SelectObject(&lightbrueBrush);
		rectView.left += x5 + 120;
		rectView.top += y5 + 120;
		rectView.right += x5 - 120;
		rectView.bottom += y5 - 120;
		newdc.Ellipse(rectView);
		newdc.SelectObject(pOldBrush);

		// 绘制姓名学号
		newdc.SelectObject(&myFont);
		newdc.SetBkMode(TRANSPARENT);//设置背景透明
		newdc.TextOut(70, 230, L"姓名:王淼");
		newdc.TextOut(70, 250, L"学号：E42114038");

	}
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCDCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCDCDlg::UpdateStaticText() {
	// 获取当前系统时间
	CTime currentTime = CTime::GetCurrentTime();

	// 获取年、月、时、分、秒
	int year = currentTime.GetYear();
	int month = currentTime.GetMonth();
	int day = currentTime.GetDay();
	int hour = currentTime.GetHour();
	int minute = currentTime.GetMinute();
	int second = currentTime.GetSecond();

	// 将年、月、日、时、分、秒分别更新到对应的static text控件
	SetDlgItemInt(IDC_STATIC_YEAR, year);
	SetDlgItemInt(IDC_STATIC_MONTH, month);
	SetDlgItemInt(IDC_STATIC_DAY, day);
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"), hour, minute, second);
	SetDlgItemText(IDC_STATIC_TIME, strTime);
}



void CCDCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateStaticText();

}


HBRUSH CCDCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_YEAR)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MONTH)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_DAY)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CCDCDlg::OnBnClickedRadioYellw()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x1);
	Slidery.SetPos(y1);

	x1 = Sliderx.GetPos();
	y1 = Slidery.GetPos();
	CCDCDlg::OnPaint();
}


void CCDCDlg::OnBnClickedRadioGreen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x3);
	Slidery.SetPos(y3);

	x3 = Sliderx.GetPos();
	y3 = Slidery.GetPos();
	CCDCDlg::OnPaint();
}


void CCDCDlg::OnBnClickedRadioRed()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x2);
	Slidery.SetPos(y2);

	x2 = Sliderx.GetPos();
	y2 = Slidery.GetPos();
	CCDCDlg::OnPaint();
}


void CCDCDlg::OnBnClickedRadioDarkbule()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x4);
	Slidery.SetPos(y4);

	x4 = Sliderx.GetPos();
	y4 = Slidery.GetPos();
	CCDCDlg::OnPaint();
}


void CCDCDlg::OnBnClickedRadioLightbule()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x5);
	Slidery.SetPos(y5);

	x5 = Sliderx.GetPos();
	y5 = Slidery.GetPos();
	CCDCDlg::OnPaint();
}


void CCDCDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	pointx = Sliderx.GetPos();
	pointy = Slidery.GetPos();
	// 假设在你的对话框类中
	CButton* pRadioButtonYellow = (CButton*)GetDlgItem(IDC_RADIO_YELLW);
	CButton* pRadioButtonRed = (CButton*)GetDlgItem(IDC_RADIO_RED);
	CButton* pRadioButtonGreen = (CButton*)GetDlgItem(IDC_RADIO_GREEN);
	CButton* pRadioButtonDarkbule = (CButton*)GetDlgItem(IDC_RADIO_DARKBULE);
	CButton* pRadioButtonLightbule = (CButton*)GetDlgItem(IDC_RADIO_LIGHTBULE);

	// 获取单选框的状态
	BOOL isChecked1 = pRadioButtonYellow->GetCheck();
	BOOL isChecked2 = pRadioButtonRed->GetCheck();
	BOOL isChecked3 = pRadioButtonGreen->GetCheck();
	BOOL isChecked4 = pRadioButtonDarkbule->GetCheck();
	BOOL isChecked5 = pRadioButtonLightbule->GetCheck();

	if (isChecked1)
	{
		x1 = pointx;
		y1 = pointy;
	}

	if (isChecked2)
	{
		x2 = pointx;
		y2 = pointy;
	}
	if (isChecked3)
	{
		x3 = pointx;
		y3 = pointy;
	}
	if (isChecked4)
	{
		x4 = pointx;
		y4 = pointy;
	}
	if (isChecked5)
	{
		x5 = pointx;
		y5 = pointy;

	}
	
	Invalidate();		// 窗口重绘
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

}

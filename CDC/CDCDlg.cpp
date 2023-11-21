
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
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CTLCOLOR()
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
}

BEGIN_MESSAGE_MAP(CCDCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
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
	x1 = 20;	x2 = 20;	x3 = 20;	x4 = 20;	x5 = 20;
	y1 = 20;	y2 = 20;	y3 = 20;	y4 = 20;	y5 = 20;
	

	// 更改static text的文字格式
	m_font.CreatePointFont(150, L"宋体");
	m_static_year.SubclassDlgItem(IDC_STATIC3, this);
	m_static_year.SetFont(&m_font);
	m_static_month.SubclassDlgItem(IDC_STATIC4, this);
	m_static_month.SetFont(&m_font);
	m_static_day.SubclassDlgItem(IDC_STATIC5, this);
	m_static_day.SetFont(&m_font);


	// 获取时间
	UpdateStaticText();
	m_static_YEAR.SubclassDlgItem(IDC_STATIC_YEAR, this);
	m_static_YEAR.SetFont(&m_font);
	m_static_MONTH.SubclassDlgItem(IDC_STATIC_MONTH, this);
	m_static_MONTH.SetFont(&m_font);
	m_static_DAY.SubclassDlgItem(IDC_STATIC_DAY, this);
	m_static_DAY.SetFont(&m_font);
	m_static_TIME.SubclassDlgItem(IDC_STATIC_TIME, this);
	m_static_TIME.SetFont(&m_font);

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

		//-----布置界面，使用一个静态文本控件，调整其大小后作为你的绘图区域。------
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

		//画黄色圆形
		CBrush* pOldBrush = newdc.SelectObject(&yellowBrush);
		CRect yellowEclipse(rectView);
		yellowEclipse.left += x1;
		yellowEclipse.top += y1;
		yellowEclipse.right -= x1;
		yellowEclipse.bottom -= y1;
		newdc.Ellipse(yellowEclipse);
		newdc.SelectObject(pOldPen);
		newdc.SelectObject(pOldBrush);

		//画红色矩形
		pOldPen = newdc.SelectObject(&pNewPen);
		CBrush redBrush(RGB(255, 0, 0));
		pOldBrush = newdc.SelectObject(&redBrush);
		CRect redRect(rectView);
		redRect.left += x2 + 58;
		redRect.top += y2 + 58;
		redRect.right -= x2 + 58;
		redRect.bottom -= y2 + 58;
		newdc.Rectangle(redRect);
		newdc.SelectObject(pOldBrush);

		// 画绿色矩形
		pOldPen = newdc.SelectObject(&pNewPen);
		CBrush greeBrush(RGB(0, 255, 0));
		pOldBrush = newdc.SelectObject(&greeBrush);
		CRect greeRect(rectView);
		greeRect.left += x3 + 80;
		greeRect.top += y3 + 80;
		greeRect.right -= x3 + 80;
		greeRect.bottom -= y3 + 80;
		newdc.Rectangle(greeRect);
		newdc.SelectObject(pOldBrush);

		//画深蓝色矩形
		 pOldPen = newdc.SelectObject(&pNewPen);
		CBrush navyblueBrush(RGB(0, 0, 255));
		pOldBrush = newdc.SelectObject(&navyblueBrush);
		CRect navyblueRect(rectView);
		navyblueRect.left += x4 + 100;
		navyblueRect.top += y4 + 100;
		navyblueRect.right -= x4 + 100;
		navyblueRect.bottom -= y4 + 100;
		newdc.Rectangle(navyblueRect);
		newdc.SelectObject(pOldBrush);

		//画浅蓝色圆形
		CBrush lightbrueBrush(RGB(0, 255, 255));
		pOldBrush = newdc.SelectObject(&lightbrueBrush);
		rectView.left += x5 + 100;
		rectView.top += y5 + 100;
		rectView.right -= x5 + 100;
		rectView.bottom -= y5 + 100;
		newdc.Ellipse(rectView);
		newdc.SelectObject(pOldBrush);
	}
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCDCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//将ID为IDC_STATIC的static控件字体颜色设置为红色

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_YEAR)
	{
		pDC->SetTextColor(RGB(255, 0, 0));

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
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






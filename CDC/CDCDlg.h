
// CDCDlg.h: 头文件
//

#pragma once


// CCDCDlg 对话框
class CCDCDlg : public CDialogEx
{
// 构造
public:
	CCDCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CFont m_font;
	CStatic m_static_year;
	CStatic m_static_month;
	CStatic m_static_day;
	CStatic m_static_YEAR;
	CStatic m_static_MONTH;
	CStatic m_static_DAY;
	CStatic m_static_TIME;



// 实现
protected:
	HICON m_hIcon;

	int x1, x2, x3, x4, x5;
	int y1, y2, y3, y4, y5;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void UpdateStaticText();
	DECLARE_MESSAGE_MAP()
	
public:
	
};

﻿
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

	//自定义全局变量，用来控制图形移动
	int x1, x2, x3, x4, x5;
	int y1, y2, y3, y4, y5;
	// 自定义滑块移动距离
	int pointx, pointy;
	// 设置字体
	CFont myFont;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void UpdateStaticText();
	DECLARE_MESSAGE_MAP()
	
public:
	
	CSliderCtrl Sliderx;
	CSliderCtrl Slidery;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRadioYellw();
	afx_msg void OnBnClickedRadioGreen();
	afx_msg void OnBnClickedRadioRed();
	afx_msg void OnBnClickedRadioDarkbule();
	afx_msg void OnBnClickedRadioLightbule();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

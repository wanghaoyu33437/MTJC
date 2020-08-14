
// MFCDlg.h : 头文件
//

#pragma once


#include <opencv2/opencv.hpp>
#include "afxwin.h"


using namespace  cv;


// CMFCDlg 对话框
class CMFCDlg : public CDialogEx
{
// 构造
public:
	CMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

	//static BOOL isClose;              //程序是否结束
	VideoCapture capture;         //视频类
	Mat frame, next, xygrad,photo1, photo2, photo3, photo4, photo5;                    //用于显示的帧数
	CRect rect1,rect2,rect3,rect4, rect5, rect6;                 //控件大小
	int Max;                                   //获取两帧灰度图变化的最大值
	CString m_diff;                             //这个变量和static text绑定在一起，用于显示变化的最大值
	
	


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnEnChangeEdit1();
	CEdit miantan;
	double dengji;
	afx_msg void OnBnClickedRadio1();
};


// MFCDlg.h : ͷ�ļ�
//

#pragma once


#include <opencv2/opencv.hpp>
#include "afxwin.h"


using namespace  cv;


// CMFCDlg �Ի���
class CMFCDlg : public CDialogEx
{
// ����
public:
	CMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

	//static BOOL isClose;              //�����Ƿ����
	VideoCapture capture;         //��Ƶ��
	Mat frame, next, xygrad,photo1, photo2, photo3, photo4, photo5;                    //������ʾ��֡��
	CRect rect1,rect2,rect3,rect4, rect5, rect6;                 //�ؼ���С
	int Max;                                   //��ȡ��֡�Ҷ�ͼ�仯�����ֵ
	CString m_diff;                             //���������static text����һ��������ʾ�仯�����ֵ
	
	


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

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

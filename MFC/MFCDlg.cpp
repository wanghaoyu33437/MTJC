
#include "stdafx.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"
#include "resource.h"



#include <dlib/opencv.h>

#include <opencv2/opencv.hpp>

#include <dlib/image_processing/frontal_face_detector.h>

#include <dlib/image_processing/render_face_detections.h>

#include <dlib/image_processing.h>

#include <dlib/gui_widgets.h>



using namespace dlib;

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static BOOL isClose, isClose1, isClose2, isClose3, isClose4, isClose5;
static double ave1, ave2, ave3, ave4, ave5;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
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
END_MESSAGE_MAP()


// CMFCDlg �Ի���



CMFCDlg::CMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
	, dengji(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, miantan);
	DDX_Text(pDX, IDC_EDIT1, dengji);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_PIC2, &CMFCDlg::OnStnClickedPic2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCDlg::OnBnClickedButton7)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CMFCDlg ��Ϣ�������

BOOL CMFCDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CWnd  *pWnd1 = GetDlgItem(IDC_PIC1);     //��ȡ��ʾ����ͷ����Ĵ����ࣨ����Ϊ�ؼ�ID��
	CWnd  *pWnd2 = GetDlgItem(IDC_PIC2);      //��ȡ��ʾ�����յĴ�����             �ؼ���ָ��
	CWnd  *pWnd3 = GetDlgItem(IDC_PIC3);      //��ȡ��ʾ�����յĴ�����                     �ؼ���ָ��
	CWnd  *pWnd4 = GetDlgItem(IDC_PIC4);     //��ȡ��ʾ����ͷ����Ĵ����ࣨ����Ϊ�ؼ�ID��
	CWnd  *pWnd5 = GetDlgItem(IDC_PIC5);      //��ȡ��ʾ�����յĴ�����             �ؼ���ָ��
	CWnd  *pWnd6 = GetDlgItem(IDC_PIC6);      //��ȡ��ʾ�����յĴ�����             �ؼ���ָ��




	pWnd1->GetClientRect(&rect1);            //GetClientRectΪ���picture control�ؼ�����������С
	pWnd2->GetClientRect(&rect2);            //GetClientRectΪ���                   �ؼ�����������С
	pWnd3->GetClientRect(&rect3);
	pWnd4->GetClientRect(&rect4);
	pWnd5->GetClientRect(&rect5);
	pWnd6->GetClientRect(&rect6);

	namedWindow("f", WINDOW_AUTOSIZE);        //�������ձ���ͼ��ʾ�Ĵ�����  
	namedWindow("g", WINDOW_AUTOSIZE);        //�������ձ���ͼ��ʾ�Ĵ�����  
	namedWindow("h", WINDOW_AUTOSIZE);        //�������ձ���ͼ��ʾ�Ĵ�����  
	namedWindow("i", WINDOW_AUTOSIZE);        //�������ձ���ͼ��ʾ�Ĵ����� 
	namedWindow("j", WINDOW_AUTOSIZE);        //�������ձ���ͼ��ʾ�Ĵ����� 

	namedWindow("src", WINDOW_AUTOSIZE);         //���û�����ʾ������

	HWND hWndl = (HWND)cvGetWindowHandle("src");    //hWnd ��ʾ���ھ��,��ȡ���ھ��            opencv��������ʾ����
	HWND hWnd2 = (HWND)cvGetWindowHandle("g");
	HWND hWnd3 = (HWND)cvGetWindowHandle("f");
	HWND hWnd4 = (HWND)cvGetWindowHandle("h");
	HWND hWnd5 = (HWND)cvGetWindowHandle("i");
	HWND hWnd6 = (HWND)cvGetWindowHandle("j");


	HWND hParent1 = ::GetParent(hWndl);             //GetParent������ȡ�Ӵ��ڵĸ����ھ��
	HWND hParent2 = ::GetParent(hWnd2);
	HWND hParent3 = ::GetParent(hWnd3);
	HWND hParent4 = ::GetParent(hWnd4);
	HWND hParent5 = ::GetParent(hWnd5);
	HWND hParent6 = ::GetParent(hWnd6);




	::SetParent(hWndl, pWnd1->m_hWnd);                //���ô��ڵĸ��࣬Ҳ���ǽ����������������ؼ�����һ��	
	::SetParent(hWnd2, pWnd2->m_hWnd);	                                                 //  ������ʾ�ڿؼ���
	::SetParent(hWnd3, pWnd3->m_hWnd);	                                                 //  ������ʾ�ڿؼ���
	::SetParent(hWnd4, pWnd4->m_hWnd);                //���ô��ڵĸ��࣬Ҳ���ǽ����������������ؼ�����һ��	
	::SetParent(hWnd5, pWnd5->m_hWnd);	                                                 //  ������ʾ�ڿؼ���
	::SetParent(hWnd6, pWnd6->m_hWnd);

	capture.open(0);                              //��Ĭ������ͷ	
	capture >> frame;                               //��ȡ��һ֡

	resize(frame, frame, Size(rect1.Width(), rect1.Height()));      //���ڴ�С��ؼ���Сһ��	

	::ShowWindow(hParent1, SW_HIDE);   //���������ڵĸ����ڣ��粻���أ�������ʾ�������ڣ����ԭ���д�
	imshow("src", frame);          //�ڶԻ�������ʾ����	    ��Ϊ�Ѿ��������ڿؼ���λ������

	resize(frame, frame, Size(rect2.Width(), rect2.Height()));      //���ڴ�С��ؼ���Сһ��	
	::ShowWindow(hParent2, SW_HIDE);
	imshow("g", frame);

	resize(frame, frame, Size(rect3.Width(), rect3.Height()));      //���ڴ�С��ؼ���Сһ��	

	::ShowWindow(hParent3, SW_HIDE);
	imshow("f", frame);


	resize(frame, frame, Size(rect4.Width(), rect4.Height()));      //���ڴ�С��ؼ���Сһ��	
	::ShowWindow(hParent4, SW_HIDE);
	imshow("h", frame);


	resize(frame, frame, Size(rect5.Width(), rect5.Height()));      //���ڴ�С��ؼ���Сһ��	
	::ShowWindow(hParent5, SW_HIDE);
	imshow("i", frame);

	resize(frame, frame, Size(rect6.Width(), rect6.Height()));      //���ڴ�С��ؼ���Сһ��	
	::ShowWindow(hParent6, SW_HIDE);
	imshow("j", frame);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCDlg::OnPaint()
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
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	while (!isClose)          //isClose�����ж��Ƿ����	

	{
		capture >> next;    //��ȡÿһ֡	

		resize(next, next, Size(rect1.Width(), rect1.Height()));  //ͼƬ����Ϊ��ؼ�ͬ����	
		next.copyTo(frame);                //frame������һ֡��next��һ֡	

		cvtColor(frame, frame, COLOR_RGB2GRAY);        //תΪ�Ҷ�ͼ		

		GaussianBlur(frame, frame, Size(3, 3), 0, 0);//�ȸ�˹ģ��
		Canny(frame, frame, 60, 60 * 2, 3, false);//frame�洢canny��Ե

		Mat xgrad, ygrad, xygrad;
		Scharr(frame, xgrad, CV_16S, 1, 0);//����x�ݶ�
		Scharr(frame, ygrad, CV_16S, 0, 1);//y�ݶ�

		convertScaleAbs(xgrad, xgrad);//������Ӱ�쾫��
		convertScaleAbs(ygrad, ygrad);

		xygrad = Mat(xgrad.size(), xgrad.type());

		int width = xgrad.cols;
		int height = ygrad.rows;
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				int xg = xgrad.at<uchar>(row, col);
				int yg = ygrad.at<uchar>(row, col);
				int xy = xg + yg;//sobel���ӵĽ��ƹ�ʽ
				xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//����������һ����Χ��
			}
		}

		addWeighted(xygrad, 0.5, frame, 0.5, 0, frame);

		imshow("src", ~frame);                 //��ʾͼƬ���ı�		

		if (!isClose1) {

			resize(frame, frame, Size(rect2.Width(), rect2.Height()));      //���ڴ�С��ؼ���Сһ��	
			imshow("g", ~frame);          //�ڶԻ�������ʾ����

		}
		if (!isClose2) {

			resize(frame, frame, Size(rect3.Width(), rect3.Height()));      //���ڴ�С��ؼ���Сһ��	
			imshow("f", ~frame);          //�ڶԻ�������ʾ����

		}


		if (!isClose3) {
			resize(frame, frame, Size(rect4.Width(), rect4.Height()));      //���ڴ�С��ؼ���Сһ��	
			imshow("h", ~frame);          //�ڶԻ�������ʾ����

		}

		if (!isClose5) {
			resize(frame, frame, Size(rect6.Width(), rect6.Height()));      //���ڴ�С��ؼ���Сһ��	
			imshow("j", ~frame);          //�ڶԻ�������ʾ����

		}

		if (!isClose4) {

			resize(frame, frame, Size(rect5.Width(), rect5.Height()));      //���ڴ�С��ؼ���Сһ��	
			imshow("i", ~frame);          //�ڶԻ�������ʾ����

		}






		waitKey(30);
	}


}


void CMFCDlg::OnBnClickedButton3()
{
	isClose1 = true;	// TODO: �ڴ���ӿؼ�֪ͨ����������


	capture >> photo1;


	cvtColor(photo1, photo1, COLOR_RGB2GRAY);        //תΪ�Ҷ�ͼ		



	GaussianBlur(photo1, photo1, Size(3, 3), 0, 0);//�ȸ�˹ģ��
	Canny(photo1, photo1, 60, 60 * 2, 3, false);//frame�洢canny��Ե

	Mat xgrad, ygrad, xygrad;
	Scharr(photo1, xgrad, CV_16S, 1, 0);//����x�ݶ�
	Scharr(photo1, ygrad, CV_16S, 0, 1);//y�ݶ�

	convertScaleAbs(xgrad, xgrad);//������Ӱ�쾫��
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel���ӵĽ��ƹ�ʽ
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//����������һ����Χ��
		}
	}




	addWeighted(xygrad, 0.5, photo1, 0.5, 0, photo1);


	cv::Mat temp, temp2;
	bitwise_not(photo1, photo1);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
	compression_params.push_back(255); //�����������Ҫ��ͼƬ������255Ϊ���𱣴棬һ��Ҫ����255������ͼ��ʧ�棩
	cv::imwrite("hunhe1.jpg", photo1, compression_params);

	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	frontal_face_detector detector = get_frontal_face_detector();


	temp = cv::imread("hunhe1.jpg");

	cvtColor(temp, temp, CV_RGB2GRAY);

	cvtColor(temp, temp, CV_GRAY2RGB);

	cv_image<bgr_pixel> cimg(temp);

	//cv::imwrite("gray.jpg", temp2);
	std::vector<dlib::rectangle> faces = detector(cimg);
	//std::vector<rectangle> facess = detector(cimg1);
	// Find the pose of each face.
	std::vector<full_object_detection> shapes;

	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	if (!shapes.empty()) {

		for (int i = 0; i < 68; i++) {
			if (i >= 17 && i <= 59) {//36���۽�45���۽�48�����54�����

				circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}


		resize(temp, temp, Size(rect2.Width(), rect2.Height()));      //���ڴ�С��ؼ���Сһ��	
		int L1[8], R1[8];

		//�ڶ�����������ߵ�
		L1[2] = shapes[0].part(37).y();
		R1[2] = shapes[0].part(44).y();
		//����������ü��͵�
		L1[3] = shapes[0].part(41).y();
		R1[3] = shapes[0].part(46).y();

		ave1 = abs((L1[3] - L1[2]) - (R1[3] - R1[2]));
		dengji = ave1;
		UpdateData(FALSE);
		imshow("g", temp);
		waitKey(0);
	}

}


void CMFCDlg::OnBnClickedButton4()
{

	isClose3 = true;	// TODO: �ڴ���ӿؼ�֪ͨ����������


	capture >> photo3;


	cvtColor(photo3, photo3, COLOR_RGB2GRAY);        //תΪ�Ҷ�ͼ		



	GaussianBlur(photo3, photo3, Size(3, 3), 0, 0);//�ȸ�˹ģ��
	Canny(photo3, photo3, 60, 60 * 2, 3, false);//frame�洢canny��Ե

	Mat xgrad, ygrad, xygrad;
	Scharr(photo3, xgrad, CV_16S, 1, 0);//����x�ݶ�
	Scharr(photo3, ygrad, CV_16S, 0, 1);//y�ݶ�

	convertScaleAbs(xgrad, xgrad);//������Ӱ�쾫��
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel���ӵĽ��ƹ�ʽ
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//����������һ����Χ��
		}
	}

	addWeighted(xygrad, 0.5, photo3, 0.5, 0, photo3);


	cv::Mat temp, temp2;
	bitwise_not(photo3, photo3);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
	compression_params.push_back(255); //�����������Ҫ��ͼƬ������255Ϊ���𱣴棬һ��Ҫ����255������ͼ��ʧ�棩
	cv::imwrite("hunhe3.jpg", photo3, compression_params);

	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	frontal_face_detector detector = get_frontal_face_detector();


	temp = cv::imread("hunhe3.jpg");

	cvtColor(temp, temp, CV_RGB2GRAY);

	cvtColor(temp, temp, CV_GRAY2RGB);

	cv_image<bgr_pixel> cimg(temp);
	std::vector<dlib::rectangle> faces = detector(cimg);
	std::vector<full_object_detection> shapes;

	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	if (!shapes.empty()) {

		for (int i = 0; i < 68; i++) {
			if (i >= 17 && i <= 59) {//36���۽�45���۽�48�����54�����

				circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}

		resize(temp, temp, Size(rect4.Width(), rect4.Height()));      //���ڴ�С��ؼ���Сһ��	

		int L[8], R[8];
		//�������������ڽǵ�
		L[5] = shapes[0].part(39).y();
		R[5] = shapes[0].part(42).y();
		//���������������
		L[7] = shapes[0].part(32).y();
		R[7] = shapes[0].part(34).y();
		ave3 = abs((L[7] - L[5]) - (R[7] - R[5]));
		imshow("h", temp);
		dengji = ave3;
		UpdateData(FALSE);
		waitKey(0);
	}


}


void CMFCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	isClose2 = true;	// TODO: �ڴ���ӿؼ�֪ͨ����������


	capture >> photo2;


	cvtColor(photo2, photo2, COLOR_RGB2GRAY);        //תΪ�Ҷ�ͼ		



	GaussianBlur(photo2, photo2, Size(3, 3), 0, 0);//�ȸ�˹ģ��
	Canny(photo2, photo2, 50, 50 * 2, 3, false);//frame�洢canny��Ե

	Mat xgrad, ygrad, xygrad;
	Scharr(photo2, xgrad, CV_16S, 1, 0);//����x�ݶ�
	Scharr(photo2, ygrad, CV_16S, 0, 1);//y�ݶ�

	convertScaleAbs(xgrad, xgrad);//������Ӱ�쾫��
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel���ӵĽ��ƹ�ʽ
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//����������һ����Χ��
		}
	}

	addWeighted(xygrad, 0.5, photo2, 0.5, 0, photo2);

	cv::Mat temp3;
	bitwise_not(photo2, photo2);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
	compression_params.push_back(255); //�����������Ҫ��ͼƬ������255Ϊ���𱣴棬һ��Ҫ����255������ͼ��ʧ�棩
	cv::imwrite("hunhe2.jpg", photo2, compression_params);

	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	frontal_face_detector detector = get_frontal_face_detector();


	temp3 = cv::imread("hunhe2.jpg");

	cvtColor(temp3, temp3, CV_RGB2GRAY);
	cvtColor(temp3, temp3, CV_GRAY2RGB);

	cv_image<bgr_pixel> cimg(temp3);
	std::vector<dlib::rectangle> faces = detector(cimg);
	std::vector<full_object_detection> shapes;


	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	if (!shapes.empty()) {
		for (int i = 0; i < 68; i++) {
			if (i >= 17 && i <= 59) {//36���۽�45���۽�48�����54�����

				circle(temp3, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}


		resize(temp3, temp3, Size(rect2.Width(), rect2.Height()));      //���ڴ�С��ؼ���Сһ��	
																		//�ڶԻ�������ʾ����	

		int L1[8], R1[8];
		//��һ������ü��ߵ�
		L1[1] = shapes[0].part(19).y();
		R1[1] = shapes[0].part(24).y();
		;
		//����������ü��͵�
		L1[3] = shapes[0].part(41).y();
		R1[3] = shapes[0].part(46).y();

		ave2 = abs((L1[3] - L1[1]) - (R1[3] - R1[1]));
		dengji = ave2;
		UpdateData(FALSE);

		imshow("f", temp3);

		waitKey(0);
	}

}
void CMFCDlg::OnStnClickedPic2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isClose4 = true;	// TODO: �ڴ���ӿؼ�֪ͨ����������
	capture >> photo4;
	cvtColor(photo4, photo4, COLOR_RGB2GRAY);        //תΪ�Ҷ�ͼ		
	GaussianBlur(photo4, photo4, Size(3, 3), 0, 0);//�ȸ�˹ģ��
	Canny(photo4, photo4, 60, 60 * 2, 3, false);//frame�洢canny��Ե

	Mat xgrad, ygrad, xygrad;
	Scharr(photo4, xgrad, CV_16S, 1, 0);//����x�ݶ�
	Scharr(photo4, ygrad, CV_16S, 0, 1);//y�ݶ�

	convertScaleAbs(xgrad, xgrad);//������Ӱ�쾫��
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel���ӵĽ��ƹ�ʽ
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//����������һ����Χ��
		}
	}

	addWeighted(xygrad, 0.5, photo4, 0.5, 0, photo4);

	cv::Mat temp10;
	bitwise_not(photo4, photo4);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
	compression_params.push_back(255); //�����������Ҫ��ͼƬ������255Ϊ���𱣴棬һ��Ҫ����255������ͼ��ʧ�棩
	cv::imwrite("hunhe11.jpg", photo4, compression_params);

	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	frontal_face_detector detector = get_frontal_face_detector();


	photo4 = cv::imread("hunhe11.jpg");

	cvtColor(photo4, photo4, CV_RGB2GRAY);
	cvtColor(photo4, photo4, CV_GRAY2RGB);

	cv_image<bgr_pixel> cimg(photo4);
	std::vector<dlib::rectangle> faces = detector(cimg);
	std::vector<full_object_detection> shapes;


	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	if (!shapes.empty()) {
		for (int i = 0; i < 68; i++) {
			if (i >= 17 && i <= 59) {//36���۽�45���۽�48�����54�����

				circle(photo4, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}

		resize(photo4, photo4, Size(rect5.Width(), rect5.Height()));      //���ڴ�С��ؼ���Сһ��	
																		  //��������������ǵ�
		int L[8], R[8];

		//��������������ǵ�
		L[4] = shapes[0].part(36).y();
		R[4] = shapes[0].part(45).y();
		//���������������
		L[7] = shapes[0].part(32).y();
		R[7] = shapes[0].part(34).y();

		ave4 = abs((L[7] - L[4]) - (R[7] - R[4]));
		imshow("i", photo4);
		dengji = ave4;
		UpdateData(FALSE);
		waitKey(0);
	}

}


void CMFCDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	isClose5 = true;	// TODO: �ڴ���ӿؼ�֪ͨ����������
	capture >> photo5;
	cvtColor(photo5, photo5, COLOR_RGB2GRAY);        //תΪ�Ҷ�ͼ		
	GaussianBlur(photo5, photo5, Size(3, 3), 0, 0);//�ȸ�˹ģ��
	Canny(photo5, photo5, 60, 60 * 2, 3, false);//frame�洢canny��Ե

	Mat xgrad, ygrad, xygrad;
	Scharr(photo5, xgrad, CV_16S, 1, 0);//����x�ݶ�
	Scharr(photo5, ygrad, CV_16S, 0, 1);//y�ݶ�

	convertScaleAbs(xgrad, xgrad);//������Ӱ�쾫��
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel���ӵĽ��ƹ�ʽ
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//����������һ����Χ��
		}
	}



	addWeighted(xygrad, 0.5, photo5, 0.5, 0, photo5);



	cv::Mat temp9;
	bitwise_not(photo5, photo5);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
	compression_params.push_back(255); //�����������Ҫ��ͼƬ������255Ϊ���𱣴棬һ��Ҫ����255������ͼ��ʧ�棩
	cv::imwrite("hunhe5.jpg", photo5, compression_params);

	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	frontal_face_detector detector = get_frontal_face_detector();


	photo5 = cv::imread("hunhe5.jpg");

	cvtColor(photo5, photo5, CV_RGB2GRAY);
	cvtColor(photo5, photo5, CV_GRAY2RGB);

	cv_image<bgr_pixel> cimg(photo5);
	std::vector<dlib::rectangle> faces = detector(cimg);
	std::vector<full_object_detection> shapes;


	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	if (!shapes.empty()) {
		for (int i = 0; i < 68; i++) {
			if (i >= 17 && i <= 59) {//36���۽�45���۽�48�����54�����

				circle(photo5, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}

		resize(photo5, photo5, Size(rect6.Width(), rect6.Height()));      //���ڴ�С��ؼ���Сһ��	
																		  //�ڶԻ�������ʾ����	


		int L[8], R[8];

		//�������������ڽǵ�
		L[5] = shapes[0].part(39).y();
		R[5] = shapes[0].part(42).y();
		//�������������ǵ�
		L[6] = shapes[0].part(31).y();
		R[6] = shapes[0].part(35).y();
		ave5 = abs((L[6] - L[5]) - (R[6] - R[5]));
		imshow("j", photo5);
		dengji = ave5;
		UpdateData(FALSE);

		waitKey(0);
	}





}


void CMFCDlg::OnBnClickedButton7()
{
	double ave6 = 0.0;
	//ave6 = (ave1 + ave2 + ave3 + ave4 + ave5) / 5;
	dengji = (double)(ave1 + ave2 + ave3 + ave4 + ave5) / 5;
	/*CString str ;
	str.Format(_T("%5.3d"),ave6);
	miantan.SetWindowText(str);
	*/
	UpdateData(FALSE);



}





void CMFCDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


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
END_MESSAGE_MAP()


// CMFCDlg 对话框



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


// CMFCDlg 消息处理程序

BOOL CMFCDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	CWnd  *pWnd1 = GetDlgItem(IDC_PIC1);     //获取显示摄像头画面的窗口类（参数为控件ID）
	CWnd  *pWnd2 = GetDlgItem(IDC_PIC2);      //获取显示的拍照的窗口类             控件的指针
	CWnd  *pWnd3 = GetDlgItem(IDC_PIC3);      //获取显示的拍照的窗口类                     控件的指针
	CWnd  *pWnd4 = GetDlgItem(IDC_PIC4);     //获取显示摄像头画面的窗口类（参数为控件ID）
	CWnd  *pWnd5 = GetDlgItem(IDC_PIC5);      //获取显示的拍照的窗口类             控件的指针
	CWnd  *pWnd6 = GetDlgItem(IDC_PIC6);      //获取显示的拍照的窗口类             控件的指针




	pWnd1->GetClientRect(&rect1);            //GetClientRect为获得picture control控件自身的坐标大小
	pWnd2->GetClientRect(&rect2);            //GetClientRect为获得                   控件自身的坐标大小
	pWnd3->GetClientRect(&rect3);
	pWnd4->GetClientRect(&rect4);
	pWnd5->GetClientRect(&rect5);
	pWnd6->GetClientRect(&rect6);

	namedWindow("f", WINDOW_AUTOSIZE);        //设置拍照表情图显示的窗口名  
	namedWindow("g", WINDOW_AUTOSIZE);        //设置拍照表情图显示的窗口名  
	namedWindow("h", WINDOW_AUTOSIZE);        //设置拍照表情图显示的窗口名  
	namedWindow("i", WINDOW_AUTOSIZE);        //设置拍照表情图显示的窗口名 
	namedWindow("j", WINDOW_AUTOSIZE);        //设置拍照表情图显示的窗口名 

	namedWindow("src", WINDOW_AUTOSIZE);         //设置画面显示窗口名

	HWND hWndl = (HWND)cvGetWindowHandle("src");    //hWnd 表示窗口句柄,获取窗口句柄            opencv本来的显示窗口
	HWND hWnd2 = (HWND)cvGetWindowHandle("g");
	HWND hWnd3 = (HWND)cvGetWindowHandle("f");
	HWND hWnd4 = (HWND)cvGetWindowHandle("h");
	HWND hWnd5 = (HWND)cvGetWindowHandle("i");
	HWND hWnd6 = (HWND)cvGetWindowHandle("j");


	HWND hParent1 = ::GetParent(hWndl);             //GetParent函数获取子窗口的父窗口句柄
	HWND hParent2 = ::GetParent(hWnd2);
	HWND hParent3 = ::GetParent(hWnd3);
	HWND hParent4 = ::GetParent(hWnd4);
	HWND hParent5 = ::GetParent(hWnd5);
	HWND hParent6 = ::GetParent(hWnd6);




	::SetParent(hWndl, pWnd1->m_hWnd);                //设置窗口的父类，也就是将两个窗口与两个控件绑定在一起	
	::SetParent(hWnd2, pWnd2->m_hWnd);	                                                 //  窗口显示在控件上
	::SetParent(hWnd3, pWnd3->m_hWnd);	                                                 //  窗口显示在控件上
	::SetParent(hWnd4, pWnd4->m_hWnd);                //设置窗口的父类，也就是将两个窗口与两个控件绑定在一起	
	::SetParent(hWnd5, pWnd5->m_hWnd);	                                                 //  窗口显示在控件上
	::SetParent(hWnd6, pWnd6->m_hWnd);

	capture.open(0);                              //打开默认摄像头	
	capture >> frame;                               //获取第一帧

	resize(frame, frame, Size(rect1.Width(), rect1.Height()));      //调节大小与控件大小一致	

	::ShowWindow(hParent1, SW_HIDE);   //隐藏两窗口的父窗口，如不隐藏，将会显示两个窗口，这个原因有待
	imshow("src", frame);          //在对话框中显示窗口	    因为已经控制了在控件的位置上面

	resize(frame, frame, Size(rect2.Width(), rect2.Height()));      //调节大小与控件大小一致	
	::ShowWindow(hParent2, SW_HIDE);
	imshow("g", frame);

	resize(frame, frame, Size(rect3.Width(), rect3.Height()));      //调节大小与控件大小一致	

	::ShowWindow(hParent3, SW_HIDE);
	imshow("f", frame);


	resize(frame, frame, Size(rect4.Width(), rect4.Height()));      //调节大小与控件大小一致	
	::ShowWindow(hParent4, SW_HIDE);
	imshow("h", frame);


	resize(frame, frame, Size(rect5.Width(), rect5.Height()));      //调节大小与控件大小一致	
	::ShowWindow(hParent5, SW_HIDE);
	imshow("i", frame);

	resize(frame, frame, Size(rect6.Width(), rect6.Height()));      //调节大小与控件大小一致	
	::ShowWindow(hParent6, SW_HIDE);
	imshow("j", frame);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDlg::OnPaint()
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
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码


	while (!isClose)          //isClose用于判断是否结束	

	{
		capture >> next;    //获取每一帧	

		resize(next, next, Size(rect1.Width(), rect1.Height()));  //图片缩放为与控件同样大	
		next.copyTo(frame);                //frame代表上一帧，next下一帧	

		cvtColor(frame, frame, COLOR_RGB2GRAY);        //转为灰度图		

		GaussianBlur(frame, frame, Size(3, 3), 0, 0);//先高斯模糊
		Canny(frame, frame, 60, 60 * 2, 3, false);//frame存储canny边缘

		Mat xgrad, ygrad, xygrad;
		Scharr(frame, xgrad, CV_16S, 1, 0);//计算x梯度
		Scharr(frame, ygrad, CV_16S, 0, 1);//y梯度

		convertScaleAbs(xgrad, xgrad);//不做会影响精度
		convertScaleAbs(ygrad, ygrad);

		xygrad = Mat(xgrad.size(), xgrad.type());

		int width = xgrad.cols;
		int height = ygrad.rows;
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				int xg = xgrad.at<uchar>(row, col);
				int yg = ygrad.at<uchar>(row, col);
				int xy = xg + yg;//sobel算子的近似公式
				xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//像素限制在一个范围内
			}
		}

		addWeighted(xygrad, 0.5, frame, 0.5, 0, frame);

		imshow("src", ~frame);                 //显示图片至文本		

		if (!isClose1) {

			resize(frame, frame, Size(rect2.Width(), rect2.Height()));      //调节大小与控件大小一致	
			imshow("g", ~frame);          //在对话框中显示窗口

		}
		if (!isClose2) {

			resize(frame, frame, Size(rect3.Width(), rect3.Height()));      //调节大小与控件大小一致	
			imshow("f", ~frame);          //在对话框中显示窗口

		}


		if (!isClose3) {
			resize(frame, frame, Size(rect4.Width(), rect4.Height()));      //调节大小与控件大小一致	
			imshow("h", ~frame);          //在对话框中显示窗口

		}

		if (!isClose5) {
			resize(frame, frame, Size(rect6.Width(), rect6.Height()));      //调节大小与控件大小一致	
			imshow("j", ~frame);          //在对话框中显示窗口

		}

		if (!isClose4) {

			resize(frame, frame, Size(rect5.Width(), rect5.Height()));      //调节大小与控件大小一致	
			imshow("i", ~frame);          //在对话框中显示窗口

		}






		waitKey(30);
	}


}


void CMFCDlg::OnBnClickedButton3()
{
	isClose1 = true;	// TODO: 在此添加控件通知处理程序代码


	capture >> photo1;


	cvtColor(photo1, photo1, COLOR_RGB2GRAY);        //转为灰度图		



	GaussianBlur(photo1, photo1, Size(3, 3), 0, 0);//先高斯模糊
	Canny(photo1, photo1, 60, 60 * 2, 3, false);//frame存储canny边缘

	Mat xgrad, ygrad, xygrad;
	Scharr(photo1, xgrad, CV_16S, 1, 0);//计算x梯度
	Scharr(photo1, ygrad, CV_16S, 0, 1);//y梯度

	convertScaleAbs(xgrad, xgrad);//不做会影响精度
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel算子的近似公式
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//像素限制在一个范围内
		}
	}




	addWeighted(xygrad, 0.5, photo1, 0.5, 0, photo1);


	cv::Mat temp, temp2;
	bitwise_not(photo1, photo1);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(255); //在这个填入你要的图片质量（255为无损保存，一定要进行255，否则图像失真）
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
			if (i >= 17 && i <= 59) {//36左眼角45右眼角48左嘴角54右嘴角

				circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}


		resize(temp, temp, Size(rect2.Width(), rect2.Height()));      //调节大小与控件大小一致	
		int L1[8], R1[8];

		//第二特征点眼最高点
		L1[2] = shapes[0].part(37).y();
		R1[2] = shapes[0].part(44).y();
		//第三特征点眉最低点
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

	isClose3 = true;	// TODO: 在此添加控件通知处理程序代码


	capture >> photo3;


	cvtColor(photo3, photo3, COLOR_RGB2GRAY);        //转为灰度图		



	GaussianBlur(photo3, photo3, Size(3, 3), 0, 0);//先高斯模糊
	Canny(photo3, photo3, 60, 60 * 2, 3, false);//frame存储canny边缘

	Mat xgrad, ygrad, xygrad;
	Scharr(photo3, xgrad, CV_16S, 1, 0);//计算x梯度
	Scharr(photo3, ygrad, CV_16S, 0, 1);//y梯度

	convertScaleAbs(xgrad, xgrad);//不做会影响精度
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel算子的近似公式
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//像素限制在一个范围内
		}
	}

	addWeighted(xygrad, 0.5, photo3, 0.5, 0, photo3);


	cv::Mat temp, temp2;
	bitwise_not(photo3, photo3);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(255); //在这个填入你要的图片质量（255为无损保存，一定要进行255，否则图像失真）
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
			if (i >= 17 && i <= 59) {//36左眼角45右眼角48左嘴角54右嘴角

				circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}

		resize(temp, temp, Size(rect4.Width(), rect4.Height()));      //调节大小与控件大小一致	

		int L[8], R[8];
		//第五特征点眼内角点
		L[5] = shapes[0].part(39).y();
		R[5] = shapes[0].part(42).y();
		//第七特征点外嘴角
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
	// TODO: 在此添加控件通知处理程序代码


	isClose2 = true;	// TODO: 在此添加控件通知处理程序代码


	capture >> photo2;


	cvtColor(photo2, photo2, COLOR_RGB2GRAY);        //转为灰度图		



	GaussianBlur(photo2, photo2, Size(3, 3), 0, 0);//先高斯模糊
	Canny(photo2, photo2, 50, 50 * 2, 3, false);//frame存储canny边缘

	Mat xgrad, ygrad, xygrad;
	Scharr(photo2, xgrad, CV_16S, 1, 0);//计算x梯度
	Scharr(photo2, ygrad, CV_16S, 0, 1);//y梯度

	convertScaleAbs(xgrad, xgrad);//不做会影响精度
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel算子的近似公式
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//像素限制在一个范围内
		}
	}

	addWeighted(xygrad, 0.5, photo2, 0.5, 0, photo2);

	cv::Mat temp3;
	bitwise_not(photo2, photo2);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(255); //在这个填入你要的图片质量（255为无损保存，一定要进行255，否则图像失真）
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
			if (i >= 17 && i <= 59) {//36左眼角45右眼角48左嘴角54右嘴角

				circle(temp3, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}


		resize(temp3, temp3, Size(rect2.Width(), rect2.Height()));      //调节大小与控件大小一致	
																		//在对话框中显示窗口	

		int L1[8], R1[8];
		//第一特征点眉最高点
		L1[1] = shapes[0].part(19).y();
		R1[1] = shapes[0].part(24).y();
		;
		//第三特征点眉最低点
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
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	isClose4 = true;	// TODO: 在此添加控件通知处理程序代码
	capture >> photo4;
	cvtColor(photo4, photo4, COLOR_RGB2GRAY);        //转为灰度图		
	GaussianBlur(photo4, photo4, Size(3, 3), 0, 0);//先高斯模糊
	Canny(photo4, photo4, 60, 60 * 2, 3, false);//frame存储canny边缘

	Mat xgrad, ygrad, xygrad;
	Scharr(photo4, xgrad, CV_16S, 1, 0);//计算x梯度
	Scharr(photo4, ygrad, CV_16S, 0, 1);//y梯度

	convertScaleAbs(xgrad, xgrad);//不做会影响精度
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel算子的近似公式
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//像素限制在一个范围内
		}
	}

	addWeighted(xygrad, 0.5, photo4, 0.5, 0, photo4);

	cv::Mat temp10;
	bitwise_not(photo4, photo4);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(255); //在这个填入你要的图片质量（255为无损保存，一定要进行255，否则图像失真）
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
			if (i >= 17 && i <= 59) {//36左眼角45右眼角48左嘴角54右嘴角

				circle(photo4, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}

		resize(photo4, photo4, Size(rect5.Width(), rect5.Height()));      //调节大小与控件大小一致	
																		  //第四特征点眼外角点
		int L[8], R[8];

		//第四特征点眼外角点
		L[4] = shapes[0].part(36).y();
		R[4] = shapes[0].part(45).y();
		//第七特征点外嘴角
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
	// TODO: 在此添加控件通知处理程序代码

	isClose5 = true;	// TODO: 在此添加控件通知处理程序代码
	capture >> photo5;
	cvtColor(photo5, photo5, COLOR_RGB2GRAY);        //转为灰度图		
	GaussianBlur(photo5, photo5, Size(3, 3), 0, 0);//先高斯模糊
	Canny(photo5, photo5, 60, 60 * 2, 3, false);//frame存储canny边缘

	Mat xgrad, ygrad, xygrad;
	Scharr(photo5, xgrad, CV_16S, 1, 0);//计算x梯度
	Scharr(photo5, ygrad, CV_16S, 0, 1);//y梯度

	convertScaleAbs(xgrad, xgrad);//不做会影响精度
	convertScaleAbs(ygrad, ygrad);

	xygrad = Mat(xgrad.size(), xgrad.type());

	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;//sobel算子的近似公式
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);//像素限制在一个范围内
		}
	}



	addWeighted(xygrad, 0.5, photo5, 0.5, 0, photo5);



	cv::Mat temp9;
	bitwise_not(photo5, photo5);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(255); //在这个填入你要的图片质量（255为无损保存，一定要进行255，否则图像失真）
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
			if (i >= 17 && i <= 59) {//36左眼角45右眼角48左嘴角54右嘴角

				circle(photo5, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);

			}

		}

		resize(photo5, photo5, Size(rect6.Width(), rect6.Height()));      //调节大小与控件大小一致	
																		  //在对话框中显示窗口	


		int L[8], R[8];

		//第五特征点眼内角点
		L[5] = shapes[0].part(39).y();
		R[5] = shapes[0].part(42).y();
		//第六特征点鼻外角点
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}

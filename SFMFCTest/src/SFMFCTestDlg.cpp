#include "stdafx.h"
#include "SFMFCTest.h"
#include "SFMFCTestDlg.h"
#include "afxdialogex.h"
#include "../res/resource.h"

#include <iostream>

using namespace std;
using namespace cv;
using namespace seeta;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CV_VERSION_ID CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) \
  CVAUX_STR(CV_SUBMINOR_VERSION)

#ifdef _DEBUG
#define cvLIB(name) "opencv_" name CV_VERSION_ID "d"
#else
#define cvLIB(name) "opencv_" name CV_VERSION_ID
#endif //_DEBUG

#pragma comment( lib, cvLIB("core") )
#pragma comment( lib, cvLIB("imgproc") )
#pragma comment( lib, cvLIB("highgui") )

#define TEST(major, minor) major##_##minor##_Tester()
#define EXPECT_NE(a, b) if ((a) == (b)) std::cout << "ERROR: "
#define EXPECT_EQ(a, b) if ((a) != (b)) std::cout << "ERROR: "

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


// CSFMFCTestDlg 对话框
CSFMFCTestDlg::CSFMFCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSFMFCTestDlg::IDD, pParent)
	, m_sModelPath("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSFMFCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IMG_PATH01, m_edtImgPath01);
	DDX_Control(pDX, IDC_EDIT_IMG_PATH02, m_edtImgPath02);
	DDX_Control(pDX, IDC_EDIT_MODEL_PATH, m_edtModelPath);
}

BEGIN_MESSAGE_MAP(CSFMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMG01, &CSFMFCTestDlg::OnBnClickedImg01)
	ON_BN_CLICKED(IDC_BTN_IMG02, &CSFMFCTestDlg::OnBnClickedImg02)
	ON_BN_CLICKED(IDC_BTN_MODELPATH, &CSFMFCTestDlg::OnBnClickedBtnModelpath)
	ON_BN_CLICKED(IMG_COMPARE, &CSFMFCTestDlg::OnBnClickedCompare)
	ON_BN_CLICKED(IDCANCEL, &CSFMFCTestDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSFMFCTestDlg 消息处理程序

BOOL CSFMFCTestDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSFMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSFMFCTestDlg::OnPaint()
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
HCURSOR CSFMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
  
void CSFMFCTestDlg::OnBnClickedImg01()
{  	   
	SetImgPath(1); 
}

void CSFMFCTestDlg::OnBnClickedImg02()
{
	SetImgPath(2);
}
void CSFMFCTestDlg::OnBnClickedBtnModelpath()
{
	CString sPath = SelectFolderPath();
	if (sPath.GetLength() > 0) {
		m_sModelPath = CStringA(sPath);
		SetDlgItemTextA(IDC_EDIT_MODEL_PATH, m_sModelPath.c_str());
	}
}

void CSFMFCTestDlg::OnBnClickedCompare()
{
	DWORD dwAttrib = GetFileAttributesA(m_sModelPath.c_str());
	if (!(INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))) {
		m_edtModelPath.SetFocus();
		m_edtModelPath.SetWindowText(_T("请选择模型存放路径"));
		return;
	}

	CString p2;
	GetDlgItemText(IDC_EDIT_IMG_PATH01, p2);

	if (m_matFace01.empty()) {
		m_edtImgPath01.SetFocus();
		MessageBox(_T("图片1有误"), _T("图片读入错误"), MB_ICONERROR);
		return;
	}

	if (m_matFace02.empty()) {
		m_edtImgPath02.SetFocus();
		MessageBox(_T("图片2有误"), _T("图片读入错误"), MB_ICONERROR);
		return;
	}

	float sim = CalcSimilarity(m_sModelPath, m_matFace01, m_matFace02);
	CString tSim;
	tSim.Format(_T("%.2f"), sim);
	SetDlgItemText(IDC_SIM, tSim);
}


void CSFMFCTestDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

float CSFMFCTestDlg::CalcSimilarity(std::string sModelPath, Mat vFaceMat1, Mat vFaceMat2)
{
	if (vFaceMat1.empty() || vFaceMat2.empty()){
		return -1;
	}
	
	DWORD dwAttrib = GetFileAttributesA(sModelPath.c_str());
	if (!(INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))) {
		return -2;
	}

	// Initialize face detection model
	seeta::FaceDetection detector((sModelPath + "\\seeta_fd_frontal_v1.0.bin").c_str());
	detector.SetMinFaceSize(40);
	detector.SetScoreThresh(2.f);
	detector.SetImagePyramidScaleFactor(0.8f);
	detector.SetWindowStep(4, 4);

	// Initialize face alignment model 
	seeta::FaceAlignment point_detector((sModelPath + "\\seeta_fa_v1.1.bin").c_str());

	// Initialize face Identification model 
	FaceIdentification face_recognizer((sModelPath + "\\seeta_fr_v1.0.bin").c_str());

	//load image
	cv::Mat gallery_img_color = vFaceMat1;
	cv::Mat gallery_img_gray;
	cv::cvtColor(gallery_img_color, gallery_img_gray, CV_BGR2GRAY);

	cv::Mat probe_img_color = vFaceMat2;
	cv::Mat probe_img_gray;
	cv::cvtColor(probe_img_color, probe_img_gray, CV_BGR2GRAY);

	//cv::imshow("gallery_img_gray", gallery_img_gray);
	//cv::imshow("probe_img_gray", probe_img_gray);

	ImageData gallery_img_data_color(gallery_img_color.cols, gallery_img_color.rows, gallery_img_color.channels());
	gallery_img_data_color.data = gallery_img_color.data;

	ImageData gallery_img_data_gray(gallery_img_gray.cols, gallery_img_gray.rows, gallery_img_gray.channels());
	gallery_img_data_gray.data = gallery_img_gray.data;

	ImageData probe_img_data_color(probe_img_color.cols, probe_img_color.rows, probe_img_color.channels());
	probe_img_data_color.data = probe_img_color.data;

	ImageData probe_img_data_gray(probe_img_gray.cols, probe_img_gray.rows, probe_img_gray.channels());
	probe_img_data_gray.data = probe_img_gray.data;

	// Detect faces
	std::vector<seeta::FaceInfo> gallery_faces = detector.Detect(gallery_img_data_gray);
	int32_t gallery_face_num = static_cast<int32_t>(gallery_faces.size());

	std::vector<seeta::FaceInfo> probe_faces = detector.Detect(probe_img_data_gray);
	int32_t probe_face_num = static_cast<int32_t>(probe_faces.size());

	cout << "gallery_face_num = " << gallery_face_num << ", probe_face_num=" << probe_face_num << endl;
	if (gallery_face_num == 0 || probe_face_num == 0)
	{
		std::cout << "Faces are not detected.";
		return 0;
	}

	// Detect 5 facial landmarks
	seeta::FacialLandmark gallery_points[5];
	point_detector.PointDetectLandmarks(gallery_img_data_gray, gallery_faces[0], gallery_points);

	seeta::FacialLandmark probe_points[5];
	point_detector.PointDetectLandmarks(probe_img_data_gray, probe_faces[0], probe_points);

	for (int i = 0; i<5; i++)
	{
		cv::circle(gallery_img_color, cv::Point(gallery_points[i].x, gallery_points[i].y), 2,
			CV_RGB(0, 255, 0));

		cv::circle(probe_img_color, cv::Point(probe_points[i].x, probe_points[i].y), 2,
			CV_RGB(0, 255, 0));
	}
	cv::imwrite("gallery_point_result.jpg", gallery_img_color);
	cv::imwrite("probe_point_result.jpg", probe_img_color);
	//cv::imshow("gallery_img_color", gallery_img_color);
	//cv::imshow("probe_img_color", probe_img_color);
 
	ShowMat(gallery_img_color, IDC_PIC1);
	ShowMat(probe_img_color, IDC_PIC2);

	// Extract face identity feature
	float gallery_fea[2048];
	float probe_fea[2048];
	face_recognizer.ExtractFeatureWithCrop(gallery_img_data_color, gallery_points, gallery_fea);
	face_recognizer.ExtractFeatureWithCrop(probe_img_data_color, probe_points, probe_fea);

	// Caculate similarity of two faces
	float sim = face_recognizer.CalcSimilarity(gallery_fea, probe_fea);
	std::cout << "sim=" << sim << endl;

	return sim;
}

void CSFMFCTestDlg::SetImgPath(int nImgNum)
{
	// 设置过滤器   
	TCHAR szFilter[] = _T("图像(*.jpg)|*.jpg|图像(*.jpeg)|*.jpeg|图像(*.png)|*.png|图像(*.bmp)|*.bmp|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("jpg|jpeg|png|bmp|gif"), NULL, 0, szFilter, this);
	CString strImgPath;
	if (IDOK == fileDlg.DoModal())
	{ 
		strImgPath = fileDlg.GetPathName();
		string sImgPath = CStringA(strImgPath);
		int nID = 0;
		float tDestLen = 1000.0; // 缩放后的对角线长度
		switch (nImgNum) {
		case 1:
			{
				nID = IDC_EDIT_IMG_PATH01;
				m_sImgPath01 = sImgPath;
				Mat img0 = imread(sImgPath);
				float scale = float(tDestLen) / (img0.rows + img0.cols);
				float newh = scale * img0.rows;
				float neww = scale * img0.cols;
				resize(img0, m_matFace01, Size(neww, newh), 0, 0, CV_INTER_LINEAR);
				ShowMat(m_matFace01, IDC_PIC1);
			}
			break;
		case 2:
			{
				nID = IDC_EDIT_IMG_PATH02;
				m_sImgPath02 = sImgPath;
				Mat img0 = imread(sImgPath);
				float scale = float(tDestLen) / (img0.rows + img0.cols);
				float newh = scale * img0.rows;
				float neww = scale * img0.cols;
				resize(img0, m_matFace02, Size(neww, newh), 0, 0, CV_INTER_LINEAR);
				ShowMat(m_matFace02, IDC_PIC2);
			}
			break;
		default:
			cout << "未知错误！" << endl;
			break;
		}
		SetDlgItemTextA(nID, sImgPath.c_str());
	}
}
  
// 显示opencv图片格式Mat到图像控件nID上
void CSFMFCTestDlg::ShowMat(Mat vMat, int nID){ 	
	if (vMat.empty()){
		return; 
	}
	
	// 获取图片的宽 高度
	int tImgWidth = vMat.cols; 
	int tImgHeight = vMat.rows; 
	 
	// 获取Picture Control控件的大小
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);
	// 将客户区选中到控件表示的矩形区域内
	 
	int tNewWidth, tNewHeight;

	int tLeft = 0, tTop = 0, tRight = rect.Width(), tBottom = rect.Height();
	if (tImgWidth > tImgHeight){
		//如果图像是横的
		tNewWidth = tRight;
		tNewHeight = tNewWidth * tImgHeight / tImgWidth;
		tTop = (tNewWidth - tNewHeight) / 2;
		tBottom = rect.Height() - tTop;
	}
	else{
		//如果图像是竖的
		tNewHeight = tBottom;
		tNewWidth = tNewHeight * tImgWidth / tImgHeight;
		tLeft = (tNewHeight - tNewWidth) / 2;
		tRight = rect.Width() - tLeft;
	}

	Mat zoomImg;
	cv::resize(vMat, zoomImg, Size(tNewWidth-1, tNewHeight-1)); 
	 
	CImage cimg; 
	MatToCImage(zoomImg, cimg);

	// 以下是显示
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(nID);// 获取控件句柄 

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();// 获取picture的DC

	CBrush brush(RGB(255, 255, 255));

	// 白色背景填充,保留边框
	CRect tRect = CRect(1, 1, rect.Width()-2, rect.Height()-2);
	pDc->FillRect(tRect, &brush);
	cimg.Draw(pDc->m_hDC, CRect(tLeft+1, tTop+1, tRight-1, tBottom-1));
	 
	ReleaseDC(pDc);
} 

// 实现cv::Mat 结构到 CImage结构的转化
void CSFMFCTestDlg::MatToCImage(Mat& mat, CImage& cImage)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy();// 这一步是防止重复利用造成内存问题
	cImage.Create(width, height, 8 * channels);

	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); // 获取CImage的像素存贮区的指针
	int step = cImage.GetPitch();// 每行的字节数,注意这个返回值有正有负

	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置  
	// CImage中内置了调色板，我们要对他进行赋值：
	if (1 == channels)
	{
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		// 这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)  
		ColorTable = new RGBQUAD[MaxColors];
		cImage.GetColorTable(0, MaxColors, ColorTable);// 这里是取得指针  
		for (int i = 0; i<MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			// BYTE和uchar一回事，但MFC中都用它  
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		cImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}


	for (int i = 0; i < height; i++)
	{
		ps = mat.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			if (1 == channels)
			{
				*(pimg + i*step + j) = ps[j];
				//*(pimg + i*step + j) = 105;
			}
			else if (3 == channels)
			{
				*(pimg + i*step + j * 3) = ps[j * 3];
				*(pimg + i*step + j * 3 + 1) = ps[j * 3 + 1];
				*(pimg + i*step + j * 3 + 2) = ps[j * 3 + 2];
			}
		}
	}
}

// CImage缩放
void CSFMFCTestDlg::CreateStretchImage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth)
{
	if (pImage->IsDIBSection())
	{
		//MessageBox(_T("is dib"), _T("tip"), MB_OK);
		// 取得 pImage 的 DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image 因為有自己的 DC, 所以必須使用 FromHandle 取得對應的 DC
		
		CBitmap *bitmap1 = pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);
		
		// 建立新的 CImage
		ResultImage->Create(StretchWidth, StretchHeight, bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());
		
		// 當 Destination 比較小的時候, 會根據 Destination DC 上的 Stretch Blt mode 決定是否要保留被刪除點的資訊
		ResultImageDC->SetStretchBltMode(HALFTONE); // 使用最高品質的方式
	 
		::SetBrushOrgEx(ResultImageDC->m_hDC, 0, 0, NULL); // 調整 Brush 的起點
		 
		// 把 pImage 畫到 ResultImage 上面
		StretchBlt(*ResultImageDC, 0, 0, StretchWidth, StretchHeight, *pImageDC1, 0, 0, pImage->GetWidth(), pImage->GetHeight(), SRCCOPY);
	 
		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}
	else{
		MessageBox(_T("not dib"), _T("tip"), MB_OK); 
	}
}

CString CSFMFCTestDlg::SelectFolderPath()
{
	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         sFolderPath;
	BROWSEINFO      sInfo;

	LPITEMIDLIST    rootLoation;
	SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &rootLoation);

	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = rootLoation;
	sInfo.lpszTitle = _T("请选择处理结果存储路径");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			sFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}

	return sFolderPath;
}

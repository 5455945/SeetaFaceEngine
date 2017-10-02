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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSFMFCTestDlg �Ի���
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


// CSFMFCTestDlg ��Ϣ�������

BOOL CSFMFCTestDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSFMFCTestDlg::OnPaint()
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
		m_edtModelPath.SetWindowText(_T("��ѡ��ģ�ʹ��·��"));
		return;
	}

	CString p2;
	GetDlgItemText(IDC_EDIT_IMG_PATH01, p2);

	if (m_matFace01.empty()) {
		m_edtImgPath01.SetFocus();
		MessageBox(_T("ͼƬ1����"), _T("ͼƬ�������"), MB_ICONERROR);
		return;
	}

	if (m_matFace02.empty()) {
		m_edtImgPath02.SetFocus();
		MessageBox(_T("ͼƬ2����"), _T("ͼƬ�������"), MB_ICONERROR);
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
	// ���ù�����   
	TCHAR szFilter[] = _T("ͼ��(*.jpg)|*.jpg|ͼ��(*.jpeg)|*.jpeg|ͼ��(*.png)|*.png|ͼ��(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("jpg|jpeg|png|bmp|gif"), NULL, 0, szFilter, this);
	CString strImgPath;
	if (IDOK == fileDlg.DoModal())
	{ 
		strImgPath = fileDlg.GetPathName();
		string sImgPath = CStringA(strImgPath);
		int nID = 0;
		float tDestLen = 1000.0; // ���ź�ĶԽ��߳���
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
			cout << "δ֪����" << endl;
			break;
		}
		SetDlgItemTextA(nID, sImgPath.c_str());
	}
}
  
// ��ʾopencvͼƬ��ʽMat��ͼ��ؼ�nID��
void CSFMFCTestDlg::ShowMat(Mat vMat, int nID){ 	
	if (vMat.empty()){
		return; 
	}
	
	// ��ȡͼƬ�Ŀ� �߶�
	int tImgWidth = vMat.cols; 
	int tImgHeight = vMat.rows; 
	 
	// ��ȡPicture Control�ؼ��Ĵ�С
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);
	// ���ͻ���ѡ�е��ؼ���ʾ�ľ���������
	 
	int tNewWidth, tNewHeight;

	int tLeft = 0, tTop = 0, tRight = rect.Width(), tBottom = rect.Height();
	if (tImgWidth > tImgHeight){
		//���ͼ���Ǻ��
		tNewWidth = tRight;
		tNewHeight = tNewWidth * tImgHeight / tImgWidth;
		tTop = (tNewWidth - tNewHeight) / 2;
		tBottom = rect.Height() - tTop;
	}
	else{
		//���ͼ��������
		tNewHeight = tBottom;
		tNewWidth = tNewHeight * tImgWidth / tImgHeight;
		tLeft = (tNewHeight - tNewWidth) / 2;
		tRight = rect.Width() - tLeft;
	}

	Mat zoomImg;
	cv::resize(vMat, zoomImg, Size(tNewWidth-1, tNewHeight-1)); 
	 
	CImage cimg; 
	MatToCImage(zoomImg, cimg);

	// ��������ʾ
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(nID);// ��ȡ�ؼ���� 

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();// ��ȡpicture��DC

	CBrush brush(RGB(255, 255, 255));

	// ��ɫ�������,�����߿�
	CRect tRect = CRect(1, 1, rect.Width()-2, rect.Height()-2);
	pDc->FillRect(tRect, &brush);
	cimg.Draw(pDc->m_hDC, CRect(tLeft+1, tTop+1, tRight-1, tBottom-1));
	 
	ReleaseDC(pDc);
} 

// ʵ��cv::Mat �ṹ�� CImage�ṹ��ת��
void CSFMFCTestDlg::MatToCImage(Mat& mat, CImage& cImage)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy();// ��һ���Ƿ�ֹ�ظ���������ڴ�����
	cImage.Create(width, height, 8 * channels);

	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); // ��ȡCImage�����ش�������ָ��
	int step = cImage.GetPitch();// ÿ�е��ֽ���,ע���������ֵ�����и�

	// �����1��ͨ����ͼ��(�Ҷ�ͼ��) DIB��ʽ����Ҫ�Ե�ɫ������  
	// CImage�������˵�ɫ�壬����Ҫ�������и�ֵ��
	if (1 == channels)
	{
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		// �������ͨ��CI.GetMaxColorTableEntries()�õ���С(�������CI.Load����ͼ��Ļ�)  
		ColorTable = new RGBQUAD[MaxColors];
		cImage.GetColorTable(0, MaxColors, ColorTable);// ������ȡ��ָ��  
		for (int i = 0; i<MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			// BYTE��ucharһ���£���MFC�ж�����  
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

// CImage����
void CSFMFCTestDlg::CreateStretchImage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth)
{
	if (pImage->IsDIBSection())
	{
		//MessageBox(_T("is dib"), _T("tip"), MB_OK);
		// ȡ�� pImage �� DC
		CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image ������Լ��� DC, ���Ա��ʹ�� FromHandle ȡ�Ì����� DC
		
		CBitmap *bitmap1 = pImageDC1->GetCurrentBitmap();
		BITMAP bmpInfo;
		bitmap1->GetBitmap(&bmpInfo);
		
		// �����µ� CImage
		ResultImage->Create(StretchWidth, StretchHeight, bmpInfo.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());
		
		// �� Destination ���^С�ĕr��, ������ Destination DC �ϵ� Stretch Blt mode �Q���Ƿ�Ҫ�������h���c���YӍ
		ResultImageDC->SetStretchBltMode(HALFTONE); // ʹ�����Ʒ�|�ķ�ʽ
	 
		::SetBrushOrgEx(ResultImageDC->m_hDC, 0, 0, NULL); // �{�� Brush �����c
		 
		// �� pImage ���� ResultImage ����
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
	sInfo.lpszTitle = _T("��ѡ�������洢·��");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// ��ʾ�ļ���ѡ��Ի���  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// ȡ���ļ�����  
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

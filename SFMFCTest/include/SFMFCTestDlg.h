#pragma once
#include <opencv2/core/version.hpp>
#include <opencv/cv.hpp>
#include <opencv/cxcore.hpp>
#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"

// CSFMFCTestDlg 对话框
class CSFMFCTestDlg : public CDialogEx
{
// 构造
public:
	CSFMFCTestDlg(CWnd* pParent = NULL);	// 标准构造函数


// 对话框数据
	enum { IDD = IDD_SFMFCTEST_DIALOG };

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
	afx_msg void OnBnClickedImg01();
	afx_msg void OnBnClickedImg02();
	afx_msg void OnBnClickedBtnModelpath();
	afx_msg void OnBnClickedCompare();
	afx_msg void OnBnClickedCancel();

private:
	// 选择文件夹
	CString SelectFolderPath();

	// 设置图片路径
	void SetImgPath(int nImgNum);

    // 计算2个照片的人脸的相似度(每张照片只取1个人)
	float CalcSimilarity(std::string sModelPath, cv::Mat vFaceMat1, cv::Mat vFaceMat2);

	// 显示指定的图像到nID指定的对象上
	void ShowMat(cv::Mat vMat, int nID);

	// CImage缩放
	void CreateStretchImage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth);

	// 实现cv::Mat 结构到 CImage结构的转化
	void MatToCImage(cv::Mat& mat, CImage& cImage);

	CEdit m_edtImgPath01;           // 图片1路径选择框
	CEdit m_edtImgPath02;           // 图片2路径选择框
	CEdit m_edtModelPath;           // 模型存放路径选择框
	cv::Mat m_matFace01;            // 选中的人脸图像1
	cv::Mat m_matFace02;            // 选中的人脸图像2
	std::string m_sModelPath;       // 模型文件夹，存放seeta_fa_v1.1.bin、seeta_fd_frontal_v1.0.bin、seeta_fr_v1.0.bin的文件夹
	std::string m_sImgPath01;       // 图片1路径
	std::string m_sImgPath02;       // 图片2路径
};

#pragma once
#include <opencv2/core/version.hpp>
#include <opencv/cv.hpp>
#include <opencv/cxcore.hpp>
#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"

// CSFMFCTestDlg �Ի���
class CSFMFCTestDlg : public CDialogEx
{
// ����
public:
	CSFMFCTestDlg(CWnd* pParent = NULL);	// ��׼���캯��


// �Ի�������
	enum { IDD = IDD_SFMFCTEST_DIALOG };

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
	afx_msg void OnBnClickedImg01();
	afx_msg void OnBnClickedImg02();
	afx_msg void OnBnClickedBtnModelpath();
	afx_msg void OnBnClickedCompare();
	afx_msg void OnBnClickedCancel();

private:
	// ѡ���ļ���
	CString SelectFolderPath();

	// ����ͼƬ·��
	void SetImgPath(int nImgNum);

    // ����2����Ƭ�����������ƶ�(ÿ����Ƭֻȡ1����)
	float CalcSimilarity(std::string sModelPath, cv::Mat vFaceMat1, cv::Mat vFaceMat2);

	// ��ʾָ����ͼ��nIDָ���Ķ�����
	void ShowMat(cv::Mat vMat, int nID);

	// CImage����
	void CreateStretchImage(CImage *pImage, CImage *ResultImage, int StretchHeight, int StretchWidth);

	// ʵ��cv::Mat �ṹ�� CImage�ṹ��ת��
	void MatToCImage(cv::Mat& mat, CImage& cImage);

	CEdit m_edtImgPath01;           // ͼƬ1·��ѡ���
	CEdit m_edtImgPath02;           // ͼƬ2·��ѡ���
	CEdit m_edtModelPath;           // ģ�ʹ��·��ѡ���
	cv::Mat m_matFace01;            // ѡ�е�����ͼ��1
	cv::Mat m_matFace02;            // ѡ�е�����ͼ��2
	std::string m_sModelPath;       // ģ���ļ��У����seeta_fa_v1.1.bin��seeta_fd_frontal_v1.0.bin��seeta_fr_v1.0.bin���ļ���
	std::string m_sImgPath01;       // ͼƬ1·��
	std::string m_sImgPath02;       // ͼƬ2·��
};

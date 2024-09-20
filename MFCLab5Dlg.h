
// MFCLab5Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMFCLab5Dlg
class CMFCLab5Dlg : public CDialogEx
{
// Создание
public:
	CMFCLab5Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLAB5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenFile();
	afx_msg void OnEnChangeEditPath();
	CString path;
	afx_msg void OnEnChangeEditDevationRoundness();
	double deviation_roundness;
	afx_msg void OnEnChangeEditFileName();
	CString file_name;
	CString main_X;
	CString main_R;
	CString main_Y;
	CString main_Z;
};

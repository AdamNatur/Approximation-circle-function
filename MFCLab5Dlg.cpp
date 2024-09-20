
// MFCLab5Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCLab5.h"
#include "MFCLab5Dlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CT_A 0
#define CT_B 1
#define CT_C 3

#define CT_R 2
#define t 1.68033989

using namespace std;




// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CMFCLab5Dlg



CMFCLab5Dlg::CMFCLab5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLAB5_DIALOG, pParent)
	, path(_T(""))
	, deviation_roundness(0)
	, file_name(_T(""))
	, main_X(_T(""))
	, main_R(_T(""))
	, main_Y(_T(""))
	, main_Z(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLab5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, path);
	DDX_Text(pDX, IDC_EDIT_DEVATION_ROUNDNESS, deviation_roundness);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, file_name);
	DDX_Text(pDX, IDC_EDIT_X, main_X);
	DDX_Text(pDX, IDC_EDIT_R, main_R);
	DDX_Text(pDX, IDC_EDIT_Y, main_Y);
	DDX_Text(pDX, IDC_EDIT1, main_Z);
}

BEGIN_MESSAGE_MAP(CMFCLab5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CMFCLab5Dlg::OnBnClickedButtonOpenFile)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CMFCLab5Dlg::OnEnChangeEditPath)
	ON_EN_CHANGE(IDC_EDIT_DEVATION_ROUNDNESS, &CMFCLab5Dlg::OnEnChangeEditDevationRoundness)
	ON_EN_CHANGE(IDC_EDIT_FILE_NAME, &CMFCLab5Dlg::OnEnChangeEditFileName)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCLab5Dlg

BOOL CMFCLab5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCLab5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCLab5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCLab5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double Radius_min = DBL_MAX ;
double Radius = 0;
double X[36], Y[36], Z[36];
double X_center = 0;
double Y_center = 0;
double Z_center = 0;

void find_center_radius(CString myfile)
{
	wstring file_path(myfile.GetString());
	ifstream fin(file_path);
	char buff[256];
	string str;
	string X_str;
	string Y_str;
	string Z_str;
	int space_pos;
	int a = 1;
	int n;
	int i = 0;

	if (!fin.is_open()) // проверяем на открытие
	{
		MessageBox(0, L"File is not found!", L"Error", MB_OK | MB_ICONERROR); // вывод при ошибку
	}
	else
	{
		MessageBox(0, L"Success", L"Info", MB_OK | MB_ICONINFORMATION); // вывод при успехе
		while (!fin.eof() && i <= 35)
		{
			if (a > 1) // условие для первой строчки считывания 
			{
				n = 0;
				fin.getline(buff, 256); // забираем срочку
				str = string(buff); // из char в string
				while(n != 6)
				{ 
					space_pos = str.find('\t'); // ищем табуляцию
					str.erase(0, space_pos+1); // стираем часть строчки
					n++;
				}

 				X_str = "";
				Y_str = "";
				Z_str = "";

				n = 0;

				while (n != str.find('\t'))
				{
					X_str = X_str + str[n];
					n++;
				}

				X[i] = atof(X_str.c_str());

				space_pos = str.find('\t');
				str.erase(0, space_pos+1);

				n = 0;

				while (n != str.find('\t'))
				{
					Y_str = Y_str + str[n];
					n++;
				}

				Y[i] = atof(Y_str.c_str());

				space_pos = str.find('\t');
				str.erase(0, space_pos + 1);

				n = 0;
				while (n != str.find('\t'))
				{
					Z_str = Z_str + str[n];
					n++;
				}

				Z[i] = atof(Z_str.c_str());


				a++;
				i++;
			}
			else
			{
				fin.getline(buff, 256);
				a++;
				continue;
			}
		}
		fin.close();

		for ( int j = 0;  j < 36; j++)
		{
			X_center += X[j];
			Y_center += Y[j];
			Z_center += Z[j];
		}

		X_center /= 36;
		Y_center /= 36;
		Z_center /= 36;


		for (int m = 0; m < 36; m++)
		{
			if (Radius_min > sqrt(pow((X_center - X[m]),2) + pow((Y_center - Y[m]), 2) + pow((Z_center - Z[m]),2)))
			{
				Radius_min = sqrt(pow((X_center - X[m]), 2) + pow((Y_center - Y[m]), 2) + pow((Z_center - Z[m]), 2));
			}
			Radius += sqrt((X_center - X[m]) * (X_center - X[m]) + (Y_center - Y[m]) * (Y_center - Y[m]));
		}

		Radius /= 36;
	}


	
}

double approximation_function_derivative(double a, double b, double R, double z, double X[], double Y[], double Z[], int c) // функция производной по каждой переменной
{
	double function_derivative = 0;

	switch (c) 
	{
	case 0: // для переменной a
		for (int i = 0; i < 36; i++) // цикл суммы по каждому квадрату расстояния и поиск производной от этого всего по переменной a
		{

			function_derivative += 2 * (pow((a - X[i]), 2) + pow((b - Y[i]),2) + pow((z - Z[i]), 2) - R * R) * 2 * (a - X[i]); // частную производную мы нашли в ручную и просто пребираем теперь массивы данных
		}
		break;
	case 1: // для переменной b
		for (int i = 0; i < 36; i++) // цикл суммы по каждому квадрату расстояния и поиск производной от этого всего по переменной b
		{
			function_derivative += 2 * (pow((a - X[i]), 2) + pow((b - Y[i]), 2) + pow((z - Z[i]), 2) - R * R) * 2 * (b - Y[i]); // частную производную мы нашли в ручную и просто пребираем теперь массивы данных
		}
		break;
	case 2: // для переменной R
		for (int i = 0; i < 36; i++) // цикл суммы по каждому квадрату расстояния и поиск производной от этого всего по переменной R
		{
			function_derivative += 2 * (pow((a - X[i]), 2) + pow((b - Y[i]), 2) + pow((z - Z[i]), 2) -  R*R) * (-2*R); // частную производную мы нашли в ручную и просто пребираем теперь массивы данных
		}
		break;
	case 3: // для переменной R
		for (int i = 0; i < 36; i++) // цикл суммы по каждому квадрату расстояния и поиск производной от этого всего по переменной R
		{
			function_derivative += 2 * (pow((a - X[i]), 2) + pow((b - Y[i]), 2) + pow((z - Z[i]), 2) - R * R) * 2 * (z-Z[i]); // частную производную мы нашли в ручную и просто пребираем теперь массивы данных
		}
		break;
	}

	return function_derivative;
}

double approximation_function(double a, double b, double R, double z, double X[], double Y[], double Z[], double alpha)
{
	double function = 0;
	a = a - alpha * approximation_function_derivative(a, b, R, z,  X, Y, Z, CT_A);
	b = b - alpha * approximation_function_derivative(a, b, R, z, X, Y, Z, CT_B);
	R = R - alpha * approximation_function_derivative(a, b, R, z, X, Y, Z, CT_R);
	z = z - alpha * approximation_function_derivative(a, b, R, z, X, Y, Z, CT_C);
	for (int i = 0; i < 36; i++)
	{
		function += pow((pow((a - X[i]),2) + pow((b - Y[i]), 2) + pow((z - Z[i]), 2) - R * R), 2);
	}

	return function;
}


void approximation_values(double &a, double &b, double &R, double &z, double X[], double Y[]) // главная функция по итерации (заданию шагов по графику)
{
	double A_previous = 0; // для хранения прошлого шага по каждой переменной
	double B_previous = 0; // для хранения прошлого шага по каждой переменной
	double R_previous = 0; // для хранения прошлого шага по каждой переменной
	double Z_previous = 0; // для хранения прошлого шага по каждой переменной
	double alpha = 0; // начальный коэфициент
	double dif_vector = 0; // переменная для проверки выходы из главного итарационного цикла
	double step = 0.001; // задаем шаг для итерации равномерного поиска
	double temp_alpha = 0; // для подбора alpha в равномерном поиске


	while (true)
	{
		A_previous = a; // запоминаем прошый шаг по a
		B_previous = b; // запоминаем прошый шаг по b
		R_previous = R; // запоминаем прошый шаг по R
		Z_previous = z;
		a = A_previous - alpha * approximation_function_derivative(A_previous, B_previous, R_previous, Z_previous, X, Y, Z, CT_A); // итерационная формула по a
		b = B_previous - alpha * approximation_function_derivative(A_previous, B_previous, R_previous, Z_previous, X, Y, Z, CT_B); // итерационная формула по b
		R = R_previous - alpha * approximation_function_derivative(A_previous, B_previous, R_previous, Z_previous, X, Y, Z, CT_R); // итерационная формула по R
		z = Z_previous - alpha * approximation_function_derivative(A_previous, B_previous, R_previous, Z_previous, X, Y, Z, CT_C);

		dif_vector = sqrt(pow((A_previous - a), 2) + pow((B_previous - b), 2) + pow((R_previous - R),2) + pow((Z_previous - z), 2));

		if ((dif_vector <= 0.00001) && (dif_vector != 0))
		{
			break;
		}

		double value_alpha_a = 0.0001;
		double Fmin = approximation_function(a, b, R, z, X, Y, Z, value_alpha_a);
		double value_alpha_b = 1;
		temp_alpha = value_alpha_a;

		while (temp_alpha <= value_alpha_b)
		{
			if (Fmin >= approximation_function(a, b, R, z, X, Y, Z, temp_alpha))
			{
				alpha = temp_alpha;
				Fmin = approximation_function(a, b, R, z, X, Y, Z, alpha);
			}

			temp_alpha += step;
		}
	}


}


void CMFCLab5Dlg::OnBnClickedButtonOpenFile()
{
	// TODO: добавьте свой код обработчика уведомлений

	CFileDialog myfile(TRUE);

	if (myfile.DoModal())
	{
		path = myfile.GetPathName(); // открываем файл и считываем информацию
		file_name = myfile.GetFileTitle(); // открываем файл и считываем информацию

		find_center_radius(path); // запускаем функцию поиска первого приближения a, b, R

		approximation_values(X_center, Y_center, Radius, Z_center, X, Y); // передаем результаты рботы функции find_center_radius(path)

	}
	else
	{
		MessageBox(L"Error", L"Error", MB_OK | MB_ICONERROR);
	}

	main_X.Format(_T("%.4f"), X_center);
	main_Y.Format(_T("%.4f"), Y_center);
	main_R.Format(_T("%.4f"), Radius);
	main_Z.Format(_T("%.4f"), Z_center);
	deviation_roundness = Radius - Radius_min;

	UpdateData(FALSE);

}


void CMFCLab5Dlg::OnEnChangeEditPath()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}





void CMFCLab5Dlg::OnEnChangeEditDevationRoundness()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления



}


void CMFCLab5Dlg::OnEnChangeEditFileName()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}



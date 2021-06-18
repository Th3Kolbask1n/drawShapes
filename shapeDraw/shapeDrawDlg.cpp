
// shapeDrawDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "shapeDraw.h"
#include "shapeDrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Диалоговое окно CshapeDrawDlg



CshapeDrawDlg::CshapeDrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAPEDRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CshapeDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CshapeDrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnDraw, &CshapeDrawDlg::OnBnClickedbtndraw)
END_MESSAGE_MAP()


// Обработчики сообщений CshapeDrawDlg

BOOL CshapeDrawDlg::OnInitDialog()
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

void CshapeDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CshapeDrawDlg::OnPaint()
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
HCURSOR CshapeDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CshapeDrawDlg::OnBnClickedbtndraw()
{
	// TODO: добавьте свой код обработчика уведомлений

	//


	CDC* pDC = GetDC();


	CRect rect;
	GetClientRect(rect);




	//Перезапись холста перед новой отрисовкой
	rect.DeflateRect(0, 0);
	pDC->Rectangle(rect);





	// Цвет обводки
	CPen penBlue(PS_SOLID, 5, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&penBlue);

	//Цвет заливки
	CBrush brushRed(RGB(255, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushRed);

	// Точки для построения фигур
	CPoint polygonPts[4];


	//Рисование ромба. Размеры выбираются в зависимости от размеров окна.

	polygonPts[0].x = rect.left + (rect.Width() / 32) + (rect.Width() / 16); //Верхний угол
	polygonPts[0].y = rect.top + (rect.Height() / 8);

	polygonPts[1].x = polygonPts[0].x + (rect.Width() / 16);
	polygonPts[1].y = rect.top + ((rect.Height() / 8) * 3);  //Правый угол

	polygonPts[2].x = polygonPts[0].x;
	polygonPts[2].y = rect.top + ((rect.Height() / 8) * 5); //Нижний угол

	polygonPts[3].x = rect.left + (rect.Width() / 32); //Левый угод
	polygonPts[3].y = polygonPts[1].y;

	pDC->Polygon(polygonPts, 4);

	// Цвет обводки
	CPen penGreen(PS_SOLID, 5, RGB(0, 255, 0));
	pDC->SelectObject(&penGreen);

	//Цвет заливки
	CBrush brushBlue(RGB(0, 0, 255));
	pDC->SelectObject(&brushBlue);


	//Запись текущих координат для рисования фигур "правее"


	CPoint currentPoint[1];
	currentPoint[0].x = polygonPts[1].x + (rect.Height() / 8);
	currentPoint[0].y = polygonPts[0].y;

	// Определение координат для прямоугольника

	polygonPts[0].x = currentPoint[0].x; //Левый верхний угол
	polygonPts[0].y = (rect.Height() / 8);

	polygonPts[1].x = polygonPts[0].x + (rect.Width() / 16);
	polygonPts[1].y = currentPoint[0].y;  //Правый верхний угол

	polygonPts[2].x = polygonPts[1].x;
	polygonPts[2].y = currentPoint[0].y + ((rect.Height() / 8) * 4); //Правый нижний угол

	polygonPts[3].x = currentPoint[0].x; //Левый нижний угол
	polygonPts[3].y = polygonPts[2].y;

	pDC->Polygon(polygonPts, 4);


	//Запись текущих координат для рисования фигур "правее"


	currentPoint[0].x = polygonPts[1].x + (rect.Height() / 8);
	currentPoint[0].y = polygonPts[1].y;


	// Цвет обводки
	CPen penOrange(PS_SOLID, 5, RGB(255, 116, 0));
	pDC->SelectObject(&penOrange);

	//Цвет заливки
	CBrush brushOrange(RGB(255, 178, 99));
	pDC->SelectObject(&brushOrange);


	// Определение координат для квадрата


	polygonPts[0].x = currentPoint[0].x; //Левый верхний угол
	polygonPts[0].y = (rect.Height() / 8);

	polygonPts[1].x = polygonPts[0].x + (rect.Height() / 4);
	polygonPts[1].y = currentPoint[0].y;  //Правый верхний угол

	polygonPts[2].x = polygonPts[1].x;
	polygonPts[2].y = currentPoint[0].y +(rect.Height() /  4); //Правый нижний угол

	polygonPts[3].x = currentPoint[0].x; //Левый нижний угол
	polygonPts[3].y = polygonPts[2].y;

	pDC->Polygon(polygonPts, 4);

	//Запись текущих координат для рисования фигур "правее"


	currentPoint[0].x = polygonPts[1].x + (rect.Height() / 8);
	currentPoint[0].y = polygonPts[1].y;



	// Цвет обводки
	CPen penPurple(PS_SOLID, 5, RGB(82, 2, 110));
	pDC->SelectObject(&penPurple);

	//Цвет заливки
	CBrush brushPurple(RGB(172, 59, 212));
	pDC->SelectObject(&brushPurple);


	// Определение координат для треугольника


	CPoint trianglePts[3];


	trianglePts[0].x = currentPoint[0].x + (rect.Height() / 8); //Верхний угол
	trianglePts[0].y = (rect.Height() / 8);


	trianglePts[1].x = trianglePts[0].x + (rect.Height() / 8);
	trianglePts[1].y = currentPoint[0].y + ((rect.Height() / 8) * 4);; //Правый нижний угол

	trianglePts[2].x = currentPoint[0].x; //Левый нижний угол
	trianglePts[2].y = trianglePts[1].y;


	//Запись текущих координат для рисования фигур "правее"


	currentPoint[0].x = trianglePts[1].x + (rect.Height() / 8);
	currentPoint[0].y = trianglePts[0].y;

	pDC->Polygon(trianglePts, 3);


	// Цвет обводки
	CPen penLightBlue(PS_SOLID, 5, RGB(3, 71, 105));
	pDC->SelectObject(&penLightBlue);

	//Цвет заливки
	CBrush brushLightBlue(RGB(60, 160, 208));
	pDC->SelectObject(&brushLightBlue);


	// Определение координат для круга


	CPoint ellipsePts[2];

	// Координаты левого верхнего угла прямоугольника, в который вписывается эллипс

	ellipsePts[0].x = currentPoint[0].x;
	ellipsePts[0].y = currentPoint[0].y;

	// Координаты правого нижнего угла прямоугольника, в который вписывается эллипс

	ellipsePts[1].x = currentPoint[0].x + (rect.Height() / 4);
	ellipsePts[1].y = currentPoint[0].y + (rect.Height() / 4);

	pDC->Ellipse(ellipsePts[0].x, ellipsePts[0].y, ellipsePts[1].x, ellipsePts[1].y);

	//Запись текущих координат для рисования фигур "правее"

	currentPoint[0].x = ellipsePts[1].x + (rect.Height() / 8);
	currentPoint[0].y = ellipsePts[0].y;


	// Цвет обводки
	CPen penLightGreen(PS_SOLID, 5, RGB(103, 155, 0));
	pDC->SelectObject(&penLightGreen);

	//Цвет заливки
	CBrush brushLightGreen(RGB(134, 176, 45));
	pDC->SelectObject(&brushLightGreen);


	// Определение координат для эллипса
	   	 
	// Координаты левого верхнего угла прямоугольника, в который вписывается эллипс

	ellipsePts[0].x = currentPoint[0].x;
	ellipsePts[0].y = currentPoint[0].y;

	// Координаты правого нижнего угла прямоугольника, в который вписывается эллипс

	ellipsePts[1].x = currentPoint[0].x + (rect.Height() / 4);
	ellipsePts[1].y = currentPoint[0].y + (rect.Height() / 2);


	//Отрисовка эллипса
	pDC->Ellipse(ellipsePts[0].x, ellipsePts[0].y, ellipsePts[1].x, ellipsePts[1].y);



}


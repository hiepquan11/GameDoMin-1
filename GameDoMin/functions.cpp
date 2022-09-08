#include "main.h"
#include "functions.h"
#include "Console.h"

CauTrucBang CTBang;
CauTrucO **CTO;

//Vi tri con tro hien tai
COORD CViTriConTro;

//Su dung phim
bool BSuDungPhim = false; 

void taoMang2ChieuDong() 
{
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}

void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete CTO[i];
	}
	delete CTO;
}

void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	veBang();
	taoBomNgauNhien();
	//xuatBom();

	//xoaMang2ChieuDong();
}

short toaDoX(short SX) //Toa do X ve bang
{
	return SX * 2;
}

short toaDoY(short SY) //Toa do y ve bang
{
	return SY;
}


void veO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0:// Rong mau xanh la
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, const_cast<char*> ("  "));
		break;
	case 1:// So 1 xanh duong, So 1 -> 8 la nen trang
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, const_cast<char*> ("1 "));
		break;
	case 2:// So 2 xanh la
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, const_cast<char*> ("2 "));
		break;
	case 3:// So 3 do
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, const_cast<char*> ("3 "));
		break;
	case 4://So 4 xanh duong dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, const_cast<char*> ("4 "));
		break;
	case 5://So 5 do dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, const_cast<char*> ("5 "));
		break;
	case 6://So 6 CYAN dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, const_cast<char*> ("6 "));
		break;
	case 7://So 7 den 
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, const_cast<char*> ("7 "));
		break;
	case 8://So 8 hong
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, const_cast<char*> ("8 "));
		break;
	case 9://Bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, const_cast<char*> ("B "));
		break;
	case 10://0 chan
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, const_cast<char*> ("  "));
		break;
	case 11://0 le
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, const_cast<char*> ("  "));
		break;
	case 12://Theo doi con tro
		setColorBGTextXY(toaDoX(SX) + 1, toaDoY(SY), 0, 13, const_cast<char*> (" "));
		break;
	case 13://Cam co
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*> ("P "));
		break;
	case 14://Cam co ko co bom -> cam co sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, const_cast<char*> ("Px "));
		break;
	case 15://Cam co co bom -> cam co dung
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*> ("B "));
		break;
	}
}
void veBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{	
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			/*if (((i % 2) && (j % 2)) || !((i % 2) || (j % 2)))
			{
				veO(j, i, 10);
			}
			else
			{
				veO(j, i, 11);
			}*/
			//Cach 2:
			if (CTO[i][j].BCamCo)
				veO(j, i, 13);
			else if (CTO[i][j].SBomLanCan)
				veO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo)
				veO(j, i, 0);
			else if ((i + j) % 2)//o le
				veO(j, i, 11);
			else//o chan
				veO(j, i, 10);

			if (BSuDungPhim)
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ;//SI vi tri dong, SJ vi tri cot, ta se random
	srand(time(NULL));//Reset time
	while (SSoBom)
	{   //CT random trong khoang (x,y) la rand() % (y - x + 1) + x = rand() % CTBang.SDong(CTBang.SCot)
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;//Cap nhat so luong bom
	}
}

void xuatBom()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			std::cout << CTO[i][j].BCoBom << " ";
		}
		std::cout << std::endl;
	}
}
short demBomLC(short x, short y) {
	short dem = 0;
	for (int i = x - 1; i <= x + 1; ++i) {
		for (int j = y - 1; j <= y + 1; ++j) {
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == x && j == y))
				continue;
			if (CTO[i][j].BCoBom)
				++dem;
		}
	}
	return dem;
}
void moO(short x, short y) {
	if (!CTO[x][y].BDaMo && !CTO[x][y].BCamCo) {
		CTO[x][y].BDaMo = true;
		if (CTO[x][y].BCoBom) // o co bom
			exit(0); //=> thua
		else
		{
			CTBang.SSoODaMo++;
			short BomLC = demBomLC(x, y);
			if (BomLC) // co bom lan can
				CTO[x][y].SBomLanCan = BomLC;
			else // o rong
			{
				// Duyet cac o lan can va goi de quy
				for (int i = x - 1; i <= x + 1; ++i)
				{
					for (int j = y - 1; j <= y + 1; ++j)
					{
						// xet nhung vi tri khong hop le=> tiep tuc lap
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == x && j == y))
							continue;
						// goi de quy
						moO(i, j);
					}
				}
			}
		}
	}
}
void clickTrai(short x, short y) {
	if (!CTO[x][y].BDaMo && !CTO[x][y].BCamCo) {
		moO(x, y);
		veBang();
	}
}
void clickPhai(short SX, short SY)//Cam co
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
	}
	veBang();
}

void xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)//Co nham phim
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP://Mui ten len
			//std::cout << "Len " << std::endl;
			BSuDungPhim = true;
			CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
			veBang();
			break;
		case VK_DOWN://Mui ten xuong
			//std::cout << "Xuong " << std::endl;
			BSuDungPhim = true;
			CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
			veBang();
			break;
		case VK_LEFT://Mui ten trai
			//std::cout << "Trai " << std::endl;
			BSuDungPhim = true;
			CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
			veBang();
			break;
		case VK_RIGHT://Mui ten phai
			//std::cout << "Phai " << std::endl;
			BSuDungPhim = true;
			CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
			veBang();
			break;
		case VK_RETURN://Phim Enter
			std::cout << "Enter " << std::endl;
			break;
		case VK_ESCAPE://Phim ESC(thoat)
			std::cout << "ESC " << std::endl;
			break;	
		case ClickTrai://Phim Z - Mo O
			//std::cout << "Z" << std::endl;
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai://Phim X - Cam co
			//std::cout << "X" << std::endl;
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}

void xuLySuKien()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0;//Luu lai su hien tai
		DWORD DWNumberOfEventsRead = 0;//Luu lai so luong su kien da doc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);//Thiet bi dau vao
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);//Dat su kien dau vao cua giao dien cho bien DWNumberOfEvents

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD;
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);//Dat cac su kien dc luu tru vao con EventBuffer

			//Chay vong lap de doc su kien
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)//Neu la xu kien phim
				{
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
				//else(IREventBuffer[i].EventType == MOUSE_EVENT)//Su kien chuot
				//{

				//}
			}
		}
	}
}
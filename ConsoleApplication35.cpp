#include <iostream>
#include <vector>
#include <string.h>
#include <Windows.h>
#include <typeinfo>
using namespace std;

enum GAMECOLORS { DBLACK, DBLUE, DGREEN, DCYAN, DRED, DPURPLE, DYELLOW, GRAY, DGRAY, BBLUE, BGREEN, BCYAN, BRED, BPURPLE, BYELLOW, BWHITE };
int turn = 0;//xac dinh luot 
#define BOARDMAX 9		// Dong va cot tren ban co.
#define MAXPAWNS 16		// Quan Tot.
#define MAXKNIGHTS 4	// Quoan Ma.
#define MAXBISHOPS 4	// Quan Tinh.
#define MAXROOKS 4		// Quan Xe.
#define MAXQUEENS 2		// Quan Hau.
#define MAXKINGS 2		// Quan vua.
#define MAXPIECES 32	// Tong So quan co.
char Board[BOARDMAX][BOARDMAX];//ban co

class QuanCo
{
protected:
	int firstMove;
	int itsColor;
	char itsSymbol;
	int x, y;

public:
	QuanCo();
	virtual ~QuanCo();
	virtual void setf(int) {}
	int GetX() const;
	int GetY() const;
	int GetColor() const;
	void SetColorBlack();
	void SetX(int x);
	void SetY(int y);
	void DrawSymbol() const;
	virtual int RuleValidate(int X = -1, int Y = -1) = 0;
};
vector<QuanCo*> ListQuanCo;

class Chot :public QuanCo
{
public:
	Chot();
	~Chot();
	void setf(int n)
	{
		firstMove = n;
	}
	int RuleValidate(int X = -1, int Y = -1);
};

class Hau :public QuanCo
{
public:
	Hau();
	~Hau();
	int RuleValidate(int Xt = -1, int Yt = -1);
};

class Ma :public QuanCo
{
public:
	Ma();
	~Ma();
	int Ktr_Xuat(int, int, int, int, int&);
	int RuleValidate(int X = -1, int Y = -1);
};

class Tuong :public QuanCo
{
public:
	Tuong();
	~Tuong();
	int RuleValidate(int X = -1, int Y = -1);
};

class Vua :public QuanCo
{

public:
	static int SL;
	Vua();
	~Vua();
	int Ktr_Xuat(int, int, int, int, int&);
	int RuleValidate(int X = -1, int Y = -1);
};

class Xe :public QuanCo
{
public:
	Xe();
	~Xe();
	int RuleValidate(int X = -1, int Y = -1);
};

///Quan Co
QuanCo::QuanCo()
{
	itsColor = 0; x = y = 0;
}
QuanCo::~QuanCo()
{

}
int QuanCo::GetX() const
{
	return x;
}
int QuanCo::GetY() const
{
	return y;
}
int QuanCo::GetColor() const
{
	return itsColor;
}
void QuanCo::SetColorBlack()
{
	itsColor = 1;
}
void QuanCo::SetX(int x)
{
	this->x = x;
}
void QuanCo::SetY(int y)
{
	this->y = y;
}
void QuanCo::DrawSymbol() const//ve quan co len ban co
{
	if (itsColor == 0)
	{
		HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hcon, BGREEN);
	}
	else
	{
		HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hcon, BRED);
	}
	std::cout << itsSymbol;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, BWHITE);
}

///		Chot/////
Chot::Chot()
{
	this->firstMove = 0;//quan chot chua di chuyen
	this->itsSymbol = 'c';
}
Chot::~Chot() {}

int Chot::RuleValidate(int X, int Y)
{
	int ktrx = 0;
	int ktr = 0;
	if (X != -1 && Y != -1)//neu truyen tham so vao ham->ham co chuc nang kiem tra di chuyen.
		ktr = 1;
	if (ktr == 0)
		cout << "CHOT - VI TRI GOI Y: ";
	int k1 = 0, k2 = 0, k3 = 0;
	for (int i = 0; i < ListQuanCo.size(); i++)
	{
		if (GetColor() == 1) {
			if (ListQuanCo[i]->GetY() == GetY() - 1)//kiem tra hang phia truoc co quan co nao hay khong
			{
				if (ListQuanCo[i]->GetX() == GetX() - 1 && ListQuanCo[i]->GetColor() == 0)
				{//kiem tra phia tren ben trai co quan co khac mau hay khong
					if (ktr == 1)
						if (X == ListQuanCo[i]->GetX() + 1 && Y == ListQuanCo[i]->GetY() + 1)
							return 1;
					if (ktr == 0) {
						cout << "Kill(" << ListQuanCo[i]->GetY() + 1 << ", " << ListQuanCo[i]->GetX() + 1 << ")" << " ";
						ktrx = 2;
					}
				}
				if (ListQuanCo[i]->GetX() == GetX() + 1 && ListQuanCo[i]->GetColor() == 0)
				{//kiem tra phia tren ben phai co quan co quan co nao hay khong
					if (ktr == 1)
						if (X == ListQuanCo[i]->GetX() + 1 && Y == ListQuanCo[i]->GetY() + 1)
							return 1;
					if (ktr == 0) {
						cout << "Kill(" << ListQuanCo[i]->GetY() + 1 << ", " << ListQuanCo[i]->GetX() + 1 << ")" << " ";
						ktrx = 2;
					}
				}

				if (ListQuanCo[i]->GetX() == GetX()) {
					k1 = 1;
				}
			}
			if (ListQuanCo[i]->GetY() == GetY() - 2)
			{//kiem tra phia truoc 2 o co quan co nao hay khong
				if (ListQuanCo[i]->GetX() == GetX()) {
					k3 = 1;
				}
			}
		}
		else
		{
			if (ListQuanCo[i]->GetY() == GetY() + 1)//kiem tra hang phia truoc co quan co nao hay khong
			{
				if (ListQuanCo[i]->GetX() == GetX() + 1 && ListQuanCo[i]->GetColor() == 1)
				{//kiem tra phia tren ben phai co quan co khac mau nao hay khong
					if (ktr == 1)
						if (X == ListQuanCo[i]->GetX() + 1 && Y == ListQuanCo[i]->GetY() + 1)
							return 1;
					if (ktr == 0) {
						cout << "Kill(" << ListQuanCo[i]->GetY() + 1 << ", " << ListQuanCo[i]->GetX() + 1 << ")" << " ";
						ktrx = 2;
					}
				}
				if (ListQuanCo[i]->GetX() == GetX() - 1 && ListQuanCo[i]->GetColor() == 1)
				{//kiem tra phia tren ben trai co quan co khac mau nao hay khong
					if (ktr == 1)
						if (X == ListQuanCo[i]->GetX() + 1 && Y == ListQuanCo[i]->GetY() + 1)
							return 1;
					if (ktr == 0) {
						cout << "Kill(" << ListQuanCo[i]->GetY() + 1 << ", " << ListQuanCo[i]->GetX() + 1 << ")" << " ";
						ktrx = 2;
					}
				}
				if (ListQuanCo[i]->GetX() == GetX())
					k2 = 1;
			}
			if (ListQuanCo[i]->GetY() == GetY() + 2)
			{//kiem tra phia truoc 2 o co quan co nao hay khong
				if (ListQuanCo[i]->GetX() == GetX()) {
					k3 = 1;
				}
			}
		}
	}
	//di chuyen 
	if (k1 == 0 && GetColor() == 1) {
		if (ktr == 1)
			if (Y == GetY() && X == GetX() + 1)
				return 1;
		if (ktr == 0) {
			cout << "(" << GetY() << ", " << GetX() + 1 << ")" << " ";
			ktrx = 2;
		}
		if (firstMove == 0 && k3 == 0)//neu phia truoc 2 o khong co quan co nào va quan co chua di chuyen-> chot co the di dc 2 o 
		{
			if (ktr == 1)
				if (Y == GetY() - 1 && X == GetX() + 1)
					return 1;
			if (ktr == 0) {
				cout << "(" << GetY() - 1 << ", " << GetX() + 1 << ")" << " ";
				ktrx = 2;
			}
		}
	}
	//di chuyen
	if (k2 == 0 && GetColor() == 0) {
		if (ktr == 1)
			if (Y == GetY() + 2 && X == GetX() + 1)
				return 1;
		if (ktr == 0) {
			cout << "(" << GetY() + 2 << ", " << GetX() + 1 << ")" << " ";
			ktrx = 2;
		}
		if (firstMove == 0 && k3 == 0)//neu phia truoc 2 o khong co quan co nào va quan co chua di chuyen-> chot co the di dc 2 o 
		{
			if (ktr == 1)
				if (Y == GetY() + 3 && X == GetX() + 1)
					return 1;
			if (ktr == 0) {
				cout << "(" << GetY() + 3 << ", " << GetX() + 1 << ")" << " ";
				ktrx = 2;
			}
		}
	}
	return ktrx;//ktrx = 0, quan co khong di chuyen duoc, = 2 co the di chuyen dc 
}

/// hau ///////
Hau::Hau()
{
	this->itsSymbol = 'h';
}
Hau::~Hau()
{}
int Hau::RuleValidate(int Xt, int Yt)
{
	int ktrx = 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)//neu truyen vao tham so-> ham kiem tra di chuyen
		ktr = 1;
	if (ktr == 0)
		cout << "Hau - VI TRI GOI Y: ";
	///Kiem tra di len
	int X = GetX();
	int Y = GetY();
	int k = 0;
	Y--;
	while (Y >= 0)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y--;
	}

	//kiem tra di xuong
	X = GetX();
	Y = GetY();
	k = 0;
	Y++;
	while (Y <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << " Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y++;
	}


	//kiem tra sang phai
	X = GetX();
	Y = GetY();
	k = 0;
	X++;
	while (X <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X++;
	}

	//kiem tra sang trai
	X = GetX();
	Y = GetY();
	k = 0;
	X--;
	while (X >= 0)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X--;
	}

	/// cheo tren ben phai
	X = GetX();
	Y = GetY();
	k = 0;
	Y--;
	X++;
	while (Y >= 0 && X <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y--;
		X++;
	}


	//cheo tren ben trai
	X = GetX();
	Y = GetY();
	k = 0;
	Y--;
	X--;
	while (Y >= 0 && X >= 0)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y--;
		X--;
	}

	//kiem tra Xuong ben phai
	X = GetX();
	Y = GetY();
	k = 0;
	X++; Y++;
	while (X <= 7 && Y <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor())
				{
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X++;
		Y++;
	}


	//kiem tra xuong ben trai
	X = GetX();
	Y = GetY();
	k = 0;
	X--; Y++;
	while (X >= 0 && Y <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0)
						cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X--;
		Y++;
	}
	return ktrx;
}

/// ma
Ma::Ma()
{
	this->itsSymbol = 'm';
}
Ma::~Ma()
{

}
int Ma::Ktr_Xuat(int X, int Y, int Xt, int Yt, int& ktrx)
{
	if (X > 7 || X < 0 || Y>7 || Y < 0)
		return 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)
		ktr = 1;
	int k = 0;

	for (int i = 0; i < ListQuanCo.size(); i++)
	{
		if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y)
		{
			k = 1;
			if (GetColor() != ListQuanCo[i]->GetColor()) {
				k = 2;
				if (ktr == 0)
					cout << " Kill";
			}
			break;
		}
	}
	if (k == 0 || k == 2) {
		if (ktr == 1)
			if (Xt == X + 1 && Yt == Y + 1)
				return 1;
		if (ktr == 0) {
			cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
			ktrx = 2;
		}
	}
	return 0;
}
int Ma::RuleValidate(int Xt, int Yt)
{
	int ktrx = 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)
		ktr = 1;
	if (ktr == 0)
		cout << "MA - VI TRI GOI Y:";
	int X = GetX() - 1;
	int Y = GetY() - 2;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() + 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	Y = GetY() + 2;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() - 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;

	X = GetX() - 2;
	Y = GetY() - 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	Y = GetY() + 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() + 2;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	Y = GetY() - 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	return ktrx;
}

/// tuong
Tuong::Tuong()
{
	this->itsSymbol = 't';
}
Tuong::~Tuong() {}
int Tuong::RuleValidate(int Xt, int Yt)
{
	int ktrx = 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)
		ktr = 1;
	if (ktr == 0)
		cout << "TUONG - VI TRI GOI Y: ";
	///Cheo ben phai
	int X = GetX();
	int Y = GetY();
	int k = 0;
	Y--;
	X++;
	while (Y >= 0 && X <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y--;
		X++;
	}


	//cheo tren ben trai
	X = GetX();
	Y = GetY();
	k = 0;
	Y--;
	X--;
	while (Y >= 0 && X >= 0)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y--;
		X--;
	}

	//kiem tra Xuong ben phai
	X = GetX();
	Y = GetY();
	k = 0;
	X++; Y++;
	while (X <= 7 && Y <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor())
				{
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X++;
		Y++;
	}


	//kiem tra xuong ben trai
	X = GetX();
	Y = GetY();
	k = 0;
	X--; Y++;
	while (X >= 0 && Y <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X--;
		Y++;
	}
	return ktrx;;
}

//// vua
Vua::Vua()
{
	this->itsSymbol = 'V';
	this->SL++;
}
Vua::~Vua()
{
	this->SL--;
}
int Vua::Ktr_Xuat(int X, int Y, int Xt, int Yt, int& ktrx)
{
	if (X > 7 || X < 0 || Y > 7 || Y < 0)
		return 0;
	int k = 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)
		ktr = 1;
	for (int i = 0; i < ListQuanCo.size(); i++)
	{
		if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y)
		{
			k = 1;
			if (GetColor() != ListQuanCo[i]->GetColor()) {
				k = 2;
				if (ktr == 0)
					cout << " Kill";
			}
			break;
		}
	}
	if (k == 0 || k == 2) {
		if (ktr == 1)
		{
			if (Xt == X + 1 && Yt == Y + 1)
				return 1;
		}
		if (ktr == 0) {
			cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
			ktrx = 2;
		}
	}
	return 0;
}
int  Vua::RuleValidate(int Xt, int Yt)
{
	int ktrx = 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)
		ktr = 1;
	if (ktr == 0)
		cout << "VUA - VI TRI GOI Y: ";
	int X = GetX() - 1;
	int Y = GetY();
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX();
	Y = GetY() - 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() + 1;
	Y = GetY();
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX();
	Y = GetY() + 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() - 1;
	Y = GetY() + 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() + 1;
	Y = GetY() - 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() + 1;
	Y = GetY() + 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	X = GetX() - 1;
	Y = GetY() - 1;
	this->Ktr_Xuat(X, Y, Xt, Yt, ktrx);
	if (ktr == 1)
		if (this->Ktr_Xuat(X, Y, Xt, Yt, ktrx) == 1)
			return 1;
	return ktrx;
}
Xe::Xe()
{
	this->itsSymbol = 'x';
}
Xe::~Xe() {}
int Xe::RuleValidate(int Xt, int Yt)
{
	int ktrx = 0;
	int ktr = 0;
	if (Xt != -1 && Yt != -1)
	{
		ktr = 1;
	}
	if (ktr == 0)
		cout << "XE - VI TRI GOI Y: ";
	///Kiem tra di len
	int X = GetX();
	int Y = GetY();
	int k = 0;
	Y--;
	while (Y >= 0)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y--;
	}

	//kiem tra di xuong
	X = GetX();
	Y = GetY();
	k = 0;
	Y++;
	while (Y <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		Y++;
	}


	//kiem tra sang phai
	X = GetX();
	Y = GetY();
	k = 0;
	X++;
	while (X <= 7)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
			{
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			}
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X++;
	}

	//kiem tra sang trai
	X = GetX();
	Y = GetY();
	k = 0;
	X--;
	while (X >= 0)
	{
		for (int i = 0; i < ListQuanCo.size(); i++)
		{
			if (ListQuanCo[i]->GetX() == X && ListQuanCo[i]->GetY() == Y) {
				k = 1;
				if (GetColor() != ListQuanCo[i]->GetColor()) {
					k = 2;
					if (ktr == 0);
					cout << "Kill";
				}
				break;
			}
		}
		if (k == 0 || k == 2) {
			if (ktr == 1)
				if (Yt == Y + 1 && Xt == X + 1)
					return 1;
			if (ktr == 0) {
				cout << "(" << Y + 1 << ", " << X + 1 << ")" << " ";
				ktrx = 2;
			}
		}
		if (k == 1 || k == 2)
			break;
		X--;
	}
	return ktrx;
}

int Vua::SL = 0;
void InitBoard()
{
	for (int i = 0; i < BOARDMAX; i++)
	{
		for (int j = 0; j < BOARDMAX; j++)
		{
			if ((i % 2 == 0) && (j % 2 == 0) || (i % 2 != 0) && (j % 2 != 0))
				Board[i][j] = 219;	// Ky tu o vuong trong bang ma ASII
			else
				Board[i][j] = ' ';		// Ky tu NULL.
		}
	}

	Board[0][8] = Board[8][0] = '1';	// So 1 trong bang ma ASII
	Board[1][8] = Board[8][1] = '2';	// So 2.
	Board[2][8] = Board[8][2] = '3';	// So 3.
	Board[3][8] = Board[8][3] = '4';	// So 4.
	Board[4][8] = Board[8][4] = '5';	// So 5.
	Board[5][8] = Board[8][5] = '6';	// So 6.
	Board[6][8] = Board[8][6] = '7';	// So 7.
	Board[7][8] = Board[8][7] = '8';	// So 8.
	Board[8][8] = 0;
	// Ky tu NULL;

	for (int i = 0; i < MAXPAWNS; ++i) {
		QuanCo* p = new Chot();
		ListQuanCo.push_back(p);
	}
	for (int i = 0; i < MAXKNIGHTS; i++)
	{
		QuanCo* p = new Ma();
		ListQuanCo.push_back(p);
	}
	for (int i = 0; i < MAXBISHOPS; ++i)
	{
		QuanCo* p = new Tuong();
		ListQuanCo.push_back(p);
	}
	for (int i = 0; i < MAXROOKS; ++i)
	{
		QuanCo* p = new Xe();
		ListQuanCo.push_back(p);
	}
	for (int i = 0; i < MAXQUEENS; ++i)
	{
		QuanCo* p = new Hau();
		ListQuanCo.push_back(p);
	}
	for (int i = 0; i < MAXKINGS; ++i)
	{
		QuanCo* p = new Vua();
		ListQuanCo.push_back(p);
	}

	for (int i = 0; i < 8; ++i)
	{// Dat Tot cua quan A len toa do ban co.
		ListQuanCo[i]->SetX(i);
		ListQuanCo[i]->SetY(1);
	}
	for (int i = 8; i < 16; ++i)
	{// Dat Tot cua quan B len toa do ban co.
		ListQuanCo[i]->SetX(i - 8);
		ListQuanCo[i]->SetY(6);
		ListQuanCo[i]->SetColorBlack();
	}
	ListQuanCo[MAXPIECES - 16]->SetX(1);	// Dat toa do cho Ma1  cua quan A.
	ListQuanCo[MAXPIECES - 16]->SetY(0);
	ListQuanCo[MAXPIECES - 15]->SetX(6);	// Dat toa do cho Ma2  cua quan A.
	ListQuanCo[MAXPIECES - 15]->SetY(0);

	ListQuanCo[MAXPIECES - 14]->SetX(1);	// Dat toa do cho Ma1  cua quan B..
	ListQuanCo[MAXPIECES - 14]->SetY(7);
	ListQuanCo[MAXPIECES - 14]->SetColorBlack();
	ListQuanCo[MAXPIECES - 13]->SetX(6);	// Dat toa do cho Ma2  cua quan B.
	ListQuanCo[MAXPIECES - 13]->SetY(7);
	ListQuanCo[MAXPIECES - 13]->SetColorBlack();

	ListQuanCo[MAXPIECES - 12]->SetX(2);	// Dat toa do cho Tinh1 cua quan A.
	ListQuanCo[MAXPIECES - 12]->SetY(0);
	ListQuanCo[MAXPIECES - 11]->SetX(5);	// Dat toa do cho Tinh2 cua quan A.
	ListQuanCo[MAXPIECES - 11]->SetY(0);

	ListQuanCo[MAXPIECES - 10]->SetX(2);	// Dat toa do cho Tinh1 cua quan B.
	ListQuanCo[MAXPIECES - 10]->SetY(7);
	ListQuanCo[MAXPIECES - 10]->SetColorBlack();
	ListQuanCo[MAXPIECES - 9]->SetX(5);	// Dat toa do cho Tinh2 cua quan B.
	ListQuanCo[MAXPIECES - 9]->SetY(7);
	ListQuanCo[MAXPIECES - 9]->SetColorBlack();

	ListQuanCo[MAXPIECES - 8]->SetX(0);	// Dat toa do cho Xe1 cua quan A.
	ListQuanCo[MAXPIECES - 8]->SetY(0);
	ListQuanCo[MAXPIECES - 7]->SetX(7);	// Dat toa do cho Xe2 cua quan A.
	ListQuanCo[MAXPIECES - 7]->SetY(0);

	ListQuanCo[MAXPIECES - 6]->SetX(0);	// Dat toa do cho Xe1 cua quan B.
	ListQuanCo[MAXPIECES - 6]->SetY(7);
	ListQuanCo[MAXPIECES - 6]->SetColorBlack();
	ListQuanCo[MAXPIECES - 5]->SetX(7);	// Dat toa do cho Xe2 cua quan B.
	ListQuanCo[MAXPIECES - 5]->SetY(7);
	ListQuanCo[MAXPIECES - 5]->SetColorBlack();

	ListQuanCo[MAXPIECES - 4]->SetX(4);	// Dat toa do cho Hau cua quan A.
	ListQuanCo[MAXPIECES - 4]->SetY(0);

	ListQuanCo[MAXPIECES - 3]->SetX(4);	// Dat toa do cho Hau cua quan B.
	ListQuanCo[MAXPIECES - 3]->SetY(7);
	ListQuanCo[MAXPIECES - 3]->SetColorBlack();

	ListQuanCo[MAXPIECES - 2]->SetX(3);	// Dat toa do cho Vua cua quan A.
	ListQuanCo[MAXPIECES - 2]->SetY(0);

	ListQuanCo[MAXPIECES - 1]->SetX(3);	// Dat toa do cho Vua cua quan B.
	ListQuanCo[MAXPIECES - 1]->SetY(7);
	ListQuanCo[MAXPIECES - 1]->SetColorBlack();
}

void Draw()
{
	for (int i = 0; i < BOARDMAX; i++)
	{
		for (int j = 0; j < BOARDMAX; j++)
		{
			int q = 1;
			for (int BLACK = 0; BLACK < ListQuanCo.size(); BLACK++)
			{
				if (ListQuanCo[BLACK]->GetX() == j && ListQuanCo[BLACK]->GetY() == i)
				{
					ListQuanCo[BLACK]->DrawSymbol();
					q = 0;
				}
			}
			if (q == 1)
			{
				cout << Board[i][j];
			}
		}
		cout << "\n";
	}
}
void PhongHau(int chon, vector<QuanCo*>& List, QuanCo* sW)
{
	if (chon == 1)
	{
		QuanCo* a = new Hau();
		a->SetX(sW->GetX());
		a->SetY(sW->GetY());
		if (sW->GetColor() == 1)
			a->SetColorBlack();
		List.push_back(a);
	}
	if (chon == 2)
	{
		QuanCo* a = new Ma();
		a->SetX(sW->GetX());
		a->SetY(sW->GetY());
		if (sW->GetColor() == 1)
			a->SetColorBlack();
		List.push_back(a);
	}
	if (chon == 3)
	{
		QuanCo* a = new Xe();
		a->SetX(sW->GetX());
		a->SetY(sW->GetY());
		if (sW->GetColor() == 1)
			a->SetColorBlack();
		List.push_back(a);
	}
	if (chon == 4)
	{
		QuanCo* a = new Tuong();
		a->SetX(sW->GetX());
		a->SetY(sW->GetY());
		if (sW->GetColor() == 1)
			a->SetColorBlack();
		List.push_back(a);
	}
}
void Go()
{
	int rightColor, a, b, c, d;//a, b: tao do diem chon; c, d: toa do di chuyen
	if (turn % 2 == 0)
	{
		rightColor = 0;
	}
	else
	{
		rightColor = 1;
	}
	cout << "Chon 1 quan co.\n";
	cout << "Nhap (y, x): ";
	cin >> a >> b;
	int ib;
	for (ib = 0; ib < ListQuanCo.size(); ++ib)
	{
		if ((ListQuanCo[ib]->GetX() == b - 1) && (ListQuanCo[ib]->GetY() == a - 1)) {
			if (ListQuanCo[ib]->GetColor() != rightColor) {
				cout << "DAY KHONG PHAI QUAN CO CUA BAN. NHAN PHIM BAT KI DE NHAP LAI\n";
				turn--;
				system("pause");
				return;
			}
			if (ListQuanCo[ib]->RuleValidate() == 0)
			{
				cout << "Quan co nay ko the di chuyen, moi ban chon quan co khac\n";
				turn--;
				system("pause");
				return;
			}
			break;
		}
	}
	if (ib == ListQuanCo.size())
	{
		cout << "Vi tri ban chon rong!.Vui long nhan phim bat ki de chon lai\n";
		turn--;
		system("pause");
		return;
	}
	cout << "\n\n1 - Di Chuyen.\n2 - Quay Lai\nMenu: ";
	while (true) {
		int chon;
		cin >> chon;
		if (chon == 2) {
			turn--;
			return;
		}
		else if (chon == 1)
			break;
		else if (chon < 1 || chon>2)
			cout << "Chon thuoc [1, 2]: ";
	}
	int kt = 0;
	while (kt == 0) {
		cout << "Chon vi tri muon den.\n";
		cout << "Nhap (y, x): ";
		cin >> c >> d;
		if (ListQuanCo[ib]->RuleValidate(d, c) == 1) {
			ListQuanCo[ib]->SetX(d - 1);
			ListQuanCo[ib]->SetY(c - 1);
			if (strcmp(typeid(*ListQuanCo[ib]).name(), "class Chot") == 0)
				ListQuanCo[ib]->setf(1);
			kt = 1;
		}
		else
		{
			cout << "Ban Nhap ko dung voi goi y, vui long nhap lai! ";
		}
	}
	for (int BLACK = 0; BLACK < ListQuanCo.size(); BLACK++)
	{//check to see if it takes another piece
		if ((ListQuanCo[ib]->GetX() == ListQuanCo[BLACK]->GetX()) && (ListQuanCo[ib]->GetY() == ListQuanCo[BLACK]->GetY()))
		{
			if (ib != BLACK)
			{
				if (strcmp(typeid(*ListQuanCo[BLACK]).name(), "class Vua") == 0)
					Vua::SL--;
				ListQuanCo.erase(ListQuanCo.begin() + BLACK);
			}
		}
	}

	///Ktr xem Chot co can phong hau
	for (int BLACK = 0; BLACK < ListQuanCo.size(); BLACK++)
	{
		if ((7 == ListQuanCo[BLACK]->GetY()) || 0 == ListQuanCo[BLACK]->GetY())
		{
			if (strcmp(typeid(*ListQuanCo[BLACK]).name(), "class Chot") == 0) {
				cout << "Chon tuong de phong (1 - Hau, 2 - Ma, 3 - Xe, 4 - Tuong): ";
				int chon;
				cin >> chon;
				PhongHau(chon, ListQuanCo, ListQuanCo[BLACK]);
				ListQuanCo.erase(ListQuanCo.begin() + BLACK);
			}
		}
	}
}

int main()
{
	InitBoard();
	while (true) {
		Draw();
		if (Vua::SL == 1) {
			if (turn % 2 == 0)
				cout << "\n----------Ben do thang--------\n";
			else
				cout << "\n-----------Ben xanh thang--------\n";
			system("pause");
			break;
		}
		if (turn % 2 == 0)
			cout << "************** Den luot ben xanh **************\n";
		else
			cout << "**************** Den luot ben do**************\n";
		Go();
		turn++;
		system("cls");
	}
	//ListQuanCo.clear();
}

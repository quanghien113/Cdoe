#ifndef _DISPLAY_H
#define _DISPLAY_H
#include "Airplane.h"

const int so_item = 8;
const int dong =5;
const int cot = 20 ;
const int Up = 72;
const int Down = 80;

const int MAXLIST =100;
char thucdon [so_item][50] = {"1. QUAN LY MAY BAY",
			                  "2. QUAN LY CHUYEN BAY      ",
			                  "3. Tim kiem May Bay  ....    ",
			                  "4. Xoa mot May Bay  ....     ",
			                  "5. Ghi danh sach     ....     ",
			                  "6. Mo  danh sach      ...    ",
			                  "7. Them May Bay co thu tu   ...   ",
			                  "8. Ket thuc chuong trinh  ...."};




void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(0);
	SetBGColor(1);
}
int MenuDong(char td [so_item][50]){ 
  Normal();
  system("cls");   int chon =0;
  int i; 
  for ( i=0; i< so_item ; i++)
  { Gotoxy(cot, dong +i);
    cout << td[i];
  }
  HighLight();
  Gotoxy(cot,dong+chon);
  cout << td[chon];
  char kytu;
do {
  kytu = getch();
  if (kytu==0) kytu = getch();
  switch (kytu) {
    case Up :if (chon+1 >1)
  			  {
  		              	Normal();
              	Gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon --;
              	HighLight();
              	Gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal();
              	Gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon ++;
              	HighLight();
              	Gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case 13 : return chon+1;
  }  // end switch
  } while (1);
}


//main menu-----
string keyMainMenu[5] = { "May Bay" ,"Chuyen Bay","Hanh Khach","Dat Ve" ,"Thong Ke" };
string keyStatistic[4] = { "Hanh Khach 1 Chuyen Bay", "Chuyen Bay Trong Ngay", "Chuyen Bay Cua 1 May Bay","Danh Sach Ve" };
int xMainMenu[5] = { 10,45,80,115,145 };

void taobang(int x, int y, string text, int length)
{
	Gotoxy(x - 2, y - 1);
	cout << char(201) << setw(length) << setfill(char(205)) << char(205) << char(187);

	Gotoxy(x - 2, y);
	cout << char(186) << text << setw(length - text.length() + 1) << setfill(' ') << char(186);

	Gotoxy(x - 2, y + 1);
	cout << char(200) << setw(length) << setfill(char(205)) << char(205) << char(188);
}


//void   EffectiveMenuHorizontal(string key[], int pos)
//{
//	int current = pos;
//
//	Gotoxy(xMainMenu[current] -1, Y_MAIN_MENU);
//	SetBGColor(GREEN);
//	cout << key[current];
//
//	Gotoxy(xMainMenu[currposPreMainMenu] - 1, Y_MAIN_MENU);
//	SetBGColor(PURPLE);
//	cout << key[currposPreMainMenu];
//
//	currposPreMainMenu = current;
//}
//
//
//void ChangeColorItemMainMenu(string key, int index, int newColor, int oldColor)
//{
//	Gotoxy(xMainMenu[index] -1 , Y_MAIN_MENU);
//	SetBGColor(newColor);
//	cout << key;
//	SetBGColor(oldColor);
//	
//}
//void MainMenu(string key[], int nKey)
//{
//	system("color 5A");
//	for (int i = 0; i < nKey; i++)
//	{
//		CreateBox(xMainMenu[i], Y_MAIN_MENU, key[i], key[i].length());
//	}
//	ChangeColorItemMainMenu(key[0], 0, GREEN, PURPLE);
//}
//
//int ChooseMainMenu(string key[], int nKey)
//{
//	ShowCur(false);
//	currposMainMenu = 0;
//	currposPreMainMenu = 0;
//	int keyboard_read = 0;
//	while (true)
//	{
//		keyboard_read = _getch();
//		if (keyboard_read == 0)
//			keyboard_read = _getch();
//
//		switch (keyboard_read)
//		{
//		case KEY_LEFT: //key left
//			if (currposMainMenu > 0)
//				currposMainMenu = currposMainMenu - 1;
//			else
//				currposMainMenu = nKey - 1; //move to last value in menu system
//			EffectiveMenuHorizontal(key, currposMainMenu);
//			break;
//		case KEY_RIGHT: //key right
//			if (currposMainMenu < nKey-1)
//				currposMainMenu = currposMainMenu + 1;
//			else
//				currposMainMenu = 0;//move to first value in menu system
//			EffectiveMenuHorizontal(key, currposMainMenu);
//			break;
//		case ESC:
//			return -1;
//			break;
//		case ENTER: //enter
//			ShowCur(true);
//			return currposMainMenu;
//			break;
//		}
//	}
//}
////------------------------END MENU----



//-----------TICKET
//1 ticket
void BoxTicket(int x, int y, int  text, int stt)
{
	Gotoxy(x - 2, y - 1);
	cout << char(201) << setw(3) << setfill(char(205)) << char(205) << char(187);
	cout << endl;
	Gotoxy(x - 2, y);
	if (stt == TICKET_SOLD) SetBGColor(stt);
	cout << char(186) << setw(3) << setfill('0') << text << char(186);
	SetBGColor(PURPLE);
	Gotoxy(x - 2, y + 1);
	cout << char(200) << setw(3) << setfill(char(205)) << char(205) << char(188);
}
//-----------end ticket



void DisplayEdit(string key[], int nKey,int length)
{
	int yAdd = Y_ADD;
	for (int i = 0; i < nKey; i++)
	{
		taobang(X_ADD, yAdd,key[i],length);
		yAdd += 3;
	}
}
void DeleteMenuAdd()
{
	for (int i = 0; i < 20; i++)
	{
		Gotoxy(X_ADD -2, Y_ADD+i-1);
		cout << setw(60) << setfill(' ') << " ";
	}
}

string keyDisplayAirplane[4] = { "SH MB: ", "Loai MB: ", "So day: ", "So dong: " };
string keyDisplayFlight[6] = { "Ma Chuyen Bay:", "SH MB:", "Ngay Gio:","San Bay Den:","Trang Thai:","So Ve:" };
string keyDisplayFlight_Edit[5] = { "Ma Chuyen Bay:", "SH MB:", "Ngay Gio:","San Bay Den:","Trang Thai:"};
string keyDisplayPassenger[4] = { "CMND: ", "Ho: ","Ten: ","Gioi tinh: " };

string keyDisplayInputIdPassenger[1] = {"CMND: "};
string keyDisplayAddFlight[5] = {"Ma Chuyen Bay:", "SH MB:", "Ngay Gio:","San Bay Den:","Trang Thai:"};


int xKeyDisplay[7] = {1,20,45,65,80,95, 107};



void Display(string key[], int nKey)
{
	
	//show key
	for (int i = 0; i < nKey; i++)
	{
		Gotoxy(xKeyDisplay[i] + 3, Y_DISPLAY+ 1);
		cout << key[i];
	}

	//show column 2 side
	for (int j = Y_DISPLAY; j <= Y_DISPLAY + 40; j++)
	{
		for (int i = 0; i < nKey+1; i++)
		{
			Gotoxy(xKeyDisplay[i], j);
			cout << char(186);
		}
	}

	//border left->right
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nKey]; i++)
	{
		//border top (key)
		Gotoxy(i, Y_DISPLAY);
		if (i == xKeyDisplay[1] || i == xKeyDisplay[2] || i == xKeyDisplay[3] || i == xKeyDisplay[4])
			cout << char(203);//nga 3
		else if (i == xKeyDisplay[0])
		{
			cout << char(201); //moc phai
		}
		else if (i == xKeyDisplay[nKey])
		{
			cout << char(187);//moc trai
		}  
		else
		{
			cout << char(205); //duong thang ngang
		}

		//border bottom(key)
		Gotoxy(i, Y_DISPLAY + 2);
		if (i == xKeyDisplay[1] || i == xKeyDisplay[2] || i == xKeyDisplay[3] || i == xKeyDisplay[4])
			cout << char(206); //nga 4
		else if (i == xKeyDisplay[0])
		{
			cout << char(204); //nga 3 sang phai
		}
		else if (i == xKeyDisplay[nKey])
		{
			cout << char(185);//nga 3 sang trai
		}
		else
		{
			cout << char(205); //duong thang ngang
		}


		//border top (note)
		Gotoxy(i, Y_DISPLAY + 39);
		if (i == xKeyDisplay[nKey])
		{
			cout << char(185); //nga 3 sang trai
		}
		else if (i == xKeyDisplay[1] || i == xKeyDisplay[2] || i == xKeyDisplay[3] || i == xKeyDisplay[4])
			cout << char(202);
		else if (i == xKeyDisplay[0])
			cout << char(204); //nga 3 sang phai
		else
		{
			cout << char(205); //duong thang ngang
		}


		//border bottom (note)
		Gotoxy(i, Y_DISPLAY + 41);
		if (i == xKeyDisplay[0])
		{
			cout << char(200); //qeo sang phai
		}
		else if (i == xKeyDisplay[nKey])
		{
			cout << char(188); //qeo sang trai
		}
		else
		{
			cout << char(205); //duong thang ngang
		}
	}
	// SHOW note
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[nKey] - xKeyDisplay[0]-1) << "F2: them F3: Xoa F4: Hieu Chinh F10: Save" << setfill(' ');
}

void DeleteOldData(int nKey, int locate)
{
	for (int i = 0; i < nKey; i++)
	{
		Gotoxy(xKeyDisplay[i] + 1, Y_DISPLAY + 3 + locate);
		cout << setw(xKeyDisplay[i + 1] - xKeyDisplay[i]-2) << setfill(' ') << " ";		
	}
}
void DeleteGuide(int nColumn)
{
	for (int i = 0; i < 4; i++)
	{
		Gotoxy(xKeyDisplay[0] - 1, Y_DISPLAY + 39 + i);
		cout << setw(xKeyDisplay[nColumn] - xKeyDisplay[0] + 3) << " " << setfill(' ');
	}
}
void DeleteNote(int nColumn)
{
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[nColumn] - xKeyDisplay[0] - 1) << " " << setfill(' ');
}
void DeleteNotify()
{
	Gotoxy(X_NOTIFY, Y_NOTIFY);
	cout << setw(35) << setfill(' ') << " ";
}

#endif

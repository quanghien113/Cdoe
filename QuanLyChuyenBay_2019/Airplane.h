#ifndef _AIRPLANE_H
#define _AIRPLANE_H
#include "validate.h"

struct Airplane
{
	char numAir[16];	// so hieu may bay
	char typeAir[41];	//loai may bay
	int sequenceNumber; // so day ghe
	int lineNumber; 	// so dong
};
typedef struct Airplane AIRPLANE;
typedef AIRPLANE* PTR_AIRPLANE;
int pageNowAirplane = 1;
int currposAirplane = 0;
int currposPrecAirplane = 0;
int totalPageAirplane = 0;
struct ListAirplane
{
	int n = -1; //also index
	PTR_AIRPLANE *listAirplane = new PTR_AIRPLANE[MAX_AIRPLANE];
};
typedef struct ListAirplane LIST_AIRPLANE;
typedef LIST_AIRPLANE* PTR_LIST_AIRPLANE;


PTR_AIRPLANE FindAirplane(PTR_LIST_AIRPLANE l, char id[])	// tra ve 1 may bay
{
	if (l->n < 0) return NULL;
	for (int i = 0; i <= l->n; i++)
		if (_stricmp(l->listAirplane[i]->numAir, id) == 0) return l->listAirplane[i];	// so sanh chuoi
	return NULL;
}

int FindIndexAirplane(PTR_LIST_AIRPLANE l, char id[]) // tra ve index(chi so) cua may bay
{
	if (l->n < 0) return -1;
	for (int i = 0; i <= l->n; i++)
		if (_strcmpi(l->listAirplane[i]->numAir, id) == 0) return i;
	return -1;
}

void OutputAirplane(PTR_AIRPLANE al, int ordinal)
{
	DeleteOldData(sizeof(keyDisplayAirplane) / sizeof(string), ordinal);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + ordinal); cout << al->numAir;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + ordinal); cout << al->typeAir;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + ordinal); cout << al->sequenceNumber;
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + ordinal); cout << al->lineNumber;
}

bool DataAirplaneIsEmpty(PTR_AIRPLANE al)
{
	if (strlen(al->numAir) == 0 || strlen(al->typeAir) == 0) return true;
	if (al->lineNumber == 0 || al->sequenceNumber == 0) return true;
	return false;
}

/*void SwapAirplane(PTR_AIRPLANE &a, PTR_AIRPLANE &b)
{
	PTR_AIRPLANE temp = a;
	a = b;
	b = temp;
} */


bool DeleteAirplaneIsSucceed(PTR_LIST_AIRPLANE &l, char *id)
{
	int index = FindIndexAirplane(l, id);
	if (index == -1) return false; //esc no choose
	for (int i = index; i < l->n; i++)
		l->listAirplane[i] = l->listAirplane[i + 1];
	l->n--;
	return true;
}

void OutputListAirplanePerPage(PTR_LIST_AIRPLANE l, int indexBegin)	// xuat ds theo trang (Phan Trang)
{
	if (l == NULL) return;
	for (int i = 0; i + indexBegin <= l->n && i < QUANTITY_PER_PAGE; i++)
		OutputAirplane(l->listAirplane[i+ indexBegin], i*2);
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowAirplane << "/" << totalPageAirplane;
}

void SetDefaultChosenAirplane(PTR_LIST_AIRPLANE l, int ordinal)	// to mau may bay can xoa.
{
	SetBGColor(1);
	OutputAirplane(l->listAirplane[ordinal], (ordinal % QUANTITY_PER_PAGE)*2);
	SetBGColor(0);
}
void   EffectiveMenuAirplane(int ordinal, PTR_LIST_AIRPLANE l)	//thay doi color cua dong dang chon
{
	int current = ordinal;
	SetDefaultChosenAirplane(l, current);
	OutputAirplane(l->listAirplane[currposPrecAirplane], (currposPrecAirplane % QUANTITY_PER_PAGE) * 2); // currposPe.. vi tri hien tai
	currposPrecAirplane = current;
}
void ChangePageAirplane(PTR_LIST_AIRPLANE l)	// chuyen trang
{
	clrscr();
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	DeleteNote(sizeof(keyDisplayAirplane) / sizeof(string));
	currposAirplane = (pageNowAirplane - 1) * QUANTITY_PER_PAGE;
	currposPrecAirplane = (pageNowAirplane - 1) * QUANTITY_PER_PAGE;
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowAirplane << "/" << totalPageAirplane;
}
int ChooseAirplane(PTR_LIST_AIRPLANE l)	// chon maybay can thao tac.
{
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	pageNowAirplane = 1;
	currposAirplane = 0;
	currposPrecAirplane = 0;
	
	OutputListAirplanePerPage(l,0);
	SetDefaultChosenAirplane(l, currposAirplane);
	
	while (true)
	{
		
		while (_kbhit())
		{
			keyboard_read = _getch();
			if (keyboard_read == 0)
				keyboard_read = _getch();
			switch (keyboard_read)
			{
			case KEY_UP:
				if (currposAirplane % QUANTITY_PER_PAGE > 0)	// keyup co tac dung khi khong nam o dong dau tien.
				{
					currposAirplane = currposAirplane - 1;
					EffectiveMenuAirplane(currposAirplane, l);
				}
				break;
			case KEY_DOWN:
				if (currposAirplane % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposAirplane < l->n) // keydown co tac dung khi nam o dong khac cuoi & khac phan tu cuoi cua mang.
				{
					currposAirplane = currposAirplane + 1;
					EffectiveMenuAirplane(currposAirplane, l);
				}
				break;
			case PAGE_DOWN:
				if (pageNowAirplane < totalPageAirplane)
				{

					pageNowAirplane++;
					ChangePageAirplane(l);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenAirplane(l, currposAirplane);

				}
				break;
			case PAGE_UP:
				if (pageNowAirplane > 1)
				{

					pageNowAirplane--;
					ChangePageAirplane(l);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenAirplane(l, currposAirplane);

				}
				break;
			case ESC:
				ShowCur(false);
				return -1;
				break; // no choose
			case ENTER:
				ShowCur(false);
				return currposAirplane;
				break;
			}
		}
		
	}
}

void InputAirplane(PTR_LIST_AIRPLANE &l, PTR_AIRPLANE al, bool isEdited = false) //True: chinh sua, False: them moi
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	string id, typeAir;
	int numLine = 0;
	int numSequence = 0;
	bool idIsExist = false;
	if (isEdited)
	{
		id = al->numAir;
		typeAir = al->typeAir;

		numLine = al->lineNumber;
		numSequence = al->sequenceNumber;
		//binding data
		Gotoxy(X_ADD + 6, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 7, 1 * 3 + Y_ADD);
		cout << typeAir;
		Gotoxy(X_ADD + 7, 2 * 3 + Y_ADD);
		cout << numSequence;
		Gotoxy(X_ADD + 7, 3 * 3 + Y_ADD);
		cout << numLine;
	}

	while (true)
	{
		switch (ordinal)
		{
		case 0:
			if(isEdited) break;
			CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave, 6);
		
			if (FindAirplane(l, (char *)id.c_str()) == NULL)
			{
				idIsExist = false;
				break;
			}
			else idIsExist = true;
			break;
		case 1:
			CheckMoveAndValidateName(typeAir, isMoveUp, ordinal, isSave, 7);
			break;
		case 2:
			CheckMoveAndValidateNumber(numSequence, isMoveUp, ordinal, isSave, 7, 5);
			break;
		case 3:
			CheckMoveAndValidateNumber(numLine, isMoveUp, ordinal, isSave, 7, 20);
		}//switch 

		if (isMoveUp)
		{
			if (ordinal == 0)isMoveUp = false;
			ordinal--;
		}
		else
		{
			if (ordinal == 3)isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";

			if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "So hieu may bay khong duoc trung";				
			}
			else
			{
				PTR_AIRPLANE temp = new AIRPLANE;	// tao 1 may bay TAM
				strcpy(temp->numAir, id.c_str());
				strcpy(temp->typeAir, typeAir.c_str());
				temp->lineNumber = numLine;
				temp->sequenceNumber = numSequence;
				if (DataAirplaneIsEmpty(temp))
				{
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Cac truong du lieu khong dc de trong";
				}
				else
				{
					strcpy(al->numAir, id.c_str());
					strcpy(al->typeAir, typeAir.c_str());
					al->sequenceNumber = numSequence;
					al->lineNumber = numLine;
					if (isEdited)	// sua may bay
					{
						int index = FindIndexAirplane(l, al->numAir);
						l->listAirplane[index] = al;						
					}
					else	// them moi may bay
					{
						l->listAirplane[++l->n] = new AIRPLANE;
						l->listAirplane[l->n] = al;
					}
					DeleteMenuAdd();	// xoa menu them moi
					//totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
					delete temp;	// Xoa may bay TAM
					return;
				}
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);
}

void ChangePageManageAirplane(PTR_LIST_AIRPLANE l)	// Thay doi Trang khi hien thi ds MAyBay
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC MAY BAY";
	OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
}

void MenuManageAirplane(PTR_LIST_AIRPLANE &l)
{
backMenu:
	clrscr();
	pageNowAirplane = 1;
	totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
	
	OutputListAirplanePerPage(l, 0);
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	int key;
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC MAY BAY";
	Gotoxy(X_PAGE, Y_PAGE);
	while (true)
	{
		
		while (_kbhit())
		{		
			
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				if (key == KEY_F2)	// F2 la them moi
				{
					PTR_AIRPLANE al = new AIRPLANE;
					DisplayEdit(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string), 35);
					InputAirplane(l, al);
					
					totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;	// Tinh lai tong so TRANG
				//	pageNowAirplane = 1;
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
				}
				else if (key == KEY_F3) //f3 Xoa MAYBAY
				{
					int k = ChooseAirplane(l);
					if (k == -1) goto backMenu; //Khi an ESC thi quay lai 
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << setw(50) << setfill(' ') << " ";
					if (key == ENTER)
					{
						bool isDeleted = DeleteAirplaneIsSucceed(l, l->listAirplane[k]->numAir);
						if (!isDeleted)
						{
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa that bai. An phim bat ki de tiep tuc."<<endl;
							_getch();
							goto backMenu;
						}
						else
						{
							clrscr();
							Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
							if ((l->n + 1) % QUANTITY_PER_PAGE == 0) pageNowAirplane--;
							totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
							OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
						}
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4)	// F4 sua thong tin MAYBAY
				{
					int k = ChooseAirplane(l);
					if (k == -1) goto backMenu;;
					Gotoxy(X_ADD, 40);
					DisplayEdit(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string), 35);
					InputAirplane(l, l->listAirplane[k], true);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Sua thanh cong";
				}
				else if (key == PAGE_DOWN && pageNowAirplane < totalPageAirplane)
				{
					
					pageNowAirplane++;
					ChangePageManageAirplane(l);
				}
				else if (key == PAGE_UP && pageNowAirplane > 1)
				{
					
					pageNowAirplane--;
					ChangePageManageAirplane(l);
					
				}
			}
			else if (key == ESC)
				return;
		}
	}
}

#endif

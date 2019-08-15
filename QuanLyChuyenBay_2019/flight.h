#ifndef _FLIGHT_H
#define _FLIGHT_H
#include <sstream> 
#include "airplane.h"
#include "datetime.h"
#include "ticket.h""

struct Flight
{
	char idFlight[16]; // ma chuyen bay
	char destiny[31]; // san bay den
	char numAir[16];	// So Hieu MB
	DateTime dateLeave; // ngay gio khoi hanh
	
	int nTicket = 0; // so luong ve
	int  nTicketSold = 0; // so luong ve da ban
	int stt = STT_REMAIN_TICKET;	// trang thai ChuyenBay
	Ticket *listTicket = new Ticket[MAX_TICKET];	//Danh Sach Ve

};
typedef struct Flight FLIGHT;
// Khai bao cau truc 1 ptu trong dslkd
struct NodeFlight
{
	FLIGHT data;
	struct NodeFlight *pNext;
};
typedef struct NodeFlight NODE_FLIGHT;
//Khai bao DSLK
struct ListFlight
{
	int n = 0;
	NODE_FLIGHT *pHead, *pTail;
};
typedef struct ListFlight LIST_FLIGHT;
//---------------------------
int pageNowFlight = 1;
int currposFlight = 0;
int currposPrecFlight = 0;
int totalPageFlight = 0;
//-------------------------------
// Cap phat vung nho cho DSLK
NODE_FLIGHT* GetNodeFlight(FLIGHT DATA)
{
	NODE_FLIGHT *p = new NODE_FLIGHT; // khoi tao ;
	if (p == NULL)
		return NULL;
	p->data = DATA; // xuat du lieu ra node p;
	p->pNext = NULL; //init link listpointer
	return p;
}

//Khoi tao DSLK
void InitListFlight(LIST_FLIGHT &l)
{
	l.pHead = l.pTail = NULL;
}

// Them vao dau DS
void AddHeadListFlight(LIST_FLIGHT &l, FLIGHT data)
{
	NODE_FLIGHT* p = GetNodeFlight(data);
	p->pNext = l.pHead;
	l.pHead = p;
	++l.n;
}
// Them vao cuoi DS
void AddTailListFlight(LIST_FLIGHT &l, FLIGHT data)
{
	NODE_FLIGHT *p = GetNodeFlight(data);
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	++l.n;
}
//Tim kiem chuyen bay
NODE_FLIGHT* FindFlight(LIST_FLIGHT l, char *id)
{
	if (l.pHead == NULL) return NULL;
	for (NODE_FLIGHT *p = l.pHead ; p != NULL; p = p->pNext)
		if (_strcmpi(p->data.idFlight, id) == 0)
			return p;
	return NULL;
}
//Tim ChuyenBay tuong ung voi  soThuTu dc truyen vao"ordinal" trong DSLK
NODE_FLIGHT* FindFlightByOridnal(LIST_FLIGHT l, int ordinal )	//Truyen vao 1 so ordinal de tim THuTu
{
	if (l.pHead == NULL) return NULL;
	if (l.n -1 < ordinal) return NULL;
	if (ordinal == 0) return l.pHead;
	if (l.n - 1 == ordinal) return l.pTail;
	
	/*int count = -1;
	for (NODE_FLIGHT *p = l.pHead; p != NULL; p = p->pNext)
	{
		++count;
		if (count == ordinal) return p;
	}*/
	NODE_FLIGHT *p = l.pHead;
	int count = 0;
	while (count != ordinal)
	{
		p = p->pNext;
		count++;
	}
	return p;	//Tra ve mot ChuyenBay p tuong ung so thu tu "ordinal" can tim.
}

//Tim soThuTu cua ChuyenBay dua vao id cua ChuyenBay --> tra ve mot con so "index"
int FindIndexFlight(LIST_FLIGHT l, char *id)
{
	int index = -1;
	if (l.pHead == NULL) return -1;
	for (NODE_FLIGHT *p = l.pHead; p != NULL; p = p->pNext)
	{
		++index;
		if (_strcmpi(p->data.idFlight, id) == 0)
			return index;
	}
	return -1;
}

// Nhap ngay thang nam KhoiHanh 
void InputDatimeee(DATETIME &dt)
{
	int newOrdinal = 0;
	bool newIsMoveUp = false;
	bool newIsSave = false;
	Gotoxy(X_ADD + 12 + 2, 3 * 2 + Y_ADD);
	cout << ":";
	Gotoxy(X_ADD + 12 + 8, 3 * 2 + Y_ADD);
	cout << "/";
	Gotoxy(X_ADD + 12 + 11, 3 * 2 + Y_ADD);
	cout << "/";
	while (true)
	{
 		switch (newOrdinal)
		{
		case 0:
			CheckMoveAndValidateDateTime(dt.h, newIsMoveUp, newOrdinal, newIsSave, 23, 12);
			break;
		case 1:
			CheckMoveAndValidateDateTime(dt.mi, newIsMoveUp, newOrdinal, newIsSave, 59, 12);
			break;
		case 2:
			CheckMoveAndValidateDateTime(dt.d, newIsMoveUp, newOrdinal, newIsSave, 31, 12);
			break;
		case 3:
			CheckMoveAndValidateDateTime(dt.m, newIsMoveUp, newOrdinal, newIsSave, 12, 12);
			break;
		case 4:
			CheckMoveAndValidateDateTime(dt.y, newIsMoveUp, newOrdinal, newIsSave, 10000, 12);
			break;
	
		} // end switch newordinal
		
		//check move
		if (newIsMoveUp)
		{
			if (newOrdinal == 0)
				newIsMoveUp = false;
			else
				newOrdinal--;
		}
		else
		{
			if (newOrdinal == 4)
			{
				newIsMoveUp = true;
				return;
			}
			else
				newOrdinal++;
		}
		//--end check move

		if (newIsSave)
			return;
		else
			newIsSave = false;
	} // end while
}

// Them ChuyenBay theo THUTU tu Nho den Lon vao DSLK theo THUTU co san.
void InsertOrderForListFlight(LIST_FLIGHT &l, FLIGHT data)
{
	
	if(l.pHead == NULL)	// DS rong thi them vao dau DS
	{	
		AddHeadListFlight(l, data);
		return;
	}
	
	NODE_FLIGHT *p, *pAfter, *pBefore;
	
	p = GetNodeFlight(data);
	
	//pAfter = pBefore->pNext;
	
	for(pAfter = l.pHead; pAfter != NULL && (strcmp(pAfter->data.idFlight, data.idFlight) < 0); pBefore = pAfter, pAfter = pAfter->pNext);
	
	if(pAfter == l.pHead) // Add Head
		AddHeadListFlight(l, p->data);
	else // them nut p vao truoc nut s
	{
		p->pNext = pAfter;
		pBefore->pNext = p;
		++l.n;
	}
}

// Xoa ptu Dau DSLK
bool IsDeletedHead(LIST_FLIGHT &l)
{
	if ( l.pHead == NULL) return false;
	NODE_FLIGHT* p = l.pHead;
	l.pHead = p->pNext;
	delete p;
	--l.n;
	return true;
}

// Xoa ptu Cuoi DSLK
bool IsDeletedTail(LIST_FLIGHT &l)
{
		if( l.pHead == NULL) return false;
		NODE_FLIGHT *beforeP = NULL;
		for (NODE_FLIGHT *p = l.pHead; p != NULL; p = p->pNext)
		{
			if (p == l.pTail)
			{
				l.pTail = beforeP;
				beforeP->pNext = NULL;
				delete p;
				--l.n;
				return true;
			}
			beforeP = p;
		}
			
}

// Xoa ptu phia sau node p.
bool IsDeletedAfter(LIST_FLIGHT &l, NODE_FLIGHT*p)
{
	if (p == NULL || p->pNext == NULL) return false;
	NODE_FLIGHT* nodeDeleted = p->pNext;
	p->pNext = nodeDeleted->pNext;
	delete nodeDeleted;
	--l.n;
	return true;
}

// Tim ptu dung TRUOC node can xoa.
bool IsDeletedFlightWithId(LIST_FLIGHT &l, Flight data)
{
	NODE_FLIGHT* nodeDeleted = FindFlight(l, data.idFlight);
	if (nodeDeleted == NULL) return false;
	if (nodeDeleted == l.pHead) return IsDeletedHead(l);
	if (nodeDeleted == l.pTail) return IsDeletedTail(l);
	else
	{
		NODE_FLIGHT* temp = l.pHead;
		while (temp->pNext != nodeDeleted)	//Vong lap tim node TEMP dung sau node can xoa
			temp = temp->pNext;
		return IsDeletedAfter(l,temp);
	}
}

// Xao toan bo DS ChuyenBay khoi bo nho dem.
bool ClearListFlight(LIST_FLIGHT &l)
{
	if (l.pHead) return false;
	NODE_FLIGHT* temp;
	while (l.pHead != NULL)
	{
		temp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete temp;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------//
void OutputFlight(FLIGHT fl, int locate)  //IN thong tin mot ChuyenBay
{
	DeleteOldData(sizeof(keyDisplayFlight) / sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << fl.idFlight;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << fl.numAir;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); OutputDateTime(fl.dateLeave);
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << fl.destiny;
	Gotoxy(xKeyDisplay[4] + 1, Y_DISPLAY + 3 + locate);
	switch (fl.stt)
	{
	case 4: cout << "Da Huy";
		break;
	case 1: cout << "Con ve";
		break;
	case 2: cout << "Het ve";
		break;
	case 3: cout << "Hoan tat";
		break;
	default:
		break;
	}
	Gotoxy(xKeyDisplay[5] + 1, Y_DISPLAY + 3 + locate); cout << fl.nTicket;
}

// Tu dong cap nhat TrangThai MAyBAY ve HoanTat, khi NgayKhoiHanh < NgayHienTai
void AutoChangeSttFlight(LIST_FLIGHT &l)
{
	NODE_FLIGHT* p = l.pHead;
	for (p ; p != NULL; p = p->pNext)
		if (!DateTimeIsValid(p->data.dateLeave)) p->data.stt = STT_FINISHED;
}

// IN DS 1 ChuyenBay ra man hinh.
void OutputListFlight(LIST_FLIGHT l)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	AutoChangeSttFlight(l);
	for (NODE_FLIGHT* q = l.pHead; q != NULL; q = q->pNext)
	{
		count++;
		OutputFlight(q->data, count);
	}
}
// In DS CHuyenBay theo Phan Trang (QUANTITY_PER_PAGE : la so ptu tren 1 TRANG)
void OutputListFlightPerPage(LIST_FLIGHT l, int indexBegin)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	AutoChangeSttFlight(l);
	for (NODE_FLIGHT* q = l.pHead; q != NULL; q = q->pNext)
	{
		count++;
		if (count == indexBegin)
		{
			int i = -1; 
			while (q != NULL && i < QUANTITY_PER_PAGE - 1)
			{
				OutputFlight(q->data, (++i) * 2);
				q = q->pNext;
			}
			break;
		}
		
	}
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowFlight << "/" << totalPageFlight;
	return;
}

// Kiem tra 1 ChuyenBay co RONG ko.
bool DataFlightIsEmpty(FLIGHT fl)
{
	if (strlen(fl.idFlight) == 0) return true;
	if (strlen(fl.destiny) == 0) return true;
	if (fl.nTicket <= 0) return true;
	return false;
}

//-------------------------
// Tao mang DS ten Ve, theo so day va so dong cua MAYBAY
string* CreateArrTicket(int soday, int sodong)
{
	int totalTicket = soday * sodong; // Tinh tong so ve
	string* arr = new string[totalTicket]; // Tao mot MANG voi so ptu la TongSoVe
	int n = 0;								
	for(int i = 0; i < soday; i++)
	{
		for(int j =1; j <= sodong; j++)
		{
			if(j < 10)
			{
				ostringstream str; 
				ostringstream str1; 
				str << char(65 + i);
				string temp = str.str();
				
				
				temp += "0";
				str1 << j;
				temp += str1.str();
				arr[n++] = temp;
			}				
			else
			{
				ostringstream str2, str3; 
				str2 << char(65 + i);
				string temp1= str2.str();
				str3 << j;
				temp1 += str3.str();
				arr[n++] = temp1;
			}		
		}
	}
	return arr;
}

// Nhap THong tin 1 ChuyenBay
void InputFlight(LIST_FLIGHT &l, PTR_LIST_AIRPLANE lal,  FLIGHT &fl, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	string id, numAir;
	DateTime dt;
	string destiny;
	int stt = STT_REMAIN_TICKET;
	Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
	cout << "F10 luu ngay gio";
	Gotoxy(X_NOTIFY - 4, Y_NOTIFY + 2);
	cout << "Trang thai: 1:Con ve 2:Het ve 3:Hoan tat 4:Huy chuyen";

	if (isEdited)
	{
		//binding data
		id = fl.idFlight;
		dt = fl.dateLeave;
		destiny = fl.destiny;
		stt = fl.stt;
		numAir = fl.numAir;
		//format datetime
		Gotoxy(X_ADD + 12 + 2, 2 * 3 + Y_ADD);
		cout << ":";
		Gotoxy(X_ADD + 12 + 8, 2 * 3 + Y_ADD);
		cout << "/";
		Gotoxy(X_ADD + 12 + 11, 2 * 3 + Y_ADD);
		cout << "/";

		//out datetime
		Gotoxy(X_ADD + 12 + 0 * 3, 2 * 3 + Y_ADD);
		cout << dt.h;
		Gotoxy(X_ADD + 12 + 1 * 3, 2 * 3 + Y_ADD);
		cout << dt.mi;
		Gotoxy(X_ADD + 12 + 2 * 3, 2 * 3 + Y_ADD);
		cout << dt.d;
		Gotoxy(X_ADD + 12 + 3 * 3, 2 * 3 + Y_ADD);
		cout << dt.m;
		Gotoxy(X_ADD + 12 + 4 * 3, 2 * 3 + Y_ADD);
		cout << dt.y;

		//out data
		Gotoxy(X_ADD + 15, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 15, 1 * 3 + Y_ADD);
		cout << numAir;
		Gotoxy(X_ADD + 15, 3 * 3 + Y_ADD);
		cout << destiny;
		Gotoxy(X_ADD + 15, 4 * 3 + Y_ADD);
		cout << stt;
	}
	while (true)
	{
		//input
		switch (ordinal)
		{
			case 0:
			{				
				CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave, 15);
				if (isEdited && _stricmp(id.c_str(), fl.idFlight) == 0)  break;
				if (FindFlight(l, (char *)id.c_str()) == NULL)
				{
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			}
			case 1:
			{
				CheckMoveAndValidateID(numAir, isMoveUp, ordinal, isSave, 15);
				break;			
			}					
			case 2:
			{
				InputDatimeee(dt);
				break;
			}
			case 3:
			{
				CheckMoveAndValidateName_1(destiny, isMoveUp, ordinal, isSave, 15, 20);
				break;
			}
			case 4:
			{
				CheckMoveAndValidateNumber(stt, isMoveUp, ordinal, isSave, 15, 4);
				break;
			}
		}//end switch

		 //--move
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false; //block move up
			ordinal--;
		}
		else
		{
			if (ordinal == 4)
				isMoveUp = true; //block move down
			ordinal++;
		}
		//--end move

		if (isSave)
		{
			//binding data
			strcpy(fl.idFlight, id.c_str());
			strcpy(fl.numAir, numAir.c_str());
			fl.dateLeave = dt;
			strcpy(fl.destiny, destiny.c_str());
			
			PTR_AIRPLANE al = FindAirplane(lal, fl.numAir); 
			fl.stt = stt;
			if(al != NULL) 
			{
				fl.nTicket = (al->lineNumber * al->sequenceNumber);	
				string* arr = CreateArrTicket(al->sequenceNumber, al->lineNumber);
				for(int i = 0; i < fl.nTicket; i++)
				{
					strcpy(fl.listTicket[i].nameTicket, arr[i].c_str());
				}
			}
					
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			bool flag = true;
			for(NODE_FLIGHT* p = l.pHead; p != NULL; p = p->pNext)
			{
				if(fl.dateLeave.d == p->data.dateLeave.d && fl.dateLeave.m == p->data.dateLeave.m && fl.dateLeave.y == p->data.dateLeave.y)
					flag = false;
			}
			if (!DateTimeIsValid(fl.dateLeave))
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ngay gio khong hop le. Phai lon hon gio he thong";

			}
			else if(al == NULL)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "May bay khong ton tai";
			}
			else if (DataFlightIsEmpty(fl))
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma so khong duoc trung";
			}
			else if(flag == false && !isEdited)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "gio khoi hanh khong hop le";
			}	
			else
			{
				StandardName(fl.destiny);
				if (isEdited)
				{
					NODE_FLIGHT* p = FindFlight(l, fl.idFlight);
					p->data = fl;
					//int index = FindIndexFlight(l, fl.id);
					//OutputFlight(p->data, (index % QUANTITY_PER_PAGE) * 2);
					/*DeleteMenuAdd();
					return;*/
				}
				else
				{
					InsertOrderForListFlight(l, fl);
					//int index = FindIndexFlight(l, fl.id);
					//OutputFlight(fl, (index % QUANTITY_PER_PAGE) * 2);
					/*DeleteMenuAdd();
					return;*/
				}
				totalPageFlight = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
				DeleteMenuAdd();
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);
}
void SetDefaultChosenFlight(FLIGHT fl, int ordinal)
{
	SetBGColor(1);
	OutputFlight(fl, (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0);
}
void   EffectiveMenuFlight(int ordinal, FLIGHT flNew, FLIGHT flOld)
{
	int current = ordinal;
	SetDefaultChosenFlight(flNew, current);

	/*SetBGColor(GREEN);
	OutputFlight(flNew, (current % QUANTITY_PER_PAGE) * 2);
	SetBGColor(PURPLE);*/
	OutputFlight(flOld, (currposPrecFlight % QUANTITY_PER_PAGE) * 2);
	currposPrecFlight = current;
}

void ChangePageChooseFlight(LIST_FLIGHT l)
{

	system("cls");
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	currposFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	currposPrecFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	
}

NODE_FLIGHT* ChooseFlight(LIST_FLIGHT l)
{
	int keyboard_read = 0;
	ShowCur(false);
	pageNowFlight = 1;
	currposFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	currposPrecFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	totalPageFlight = ((l.n-1) / QUANTITY_PER_PAGE) + 1;
	
	NODE_FLIGHT* newNodeFlight = FindFlightByOridnal(l, currposFlight);
	NODE_FLIGHT* oldNodeFilght = NULL;
	
	OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
	SetDefaultChosenFlight(newNodeFlight->data, currposFlight);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (currposFlight % QUANTITY_PER_PAGE> 0)
			{
				currposFlight = currposFlight - 1;
				oldNodeFilght = newNodeFlight;
				for (newNodeFlight = l.pHead; newNodeFlight->pNext != oldNodeFilght; newNodeFlight = newNodeFlight->pNext);
				EffectiveMenuFlight(currposFlight, newNodeFlight->data, oldNodeFilght->data);
			}
			break;
		case KEY_DOWN:
			if (currposFlight  % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && newNodeFlight->pNext != NULL) //&& currposFlight < 3)
			{
				currposFlight = currposFlight + 1;
				oldNodeFilght = newNodeFlight;
				newNodeFlight = newNodeFlight->pNext;
				EffectiveMenuFlight(currposFlight, newNodeFlight->data, oldNodeFilght->data);
			}
			break;
		
		case PAGE_DOWN:
			if (pageNowFlight < totalPageFlight)
			{

				pageNowFlight++;
				ChangePageChooseFlight(l);
				OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
				newNodeFlight = FindFlightByOridnal(l, currposFlight);
				SetDefaultChosenFlight(newNodeFlight->data, currposFlight);
				
			}
			break;
		case PAGE_UP:
			if (pageNowFlight > 1)
			{
			
				pageNowFlight--;	
				ChangePageChooseFlight(l);
				OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
				newNodeFlight = FindFlightByOridnal(l, currposFlight);
				SetDefaultChosenFlight(newNodeFlight->data, currposFlight);
				
			}
			break;


		case ENTER:  //enter
			ShowCur(true);
			return newNodeFlight;
			break;
		case 27: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

void ChangePageManageFlight(LIST_FLIGHT l)
{
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY";
	OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
}




void MenuManageFlight(LIST_FLIGHT &l, PTR_LIST_AIRPLANE lal)
{

backMenu:
	system("cls");
	 pageNowFlight = 1;
	OutputListFlightPerPage(l, 0);
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));

	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY";
	int key;
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				
				if (key == KEY_F2) //f2
				{
					FLIGHT fl;
					DeleteNotify();
					DisplayEdit(keyDisplayAddFlight, sizeof(keyDisplayAddFlight) / sizeof(string), 35);
					InputFlight(l, lal, fl, false);
					totalPageFlight = ((l.n-1)/ QUANTITY_PER_PAGE) + 1;
					ChangePageManageFlight(l);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
					
					//OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
				}
				else if (key == KEY_F3) //f3
				{
					
					NODE_FLIGHT* k = ChooseFlight(l);
					DeleteNotify();
					if (k == NULL) goto backMenu;
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					if (key == ENTER)
					{
						if (k->data.nTicketSold  != 0)
						{
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Khong xoa duoc vi da co nguoi dat ve";
							_getch();
							goto backMenu;
						}
						if (IsDeletedFlightWithId(l, k->data))
						{

							totalPageFlight = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
							//pageNowFlight = 1;
							if (l.n % QUANTITY_PER_PAGE == 0) pageNowFlight--;
							ChangePageManageFlight(l);
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						
							
						}

						/*system("cls");
						Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
						IsDeletedFlightWithId(l, k->data);
						
						OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);*/
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4) //f4
				{
					
					NODE_FLIGHT* k = ChooseFlight(l);
					if (k == NULL) goto backMenu;
					DeleteNotify();
					DisplayEdit(keyDisplayFlight_Edit, sizeof(keyDisplayFlight_Edit) / sizeof(string), 35);
					InputFlight(l, lal, k->data, true);
					OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Sua thanh cong";
				}
				else if (key == PAGE_DOWN && pageNowFlight < totalPageFlight)
				{
					pageNowFlight++;
					ChangePageManageFlight(l);
					
				}
				else if (key == PAGE_UP && pageNowFlight > 1)
				{
					pageNowFlight--;
					ChangePageManageFlight(l);

					/*system("cls");
					Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY";
					OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
					Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));*/
				}
			}
			else if (key == ESC)
				return;
		}//end while kbhit
	}
}
#endif

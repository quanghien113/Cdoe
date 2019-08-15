#ifndef _PROCESSS_H
#define _PROCESSS_H
#include <fstream>
#include "flight.h"
// Luu 
/* void SaveAirplane(PTR_AIRPLANE al, fstream &file)
{
	file << al->numAir << endl;
	file << al->typeAir << endl;
	file << al->sequenceNumber << endl;
	file << al->lineNumber << endl;
} */

//========================DOC GHI FILE MAYBAY==============================================================

// Xuat du lieu MAYBAY ra file
void SaveAirplaneToFile(PTR_LIST_AIRPLANE l)
{
	fstream outFile;
	outFile.open("DSMB.txt", ios::out );
	if (outFile.is_open())
	{
		outFile << l->n <<endl;
		for(int i = 0; i<= l->n;i++)
		{
			//SaveAirplane(l->listAirplane[i], outFile);
			outFile << l->listAirplane[i]->numAir << endl;
			outFile << l->listAirplane[i]->typeAir << endl;
			outFile << l->listAirplane[i]->sequenceNumber << endl;
			outFile << l->listAirplane[i]->lineNumber << endl;
		}
	}else
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "KET NOI VOI FILE THAT BAI! ";
	}
	
	outFile.close();
}

// Doc du lieu MAYBAY tu file
void LoadAirplaneFromFile(PTR_LIST_AIRPLANE &l)
{
	fstream inFile;
	
	int nAirplane;
	inFile.open("DSMB.txt", ios::in);
	
	if(inFile.is_open())
	{
		string temp;		
		inFile >> nAirplane;
		
		for(int i = 0; i <= nAirplane; i++)
		{
		
			l->listAirplane[i] = new AIRPLANE;
			getline(inFile, temp);
			inFile.getline(l->listAirplane[i]->numAir, 15, '\n');
			inFile.getline(l->listAirplane[i]->typeAir, 40, '\n');
			
			inFile >> l->listAirplane[i]->sequenceNumber;
			inFile >> l->listAirplane[i]->lineNumber;
				
			++l->n;
			//delete l->listCreditClass[i];
		}
	}
	inFile.close();
}

//===============================DOC GHI FILE CHUYEN BAY==========================================================
void SaveFlight(FLIGHT fl, fstream &file)
{
	file << fl.idFlight << endl;
	file << fl.numAir << endl;
	file << fl.destiny << endl;
	
	file << fl.dateLeave.y << endl;
	file << fl.dateLeave.m << endl;
	file << fl.dateLeave.d << endl;
	file << fl.dateLeave.h << endl;
	file << fl.dateLeave.mi << endl;
	
	file << fl.nTicket << endl;
	file << fl.stt << endl;
	file << fl.nTicketSold << endl;
	
	for(int i = 0; i < fl.nTicket; i++ )
	{
		file << fl.listTicket[i].nameTicket << endl;
		file << fl.listTicket[i].idPassenger << endl;
	}
}

void SaveFlightToFile(LIST_FLIGHT l)
{
	fstream outFile;
	outFile.open("DSCB.txt", ios::out);
	if (outFile.is_open())
	{
		outFile << l.n << endl;
		
		for(NODE_FLIGHT* k = l.pHead; k != NULL; k = k->pNext)
		{
			SaveFlight(k->data, outFile);
		}
	}
	else
	{
		cout << "KET NOI VOI FILE DSMH THAT BAI! ";
	}
	outFile.close();

}


void LoadFlightFromFile(LIST_FLIGHT &l)
{
	fstream inFile;
	FLIGHT fl;
	int n;
	inFile.open("DSCB.txt", ios::in);
	if (inFile.is_open())
	{
		string temp;		
		inFile >> n;
		
		for(int i = 0; i < n; i++)
		{
			getline(inFile, temp);
			inFile.getline(fl.idFlight, 15, '\n');
			inFile.getline(fl.numAir, 15, '\n');
			inFile.getline(fl.destiny, 30, '\n');
			
			inFile >> fl.dateLeave.y;
			inFile >> fl.dateLeave.m;
			inFile >> fl.dateLeave.d;
			inFile >> fl.dateLeave.h;
			inFile >> fl.dateLeave.mi;
			
			inFile >> fl.nTicket;
			inFile >> fl.stt;
			inFile >> fl.nTicketSold;
						
			for(int i = 0; i< fl.nTicket; i++)
			{
				getline(inFile, temp);
				inFile.getline(fl.listTicket[i].nameTicket, 3, '\n');
				inFile >> fl.listTicket[i].idPassenger;
			}
			
			AddTailListFlight(l, fl);
		}
	}
	else {
		cout << "KET NOI VOI FILE DSMH THAT BAI! ";
	}

	inFile.close();
}


///-----------------
void main_menu(PTR_LIST_AIRPLANE &dsMAYBAY, LIST_FLIGHT &dsCHUYENBAY)
{
	int chon;
	do {
		chon = MenuDong(thucdon);
		switch (chon)
		{
			case 1: MenuManageAirplane(dsMAYBAY); break;
			case 2: MenuManageFlight(dsCHUYENBAY, dsMAYBAY); break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			case 8: return;
		}
		
		} while (true);
}
#endif

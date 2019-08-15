#include "airplane.h"
#include "display.h"
#include "process.h"
#include"flight.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	fullscreen();
	
// ==== DS May Bay ===	
	PTR_LIST_AIRPLANE la = new LIST_AIRPLANE;
	LoadAirplaneFromFile(la);	
//==== DS Chuyen Bay====
	LIST_FLIGHT l;	
	InitListFlight(l);
	LoadFlightFromFile(l);
//====Goi Menu Chinh====	
	main_menu(la,l);
//=== Luu du lieu vao file.	
	SaveFlightToFile(l);
	SaveAirplaneToFile(la);
	return 0;
}

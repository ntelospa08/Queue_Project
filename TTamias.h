/**********************************************+**************************
Header File Name 		: TTamias.h
Purpose					: 
Revision				:  <Your Name - Date>
**************************************************************************/

#define __TTameio__


typedef struct {
    int TimeBusy;			//xronos pou to tameio einai apasxolimeno
    int TimeInactive;		//xronos pou to tameio itan adranes
    int ArithmoPelaton;		//arithmos pelatwn pou to tameio eksipiretise
    int enapomenonXronos;	//enapomeinan xronos gia na eksipiretithei enas pelatis
} TTameio;

void TameioDimiourgia(TTameio *tameio);		//arxikopoiei to struct tameio
void TameioNewCustomer(TTameio *tameio, int Duration);		//auksanei ton metriti pelatwn kai arxikopoiei enapominanta xrono eksipiretisis
void TameioInService(TTameio *tameio);		//meiwnei to xrono eksipiretisis kata 1
void TameioNoWork(TTameio *tameio);		//auksanei xrono adraneias kata 1
void TameioBusy(TTameio *tameio);		//auksanei xrono pasxolisis kata 1
int TameioFree(TTameio tameio);		//elegxei an eiani diathesimo

int TameioGetArithmosPelatwn(TTameio tameio);	//epiustrefei ton arithmo pelatwn
int TameioGetInactiveXronos(TTameio tameio);	//epistrefei to xrono adraneias tou
int TameioGetBusyXronos(TTameio tameio);		//epistrefei to xrono enasxolisis tou

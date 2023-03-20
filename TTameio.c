/*************************************************************************
Implementation File	: TStoixeiouOyras.c
Author	Date		: Y. Cotronis 07/03/2016
Purpose 			: Ylopoihsh typou stoixeiou ths oyras
Revision			:  <Your Name - date>
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "TTameio.h"

void TameioDimiourgia(TTameio *tameio)
{
    tameio->TimeBusy = 0;			//xronos pou to tameio einai apasxolimeno
    tameio->TimeInactive = 0;		//xronos pou to tameio itan adranes
    tameio->ArithmoPelaton = 0;		//arithmos pelatwn pou to tameio eksipiretise
    tameio->enapomenonXronos = 0;	//enapomeinan xronos gia na eksipiretithei enas pelatis
}

void TameioNewCustomer(TTameio *tameio, int Duration)
{
	tameio->ArithmoPelaton++;
	tameio->enapomenonXronos=Duration;
}

void TameioInService(TTameio *tameio)
{
	tameio->enapomenonXronos--;	
}

void TameioNoWork(TTameio *tameio)
{
	tameio->TimeInactive++;
}

void TameioBusy(TTameio *tameio)
{
	tameio->TimeBusy++;
}

int TameioFree(TTameio tameio)
{
	return tameio.enapomenonXronos==0;
}

int TameioGetArithmosPelatwn(TTameio tameio)
{
	return tameio.ArithmoPelaton;
}

int TameioGetInactiveXronos(TTameio tameio)
{
	return tameio.TimeInactive;
}

int TameioGetBusyXronos(TTameio tameio)
{
	return tameio.TimeBusy;
}

int TameioGetEnapomenonXronos(TTameio tameio)
{
	return tameio.enapomenonXronos;
}

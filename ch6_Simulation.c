/*************************************************
Arxeio ylopoihshs	: ch6_Simulation.c
Syggrafeas			: Y. Cotronis 07/03/2016
Skopos				: Ylopoihsh ouras prosomoiwshs
Revision 			:  <Your Name - Date>
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TStoixeiouOuras.h"
#include "ch6_QArray.h"
#include "TTameio.h"
#define N 5

int 			total_metritis=0;
int				pelates_tameiwn=0;
//int 			N;

int main(void)

{	
	TOuras      	oura;				 /*oura pelatwn-aytokinhtvn */
	TTameio			Tameio[N];
	TSOuras			Pelatis;		 	/* o pelaths sthn oyra*/
	

	float			pithanotita_afiksis; /*pi8anothta afikshs*/
	unsigned int	xronos_eksipiretisis;/*xronos e3yphrethshs enos pelath*/ 
	unsigned int	xronos_leitourgias; /*synolikos xronos prosomoiwshs*/
	unsigned int 	wrario_trapezas;
	unsigned int	xronos;				 /*roloi prosomoiwshs*/
	unsigned int	extra_time;
	unsigned int	enapomenon_xronos;	 /*xronos gia to telos e3yphrethshs enos pelath*/
	unsigned int	arithmos_pelaton; 	 /*plh8os e3yphreth8entwn pelatwn*/
	unsigned int	xronos_anamonis;	 /*synolikos xronos anamonhs*/
	float			mesos_xronos;		 /*mesos xronos anamonhs twn pelatvn*/
	float			randomAfixi;
	int             tamiasInactive=0;
	time_t			t;
	int 			i,j;
	
	
	
	unsigned int max_serveTime;

	//printf("Eisagete ton arithmo twn tameiwn tis trapezas: ");
//	scanf("%d",&N);
	
	printf("Eisagete to xrono leitourgias tis trapezas se lepta: ");
	scanf("%u",&xronos_leitourgias);
	
	printf("Eisagete pithanotita afiksis enos pelati ana lepto: ");
	scanf("%f",&pithanotita_afiksis);

	printf("Eisagete megisto xrono eksipiretisis ana pelati se lepta: ");
	scanf("%u",&max_serveTime);
	
	printf("\n**************************************************************");
	
	getchar();
	
	printf("\n\nO xronos leitourgias tis trapezas einai %u lepta.\n",xronos_leitourgias);
	printf("H pithanotita afiksis pelati se ena lepto einai %4.2f.\n",pithanotita_afiksis);
	printf("H megisti diarkeia eksipiretisis enos pelati einai %u lepta.\n",max_serveTime);
	
	printf("\n**************************************************************");

	for(i=0; i<N; i++)
	{
		TameioDimiourgia(&Tameio[i]);
		//printf("\nArxikopoiisi:\ni=%d:\tTimeBusy:%d TimeInactive:%d ArithmoPelaton:%d enapomenonXronos:%d",i,Tameio[i].TimeBusy,Tameio[i].TimeInactive,Tameio[i].ArithmoPelaton,Tameio[i].enapomenonXronos );

	}
	
		
	OuraDimiourgia(&oura);
	
	xronos = 0;
	enapomenon_xronos = 0;
	arithmos_pelaton = 0;
	xronos_anamonis =0;
	srand(time(&t));

	while( xronos < xronos_leitourgias )
	{	
		//printf("\n0-CHECK xronos<xronosleitourgias");

		randomAfixi = (float)rand()/(float)RAND_MAX; 
		//printf("\n1-random afiksi:%f", randomAfixi);
		if ( randomAfixi < pithanotita_afiksis )
		{		
			xronos_eksipiretisis=rand()%max_serveTime+1;
			
		//	printf("\n2-xronos_eksipiretisis:%u", xronos_eksipiretisis);

			PelatisSetXronoEisodou(&Pelatis, xronos);
			PelatisSetXronoEksipiretisis(&Pelatis,xronos_eksipiretisis);
			total_metritis++; 
		//	printf("\n3-total_metritis:%d", total_metritis);
			
			if (!OuraProsthesi(&oura, Pelatis))
			{
            	printf("H oura einai mikri! H prosomoiwsi stamataei \n");
            	getchar();
            	return 0;
        	}
					//	printf("\n4-CHECK egine i prosthesi");
       	
        	//printf("\n\n-----------------------------------\nKata ti diarkeia tou %dou leptou:\nMpike o %dos pelatis stin trapeza me xrono eksipiretisis %u lepta\nstin oura vriskontai %d atoma\n-----------------------------------\n", xronos+1,total_metritis,PelatisGetXronoEksipiretisis(&Pelatis), OuraGetSize(oura));
    	}
    	
    	//printf("\n\n-----------------------------------\nKata ti diarkeia tou %dou leptou:\nrandom Afiksi:%f\nxronos eksipiretisis %u\nstin oura vriskontai %d atoma\n-----------------------------------\n", xronos+1,randomAfixi,xronos_eksipiretisis,OuraGetSize(oura));
    	printf("\n\n===============================================================================");
    	printf("\nxronos:%d xronos eksipiretisis:%d total.metritis:%d",xronos,PelatisGetXronoEksipiretisis(&Pelatis),total_metritis);
    	/* Tamias-Elegxos */
    	
		//prin if ( enapomenon_xronos == 0)	/*eley8eros tamias*/
		for(i=0; i<N; i++)
		{
			if(TameioFree(Tameio[i]))
			{
				
				
				if (!OuraKeni(oura))			/*yparxei pelaths*/
				{	
					printf("\nTameio[%d] is free and serving",i);
					OuraApomakrynsh(&oura,&Pelatis);		/*phgainei sto tamio*/
					xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);	/*ypologismos xronoy paramonhs sthn oura*/
					/* printf("Time is %d Time out %d\n", xronos, PelatisGetXronoEisodou(Pelatis)); */
				
					//prin arithmos_pelaton++;
					if(oura.embros==0)
						enapomenon_xronos = xronos_eksipiretisis-1;
					else
						enapomenon_xronos = oura.pinakas[oura.embros-1].XronosEksipiretisis-1; /* kallyptei to trexon unit time */
					TameioNewCustomer(&Tameio[i],enapomenon_xronos);
					pelates_tameiwn = pelates_tameiwn + TameioGetArithmosPelatwn(Tameio[i]);
				}
				else 
				{
					TameioNoWork(&Tameio[i]);
					printf("\nTameio[%d] is free, but not serving",i);					
				}
					
			}
				else 
					TameioInService(&Tameio[i]);		/*o tamias apasxolhmenos me pelath */	
									
			printf("\n\ni=%d:\tTimeBusy:%d TimeInactive:%d ArithmoPelaton:%d enapomenonXronos:%d",i,Tameio[i].TimeBusy,Tameio[i].TimeInactive,Tameio[i].ArithmoPelaton,Tameio[i].enapomenonXronos );
		}
    	printf("\n===============================================================================\n\n");

		
		//printf("\nCHECK-AFTER:\nempros:%d\npiso:%d\nmetritis:%d\nenapomenon xronos:%u\nxronos eksipiretisis:%d\n",oura.embros,oura.piso,oura.metritis,enapomenon_xronos,oura.pinakas[oura.embros-1].XronosEksipiretisis);
		xronos++; /*o xronos prosomoivshs ay3anetai kata 1 unit of time*/
	 }/*while( xronos < xronos_leitourgias )*/
	
	if(total_metritis>pelates_tameiwn)
	{
		
		printf("\n !!!!!!!!!!!!!!!Exoume paratasi!!!!!!!!!!!!!");
		extra_time=0;
		
		for(i=0; i<N; i++)
		{
			
		
			if(TameioFree(Tameio[i]))
			{
				//printf("\n!enapomenon_xronos=0!\n"); 
				for (j=pelates_tameiwn; j<total_metritis; j++ )
				{
					//printf("\npelatis[%d]: xronos eksipiretisis %u", i,oura.pinakas[i].XronosEksipiretisis);
					extra_time = extra_time + oura.pinakas[j].XronosEksipiretisis;
				}
			}
			else
			{
				for (j=pelates_tameiwn+1; j<total_metritis; j++ )
				{
					//printf("\npelatis[%d]: xronos eksipiretisis %u", i,oura.pinakas[i].XronosEksipiretisis);
					extra_time = extra_time + oura.pinakas[j].XronosEksipiretisis;
				}	
			
				extra_time+=TameioGetEnapomenonXronos(Tameio[i]);
			
			}
		
			while(xronos<xronos_leitourgias+extra_time)
			{
				if (TameioFree(Tameio[i]))	
				if (!OuraKeni(oura))			
				{	OuraApomakrynsh(&oura,&Pelatis);		
					xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);
					enapomenon_xronos = oura.pinakas[oura.embros-1].XronosEksipiretisis-1; 
					TameioNewCustomer(&Tameio[i],enapomenon_xronos);
				}else TameioNoWork(&Tameio[i]);
				else TameioInService(&Tameio[i]);
				xronos++;
			}			
		}
		
	}
	
	
	//printf("\n\nCHECK EXTRA TIME:\n\ntotal_metritis:%d\narithmos pelatwn: %d\nextra tme is %d\n",total_metritis,arithmos_pelaton, extra_time);
	
	if (pelates_tameiwn==0)
		mesos_xronos = 0.0;
	else
		mesos_xronos = ((float)xronos_anamonis)/((float)pelates_tameiwn);

	printf("\n\n-Eksipiretithikan %d pelates sunolika.",total_metritis);
	printf("\n-I trapeza emeine anoixti gia %u lepta epipleon.",extra_time);
	printf("\n-O sunolikos xronos leitoyrgias tis trapezas itan %u lepta.",xronos_leitourgias+extra_time);
	printf("\n-O mesos xronos anamonhs htan %4.2f lepta.",mesos_xronos);
	
	for(i=0; i<N; i++)
	{
		printf("\n-O %dos tamias htan adranis gia %d lepta kai eksipiretise %d pelates", i+1,TameioGetInactiveXronos(Tameio[i]),TameioGetArithmosPelatwn(Tameio[i]));	
	}
    getchar();
    
	return 0;
}


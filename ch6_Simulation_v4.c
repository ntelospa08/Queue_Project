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

int total_metritis=0;

int main(void)

{	
	TOuras      	oura;				 /*oura pelatwn-aytokinhtvn */
	TTameio			Tameio;
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
	int 			i;
	
	
	unsigned int max_serveTime;

	
	
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


	OuraDimiourgia(&oura);
	TameioDimiourgia(&Tameio);
	xronos = 0;
	enapomenon_xronos = 0;
	arithmos_pelaton = 0;
	xronos_anamonis =0;
	srand(time(&t));

	while( xronos < xronos_leitourgias )
	{	
		randomAfixi = (float)rand()/(float)RAND_MAX; 

		if ( randomAfixi < pithanotita_afiksis )
		{		
			xronos_eksipiretisis=rand()%max_serveTime+1;
			PelatisSetXronoEisodou(&Pelatis, xronos);
			PelatisSetXronoEksipiretisis(&Pelatis,xronos_eksipiretisis);
			total_metritis++; 
			
			if (!OuraProsthesi(&oura, Pelatis))
			{
            	printf("H oura einai mikri! H prosomoiwsi stamataei \n");
            	getchar();
            	return 0;
        	}       	
        	//printf("\n\n-----------------------------------\nKata ti diarkeia tou %dou leptou:\nMpike o %dos pelatis stin trapeza me xrono eksipiretisis %u lepta\nstin oura vriskontai %d atoma\n-----------------------------------\n", xronos+1,total_metritis,PelatisGetXronoEksipiretisis(&Pelatis), OuraGetSize(oura));
    	}
    	
    	//printf("\n\n-----------------------------------\nKata ti diarkeia tou %dou leptou:\nrandom Afiksi:%f\nxronos eksipiretisis %u\nstin oura vriskontai %d atoma\n-----------------------------------\n", xronos+1,randomAfixi,xronos_eksipiretisis,OuraGetSize(oura));
    	
    	/* Tamias-Elegxos */
    	
		if ( enapomenon_xronos == 0)	/*eley8eros tamias*/
			if (!OuraKeni(oura))			/*yparxei pelaths*/
			{	OuraApomakrynsh(&oura,&Pelatis);		/*phgainei sto tamio*/
				xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);	/*ypologismos xronoy paramonhs sthn oura*/
				/* printf("Time is %d Time out %d\n", xronos, PelatisGetXronoEisodou(Pelatis)); */
				arithmos_pelaton++;
				if(oura.embros==0)
					enapomenon_xronos = xronos_eksipiretisis-1;
				else
				enapomenon_xronos = oura.pinakas[oura.embros-1].XronosEksipiretisis-1; /* kallyptei to trexon unit time */
			}else tamiasInactive++;
		else enapomenon_xronos --;		/*o tamias apasxolhmenos me pelath */
		
		//printf("\nCHECK-AFTER:\nempros:%d\npiso:%d\nmetritis:%d\nenapomenon xronos:%u\nxronos eksipiretisis:%d\n",oura.embros,oura.piso,oura.metritis,enapomenon_xronos,oura.pinakas[oura.embros-1].XronosEksipiretisis);
		xronos++; /*o xronos prosomoivshs ay3anetai kata 1 unit of time*/
	} /*while( xronos < xronos_leitourgias )*/
	
	if(total_metritis>arithmos_pelaton)
	{
		//printf("\n\ntotal_metritis>arithmos_pelaton");
		
		extra_time=0;
		
		if(enapomenon_xronos==0)
		{
			//printf("\n!enapomenon_xronos=0!\n"); 
			for (i=arithmos_pelaton; i<total_metritis; i++ )
			{
				//printf("\npelatis[%d]: xronos eksipiretisis %u", i,oura.pinakas[i].XronosEksipiretisis);
				extra_time = extra_time + oura.pinakas[i].XronosEksipiretisis;
			}
		}
		else
		{
			for (i=arithmos_pelaton+1; i<total_metritis; i++ )
			{
				//printf("\npelatis[%d]: xronos eksipiretisis %u", i,oura.pinakas[i].XronosEksipiretisis);
				extra_time = extra_time + oura.pinakas[i].XronosEksipiretisis;
			}
			
			extra_time+=enapomenon_xronos;
			
		}
		
		while(xronos<xronos_leitourgias+extra_time)
		{
			if ( enapomenon_xronos == 0)	
			if (!OuraKeni(oura))			
			{	OuraApomakrynsh(&oura,&Pelatis);		
				xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);	
				arithmos_pelaton++;
				enapomenon_xronos = oura.pinakas[oura.embros-1].XronosEksipiretisis-1; 
			}else tamiasInactive++;
			else enapomenon_xronos --;
			xronos++;
		}
		
	}
	
	
	//printf("\n\nCHECK EXTRA TIME:\n\ntotal_metritis:%d\narithmos pelatwn: %d\nextra tme is %d\n",total_metritis,arithmos_pelaton, extra_time);
	
	if (arithmos_pelaton == 0)
		mesos_xronos = 0.0;
	else
		mesos_xronos = ((float)xronos_anamonis)/((float)arithmos_pelaton);

	printf("\n\n-Eksipiretithikan %d pelates sunolika.",arithmos_pelaton);
	printf("\n-I trapeza emeine anoixti gia %u lepta epipleon.",extra_time);
	printf("\n-O sunolikos xronos leitoyrgias tis trapezas itan %u lepta.",xronos_leitourgias+extra_time);
	printf("\n-O mesos xronos anamonhs htan %4.2f lepta.",mesos_xronos);
	printf("\n-O tamias htan adranhs gia %d lepta", tamiasInactive);
    getchar();
    
    for(i=0; i<=total_metritis-arithmos_pelaton; i++)
    {
    	
	}
	return 0;
}


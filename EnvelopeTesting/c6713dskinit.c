//C6713dskinit.c Includes functions from TI in the C6713 CSL and C6713DSK BSL

#include "C6713dskinit.h"
#define using_bios                  //if BIOS don't use top of vector table
extern Uint32 fs;            			//for sampling frequency

void c6713_dsk_init()       			//dsp-peripheral initialization
{
DSK6713_init();                   	//call BSL to init DSK-EMIF,PLL)

hAIC23_handle=DSK6713_AIC23_openCodec(0, &config);//handle(pointer) to codec
DSK6713_AIC23_setFreq(hAIC23_handle, fs);  //set sample rate
MCBSP_config(DSK6713_AIC23_DATAHANDLE,&AIC23CfgData);//interface 32 bits toAIC23

MCBSP_start(DSK6713_AIC23_DATAHANDLE, MCBSP_XMIT_START | MCBSP_RCV_START |
	MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);//start data channel again
}

void comm_poll()					 		//added for communication/init using polling
{
	poll=1;              				//1 if using polling
   c6713_dsk_init();    				//init DSP and codec
}

void comm_intr()						 	//for communication/init using interrupt
{
	poll=0;                        	//0 since not polling
   IRQ_globalDisable();           	//disable interrupts
	c6713_dsk_init(); 					//init DSP and codec
	CODECEventId=MCBSP_getXmtEventId(DSK6713_AIC23_codecdatahandle);//McBSP1 Xmit

#ifndef using_bios						//do not need to point to vector table
  	IRQ_setVecs(vectors);     			//point to the IRQ vector table
#endif										//since interrupt vector handles this

  	IRQ_map(CODECEventId, 11);			//map McBSP1 Xmit to INT11
  	IRQ_reset(CODECEventId);    		//reset codec INT 11
   IRQ_globalEnable();       			//globally enable interrupts
  	IRQ_nmiEnable();          			//enable NMI interrupt
   IRQ_enable(CODECEventId);			//enable CODEC eventXmit INT11

	output_sample(0);        			//start McBSP interrupt outputting a sample
}

void output_sample(int out_data)    //for out to Left and Right channels
{
	short CHANNEL_data;

	AIC_data.uint=0;                 //clear data structure
	AIC_data.uint=out_data;          //32-bit data -->data structure

//The existing interface defaults to right channel. To default instead to the
//left channel and use output_sample(short), left and right channels are swapped
//In main source program use LEFT 0 and RIGHT 1 (opposite of what is used here)
	CHANNEL_data=AIC_data.channel[RIGHT]; 			//swap left and right channels
	AIC_data.channel[RIGHT]=AIC_data.channel[LEFT];
	AIC_data.channel[LEFT]=CHANNEL_data;
   if (poll) while(!MCBSP_xrdy(DSK6713_AIC23_DATAHANDLE));//if ready to transmit
		MCBSP_write(DSK6713_AIC23_DATAHANDLE,AIC_data.uint);//write/output data
}

void output_left_sample(short out_data)     	  	 //for output from left channel
{
	AIC_data.uint=0;                              //clear data structure
	AIC_data.channel[LEFT]=out_data;   //data from Left channel -->data structure

	if (poll) while(!MCBSP_xrdy(DSK6713_AIC23_DATAHANDLE));//if ready to transmit
		MCBSP_write(DSK6713_AIC23_DATAHANDLE,AIC_data.uint);//output left channel
}

void output_right_sample(short out_data)  		//for output from right channel
{
	AIC_data.uint=0;                             //clear data structure
	AIC_data.channel[RIGHT]=out_data; //data from Right channel -->data structure

	if (poll) while(!MCBSP_xrdy(DSK6713_AIC23_DATAHANDLE));//if ready to transmit
		MCBSP_write(DSK6713_AIC23_DATAHANDLE,AIC_data.uint);//output right channel
}

Uint32 input_sample()                      	  	//for 32-bit input
{
	short CHANNEL_data;

	if (poll) while(!MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE));//if ready to receive
		 AIC_data.uint=MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data

//Swapping left and right channels (see comments in output_sample())
	CHANNEL_data=AIC_data.channel[RIGHT]; 			//swap left and right channel
	AIC_data.channel[RIGHT]=AIC_data.channel[LEFT];
	AIC_data.channel[LEFT]=CHANNEL_data;

	return(AIC_data.uint);
}

short input_left_sample()                   		//input to left channel
{
	if (poll) while(!MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE));//if ready to receive
	 AIC_data.uint=MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read into left channel
	return(AIC_data.channel[LEFT]);					//return left channel data
}

short input_right_sample()                  		//input to right channel
{
	if (poll) while(!MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE));//if ready to receive
	 AIC_data.uint=MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read into right channel
	return(AIC_data.channel[RIGHT]); 				//return right channel data
}

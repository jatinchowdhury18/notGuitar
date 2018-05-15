// Ring modulator lab template.

// Must include for sine sinf(x) function.
#include <math.h>
#include <stdio.h>

// Must include for DSK functionality.
#include "dsk6713_aic23.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"

Uint32 fs=DSK6713_AIC23_FREQ_24KHZ;		// Set codec sampling rate to 44100.

// Defines **************************************************.
// Add your own... Frequency of LED blinking, Carrier waveform (sine), Length of sine-table, etc.
// For example: #define SAMPLE_RATE 44100				// Sample rate of AIC23 codec.
// #define ...
//GLOBALS
#define ATT_LENGTH 5001 //10001 //15001
#define REL_LENGTH 5001 //10001
#define SUS_LENGTH 50000 //100000
#define SMOOTH_LENGTH 90 //200
//Max signed 16-bit value = 32767, 0.03*32767 = 
//TUNE THESE THRESHOLDS
#define THRESH_ATT 20
#define THRESH_REL 18

short j = 0;
//short i = 1;
short y_buff[SMOOTH_LENGTH];
short y = 0;
int y_avg = 0;
int i = 0;
short y_index = 0;
int k = 0;
short lastState = 0;
short max_index;

//LOOK UP TABLES
#pragma DATA_SECTION (att_env_table, ".EXT_RAM")
int att_env_table[ATT_LENGTH];
#pragma DATA_SECTION (rel_env_table, ".EXT_RAM")
int rel_env_table[REL_LENGTH];
#pragma DATA_SECTION (sus_env_table, ".EXT_RAM")
int sus_env_table[SUS_LENGTH];

short LED_counter = 0;	//LED to check if connection to board

short max(short arr[], short size){
	//return largest magnitude value from array
	if(arr[y_index] > y){max_index = y_index; return arr[y_index];}
	else if(y_index != max_index){return y;}
	else if(y_index == max_index && y_index != SMOOTH_LENGTH - 1){max_index = y_index+1; return arr[max_index];}
	//If shortcuts dont work...
	short max = 0;
	short i = 0;
	short test = 0;
	for(i = 0; i < size; i++){
		test = arr[i];
		if(test > max){max = test; max_index = i;}	
	}
	return max;
}

short absolute(short x){
	if(x < 0)
		x = -x;	
	return x;
}

// Interrupt service routine, called on audio codec sample 
// clock trigger.
// **********************************************************.
interrupt void c_int11()         		
{
   // The majority of your code should go in this function.

   // 32bit audio IO. 16 bits per channel, highword|lowword.
   int   in_sample;
   int   out_sample;
   short x_p;
   long int x; 
   //short y;  
   // Define more variables here. ***************************.

   // Get the state of the DIP switches. ********************.
   //g_input_line_in = DSK6713_DIP_get(0);
   
   LED_counter++;
   // Handle the LED toggling. ******************************.
   if(LED_counter == 2000){
      LED_counter = 0;
      DSK6713_LED_toggle(0);
   }
   
   y_index++;
   if(y_index == SMOOTH_LENGTH){
   	  y_index = 0;
   }
   
   //Audio input
   in_sample   = input_sample();
   
   x_p = (0xFFFF & in_sample);
   x = x_p;
   int x_ref = x_p;
   y_avg -= y_buff[y_index] >> 6;
   y_buff[y_index] = absolute(x);
   y_avg += y_buff[y_index] >> 6;
   //y = 10*filter(max(y_buff, SMOOTH_LENGTH));	//SMOOOOTH
   //y = max(y_buff, SMOOTH_LENGTH);
   
   if(y >= THRESH_ATT && j < ATT_LENGTH && (lastState == 3 || lastState == 0)){
      //attack
      x *= att_env_table[j];
      x >>= 18; //x /= 1000000;///11700;
      //x = 0;
      j++;
      lastState = 0;
   }
   else if(y > THRESH_REL){
      //sustain      
      if(k < SUS_LENGTH-1)
        k++;
      x *= sus_env_table[k];
      x >>= 18;
      //x = 0;
      lastState = 1;
      
       if(y > (y_avg*9 >> 1) && y > 800)
         j = 0; k = 0; lastState = 3;
   }
   else if(j > 0 && (lastState == 1 || lastState == 2) && y < 5*THRESH_ATT){
      //release
      if(k < SUS_LENGTH-1)
        k++;     
      x *= rel_env_table[REL_LENGTH-j];
      x >>= 18; //x /= 1000000;
      x *= sus_env_table[k];
      x >>= 18; //x /= 1000000;
      //x = 0;
      j--;
      lastState = 2;
   }
   else{
       //idle
       x = 0;
       k = 0;
       j = 0;
       y_buff[y_index] = 0;
       lastState = 3;
   }
   //x <<= 1;
   if(DSK6713_DIP_get(0)){ x = x_ref; }	//If swith is up, use reference output
   x_p = x << 1;
   out_sample = (0x0000FFFF & (x_p)) | 
    	         (0xFFFF0000 & (x_p << 16));	   

   output_sample(out_sample);

   return;
}

void gen_env_tables(){
	//generate look-up tables for envelope
	//get sax envelope
	
	FILE *fp1;
	fp1 = fopen("sax_att.txt", "r");	//open file
	float test;
	for(i = 0; i < ATT_LENGTH; i++){
		fscanf(fp1, "%f", &test);
    	att_env_table[i] = test*1024*256; // << 18  //*1000000;
    	fscanf(fp1, "%f", &test);
	}
    fclose(fp1);
    
	FILE *fp2;
    fp2 = fopen("sax_rel.txt", "r"); //open file
    for(i = 0; i < REL_LENGTH; i++){
    	fscanf(fp1, "%f", &test);
    	//fread((void*)(&test), sizeof(test), 1, fp2);
    	rel_env_table[i] = test*1024*256;// << 18   //*1000000;
        fscanf(fp1, "%f", &test);
  	}
  	fclose(fp2);
    
  	for(i = 0; i < SUS_LENGTH; i++){  
    	sus_env_table[i] = (0.75 + 1.85*(1-exp((-1.0)*i/15000.0)))*1024*256;// << 18   //*1000000;
  	}
	// construct sustain look up table
	
}


void main()
{
  // Generate sine lookup table.
  //gen_sine_table();
  gen_env_tables();
  
  for(i = 0; i < SMOOTH_LENGTH; i++){
	y_buff[i] = 0;
  }

  // Init DSK, codec, McBSP.
  comm_intr();                   

  // Init DSK functionality. ********************************.
  // Call the init functions for the LEDs and DIPs 
  while(1){ // Inf. loop. Interrupt-driven at this point.
  	y = max(y_buff, SMOOTH_LENGTH);
  }
}

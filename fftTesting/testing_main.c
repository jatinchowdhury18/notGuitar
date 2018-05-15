// Ring modulator lab template.

// Must include for sine sinf(x) function.
#include <math.h>
#include <stdio.h>

// Must include for DSK functionality.
#include "dsk6713_aic23.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"

Uint32 fs=DSK6713_AIC23_FREQ_24KHZ;		// Set codec sampling rate to 22050.

// Defines **************************************************.
// Add your own... Frequency of LED blinking, Carrier waveform (sine), Length of sine-table, etc.
// For example: #define SAMPLE_RATE 44100				// Sample rate of AIC23 codec.
// #define ...
//GLOBALS
#define WIN_LENGTH 50//188
#define M_PI 3.14159265359
#define BUFFER_LENGTH 300
#define PAUL_LENGTH 90

int LED_counter = 0;

int kernels[WIN_LENGTH][2]; //array for Fourier Kernels first array has cosines, second has sines

//buffers
int inBuffer[WIN_LENGTH];
int fourierBuffer[WIN_LENGTH][2]; //real part in first array, imaginary in second
int outBuffer[WIN_LENGTH];//[WIN_LENGTH];
int paulBuffer[WIN_LENGTH][2]; //int pushBuffer[WIN_LENGTH];
int y_n[WIN_LENGTH];
int lastSampleIn; int lastSampleOut;
int joey_index = 0;
int oldFourierReal; //int oldFourierImag;//[WIN_LENGTH];
int in = 0;
int out = 0;
int delay_count = 0;
int paul_mult[PAUL_LENGTH];

int joey(int x){
  //x <<= 10;
  //shift buffers
  joey_index++; if(joey_index >= WIN_LENGTH){joey_index = 0;} //update index
  lastSampleIn = inBuffer[joey_index];
  inBuffer[joey_index] = x;
  
  //save old Fourier
  //oldFourier = fourierBuffer[0][0];
  int k = 0;  
  int sum = (x - lastSampleIn);
  //calc 5 bands for PAUL
  fourierBuffer[0][0] = fourierBuffer[0][0] + sum;
  //for(k=1; k<5; k++){
  //	oldFourierReal = fourierBuffer[k][0] + sum;
  //  fourierBuffer[k][0] = (oldFourierReal*kernels[k][0] - fourierBuffer[k][1]*kernels[k][1]) >> 10;
  //  fourierBuffer[k][1] = (oldFourierReal*kernels[k][1] + fourierBuffer[k][1]*kernels[k][0]) >> 10;
  //}
  //Paul logic to figure out which table to use
  x = 0; //(fourierBuffer[0][0]) >> 1;
  fourierBuffer[WIN_LENGTH/2][0] = -(fourierBuffer[WIN_LENGTH/2][0] + sum);
  for(k=1; k<WIN_LENGTH/2; k++){
  	oldFourierReal = fourierBuffer[k][0] + sum;
    fourierBuffer[k][0] = (oldFourierReal*kernels[k][0] - fourierBuffer[k][1]*kernels[k][1]) >> 10;
    fourierBuffer[k][1] = (oldFourierReal*kernels[k][1] + fourierBuffer[k][1]*kernels[k][0]) >> 10;
    //inverse
    x += (fourierBuffer[k][0]*kernels[k][0] + fourierBuffer[k][1]*kernels[k][1]) >> 10;
  }
  x += (fourierBuffer[0][0] - paulBuffer[WIN_LENGTH/2][0]) >> 1;

  //inverse DFT
  //x = (fourierBuffer[0][0] - paulBuffer[WIN_LENGTH/2][0]) >> 1;
  //for(k = 1; k < WIN_LENGTH/2; k++){
  //  x += (fourierBuffer[k][0]*kernels[k][0] + fourierBuffer[k][1]*kernels[k][1]) >> 10;
  //}
  x >>= 5; ///= WIN_LENGTH;

  //joey's output
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
   short y;  
   // Define more variables here. ***************************.

   // Get the state of the DIP switches. ********************.
   //g_input_line_in = DSK6713_DIP_get(0);
   
   LED_counter++;
   // Handle the LED toggling. ******************************.
   if(LED_counter == 2000){
      LED_counter = 0;
      DSK6713_LED_toggle(0);
   }
  
   //Audio input
   in_sample   = input_sample();
   
   x_p = (0xFFFF & in_sample);
   x = x_p;
   int x_ref = x_p;
   
   x = joey(x);
   /*if(x < 0){
   	x -= ((x*x) >> 10);	//add input sample to buffer
   }
   else{
   	x += ((x*x) >> 10);
   }
   x = joey(x);*/
   
   if(DSK6713_DIP_get(0)){ x = x_ref; }	//If swith is up, use reference output
   x_p = x;
   out_sample = (0x0000FFFF & (x_p)) | 
    	         (0xFFFF0000 & (x_p << 16));	   

   output_sample(out_sample);

   return;
}

void gen_kernels(){
  int k = 0;
  for(k=0; k < WIN_LENGTH; k++){
    kernels[k][0] = cosf(2*M_PI*k/WIN_LENGTH)*1024;
    kernels[k][1] = sinf(2*M_PI*k/WIN_LENGTH)*1024;
  }
}

void loadPAULFile(){
	FILE *fp1;
	fp1 = fopen("multipliers.txt", "r");	//open file
	float test;
	int i = 0;
	for(i = 0; i < PAUL_LENGTH; i++){
		fscanf(fp1, "%f", &test);
    	paul_mult[i] = test*1024;//32768;
	}
    fclose(fp1);	
}


void main()
 {
  // Generate sine lookup table.
  gen_kernels();
  loadPAULFile();

  //zero buffers
  int z = 0;
  for(z=0; z < WIN_LENGTH; z++){
    inBuffer[z]=0; y_n[z]=0;
    fourierBuffer[z][0]=0; fourierBuffer[z][1]=0;
    outBuffer[z] = 0;
    paulBuffer[z][0] = 0; paulBuffer[z][1] = 0;
    oldFourierReal = 0;
    int zz = 0;
    for(zz = 0; zz < WIN_LENGTH; zz++){
      //outBuffer[z][zz] = 0;	
    }
  }
  for(z =  0; z < BUFFER_LENGTH; z++){
  	//realBuffer[z] = 0;
  }

  // Init DSK, codec, McBSP.
  comm_intr();                   

  //int ind = 0;
  // Init DSK functionality. ********************************.
  // Call the init functions for the LEDs and DIPs 
  while(1) // Inf. loop. Interrupt-driven at this point.
  {
  	/*
  	if(delay_count > 0){
  	  ind = buff_index - 1; if(ind < 0){ind = BUFFER_LENGTH-1;} 
  	  realBuffer[ind] = joey(realBuffer[ind]);
  	  delay_count--;
  	}
  	*/
  }
}

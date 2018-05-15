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
//Freq
#define WIN_LENGTH 188
#define M_PI 3.14159265359
#define FREQ_THRESH 7500 //150000000
//#define FREQ_THRESH_Note0 32000 //you cannot hear any of the notes for first if statement
//#define FREQ_THRESH_Note2 17500 //you can hear notes 1 and 2 but not the rest for first if statement
//#define FREQ_THRESH_Note3 7500 //you can hear notes 1,2 and 3 but not the rest for first if statement

//Cosines
#define COS_1 1023 //cos(2*pi*1/188)
#define COS_2 1022
#define COS_3 1019

//Amp
#define ATT_LENGTH 5001 
#define REL_LENGTH 5001 
#define SUS_LENGTH 50000 
#define SMOOTH_LENGTH 75 //90
#define THRESH_ATT 25
#define THRESH_REL 18

//GLOBALS
int LED_counter = 0;

//Amplitude variables
short j = 0;
short y_buff[SMOOTH_LENGTH];
short y = 0;
int y_avg = 0;
int i = 0;
short y_index = 0;
int k = 0;
short lastState = 0;
short max_index;

//LOOK UP TABLES - Amplitude Multipliers
#pragma DATA_SECTION (att_env_table, ".EXT_RAM")
int att_env_table[ATT_LENGTH];
#pragma DATA_SECTION (rel_env_table, ".EXT_RAM")
int rel_env_table[REL_LENGTH];
#pragma DATA_SECTION (sus_env_table, ".EXT_RAM")
int sus_env_table[SUS_LENGTH];


//Freq Variables
//int kernels[WIN_LENGTH][2]; //array for Fourier Kernels first array has cosines, second has sines

//buffers
int joeyBuffer[WIN_LENGTH];	//Window of time domain samples
int fourierBuffer[WIN_LENGTH][2]; //real part in first array, imaginary in second
int joey = 0; int oldFourier; int sum;

//LOOK UP TABLES - Freq Multipliers
int paul_band12[WIN_LENGTH];
int paul_band3[WIN_LENGTH];
int paul_band4[WIN_LENGTH];
int paul_avg[WIN_LENGTH];
//int paul_mult[4*WIN_LENGTH];
short which_band = 0;//WIN_LENGTH; 
short band_picked = 0;

void paul(){
  //Determine which set of multipliers to use
  
  //Fourier transform
  //fourierBuffer[1][0] = ((fourierBuffer[1][0] + sum)*kernels[1][0] - fourierBuffer[1][1]*kernels[1][1]) >> 10;
  //fourierBuffer[1][1] = ((fourierBuffer[1][0] + sum)*kernels[1][1] + fourierBuffer[1][1]*kernels[1][0]) >> 10;
  
  fourierBuffer[1][0] = (fourierBuffer[1][0] + sum)*COS_1 >> 10;
  //fourierBuffer[1][1] = ((fourierBuffer[1][0] + sum)*kernels[1][1] + fourierBuffer[1][1]*kernels[1][0]) >> 10;
  
  fourierBuffer[2][0] = (fourierBuffer[2][0] + sum)*COS_2 >> 10;
  //fourierBuffer[2][1] = ((fourierBuffer[2][0] + sum)*kernels[2][1] + fourierBuffer[2][1]*kernels[2][0]) >> 10;
  
  fourierBuffer[3][0] = (fourierBuffer[3][0] + sum)*COS_3 >> 10;
  //fourierBuffer[3][1] = ((fourierBuffer[3][0] + sum)*kernels[3][1] + fourierBuffer[3][1]*kernels[3][0]) >> 10;
  
  //Paul's logic
  if(abs(fourierBuffer[1][0]) > FREQ_THRESH){
  	which_band = 2;// WIN_LENGTH; // WIN_LENGTH
  }
  else if(abs(fourierBuffer[2][0]) > FREQ_THRESH){
  	which_band = 3;//2*WIN_LENGTH; //2*WIN_LENGTH
  }
  else if(abs(fourierBuffer[3][0]) > FREQ_THRESH){
  	which_band = 4;//564; //3*WIN_LENGTH
  }
  else{ which_band = 0;}//752; } //4*WIN_LENGTH
  
}


//Function for freq adjustments - determine fund freq band, and circular convolution
int leahy(int x){

  //shift buffers
  joey++; if(joey >= WIN_LENGTH){joey = 0;} //update index
  sum = x - joeyBuffer[joey];
  joeyBuffer[joey] = x;  
  
  //Fourier
  
  //Paul logic to figure out which table to use
  int n = 0; int ind; x = 0;
  switch(which_band){

  	//note is in band 2
  	//circular conv
  case 2:
  	for(ind = joey+1; ind < WIN_LENGTH; ind++){
      n++;
  	  x += joeyBuffer[ind]*paul_band12[WIN_LENGTH-n] >> 10;
    }
    for(ind = 0; ind <= joey; ind++){
  	  n++;
  	  x += joeyBuffer[ind]*paul_band12[WIN_LENGTH-n] >> 10;
    }
    break;

  case 3:	
  	//note is in band 3
  	//circular conv
  	for(ind = joey+1; ind < WIN_LENGTH; ind++){
      n++;
  	  x += joeyBuffer[ind]*paul_band3[WIN_LENGTH-n] >> 10;
    }
    for(ind = 0; ind <= joey; ind++){
  	  n++;
  	  x += joeyBuffer[ind]*paul_band3[WIN_LENGTH-n] >> 10;
    }
    break;

  case 4:	
  	//note is in band 4
  	//cirular conv
  	for(ind = joey+1; ind < WIN_LENGTH; ind++){
      n++;
  	  x += joeyBuffer[ind]*paul_band4[WIN_LENGTH-n] >> 10;
    }
    for(ind = 0; ind <= joey; ind++){
  	  n++;
  	  x += joeyBuffer[ind]*paul_band4[WIN_LENGTH-n] >> 10;
    }
    break;
    
  default:
  	//in case note not detected in any band
  	//circular conv
  	//int rev = which_band*WIN_LENGTH
  	for(ind = joey+1; ind < WIN_LENGTH; ind++){
      n++;
  	  x += joeyBuffer[ind]*paul_avg[WIN_LENGTH-n] >> 10;
    }
    for(ind = 0; ind <= joey; ind++){
  	  n++;
  	  x += joeyBuffer[ind]*paul_avg[WIN_LENGTH-n] >> 10;
    } 
  }

  //joey's output
  return x;
  
}

//optimized max function
short max(short arr[], short size){
	//return largest magnitude value from array
	if(arr[y_index] > y){max_index = y_index; return arr[y_index];}
	else if(y_index != max_index){return y;}
	//else if(y_index != SMOOTH_LENGTH - 1){max_index = y_index+1; y = arr[max_index];}
	//If shortcuts dont work...
	short max = 0;//y;
	short ind = 0;
	for(ind = 0; ind < size; ind++){
		if(arr[ind] > max){max = arr[ind]; max_index = ind;}	
	}
	return max;
}
//absolute value function
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
   // Define more variables here. ***************************.

   //LED to see if things are running
   /*LED_counter++;
   if(LED_counter == 2000){
      LED_counter = 0;
      DSK6713_LED_toggle(0);
   }*/
   
   //update smoothing buffer
   y_index++;
   if(y_index == SMOOTH_LENGTH){
   	  y_index = 0;
   }
  
   //Audio input
   in_sample   = input_sample();
   x_p = (0xFFFF & in_sample);
   x = x_p;
   int x_ref = x_p;
   
   //Do smoothing
   //y_avg -= y_buff[y_index] >> 6;
   y_buff[y_index] = absolute(x);
   //y_avg += y_buff[y_index] >> 6;
   //y = max(y_buff, SMOOTH_LENGTH);

   //square signal
   if(x < 0){
   	x -= ((x*x) >> 10);	//add input sample to buffer
   }
   else{
   	x += ((x*x) >> 10);
   }
   //freq control function
   
   x = leahy(x);

   //amplitude things happen here
   if(y >= THRESH_ATT && j < ATT_LENGTH && (lastState == 0 || lastState == 3)){
      //DSK6713_LED_on(1);
      //DSK6713_LED_off(2);
      //DSK6713_LED_off(3);
      
      //attack
      x *= att_env_table[j];
      x >>= 18; //x /= 1000000;///11700;
      j++;
      lastState = 0;
      //y_avg = 100;
   }
   else if(y > THRESH_REL){
   	  /*DSK6713_LED_off(1);
      DSK6713_LED_on(2);
      DSK6713_LED_off(3);*/
      
      //sustain      
      if(k < SUS_LENGTH-1)
        k++;
      if(DSK6713_DIP_get(1)){  
      x *= sus_env_table[k];
      x >>= 18;
      }
      //x = 0;
      lastState = 1;
      
       if((y_buff[y_index] - y) > 600 /*(y_avg*2)*/ && y_buff[y_index] > 800){
         j = 0;
         k = 0;
         lastState = 3; 
       }  
   }
   /*else if(j > 0 && (lastState == 1 || lastState == 2) && y < 5*THRESH_ATT){
      DSK6713_LED_off(1);
      DSK6713_LED_off(2);
      DSK6713_LED_on(3);  	
   	
      //release
      //paul();
      if(k < SUS_LENGTH-1)
        k++;     
      x *= rel_env_table[REL_LENGTH-j];
      x >>= 18; //x /= 1000000;
      x *= sus_env_table[k];
      x >>= 18; //x /= 1000000;
      j--;
      lastState = 2;
   }*/
   else{
       //DSK6713_LED_off(1);
       //DSK6713_LED_off(2);
       //DSK6713_LED_off(3);  	
    	  
       //idle
       x = 0;
       k = 0;
       j = 0;
       lastState = 3;
       //y_buff[y_index] = 0;
       //which_band = 0;
       //band_picked = 0;
   }
   //x <<= 1;
   if(DSK6713_DIP_get(0)){ x = x_ref; }	//If swith is up, use reference output
   x_p = x << 1;
   out_sample = (0x0000FFFF & (x_p)) | 
    	         (0xFFFF0000 & (x_p << 16));	   

   output_sample(out_sample);

   return;
}

void gen_kernels(){
  int k = 0;
  for(k=0; k < WIN_LENGTH; k++){
    //kernels[k][0] = cosf(2*M_PI*k/WIN_LENGTH)*1024;
    //kernels[k][1] = sinf(2*M_PI*k/WIN_LENGTH)*1024;
  }
}

void loadPAULFile(){
	//load freq multiplier tables
	float test;
	
	/*//bands 1 and 2
	FILE *fp1;
	fp1 = fopen("mult12IF.txt", "r");	//open file
	int i = 0;
	for(i = 0; i < WIN_LENGTH; i++){
		fscanf(fp1, "%f", &test);
    	paul_band12[i] = test*1024;//32768;
    	//paul_mult[i] = test*1024;
	}
    fclose(fp1);
    
    //band 3
    FILE *fp2;
	fp2 = fopen("mult3IF.txt", "r");	//open file
	for(i = 0; i < WIN_LENGTH; i++){
		fscanf(fp2, "%f", &test);
    	paul_band3[i] = test*1024;//32768;
    	//paul_mult[i+WIN_LENGTH] = test*1024;
	}
    fclose(fp2);
    
    //band 4
    FILE *fp3;
	fp3 = fopen("mult4IF.txt", "r");	//open file
	for(i = 0; i < WIN_LENGTH; i++){
		fscanf(fp3, "%f", &test);
    	paul_band4[i] = test*1024;//32768;
    	//paul_mult[i + 2*WIN_LENGTH] = test*1024;
	}
    fclose(fp3);
    */
    //averaged
    FILE *fp4;
	fp4 = fopen("multTotIF.txt", "r");	//open file
	for(i = 0; i < WIN_LENGTH; i++){
		fscanf(fp4, "%f", &test);
    	paul_avg[i] = test*1024;//32768;
    	//paul_mult[i + 3*WIN_LENGTH] = test*1024;
	}
    fclose(fp4);
    	
}

void gen_env_tables(){
	//generate look-up tables for amplitude envelope
	
	//attack envelope
	FILE *fp1;
	fp1 = fopen("sax_att.txt", "r");	//open file
	float test;
	for(i = 0; i < ATT_LENGTH; i++){
		fscanf(fp1, "%f", &test);
		//fread((void*)(&test), sizeof(test), 1, fp1);//ENV_LENGTH, fp1);
    	att_env_table[i] = test*1024*256; // << 18  //*1000000;
    	fscanf(fp1, "%f", &test);
	}
    fclose(fp1);
    /*
    //sustain envelope
	FILE *fp2;
    fp2 = fopen("sax_rel.txt", "r"); //open file
    for(i = 0; i < REL_LENGTH; i++){
    	fscanf(fp1, "%f", &test);
    	//fread((void*)(&test), sizeof(test), 1, fp2);
    	rel_env_table[i] = test*1024*256;// << 18   //*1000000;
        fscanf(fp1, "%f", &test);
  	}
  	fclose(fp2);
  	*/
    // construct sustain look up table
  	for(i = 0; i < SUS_LENGTH; i++){  
    	sus_env_table[i] = (0.75 + 1.85*(1-exp((-1.0)*i/15000.0)))*1024*256;// << 18   //*1000000;
  	}
	
}

void main(){
  DSK6713_LED_off(0);
  // Generate sine lookup table.
  //gen_kernels();
  loadPAULFile();
  gen_env_tables();

  //zero buffers
  int z = 0;
  for(z=0; z < WIN_LENGTH; z++){
    joeyBuffer[z]=0;
    fourierBuffer[z][0]=0; fourierBuffer[z][1]=0;
  }

  for(z = 0; z < SMOOTH_LENGTH; z++){
	y_buff[z] = 0;
  }

  // Init DSK, codec, McBSP.
  comm_intr();                   
  DSK6713_LED_on(0);
  // Init DSK functionality. ********************************.
  // Call the init functions for the LEDs and DIPs 
  while(1) // Inf. loop. Interrupt-driven at this point.
  {
  	if(lastState == 3){y_buff[y_index] = 0;}
  	y = max(y_buff, SMOOTH_LENGTH);
  }
}

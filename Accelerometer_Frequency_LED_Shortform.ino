#include "arduinoFFT.h"
 
#define SAMPLES 64             //Must be a power of 2
#define SAMPLING_FREQUENCY 100 //Hz, must be less than 10000 due to ADC
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;

int led1 = 8;
int led2 = 9;
int led3 = 10;
int Ft;
int Fd; 
//int MA; //Moving Average
int count;
double vReal[SAMPLES];
double vImag[SAMPLES];
//double peak; 
void setup() {
    Serial.begin(115200);
    
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
    pinMode(led1, OUTPUT);
    digitalWrite(led1,LOW);
    pinMode(led2, OUTPUT);
    digitalWrite(led2,LOW);
    pinMode(led3, OUTPUT);
    digitalWrite(led3,LOW);
}
 
void loop() {
   
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
   
   
   Ft = 50;
   Fd=5;
    /*SAMPLING*/
 count = 0;
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = (analogRead(A2)-408);

        //Serial.print("\n");
        //Serial.print (vReal[i]);
        if (vReal[i]<-3 || vReal[i]>3)

        {
          
          count = count+1 ;
          }

        
        
      
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }

if (count>0.7*SAMPLES)

     {
       
          /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
          
          
           /*PRINT RESULTS*/
    Serial.print("\n");
    Serial.println(peak);     //Print out what frequency is the most dominant.   
         
              if(peak < Ft+Fd)
      {
        digitalWrite(led1, HIGH);
      
      }
    else if (( Ft-Fd <= peak)&&(peak <= Ft+Fd) )
      {
       digitalWrite(led2, HIGH);
                  
        } 
    else if ( peak > Ft-Fd) 
                   
      {
       digitalWrite(led3, HIGH);
       }
          }
    
 
       

    delay(1000);  //Repeat the process every second OR:
}

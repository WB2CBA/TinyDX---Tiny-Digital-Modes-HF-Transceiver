//*********************************************************************************************************
//**********************  TinyDX  - QRPp DIGITAL MODES MULTIBAND HF TRANSCEIVER   *****************
//********************************* Write up start: 06/01/2024 ********************************************
// FIRMWARE VERSION: TinyDX_V1.4
// Barb(Barbaros ASUROGLU) - WB2CBA - 2025
//*********************************************************************************************************
// Required Libraries
// ----------------------------------------------------------------------------------------------------------------------
// Etherkit Si5351 (Needs to be installed via Library Manager to arduino ide) - SI5351 Library by Jason Mildrum (NT7S) - https://github.com/etherkit/Si5351Arduino
//*****************************************************************************************************
//* IMPORTANT NOTE: Use V2.1.3 of NT7S SI5351 Library. This is the only version compatible with TinyDX!!!*
//*****************************************************************************************************

//*************************************[ LICENCE and CREDITS ]*********************************************
//  Initial FSK TX Signal Generation code by: Burkhard Kainka(DK7JD) - http://elektronik-labor.de/HF/SDRtxFSK2.html
//  SI5351 Library by Jason Mildrum (NT7S) - https://github.com/etherkit/Si5351Arduino
//  Improved FSK TX  signal generation code is from JE1RAV https://github.com/je1rav/QP-7C
//
// License
// -------
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject
// to the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


//*******************************[ LIBRARIES ]*************************************************
#include <si5351.h>
#include "Wire.h"
#include <EEPROM.h>
//*******************************[ VARIABLE DECLERATIONS ]*************************************
uint32_t val;
int addr;
unsigned int Band = 0;
//unsigned long freq; 
unsigned long int freq1;
unsigned long int freq = 14074000;
unsigned long int freq4;
unsigned long int freqdiv;
int32_t cal_factor = 0;
int TX_State = 0;
int TX_inh;
int TXSW_State;
int index = 0;
int B;
int M;

unsigned long F_FT8;
unsigned long F_FT4;

unsigned long B1_FT8;
unsigned long B1_FT4;
unsigned long B2_FT8;
unsigned long B2_FT4;

uint32_t ReferenceFrequency = 26000000; //TCXO Frequency used as a reference for the Si5351PLL

// **********************************[ DEFINE's ]***********************************************
#define BAND1 20 // Change to your preferred band 20m/17m/15/m12m/10m
#define BAND2 10 // Change to your preferred band 20m/17m/15/m12m/10m
#define TX 13 //TX LED
#define TXSW 9 //TX BOOST SUPPLY
#define RX  8 // RX SWITCH
#define M_SW  5 // MODE SWITCH
#define B_SW  4 // BAND SWITCH
Si5351 si5351;

//*************************************[ SETUP FUNCTION ]************************************** 
void setup()
{
      
  Wire.begin(); // wake up I2C bus 
  
  Serial.begin(9600); while (!Serial);
       
pinMode(TX, OUTPUT);

     pinMode(TXSW, OUTPUT);

        pinMode(RX, OUTPUT);
        
         pinMode(M_SW, INPUT);

     pinMode(B_SW, INPUT);

       digitalWrite(TX,0);
      
          digitalWrite(TXSW,0);


pinMode(7, INPUT); //PD7 = AN1 = HiZ, PD6 = AN0 = 0

//FLASH RED TX LED FOR POWER ON INDICATION
 
   for (int i = 0; i < 3; i++) {
    digitalWrite(TX, HIGH);  
    delay(200);
    digitalWrite(TX, LOW);
    delay(200);
  }
   

 SW_assign();  
                              
//------------------------------- SET SI5351 VFO -----------------------------------  
   // The crystal load value needs to match in order to have an accurate calibration
 si5351.init(SI5351_CRYSTAL_LOAD_8PF, ReferenceFrequency, 0); //initialize the VFO
  si5351.set_correction(cal_factor, SI5351_PLL_INPUT_XO);
  si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);// SET For Max Power
  si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_8MA); // Set for reduced power for RX 
  
 
  TCCR1A = 0x00;
  TCCR1B = 0x01; // Timer1 Timer 16 MHz
  TCCR1B = 0x81; // Timer1 Input Capture Noise Canceller
  ACSR |= (1<<ACIC);  // Analog Comparator Capture Input
  
  pinMode(7, INPUT); //PD7 = AN1 = HiZ, PD6 = AN0 = 0
          digitalWrite(RX,LOW);   
          
}
 
//**************************[ END OF SETUP FUNCTION ]************************

//***************************[ Main LOOP Function ]**************************
void loop()
{  

Band_Select();

 //--------------------------- LIMIT OUT OF OPERATION BANDS TO ONLY RX -----------------
freqdiv = freq / 1000000;

if (freqdiv < 11 || freqdiv > 30){

         goto RX1; // Skip TX Loop
         
}  

// --------------------------- FSK  TX LOOP -----------------------------------
 // The following code is from JE1RAV https://github.com/je1rav/QP-7C
  //(Using 3 cycles for timer sampling to improve the precision of frequency measurements)
  //(Against overflow in low frequency measurements)
  
  int FSK = 1;
  int FSKtx = 0;

  while (FSK>0){
    int Nsignal = 10;
    int Ncycle01 = 0;
    int Ncycle12 = 0;
    int Ncycle23 = 0;
    int Ncycle34 = 0;
    unsigned int d1=1,d2=2,d3=3,d4=4;
  
    TCNT1 = 0;  
    while (ACSR &(1<<ACO)){
      if (TIFR1&(1<<TOV1)) {
        Nsignal--;
        TIFR1 = _BV(TOV1);
        if (Nsignal <= 0) {break;}
      }
    }
    while ((ACSR &(1<<ACO))==0){
      if (TIFR1&(1<<TOV1)) {
        Nsignal--;
        TIFR1 = _BV(TOV1);
        if (Nsignal <= 0) {break;}
      }
    }
    if (Nsignal <= 0) {break;}
    TCNT1 = 0;
    while (ACSR &(1<<ACO)){
        if (TIFR1&(1<<TOV1)) {
        Ncycle01++;
        TIFR1 = _BV(TOV1);
        if (Ncycle01 >= 2) {break;}
      }
    }
    d1 = ICR1;  
    while ((ACSR &(1<<ACO))==0){
      if (TIFR1&(1<<TOV1)) {
        Ncycle12++;
        TIFR1 = _BV(TOV1);
        if (Ncycle12 >= 3) {break;}      
      }
    } 
    while (ACSR &(1<<ACO)){
      if (TIFR1&(1<<TOV1)) {
        Ncycle12++;
        TIFR1 = _BV(TOV1);
        if (Ncycle12 >= 6) {break;}
      }
    }
    d2 = ICR1;
    while ((ACSR &(1<<ACO))==0){
      if (TIFR1&(1<<TOV1)) {
        Ncycle23++;
        TIFR1 = _BV(TOV1);
        if (Ncycle23 >= 3) {break;}
      }
    } 
    while (ACSR &(1<<ACO)){
      if (TIFR1&(1<<TOV1)) {
      Ncycle23++;
      TIFR1 = _BV(TOV1);
      if (Ncycle23 >= 6) {break;}
      }
    } 
    d3 = ICR1;
    while ((ACSR &(1<<ACO))==0){
      if (TIFR1&(1<<TOV1)) {
        Ncycle34++;
        TIFR1 = _BV(TOV1);
        if (Ncycle34 >= 3) {break;}
      }
    } 
    while (ACSR &(1<<ACO)){
      if (TIFR1&(1<<TOV1)) {
        Ncycle34++;
        TIFR1 = _BV(TOV1);
        if (Ncycle34 >= 6) {break;}
      }
    } 
    d4 = ICR1;
    unsigned long codefreq1 = 1600000000/(65536*Ncycle12+d2-d1);
    unsigned long codefreq2 = 1600000000/(65536*Ncycle23+d3-d2);
    unsigned long codefreq3 = 1600000000/(65536*Ncycle34+d4-d3);
    unsigned long codefreq = (codefreq1 + codefreq2 + codefreq3)/3;
    if (d3==d4) codefreq = 5000;     
    if ((codefreq < 310000) and  (codefreq >= 10000)) {
       
        
      if (FSKtx == 0){
              
        TX_State = 1;
        digitalWrite(RX,LOW);
         digitalWrite(TXSW,HIGH);
        digitalWrite(TX,HIGH);
        
        delay(10);
        
        si5351.output_enable(SI5351_CLK1, 0);   //RX off
        si5351.output_enable(SI5351_CLK0, 1);   // TX on
      }
    
      si5351.set_freq((freq * 100 + codefreq), SI5351_CLK0);    
        
      FSKtx = 1;
    }
    else{
      FSK--;
    }
  }

 RX1:
   si5351.output_enable(SI5351_CLK0, 0);   //TX off
  digitalWrite(TX,0);
   digitalWrite(TXSW,0);
   

   
       freq4 = freq * 4;
freqdiv = freq / 1000000;

if (freqdiv <= 25){
  
           si5351.set_freq(freq4*100ULL, SI5351_CLK1);
   si5351.output_enable(SI5351_CLK1, 1);   //RX on
}

if (freqdiv > 25 && freqdiv < 30){
            // Set CLK1 to output 112 MHz
  si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB);
  si5351.set_freq_manual(freq4*100ULL, 70000000000ULL, SI5351_CLK1);
                si5351.output_enable(SI5351_CLK1, 1);   //RX on
}
  /*
  Serial.println(freq);
  Serial.println(freq4); 
    */
    
    TX_State = 0;
    digitalWrite(RX,HIGH);
   
  FSKtx = 0;
    
}
//*********************[ END OF MAIN LOOP FUNCTION ]*************************

//********************************************************************************
//******************************** [ FUNCTIONS ] *********************************
//********************************************************************************

void Band_Select(){
M = digitalRead(M_SW);
B = digitalRead(B_SW);

if ((B == LOW)&&(M == LOW)) {
   delay(100); 
if ((B == LOW)&&(M == LOW)) 
 {
 freq = B1_FT8;   
  }
}


if ((B == LOW)&&(M == HIGH)) {
   delay(100); 
if ((B == LOW)&&(M == HIGH)) 
 {
 freq = B1_FT4;   
  }
}


if ((B == HIGH)&&(M == LOW)) {
   delay(100); 
if ((B == HIGH)&&(M == LOW)) 
 {
 freq = B2_FT8;   
  }
}


if ((B == HIGH)&&(M == HIGH)) {
   delay(100); 
if ((B == HIGH)&&(M == HIGH)) 
 {
 freq = B2_FT4;   
  }
}
}


//***************[ Band Switch Frequency and Mode Assign Function ]********************

void SW_assign(){

Band = BAND1;
    Freq_assign();
       B1_FT8 = F_FT8;
         B1_FT4 = F_FT4;

Band = BAND2;
     Freq_assign();
         B2_FT8 = F_FT8;
             B2_FT4 = F_FT4;

}

//*********************[ Band dependent Frequency Assign Function ]********************
void Freq_assign() {

  switch (Band) {
   
    case 20:
      F_FT8 = 14074000;
      F_FT4 = 14080000;
      break;
    case 17:
      F_FT8 = 18100000;
      F_FT4 = 18104000;
      break;
    case 15:
      F_FT8 = 21074000;
      F_FT4 = 21140000;
      break;
  case 12:
      F_FT8 = 24915000;
      F_FT4 = 24919000;
      break;
    case 10:
      F_FT8 = 28074000;
      F_FT4 = 28180000;
      break;
  }
}
//************************[ End of Frequency assign function ]*************************

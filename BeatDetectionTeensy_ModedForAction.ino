// based off of PassThroughStereo example

#include "Beat.h"
#include <QuickStats.h>


//w/outbiquad
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
/*
// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=125,180
AudioMixer4              mixer;          //xy=305,179
AudioAnalyzePeak         analyzer;       //xy=620,116
AudioOutputI2S           i2s2;           //xy=669,274
AudioConnection          patchCord1(i2s1, 0, mixer, 0);
AudioConnection          patchCord2(i2s1, 1, mixer, 1);
AudioConnection          patchCord3(mixer, 0, i2s2, 0);
AudioConnection          patchCord4(mixer, analyzer);
AudioConnection          patchCord5(mixer, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=606,364
// GUItool: end automatically generated code
*/

//with biquad

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=55,177
AudioMixer4              mixer;          //xy=234,177
AudioFilterBiquad        biquad1;        //xy=379,161
AudioAnalyzePeak         analyzer;       //xy=550,113
AudioOutputI2S           i2s2;           //xy=599,271
AudioConnection          patchCord1(i2s1, 0, mixer, 0);
AudioConnection          patchCord2(i2s1, 1, mixer, 1);
AudioConnection          patchCord3(mixer, biquad1);
AudioConnection          patchCord4(mixer, 0, i2s2, 0);
AudioConnection          patchCord5(biquad1, analyzer);
AudioConnection          patchCord6(biquad1, 0, i2s2, 1);
//AudioControlSGTL5000     925f15f6.77ab18; //xy=454,579
AudioControlSGTL5000     sgtl5000_1;     //xy=536,361
// GUItool: end automatically generated code


BeatAnalyzer beatAnalyzer(&analyzer);
 

const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;


void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  
  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);



//option 0 capturing value as is


//option 1 averaging bpms and playing with them

//Eqy=ualizer?
  sgtl5000_1.audioPreProcessorEnable();
  //sgtl5000_1.eqBands(0.5,0.5);
  //sgtl5000_1.eqBand(4,-1);

  sgtl5000_1.eqBands(0,-1,-1,0,0);
  

//option 5 notch the middle

  //biquad1.setHighpass(0,3500,0.054);
  //biquad1.setNotch(0,1300,0.054); //good at 1300
  //biquad1.setHighpass(1,1500,0.54);
  //biquad1.setHighShelf(1, 2000,10,0.05);//this detects bass as a signal, otherwise zero
  //biquad1.setNotch(0,1300,0.054); //good at 1300

//option 3 bass response... doesn't pick up any snare, and picks up so much bassy noise sometimes but still most accurate

  biquad1.setLowpass(0, 200, 0.5);
  //biquad1.setHighpass(1, 100, 0.54);
  //biquad1.setLowShelf(1, 100, 10,0.3);//this detects bass as a signal, otherwise zero
    
  Serial.begin(9600);
  // turn on onboard led to signal successful completion of setup //
  digitalWrite(13, HIGH);
}

elapsedMillis volmsec=0;

void loop() {
  beatAnalyzer.update();
  //Serial.println(peak);
  
}



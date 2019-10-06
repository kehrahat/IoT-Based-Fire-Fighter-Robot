#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#define SD_ChipSelectPin 10 // CS-10, SCK-13, MOSI-11, MISO-12

	int led = 8;
	int sensor = 2;
	int state = LOW;
	int val = 0;
	boolean cmd = false;
	TMRpcm tmrpcm;
	
void setup(){
	tmrpcm.speakerPin = 9;
	pinMode(led, OUTPUT);      
	pinMode(sensor, INPUT);   
	Serial.begin(9600);
	if(!SD.begin(SD_ChipSelectPin)){
		Serial.println("SD fail");
		return;
	}
}
void command(){  
	Serial.println("SD OK");
	tmrpcm.setVolume(7);
	tmrpcm.quality(1); 
	tmrpcm.play("audio.wav");
	digitalWrite(led, HIGH);  
}
void loop(){
	val = digitalRead(sensor);   
	if (val == HIGH){           
		command(); 
		delay(15000);   
		if (state == LOW) {
			Serial.println("Motion detected!");
			state = HIGH;       
		}      
	}else{
		digitalWrite(led, LOW); 
		if (state == HIGH) {
			Serial.println("Motion stopped!");
			state = LOW;       
		}
		delay(100);    
	}  
} 

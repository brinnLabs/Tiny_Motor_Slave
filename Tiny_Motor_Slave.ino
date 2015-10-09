#include <TinyWireS.h>

//this needs to change for each sensor
#define I2C_SLAVE_ADDR  0x01            // i2c slave address 

#define STEP_PIN      			4              // ATtiny Pin 3
#define DIR_PIN      				3              // ATtiny Pin 2
//#define LED							1              // ATtiny Pin 6
boolean direction, start;
uint16_t steps, speed;

// The default buffer size, Can't recall the scope of defines right now
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

byte buffer[16];

void setup(){
  
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);             
  pinMode(LED, INPUT);

  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode

  TinyWireS.onRecieve(recieveEvent);  //the function associated with a read request

	start = false;
}

//the i2c recieve handle which says how many bytes we are recieving
void recieveEvent(uint8_t howMany)
{  
	//Is it a clock sync or a data buffer
	if(howMnay>1){
		uint8_t count =0;
		while (TinyWireS.available()) { // loop through all 
			buffer[count++] = TinyWireS.receive(){  // receive byte
		}
	}
	else {
		start = true;
	}
}

void loop(){
  TinyWireS_stop_check(); //maybe it would be easier to attach this to a timer, will that cause issues with the callback?
}

//we should try to make this as non-blocking as possible
void step(){
	digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
}

//stop stepping
void stop(){

}
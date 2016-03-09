 /*  
   Board connection:
   Arduino       <-> TSYS01
   ------------------------
   5V OR 3V3      -> Vin
   GND            -> GND
   SDA           <-> SDA
   SCL AND SCLK  <-> SCL
   MISO          <-  MISO
   MOSI           -> MOSI
   10             -> SS
   A0             -> EN 
   A1             -> SEL
   
*/

#include "Tsys01.h"

#define slaveSelectPin 10
#define powerPin A0

float temperature = 0.0;
Tsys01* sensor;
long unsigned int ADCStartTime = 0;
long unsigned int oldADCStartTime = 0;
float seconds = 0.0;

void waitUntilTime(long unsigned int endTime) {
  while(endTime > micros()) {
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sensor = new Tsys01(TSYS01_SPI, powerPin, slaveSelectPin);
  
  sensor->startAdc();
  ADCStartTime = micros();
  oldADCStartTime = ADCStartTime;
}

void loop() {
  // put your main code here, to run repeatedly:
  waitUntilTime(ADCStartTime + 9040 + (100000-9040)); // Wait 9.04 ms (Max conversion time according to spec sheet)
  temperature = sensor->readTemperature();
  sensor->startAdc();
  ADCStartTime = micros();
  seconds = ((float)oldADCStartTime)/((float)1000000);
  if(seconds > 180) {
    Serial.print("end");
    while(1) {
      
    }
  }
  Serial.print(seconds,3); // print in seconds
  Serial.print("; ");
  Serial.print(temperature,2);
  Serial.println(";");
  oldADCStartTime = ADCStartTime;
}

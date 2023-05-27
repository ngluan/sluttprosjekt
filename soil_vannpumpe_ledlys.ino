int val = 0;
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Variable for Soil moisture Power
const int sensorPin = A1;

int sensorValue;

#include <FastLED.h>
#define NUM_LEDS 16
#define DATA_PIN 8
CRGB leds[NUM_LEDS];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //led lys
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  //soil moisture sensor
  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower, LOW);


  //vannpumpe
  pinMode(3, OUTPUT);

}

//metoden for å kjøre ledlys: https://www.makeuseof.com/tag/connect-led-light-strips-arduino/
void solidColor(CRGB colors){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = colors;
  }
  FastLED.show();
}


void loop() {
  //koden ble tatt i fra: https://learn.sparkfun.com/tutorials/soil-moisture-sensor-hookup-guide/all
  Serial.print("Soil Moisture = ");    
  //get soil moisture value from the function below and print it
  Serial.println(readSoil());
  
  //This 1 second timefrme is used so you can test the sensor and see it change in real-time.
  //For in-plant applications, you will want to take readings much less frequently.
  delay(1000);//take a reading every second

  if (val > 100) {
    digitalWrite(3, LOW);
  } 

  else {
    digitalWrite(3, HIGH);
  }


  sensorValue = analogRead(A1);
  Serial.println(sensorValue);

  if (sensorValue < 100){
    solidColor(CRGB(255, 255, 255));
  }
  else{
    //skrur av ledstrip for den gir nullverdier til metoden
    solidColor(CRGB(0, 0, 0));
  }

}

//This is a function used to get the soil moisture content
int readSoil()
{
    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}





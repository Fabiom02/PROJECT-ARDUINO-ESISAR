// Libraries includes
#include <Arduino.h>
#include "DHT.h"
#include "TM1637Display.h"
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

// Define pins of display
#define CLK 3
#define DIO 4

// Define pins of bluetooth
#define rxPin 11
#define txPin 10

// Define pin of sensor
#define DHTPIN 5

// Define DHT type
#define DHTTYPE DHT11

// Define pin of button
#define BUTTON 8 


// initialization of sensor, display and bluetooth
DHT dht(DHTPIN, DHTTYPE);
TM1637Display display(CLK, DIO);
SoftwareSerial MaLiaisonBluetooth(rxPin, txPin);

// variables of max temperature and max humidity
float t_max = 0;
float h_max = 0;


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(BUTTON, INPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  dht.begin();

  display.setBrightness(7, true);
  display.showNumberDec(0);

  MaLiaisonBluetooth.begin(9600);

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  if (t_max < t){  
    t_max = t ;
  }

  if (h_max < h){  
    h_max = h ;
  }

  

  MaLiaisonBluetooth.println(F("Humidity: "));
  MaLiaisonBluetooth.println(h);
  MaLiaisonBluetooth.println(F("%  Temperature: "));
  MaLiaisonBluetooth.println(t);
  MaLiaisonBluetooth.println(F("°C "));
  MaLiaisonBluetooth.println(f);
  MaLiaisonBluetooth.println(F("°F  Heat index: "));
  MaLiaisonBluetooth.println(hic);
  MaLiaisonBluetooth.println(F("°C "));
  



  if(digitalRead(BUTTON)==HIGH){
    
    int tempDisplay = (int)(t_max * 10);
    display.showNumberDec(tempDisplay / 10, true, 2,0);
    display.showNumberDec(tempDisplay % 10, false, 1,2);    


    
    MaLiaisonBluetooth.println(F("Max Humidity: "));
    MaLiaisonBluetooth.println(h_max);
    MaLiaisonBluetooth.println(F("% Max Temperature: "));
    MaLiaisonBluetooth.println(t_max);
    MaLiaisonBluetooth.println(F("°C "));
  
    }
  }

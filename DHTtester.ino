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
#define rxPin
#define txPin

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

  MaLiaisonBluetooth.begin(38400);
  Serial.begin(38400);

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

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  MaLiaisonBluetooth.print(F("Humidity: "));
  MaLiaisonBluetooth.print(h);
  MaLiaisonBluetooth.print(F("%  Temperature: "));
  MaLiaisonBluetooth.print(t);
  MaLiaisonBluetooth.print(F("°C "));
  MaLiaisonBluetooth.print(f);
  MaLiaisonBluetooth.print(F("°F  Heat index: "));
  MaLiaisonBluetooth.print(hic);
  MaLiaisonBluetooth.print(F("°C "));
  MaLiaisonBluetooth.print(hif);
  MaLiaisonBluetooth.println(F("°F"));



  if(digitalRead(BUTTON)==HIGH){
    
    int tempDisplay = (int)(t_max * 10);
    display.showNumberDec(tempDisplay / 10, true, 2,0);
    display.showNumberDec(tempDisplay % 10, false, 1,2);    

    Serial.print(F("Max Humidity: "));
    Serial.print(h_max);
    Serial.print(F("% Max Temperature: "));
    Serial.print(t_max);
    Serial.print(F("°C "));
    
    MaLiaisonBluetooth.print(F("Max Humidity: "));
    MaLiaisonBluetooth.print(h_max);
    MaLiaisonBluetooth.print(F("% Max Temperature: "));
    MaLiaisonBluetooth.print(t_max);
    MaLiaisonBluetooth.print(F("°C "));
  
    }
  }

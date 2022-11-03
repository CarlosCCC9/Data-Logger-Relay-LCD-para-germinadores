//Librerias necesarias
#include <SPI.h>      
#include <SD.h>       
#include <DHT.h>
#include <LiquidCrystal.h>
#include <DS3231.h>

//Sensores
#define DHTPIN1 8
#define DHTPIN2 9
#define DHTTYPE DHT11 
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
/*
DHT dht = {
{DHTPIN1, DHT22},
{DHTPIN2, DHT22},
};*/
float humidity[2];
float temperature[2];

//parametros del reloj
DS3231  rtc(SDA, SCL);
Time t;

const int OnHour = 22; //hora para encender
const int OnMin = 48;
const int OffHour = 22; //hora para apagar
const int OffMin = 49;

//SD Logger
File datafile;

//Pantalla
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);	// pines RS, E, D4, D5, D6, D7

//Relays
int Relaypin1= 16;
int Relaypin2= 17;

void setup() {
  Serial.begin(9600);
  //for (auto& sensor : dht) {sensor.begin();}
  lcd.begin(16, 2);
  pinMode(Relaypin1, OUTPUT);
  pinMode(Relaypin2, OUTPUT);
  digitalWrite(Relaypin1, HIGH);
  digitalWrite(Relaypin2, HIGH);

}

void loop() {
  //obtener valores de temperatura y humedad
  
  /*for (int i = 0; i < 2; i++) {
    temperature[i] = dht[i].readTemperature();
    humidity[i] = dht[i].readHumidity();
  }*/
  temperature[0] = dht1.readTemperature();
  humidity[0] = dht1.readHumidity();
  temperature[1] = dht2.readTemperature();
  humidity[1] = dht2.readHumidity();
  //Obtener tiempo
  t=rtc.getTime();
   //abrir sd
  datafile = SD.open("TempLog.csv", FILE_WRITE);
  if (datafile) {
    for (int i = 0; i < 2; i++) {
      datafile.print(temperature[i]);
      datafile.print(",");
      datafile.print(humidity[i]);
      datafile.print(",");
      }
    datafile.print(t.hour);
    datafile.print(",");
    datafile.println(t.min);
    datafile.close();
  }
  //pantalla
  lcd.setCursor(0, 0);
  lcd.print("T1");
  lcd.print(temperature[0]);
  lcd.print("H1");
  lcd.print(humidity[0]);
  lcd.setCursor(0, 1);
  lcd.print("T2");
  lcd.print(temperature[1]);
  lcd.print("H2");
  lcd.print(humidity[1]);
  //Relays
  if(t.hour == OnHour && t.min == OnMin){
    digitalWrite(Relaypin1,LOW);
    digitalWrite(Relaypin2,LOW);
  }
  else if(t.hour == OffHour && t.min == OffMin){
    digitalWrite(Relaypin1,HIGH);
    digitalWrite(Relaypin2,HIGH);
    }


delay(10000);
}
//Librerias
#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <Wire.h>
#include <ds3231.h>
#include <LiquidCrystal.h>

//Sensores
#define DHTPIN1 8
#define DHTPIN2 9
#define DHTTYPE DHT22 
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
float humidity[2];
float temperature[2];

//SD
File dataFile;

//Reloj
struct ts t;

//Relays
int Relaypin1= 16;
int Relaypin2= 17;
const int OnHour = 12; //hora para encender
const int OnMin = 10;
const int OffHour = 12; //hora para apagar
const int OffMin = 40;

//LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup(){
  Serial.begin(9600);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  lcd.begin(16, 2);
  dht1.begin();
  dht2.begin();
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  pinMode(Relaypin1, OUTPUT);
  pinMode(Relaypin2, OUTPUT);
  digitalWrite(Relaypin1, HIGH);
  digitalWrite(Relaypin2, HIGH);
  /*----------------------------------------------------------------------------
  Quitar los comentarios pra fijar nueva fecha y hora
  ----------------------------------------------------------------------------*/
  //t.hour=12; 
  //t.min=30;
  //t.sec=0;
  //t.mday=25;
  //t.mon=12;
  //t.year=2019;
  //DS3231_set(t);
 
  delay(2000);
}
void loop(){
  temperature[0] = dht1.readTemperature();
  humidity[0] = dht1.readHumidity();
  temperature[1] = dht2.readTemperature();
  humidity[1] = dht2.readHumidity();
  for (int i = 0; i < 2; i++){
    Serial.print(temperature[i]);
    Serial.print("\t");
    Serial.print(humidity[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
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
  
  dataFile = SD.open("TempLog.txt", FILE_WRITE);
  if (dataFile) {
    for (int i = 0; i < 2; i++){
      dataFile.print(temperature[i]);
      dataFile.print(",");
      dataFile.print(humidity[i]);
      dataFile.print(",");
    }
    DS3231_get(&t);
    dataFile.print(t.hour);
    dataFile.print(",");
    dataFile.print(t.min);
    dataFile.print("\n");
    dataFile.close();
    lcd.print("S");
   }
  // Si no hay SD
  else{
    Serial.println("error opening DHT11Log.txt");
    lcd.print("N");
  }
 DS3231_get(&t);
  //if(t.hour == OnHour && t.sec == OnMin){
  if (t.sec==10){
    digitalWrite(Relaypin1,LOW);
    digitalWrite(Relaypin2,LOW);
  }
  //else if(t.hour == OffHour && t.sec == OffMin){
  else if(t.sec==40){
    digitalWrite(Relaypin1,HIGH);
    digitalWrite(Relaypin2,HIGH);
    }

  delay(1000);
}
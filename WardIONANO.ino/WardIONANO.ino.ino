//#include <Arduino.h>        //usado para o Visual Studio Code
#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define TEMPOLEITURA 1000
#define RXPIN 10
#define TXPIN 11

PulseOximeter pox;
SoftwareSerial nano(RXPIN,TXPIN);             //(RX,TX)

StaticJsonDocument<200> doc;

unsigned long tempo = 0;
uint32_t xBPM = 0, Spo2 = 0;

void pulso()
{
  Serial.println("B:1");
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  if(!pox.begin())
  {
    Serial.println("Erro ao inicializar o Sensor");
    for(;;);
  }
  pox.setOnBeatDetectedCallback(pulso);
  pox.setIRLedCurrent(MAX30100_LED_CURR_30_6MA);
  pox.setSamplingRate(MAX30100_SAMPRATE_50HZ);
  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);
  nano.begin(9600);
}

void loop() {
  pox.update();
  static uint16_t iLastBPM = 0, BPM = 0;
  if (millis() - tempo >= TEMPOLEITURA)
  {
    BPM = pox.getHeartRate();
    Spo2 = pox.getSpO2();
    if (Spo2 > 100)
    {
      Spo2 = 100;
    }
    
    if (BPM > 240)
    {
      BPM = iLastBPM;
    }else
    {
      iLastBPM = BPM;
    }
    if ((BPM > (xBPM + 15))&& xBPM > 50)
    {
      xBPM += 15;
    }else if ((BPM < (xBPM - 15))&&(xBPM < 150)&&(xBPM > 50))
    {
      xBPM -= 15;
    }else
    {
      xBPM = BPM;
    }
    Serial.print("BPM = ");
    Serial.println(BPM);
    Serial.print("Spo2 = ");
    Serial.println(Spo2);
    tempo = millis();
    
    doc["sensor"] = "oximetro";
    doc["bpm"] = BPM;
    doc["spo2"] = Spo2;
    nano.println();
    serializeJson(doc, nano);
    serializeJson(doc, Serial);
    Serial.println("");
  }
  
}

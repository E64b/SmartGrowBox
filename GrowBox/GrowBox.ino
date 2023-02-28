/*
EisenGrowBox v0.1
Система автоматизации выращивания растений по температуре, влажности почвы, досветке.

Датчик температуры - NTC 10кОм при 25C.
Датчик влажности почвы - емкостный датчик влажности v2.
Часы реального времени - RTC DS3231 с датчиком температуры.
Насос для полива - насос омывателя ВАЗ 2121/ГАЗ 3302 (опционально докупить бачек омывателя).
Свет - светодиодная лента 4200К 12В.
Оптимальная температура 22C-26C
Оптимальное время досветки 16ч
Оптимальная влажность почвы от 70% до 100%
*/
//delay(57600000); 16 часов
//delay(28800000); 8 часов

using namespace std;
//#include <EEManager.h>
#include <EEPROM.h>
#include <avr/eeprom.h>
#include <Wire.h>
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <GyverNTC.h>
#include <microDS3231.h>
#include <LiquidCrystal_I2C.h>

#define Exit digitalRead(8)
#define Left digitalRead(12)
#define Right digitalRead(13)
#define Menu digitalRead(1)

const int AirValue = 630;             // Максимальное значение сухого датчика
const int WaterValue = 266;           // Минимальное значение погруженного датчика
int SoilMoistureValue = 0;
int SoilMoisturePercent = 0;
float InTemp = 0;
float OutTemp = 0;
int Case = 0;
int PumpTime = 1000; //Время полива (мс)
int MinTemp = 22; //Температура выключения вентилятора
int MaxTemp = 25; //Температура включения вентилятора
int NightTime = 21600000; //Сколько часов длится ночь (мс)
int MinTemp = 22; //Температура выключения вентилятора

bool Red = LOW;
bool White = LOW;
bool Pump = false;
bool Fan = LOW;
bool Led = false;
bool Germination = false;

GyverNTC therm(A0, 100000, 4600); //пин, сопротивление, коэф
LiquidCrystal_I2C lcd(0x27, 16, 2);
MicroDS3231 rtc(0x68);

void setup()
{
    Serial.begin(9600);

    rtc.setTime(COMPILE_TIME);

    lcd.init();
    lcd.backlight();

    lcd.home();
    lcd.print("Grow Box v0.1");

    //pinMode(A0,INPUT); датчик температуры 
    pinMode(A1, INPUT); //датчик влажности
    pinMode(1, INPUT_PULLUP); //кнопка Center
    pinMode(2, OUTPUT); //индикаторный светодиод
    pinMode(3, OUTPUT); //красный
    pinMode(4, OUTPUT); //насос полива
    pinMode(5, OUTPUT); //белый
    pinMode(6, OUTPUT); //нагреватель
    pinMode(7, OUTPUT); //вентилятор
    pinMode(8, INPUT_PULLUP); //кнопка Info 
    // pinMode(9,);
    // pinMode(10,);
    // pinMode(11,); 
    pinMode(12, INPUT_PULLUP); //кнопка Up
    pinMode(13, INPUT_PULLUP); //кнопка Down 


    delay(5000);
}

void loop()

{
    //lcd.setCursor(0, 0);
    lcd.home();

    delay(5000);

    Case = 0;

    Serial.println("Grow Box v0.1");

    /*Текущее время*/
    Serial.print("Time ");
    Serial.print(rtc.getHours());
    Serial.print(":");
    Serial.println(rtc.getMinutes());

    /*Опрос датчика температуры*/
    InTemp += (therm.getTemp() - InTemp) * 0.1;
    Serial.print("In Temp ");
    Serial.print(InTemp);
    Serial.println("C");

    /*Температура снаружи бокса*/
    OutTemp = rtc.getTemperatureFloat();
    Serial.print("Out Temp ");
    Serial.print(OutTemp);
    Serial.println("C");

    /*Опрос датчика влажности*/
    SoilMoistureValue = analogRead(A1);
    SoilMoisturePercent = map(SoilMoistureValue, AirValue, WaterValue, 0, 100); //Влажность в %
    Serial.print("Soil Moisture ");
    Serial.println(SoilMoisturePercent);
    Serial.print("%");

    digitalWrite(3, Red);
    digitalWrite(5, White);
    digitalWrite(7, Fan);
    digitalWrite(2, Led);

    //lcd.setCursor(0, 0);
    lcd.print("In ");
    //lcd.setCursor(0, 0);
    lcd.print(InTemp);
    //lcd.setCursor(0, 0); 
    lcd.print("C");

    //lcd.setCursor(0, 0);
    lcd.print("Out ");
    //lcd.setCursor(0, 0);
    lcd.print(OutTemp);
    //lcd.setCursor(0, 0);
    lcd.print("C");

    //lcd.setCursor(0, 0);
    lcd.print(SoilMoisturePercent);
    //lcd.setCursor(0, 0);
    lcd.print("%");

    //lcd.setCursor(0, 0);    
    lcd.print("Germination ");
    //lcd.setCursor(0, 0);
    lcd.print(Germination);

    //lcd.setCursor(0, 0);
    lcd.print(rtc.getHours());
    //lcd.setCursor(0, 0);
    lcd.print(":");
    //lcd.setCursor(0, 0);
    lcd.print(rtc.getMinutes());



    if ((Left == LOW) and (Right == LOW))
    {
        Case = 1;
    }

    if (Germination == true)
    {
        Red = HIGH;
        White = LOW;
    }

    if (Germination == false)
    {
        Red = LOW;
        White = HIGH;
    }

    if (SoilMoisturePercent <= 50)
    {
        Pump = true;
    }

    if (Pump == true)
    {
        digitalWrite(4, HIGH);
        delay(PumpTime);
        digitalWrite(4, LOW);
        delay(10000);
    }

    if (SoilMoisturePercent >= 70)
    {
        Pump = false;
    }

    if ((InTemp > MaxTemp) and (OutTemp < InTemp))
    {
        Fan = HIGH;
    }

    if (InTemp <= MinTemp)
    {
        Fan = LOW;
    }

    if ((Pump == false) and (Fan == LOW) and (rtc.getHours() >= 21))
    {
        lcd.clear();
        lcd.print("NIGHT");
        digitalWrite(2, HIGH);
        delay(NightTime);
        digitalWrite(2, LOW);
    }



}


//Меню настроек времени полива, досветки и тд
/*
  if (Left == LOW)
  {
    Case = 0;
    lcd.clear();
    lcd.print("Exit Setup");
    delay(3000);
  }

  while (Center == LOW)
  {
    Case=Case+1;
    lcd.clear();
    lcd.print("Case ");
    lcd.print(Case);
    delay(1000);
    if (Case == MAX)
    {
      Case=0;
    }
  }

  while (Right == LOW)
  {
    for (;NightTime<43200000;NightTime+3600000)
    {
      lcd.clear();
      lcd.print("NightTime ms ");
      lcd.print(NightTime);
      delay(5000);
      break;
    }
    if (NightTime = 43200000)
    {
      NightTime=21600000;
      lcd.clear();
      lcd.print("NightTime ms ");
      lcd.print(NightTime);
      delay(5000);
      break;
    }
  }



   while (Right == LOW)
  {
    for (;PumpTime<=10000;PumpTime+500)
    {
      lcd.clear();
      lcd.print("PumpTime ms ");
      lcd.print(PumpTime);
      delay(5000);
      break;
    }
    if (PumpTime = 10500)
    {
      PumpTime=1000;
      lcd.clear();
      lcd.print("PumpTime ms ");
      lcd.print(PumpTime);
      delay(5000);
      break;
    }
  }
*/
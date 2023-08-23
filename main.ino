/*
E64b Grow Box
https://github.com/E64b/SmartGrowBox
������� ������������� ����������� ��������.
�������� �����������, ���������, ���������.

������ ����������� - NTC 100��� ��� 25C ���� 10���.
������ ��������� ����� - ��������� ������ ��������� v2.
���� ��������� ������� - RTC DS3231 � �������� �����������.
����� ��� ������ ��� ��������� �������� ��.�. ������.
���� - ������������ ����� 4200� 12�.
*/

using namespace std;
#include <math.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <GyverNTC.h>
#include <microDS3231.h>
#include <LiquidCrystal_I2C.h>

#define Exit digitalRead(5)
#define Left digitalRead(4)
#define Right digitalRead(3)
#define Menu digitalRead(2)
#define SoilSens analogRead(A1)

uint32_t display;
uint32_t air;

const int AirValue = 571;    // �������� ������ �������
const int WaterValue = 242;  // �������� ������������ �������
int SoilMoistureValue = 0;
int SoilMoisturePercent = 0;
float InTemp, OutTemp;
int Case = 0;
int SEC, MIN, HOUR, DAY, MONTH, YEAR;
bool Red, White, Fan, Healer, Led, Pump;

struct Data
{
    int Delta = 1;         //������ ��� ����������� ����������
    int PumpTime = 1000;   //����� ������ (��)
    int MinTemp = 22;      //����������� ���������� �����������
    int MaxTemp = 25;      //����������� ��������� �����������
    int Sunrise = 6;       //�������
    int Sunset = 22;       //�����
    int HumidityMax = 80;  // ������������ ��������� �����
    int HumidityMin = 60;  //����������� ��������� �����
    bool Daybreak = true;  //��������� ������� ������ � ������
    bool Sprout = false;   //������ ������� ����
    bool Airing = false;   //�������������
};

GyverNTC ntc(A0, 100000, 3950, 25, 10180);  // ���, R ����������, B ����������, ������� �����������, R ���������
LiquidCrystal_I2C lcd(0x27, 16, 2);
MicroDS3231 rtc(0x68);



void setup()
{
    Serial.begin(9600);

    //rtc.setTime(COMPILE_TIME); // �������� ������� ��� ������ ���������� ��� ��������� ������� � ����
    //EEPROM.put(0, data); // �������� ���������� ��� ������ ����������
    lcd.init();
    lcd.backlight();
    lcd.home();
    lcd.print("E64bGrowBox v1.5");

    pinMode(A1, INPUT);  //������ ���������
    //pinMode(A2, INPUT); //������ ��� �������
    //pinMode(A3, INPUT); //������ ��� �������
    //pin A4 SDA
    //pin A5 SCL
    //pin 0 RX
    //pin 1 TX
    pinMode(2, INPUT_PULLUP);  //������ Menu
    pinMode(3, INPUT_PULLUP);  //������ Right
    pinMode(4, INPUT_PULLUP);  //������ Left
    pinMode(5, INPUT_PULLUP);  //������ Exit
    pinMode(6, OUTPUT);        //���������
    pinMode(7, OUTPUT);        //�����
    pinMode(8, OUTPUT);        //�������
    pinMode(9, OUTPUT);        //����������
    pinMode(10, OUTPUT);       //�����
    pinMode(11, OUTPUT);       //�����������
    //pinMode(12, OUTPUT); //������
    //pinMode(13, OUTPUT); //������

    EEPROM.get(0, data);

    HOUR = rtc.getHours();
    MIN = rtc.getMinutes();
    SEC = rtc.getSeconds();
    DAY = rtc.getDate();
    MONTH = rtc.getMonth();
    YEAR = rtc.getYear();

    delay(5000);
    lcd.clear();
}

void loop()
{
    delay(100);

    /*����� ������� �����������*/
    InTemp += (ntc.getTemp() - InTemp) * 0.1;

    /*����������� ������� �����*/
    OutTemp += ((rtc.getTemperatureFloat() - 3) - OutTemp) * 0.1;

    /*����� ������� ���������*/
    SoilMoistureValue += (SoilSens - SoilMoistureValue) * 0.1;
    SoilMoisturePercent = map(SoilMoistureValue, AirValue, WaterValue, 0, 100);  //��������� � %

    digitalWrite(6, Led);
    digitalWrite(7, White);
    digitalWrite(8, Red);
    digitalWrite(9, Fan);
    digitalWrite(11, Healer);

    /*����� ���������� � ����*/
    if (millis() - display >= 5000)
    {
        /*������� �����*/
        Serial.print("Time ");
        Serial.print(rtc.getHours());
        Serial.print(":");
        Serial.println(rtc.getMinutes());

        /*����������� ������*/
        Serial.print("In Temp ");
        Serial.print(InTemp);
        Serial.println("C");

        /*����������� �������*/
        Serial.print("Out Temp ");
        Serial.print(OutTemp);
        Serial.println("C");

        /*��������� � %*/
        Serial.print("Soil Moisture ");
        Serial.print(SoilMoisturePercent);
        Serial.println("%");
        Serial.println(SoilMoistureValue);
    }

    /*����� ������� ���������� �� �������*/
    if (millis() - display >= 5000)
    {
        lcd.clear();
        display = millis();
        lcd.setCursor(0, 0);
        lcd.print(InTemp);
        lcd.setCursor(5, 0);
        lcd.print("C");

        lcd.setCursor(7, 0);
        lcd.print(OutTemp);
        lcd.setCursor(12, 0);
        lcd.print("C");

        if (SoilMoisturePercent >= 100)
        {
            lcd.setCursor(14, 0);
            lcd.print("HI");
        }
        else
        {
            lcd.setCursor(14, 0);
            lcd.print(SoilMoisturePercent);
        }

        if (data.Daybreak == true)
        {
            lcd.setCursor(0, 1);
            lcd.print("Daybreak");
        }

        if (data.Sprout == true)
        {
            lcd.setCursor(0, 1);
            lcd.print("Sprout");
        }

        if ((data.Daybreak == false) and (data.Sprout == false))
        {
            lcd.setCursor(0, 1);
            lcd.print("White");
        }

        if (rtc.getHours() < 10)
        {
            lcd.setCursor(11, 1);
            lcd.print("0");
            lcd.setCursor(12, 1);
            lcd.print(rtc.getHours());
        }
        else
        {
            lcd.setCursor(11, 1);
            lcd.print(rtc.getHours());
        }

        lcd.setCursor(13, 1);
        lcd.print(":");

        if (rtc.getMinutes() < 10)
        {
            lcd.setCursor(14, 1);
            lcd.print("0");
            lcd.setCursor(15, 1);
            lcd.print(rtc.getMinutes());
        }
        else
        {
            lcd.setCursor(14, 1);
            lcd.print(rtc.getMinutes());
        }
    }

    /*��� ������� �� ������ �������� � ����*/
    if (Menu == LOW)
    {
        Case = 1;
        delay(500);
    }

    /*������ �������� � EEPROM*/
    if ((Left == LOW) and (Right == LOW))
    {
        lcd.clear();
        lcd.home();
        EEPROM.put(0, data);
        rtc.setTime(SEC, MIN, HOUR, DAY, MONTH, YEAR);
        lcd.print("Setting save");
        delay(1000);
    }

    if ((((SoilMoisturePercent <= data.HumidityMin)) or (Pump == true)) and (data.PumpTime > 0))
    {
        Pump = true;
        lcd.clear();
        lcd.home();
        lcd.print("Watering");
        digitalWrite(10, HIGH);
        delay(data.PumpTime);
        digitalWrite(10, LOW);
    }

    if (SoilMoisturePercent >= data.HumidityMax)
    {
        Pump = false;
        digitalWrite(10, LOW);
    }

    if (InTemp >= (data.MaxTemp + data.Delta))
    {
        Fan = HIGH;
    }

    if (InTemp <= (data.MinTemp - data.Delta))
    {
        Fan = LOW;
    }

    if ((data.Airing == true) and (millis() - air > 1800000))
    {
        air = millis();
        Fan = HIGH;
    }

    if ((data.Airing == true) and (millis() - air > 60000) and (millis() - air < 90000))
    {
        Fan = LOW;
    }

    if (InTemp <= (data.MinTemp - data.Delta))
    {
        Healer = HIGH;
    }

    if (InTemp >= data.MaxTemp - data.Delta)
    {
        Healer = LOW;
    }

    if ((rtc.getHours() < data.Sunset) and (rtc.getHours() >= data.Sunrise) or (Case > 0))
    {
        if ((data.Sprout == true) or (data.Daybreak == true))
        {
            Red = HIGH;
        }
        else
        {
            Red = LOW;
        }

        if (data.Sprout == false)
        {
            White = HIGH;
        }
        else
        {
            White = LOW;
        }
        lcd.backlight();
    }

    else
    {
        Red = LOW;
        White = LOW;
        Led = HIGH;
        lcd.noBacklight();
    }

    /*����*/
    switch (Case)
    {
    case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Min Temp");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.MinTemp);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.MinTemp >= 18))
            {
                data.MinTemp = data.MinTemp - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.MinTemp < data.MaxTemp))
            {
                data.MinTemp = data.MinTemp + 1;
                delay(250);
            }
        }
        break;

    case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Max Temp");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.MaxTemp);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.MaxTemp > data.MinTemp))
            {
                data.MaxTemp = data.MaxTemp - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.MaxTemp < 28))
            {
                data.MaxTemp = data.MaxTemp + 1;
                delay(250);
            }
        }
        break;

    case 3:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Delta");

        while (true)
        {
            lcd.setCursor(6, 1);
            lcd.print(data.Delta);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Delta > 0))
            {
                data.Delta = data.Delta - 1;
                delay(250);
            }

            if (((Right == LOW) and (data.Delta < 5)) and (data.MaxTemp - data.MinTemp > data.Delta))
            {
                data.Delta = data.Delta + 1;
                delay(250);
            }
        }
        break;

    case 4:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Sun rise");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.Sunrise);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Sunrise > 4) and (data.Sunrise <= 10))
            {
                data.Sunrise = data.Sunrise - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.Sunrise >= 4) and (data.Sunrise < 10))
            {
                data.Sunrise = data.Sunrise + 1;
                delay(250);
            }
        }
        break;

    case 5:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Sun set");

        while (true)
        {
            lcd.setCursor(8, 1);
            lcd.print(data.Sunset);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Sunset > 16) and (data.Sunset <= 23))
            {
                data.Sunset = data.Sunset - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.Sunset >= 16) and (data.Sunset < 23))
            {
                data.Sunset = data.Sunset + 1;
                delay(250);
            }
        }
        break;

    case 6:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Humidity min");

        while (true)
        {
            lcd.setCursor(13, 1);
            lcd.print(data.HumidityMin);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.HumidityMin >= 55))
            {
                data.HumidityMin = data.HumidityMin - 5;
                delay(250);
            }

            if ((Right == LOW) and (data.HumidityMin < data.HumidityMax) and (data.HumidityMin < 95))
            {
                data.HumidityMin = data.HumidityMin + 5;
                delay(250);
            }
        }
        break;

    case 7:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Humidity max");

        while (true)
        {
            lcd.setCursor(13, 1);
            lcd.print(data.HumidityMax);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.HumidityMax > data.HumidityMin) and (data.HumidityMax >= 55))
            {
                data.HumidityMax = data.HumidityMax - 5;
                delay(250);
            }

            if ((Right == LOW) and (data.HumidityMax < 100))
            {
                data.HumidityMax = data.HumidityMax + 5;
                delay(250);
            }
        }
        break;

    case 8:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Watering sec");

        while (true)
        {
            lcd.setCursor(13, 1);
            lcd.print((data.PumpTime / 1000));

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.PumpTime >= 1000))
            {
                data.PumpTime = data.PumpTime - 1000;
                delay(250);
            }

            if ((Right == LOW) and (data.PumpTime <= 59000))
            {
                data.PumpTime = data.PumpTime + 1000;
                delay(250);
            }
        }
        break;

    case 9:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Daybreak");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.Daybreak);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Daybreak == true))
            {
                data.Daybreak = false;
                delay(250);
            }

            if ((Right == LOW) and (data.Daybreak == false))
            {
                data.Daybreak = true;
                data.Sprout = false;
                delay(250);
            }
        }
        break;

    case 10:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Sprout");

        while (true)
        {
            lcd.setCursor(12, 1);
            lcd.print(data.Sprout);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Sprout == true))
            {
                data.Sprout = false;
                delay(250);
            }

            if ((Right == LOW) and (data.Sprout == false))
            {
                data.Sprout = true;
                data.Daybreak = false;
                delay(250);
            }
        }
        break;

    case 11:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Airing");

        while (true)
        {
            lcd.setCursor(7, 1);
            lcd.print(data.Airing);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Airing == true))
            {
                data.Airing = false;
                delay(250);
            }

            if ((Right == LOW) and (data.Airing == false))
            {
                data.Airing = true;
                delay(250);
            }
        }
        break;

    case 12:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Hour");
        HOUR = rtc.getHours();

        while (true)
        {
            lcd.setCursor(5, 1);
            lcd.print(HOUR);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (HOUR > 0) and (HOUR <= 23))
            {
                HOUR--;
                delay(250);
            }

            if ((Right == LOW) and (HOUR >= 0) and (HOUR < 23))
            {
                HOUR++;
                delay(250);
            }
        }
        break;

    case 13:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Minutes");
        MIN = rtc.getMinutes();

        while (true)
        {
            lcd.setCursor(8, 1);
            lcd.print(MIN);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (MIN > 0) and (MIN <= 59))
            {
                MIN--;
                delay(250);
            }

            if ((Right == LOW) and (MIN >= 0) and (MIN < 59))
            {
                MIN++;
                delay(250);
            }
        }
        break;

    case 14:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Day");
        DAY = rtc.getDate();

        while (true)
        {
            lcd.setCursor(4, 1);
            lcd.print(DAY);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (DAY > 1) and (DAY <= 31))
            {
                DAY--;
                delay(250);
            }

            if ((Right == LOW) and (DAY >= 0) and (DAY <= 30))
            {
                DAY++;
                delay(250);
            }
        }
        break;

    case 15:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Month");
        MONTH = rtc.getMonth();

        while (true)
        {
            lcd.setCursor(7, 1);
            lcd.print(MONTH);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (MONTH > 1) and (MONTH <= 12))
            {
                MONTH--;
                delay(250);
            }

            if ((Right == LOW) and (MONTH >= 1) and (MONTH < 12))
            {
                MONTH++;
                delay(250);
            }
        }
        break;

    case 16:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Year");
        YEAR = rtc.getYear();

        while (true)
        {
            lcd.setCursor(5, 1);
            lcd.print(YEAR);

            if (Menu == LOW)
            {
                Case = 1;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (YEAR > 1970) and (YEAR <= 2300))
            {
                YEAR--;
                delay(250);
            }

            if ((Right == LOW) and (YEAR >= 1970) and (YEAR < 2299))
            {
                YEAR++;
                delay(250);
            }
        }
        break;
    }
}
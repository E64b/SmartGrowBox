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

struct Data{
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
uint32_t display;
uint32_t air;

const int AirValue = 571;    // �������� ������ �������
const int WaterValue = 242;  // �������� ������������ �������
uint16_t SoilMoistureValue = 0;
uint8_t SoilMoisturePercent = 0;
float InTemp, OutTemp;
uint8_t Case = 0;
uint8_t SEC, MIN, HOUR, DAY, MONTH;
uint16_t YEAR;
bool Red, White, Fan, Healer, Led, Pump;

GyverNTC ntc (A0, 100000, 3950, 25, 10180);  // ���, R ����������, B ����������, ������� �����������, R ���������
LiquidCrystal_I2C lcd (0x27, 16, 2);
MicroDS3231 rtc (0x68);

extern Data data;
extern LiquidCrystal_I2C lcd;
extern MicroDS3231 rtc;
extern GyverNTC ntc;
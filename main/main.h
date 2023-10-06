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
	int Delta = 1;         //Дельта для компенсации инертности
	int PumpTime = 1000;   //Время полива (мс)
	int MinTemp = 22;      //Температура выключения вентилятора
	int MaxTemp = 25;      //Температура включения вентилятора
	int Sunrise = 6;       //Рассвет
	int Sunset = 22;       //Закат
	int HumidityMax = 80;  // Максимальная влажность почвы
	int HumidityMin = 60;  //Минимальная влажность почвы
	bool Daybreak = true;  //Добавляет красный спектр к белому
	bool Sprout = false;   //Только красный свет
	bool Airing = false;   //Проветривание
	};
uint32_t display;
uint32_t air;

const int AirValue = 571;    // Значение сухого датчика
const int WaterValue = 242;  // Значение погруженного датчика
uint16_t SoilMoistureValue = 0;
uint8_t SoilMoisturePercent = 0;
float InTemp, OutTemp;
uint8_t Case = 0;
uint8_t SEC, MIN, HOUR, DAY, MONTH;
uint16_t YEAR;
bool Red, White, Fan, Healer, Led, Pump;

GyverNTC ntc (A0, 100000, 3950, 25, 10180);  // пин, R термистора, B термистора, базовая температура, R резистора
LiquidCrystal_I2C lcd (0x27, 16, 2);
MicroDS3231 rtc (0x68);

extern Data data;
extern LiquidCrystal_I2C lcd;
extern MicroDS3231 rtc;
extern GyverNTC ntc;
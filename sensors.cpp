#include "main.h" 

void sensors()
{
	/*Опрос датчика температуры*/
	InTemp += (ntc.getTemp() - InTemp) * 0.1;

	/*Температура снаружи бокса*/
	OutTemp += ((rtc.getTemperatureFloat() - 3) - OutTemp) * 0.1;

	/*Опрос датчика влажности*/
	SoilMoistureValue += (SoilSens - SoilMoistureValue) * 0.1;
	SoilMoisturePercent = map(SoilMoistureValue, AirValue, WaterValue, 0, 100);  //Влажность в %
	delay(100);
}
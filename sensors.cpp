#include "main.h" 

void sensors()
{
	/*����� ������� �����������*/
	InTemp += (ntc.getTemp() - InTemp) * 0.1;

	/*����������� ������� �����*/
	OutTemp += ((rtc.getTemperatureFloat() - 3) - OutTemp) * 0.1;

	/*����� ������� ���������*/
	SoilMoistureValue += (SoilSens - SoilMoistureValue) * 0.1;
	SoilMoisturePercent = map(SoilMoistureValue, AirValue, WaterValue, 0, 100);  //��������� � %
	delay(100);
}
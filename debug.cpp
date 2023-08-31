#include "main.h" 
/*����� ���������� � ����*/
void debug()
{
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
}
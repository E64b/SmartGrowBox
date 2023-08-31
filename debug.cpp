#include "main.h" 
/*Вывод информации в порт*/
void debug()
{
    if (millis() - display >= 5000)
    {
        /*Текущее время*/
        Serial.print("Time ");
        Serial.print(rtc.getHours());
        Serial.print(":");
        Serial.println(rtc.getMinutes());

        /*Температура внутри*/
        Serial.print("In Temp ");
        Serial.print(InTemp);
        Serial.println("C");

        /*Температура снаружи*/
        Serial.print("Out Temp ");
        Serial.print(OutTemp);
        Serial.println("C");

        /*Влажность в %*/
        Serial.print("Soil Moisture ");
        Serial.print(SoilMoisturePercent);
        Serial.println("%");
        Serial.println(SoilMoistureValue);
    }
}
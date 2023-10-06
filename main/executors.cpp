#include "main.h" 
void executors (){
	digitalWrite (6, Led);
	digitalWrite (7, White);
	digitalWrite (8, Red);
	digitalWrite (9, Fan);
	digitalWrite (11, Healer);

	if ((((SoilMoisturePercent <= data.HumidityMin)) or (Pump == true)) and (data.PumpTime > 0)){
		Pump = true;
		lcd.clear ();
		lcd.home ();
		lcd.print ("Watering");
		digitalWrite (10, HIGH);
		delay (data.PumpTime);
		digitalWrite (10, LOW);
		}

	if (SoilMoisturePercent >= data.HumidityMax){
		Pump = false;
		digitalWrite (10, LOW);
		}

	if (InTemp >= (data.MaxTemp + data.Delta)){
		Fan = HIGH;
		}

	if (InTemp <= (data.MinTemp - data.Delta)){
		Fan = LOW;
		}

	if ((data.Airing == true) and (millis () - air > 1800000)){
		air = millis ();
		Fan = HIGH;
		}

	if ((data.Airing == true) and (millis () - air > 60000) and (millis () - air < 90000)){
		Fan = LOW;
		}

	if (InTemp <= (data.MinTemp - data.Delta)){
		Healer = HIGH;
		}

	if (InTemp >= data.MaxTemp - data.Delta){
		Healer = LOW;
		}

	if ((rtc.getHours () < data.Sunset) and (rtc.getHours () >= data.Sunrise) or (Case > 0)){
		if ((data.Sprout == true) or (data.Daybreak == true)){
			Red = HIGH;
			} else{
			Red = LOW;
			}

		if (data.Sprout == false){
			White = HIGH;
			} else{
			White = LOW;
			}
		lcd.backlight ();
		}

	else{
		Red = LOW;
		White = LOW;
		Led = HIGH;
		lcd.noBacklight ();
		}
	}
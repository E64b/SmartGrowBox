/*Вывод текущей информации на дисплей*/
#include "main.h" 
void display (){
	if (millis () - display >= 5000){
		lcd.clear ();
		display = millis ();
		lcd.setCursor (0, 0);
		lcd.print (InTemp);
		lcd.setCursor (5, 0);
		lcd.print ("C");

		lcd.setCursor (7, 0);
		lcd.print (OutTemp);
		lcd.setCursor (12, 0);
		lcd.print ("C");

		if (SoilMoisturePercent >= 100){
			lcd.setCursor (14, 0);
			lcd.print ("HI");
			} else{
			lcd.setCursor (14, 0);
			lcd.print (SoilMoisturePercent);
			}

		if (data.Daybreak == true){
			lcd.setCursor (0, 1);
			lcd.print ("Daybreak");
			}

		if (data.Sprout == true){
			lcd.setCursor (0, 1);
			lcd.print ("Sprout");
			}

		if ((data.Daybreak == false) and (data.Sprout == false)){
			lcd.setCursor (0, 1);
			lcd.print ("White");
			}

		if (rtc.getHours () < 10){
			lcd.setCursor (11, 1);
			lcd.print ("0");
			lcd.setCursor (12, 1);
			lcd.print (rtc.getHours ());
			} else{
			lcd.setCursor (11, 1);
			lcd.print (rtc.getHours ());
			}

		lcd.setCursor (13, 1);
		lcd.print (":");

		if (rtc.getMinutes () < 10){
			lcd.setCursor (14, 1);
			lcd.print ("0");
			lcd.setCursor (15, 1);
			lcd.print (rtc.getMinutes ());
			} else{
			lcd.setCursor (14, 1);
			lcd.print (rtc.getMinutes ());
			}
		}
	}
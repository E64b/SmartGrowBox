#include "main.h" 
void keys (){
	/*��� ������� �� ������ �������� � ����*/
	if (Menu == LOW){
		Case = 1;
		delay (500);
		}

	/*������ �������� � EEPROM*/
	if ((Left == LOW) and (Right == LOW)){
		lcd.clear ();
		lcd.home ();
		EEPROM.put (0, data);
		rtc.setTime (SEC, MIN, HOUR, DAY, MONTH, YEAR);
		lcd.print ("Setting save");
		delay (1000);
		}
	}
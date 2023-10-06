/*
E64b Grow Box
https://github.com/E64b/SmartGrowBox
Система автоматизации выращивания растений.
Контроль температуры, влажности, освещения.

Датчик температуры - NTC 100кОм при 25C шунт 10кОм.
Датчик влажности почвы - емкостный датчик влажности v2.
Часы реального времени - RTC DS3231 с датчиком температуры.
Насос для полива или нормально закрытый эл.м. клапан.
Свет - светодиодная лента 4200К 12В.
*/

#include "main.h" 



void setup (){

	if (rtc.lostPower ()){
		rtc.setTime (BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
		}
	//EEPROM.put(0, data); // прошивка переменных при первой компиляции
	lcd.init ();
	lcd.backlight ();
	lcd.home ();
	lcd.print ("E64bGrowBox v1.5");
	delay (5000);
	lcd.clear ();
	pinMode (A1, INPUT);  //датчик влажности
	pinMode (2, INPUT_PULLUP);  //Кнопка Menu
	pinMode (3, INPUT_PULLUP);  //Кнопка Right
	pinMode (4, INPUT_PULLUP);  //Кнопка Left
	pinMode (5, INPUT_PULLUP);  //Кнопка Exit
	pinMode (6, OUTPUT);        //Индикатор
	pinMode (7, OUTPUT);        //Белый
	pinMode (8, OUTPUT);        //Красный
	pinMode (9, OUTPUT);        //Вентилятор
	pinMode (10, OUTPUT);       //Насос
	pinMode (11, OUTPUT);       //Нагреватель

	EEPROM.get (0, data);

	HOUR = rtc.getHours ();
	MIN = rtc.getMinutes ();
	SEC = rtc.getSeconds ();
	DAY = rtc.getDate ();
	MONTH = rtc.getMonth ();
	YEAR = rtc.getYear ();

	Serial.begin (9600);
	}

void loop (){
	sensors ();
	debug ();
	display ();
	setting ();
	executors ();
	keys ();
	}
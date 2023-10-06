/*
E64b Grow Box
https://github.com/E64b/SmartGrowBox
������� ������������� ����������� ��������.
�������� �����������, ���������, ���������.

������ ����������� - NTC 100��� ��� 25C ���� 10���.
������ ��������� ����� - ��������� ������ ��������� v2.
���� ��������� ������� - RTC DS3231 � �������� �����������.
����� ��� ������ ��� ��������� �������� ��.�. ������.
���� - ������������ ����� 4200� 12�.
*/

#include "main.h" 



void setup (){

	if (rtc.lostPower ()){
		rtc.setTime (BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
		}
	//EEPROM.put(0, data); // �������� ���������� ��� ������ ����������
	lcd.init ();
	lcd.backlight ();
	lcd.home ();
	lcd.print ("E64bGrowBox v1.5");
	delay (5000);
	lcd.clear ();
	pinMode (A1, INPUT);  //������ ���������
	pinMode (2, INPUT_PULLUP);  //������ Menu
	pinMode (3, INPUT_PULLUP);  //������ Right
	pinMode (4, INPUT_PULLUP);  //������ Left
	pinMode (5, INPUT_PULLUP);  //������ Exit
	pinMode (6, OUTPUT);        //���������
	pinMode (7, OUTPUT);        //�����
	pinMode (8, OUTPUT);        //�������
	pinMode (9, OUTPUT);        //����������
	pinMode (10, OUTPUT);       //�����
	pinMode (11, OUTPUT);       //�����������

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
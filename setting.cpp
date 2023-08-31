#include "main.h" 
/*Μενώ*/
void setting()
{
    switch (Case)
    {
    case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Min Temp");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.MinTemp);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.MinTemp >= 18))
            {
                data.MinTemp = data.MinTemp - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.MinTemp < data.MaxTemp))
            {
                data.MinTemp = data.MinTemp + 1;
                delay(250);
            }
        }
        break;

    case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Max Temp");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.MaxTemp);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.MaxTemp > data.MinTemp))
            {
                data.MaxTemp = data.MaxTemp - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.MaxTemp < 28))
            {
                data.MaxTemp = data.MaxTemp + 1;
                delay(250);
            }
        }
        break;

    case 3:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Delta");

        while (true)
        {
            lcd.setCursor(6, 1);
            lcd.print(data.Delta);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Delta > 0))
            {
                data.Delta = data.Delta - 1;
                delay(250);
            }

            if (((Right == LOW) and (data.Delta < 5)) and (data.MaxTemp - data.MinTemp > data.Delta))
            {
                data.Delta = data.Delta + 1;
                delay(250);
            }
        }
        break;

    case 4:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Sun rise");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.Sunrise);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Sunrise > 4) and (data.Sunrise <= 10))
            {
                data.Sunrise = data.Sunrise - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.Sunrise >= 4) and (data.Sunrise < 10))
            {
                data.Sunrise = data.Sunrise + 1;
                delay(250);
            }
        }
        break;

    case 5:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Sun set");

        while (true)
        {
            lcd.setCursor(8, 1);
            lcd.print(data.Sunset);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Sunset > 16) and (data.Sunset <= 23))
            {
                data.Sunset = data.Sunset - 1;
                delay(250);
            }

            if ((Right == LOW) and (data.Sunset >= 16) and (data.Sunset < 23))
            {
                data.Sunset = data.Sunset + 1;
                delay(250);
            }
        }
        break;

    case 6:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Humidity min");

        while (true)
        {
            lcd.setCursor(13, 1);
            lcd.print(data.HumidityMin);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.HumidityMin >= 55))
            {
                data.HumidityMin = data.HumidityMin - 5;
                delay(250);
            }

            if ((Right == LOW) and (data.HumidityMin < data.HumidityMax) and (data.HumidityMin < 95))
            {
                data.HumidityMin = data.HumidityMin + 5;
                delay(250);
            }
        }
        break;

    case 7:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Humidity max");

        while (true)
        {
            lcd.setCursor(13, 1);
            lcd.print(data.HumidityMax);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.HumidityMax > data.HumidityMin) and (data.HumidityMax >= 55))
            {
                data.HumidityMax = data.HumidityMax - 5;
                delay(250);
            }

            if ((Right == LOW) and (data.HumidityMax < 100))
            {
                data.HumidityMax = data.HumidityMax + 5;
                delay(250);
            }
        }
        break;

    case 8:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Watering sec");

        while (true)
        {
            lcd.setCursor(13, 1);
            lcd.print((data.PumpTime / 1000));

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.PumpTime >= 1000))
            {
                data.PumpTime = data.PumpTime - 1000;
                delay(250);
            }

            if ((Right == LOW) and (data.PumpTime <= 59000))
            {
                data.PumpTime = data.PumpTime + 1000;
                delay(250);
            }
        }
        break;

    case 9:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Daybreak");

        while (true)
        {
            lcd.setCursor(9, 1);
            lcd.print(data.Daybreak);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Daybreak == true))
            {
                data.Daybreak = false;
                delay(250);
            }

            if ((Right == LOW) and (data.Daybreak == false))
            {
                data.Daybreak = true;
                data.Sprout = false;
                delay(250);
            }
        }
        break;

    case 10:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Sprout");

        while (true)
        {
            lcd.setCursor(12, 1);
            lcd.print(data.Sprout);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Sprout == true))
            {
                data.Sprout = false;
                delay(250);
            }

            if ((Right == LOW) and (data.Sprout == false))
            {
                data.Sprout = true;
                data.Daybreak = false;
                delay(250);
            }
        }
        break;

    case 11:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Airing");

        while (true)
        {
            lcd.setCursor(7, 1);
            lcd.print(data.Airing);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (data.Airing == true))
            {
                data.Airing = false;
                delay(250);
            }

            if ((Right == LOW) and (data.Airing == false))
            {
                data.Airing = true;
                delay(250);
            }
        }
        break;

    case 12:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Hour");
        HOUR = rtc.getHours();

        while (true)
        {
            lcd.setCursor(5, 1);
            lcd.print(HOUR);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (HOUR > 0) and (HOUR <= 23))
            {
                HOUR--;
                delay(250);
            }

            if ((Right == LOW) and (HOUR >= 0) and (HOUR < 23))
            {
                HOUR++;
                delay(250);
            }
        }
        break;

    case 13:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Minutes");
        MIN = rtc.getMinutes();

        while (true)
        {
            lcd.setCursor(8, 1);
            lcd.print(MIN);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (MIN > 0) and (MIN <= 59))
            {
                MIN--;
                delay(250);
            }

            if ((Right == LOW) and (MIN >= 0) and (MIN < 59))
            {
                MIN++;
                delay(250);
            }
        }
        break;

    case 14:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Day");
        DAY = rtc.getDate();

        while (true)
        {
            lcd.setCursor(4, 1);
            lcd.print(DAY);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (DAY > 1) and (DAY <= 31))
            {
                DAY--;
                delay(250);
            }

            if ((Right == LOW) and (DAY >= 0) and (DAY <= 30))
            {
                DAY++;
                delay(250);
            }
        }
        break;

    case 15:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Month");
        MONTH = rtc.getMonth();

        while (true)
        {
            lcd.setCursor(7, 1);
            lcd.print(MONTH);

            if (Menu == LOW)
            {
                Case++;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (MONTH > 1) and (MONTH <= 12))
            {
                MONTH--;
                delay(250);
            }

            if ((Right == LOW) and (MONTH >= 1) and (MONTH < 12))
            {
                MONTH++;
                delay(250);
            }
        }
        break;

    case 16:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(5, 0);
        lcd.print(Case);
        lcd.setCursor(0, 1);
        lcd.print("Year");
        YEAR = rtc.getYear();

        while (true)
        {
            lcd.setCursor(5, 1);
            lcd.print(YEAR);

            if (Menu == LOW)
            {
                Case = 1;
                delay(250);
                break;
            }

            if (Exit == LOW)
            {
                Case = 0;
                delay(250);
                break;
            }

            if ((Left == LOW) and (YEAR > 1970) and (YEAR <= 2300))
            {
                YEAR--;
                delay(250);
            }

            if ((Right == LOW) and (YEAR >= 1970) and (YEAR < 2299))
            {
                YEAR++;
                delay(250);
            }
        }
        break;
    }
}
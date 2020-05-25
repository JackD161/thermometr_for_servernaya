#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

// пин для подключения датчика DHT
#define DHTPIN 10
// тип датчика DHT
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f,16,2);  // Устанавливаем дисплей 16 символов в 2 строки, некоторые адаптеры имеют адрес 0x27
void setup()
{
  dht.begin();
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  // 11 pin зеленый
  // 12 pin синий
  // 13 pin красный
}
void loop()
{
  // получение данных влажности
  int h = dht.readHumidity();
  //Измеряем температуру
  int t = dht.readTemperature();
  // Устанавливаем курсор на первую строку в нулевой символ
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(h);
  // Устанавливаем курсор на вторую строку в нулевой символ
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(t);
  // если температура меньше 20 градусов - зажигаем голубой светодиод, а зеленый и красный гасим
  if (t < 20)
  {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);
  }
  // если температура от 20 до 27 градусов включительно - зажигаем зеленый светодиод, а голубой и красный гасим
  else if (t >= 20 && t <=27)
  {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
  }
  // иначе температура получается больше 27 градусов - зажигаем красный и гасим зеленый и голубой 
  else
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
}

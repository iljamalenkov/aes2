

#include <LiquidCrystal.h> //для экрана
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //для экрана

#include <dht.h>        //для сенсора температуры
DHT sensor = DHT();     //для сенсора температуры
int tt=0; //триггер времени для запуска подпрограмм

#include <Wire.h>

const byte MY_ADDRESS = 25;
const byte SLAVE_ADDRESS = 42;
const byte BOX1_ADDRESS = 42;



void setup() {
  Serial.begin(9600);
    Wire.begin (MY_ADDRESS);
 lcd.begin(16, 2);  //для экрана
lcd.print("Starting");

sensor.attach(A1);  //для сенсора температуры
delay(1000);        //для сенсора температуры

}

void loop() {
 serialRead();
 
lcd.setCursor(0, 0);
 // метод update заставляет сенсор выдать текущие измерения
   delay (10);
   
    // метод update заставляет сенсор выдать текущие измерения
    if (tt==500) tempRead(); //запуск чтения температуры
    if (tt==400) lightRead(); //запуск чтения освещенности
    if (tt>500) tt=0;
   
tt++;
}
void tempRead ()
  {  sensor.update();

    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
            char msg[128];
            // данные последнего измерения можно считать соответствующими
            // методами
            sprintf(msg, "T=%dC H=%d%%", 
                    sensor.getTemperatureInt(), sensor.getHumidityInt());
            Serial.println(msg);
            lcd.setCursor(0, 0);
            lcd.print(msg);
            break;
        case DHT_ERROR_START_FAILED_1:
        
            Serial.println("Error: start failed (stage 1)");
            lcd.println("Error: start failed (stage 1)");
             sensor.attach(A1);
                delay (100);
            break;
        case DHT_ERROR_START_FAILED_2:
            Serial.println("Error: start failed (stage 2)");
            lcd.println("Error: start failed (stage 2)");
            break;
        case DHT_ERROR_READ_TIMEOUT:
            Serial.println("Error: read timeout");
            lcd.println("Error: read timeout");
            break;
        case DHT_ERROR_CHECKSUM_FAILURE:
            Serial.println("Error: checksum error");
            lcd.println("Error: checksum error");
            break;
    }}
    
    void lightRead ()
    {
      int t=analogRead(A2);
      Serial.println(t);
      lcd.setCursor(0, 1);
      lcd.print(t);
      
    }
     void serialRead(){
       if (Serial.available() > 0) {
 tellBox1(Serial.read());
     
}}
    void tellBox1(char mess){
      Wire.beginTransmission (BOX1_ADDRESS);
      Wire.write (mess);
      Wire.endTransmission ();  
  }

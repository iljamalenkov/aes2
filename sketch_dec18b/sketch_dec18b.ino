#include <LiquidCrystal.h> //для экрана
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //для экрана

#include <dht.h>        //для сенсора температуры
DHT sensor = DHT();     //для сенсора температуры
int tt=0;
void setup() {
  Serial.begin(9600);
 lcd.begin(16, 2);  //для экрана
lcd.print("fucking fuck");

sensor.attach(A1);  //для сенсора температуры
delay(1000);        //для сенсора температуры

}

void loop() {
  
lcd.setCursor(0, 1);
lcd.print(millis()/1000);
 // метод update заставляет сенсор выдать текущие измерения
   delay (10);
   
    // метод update заставляет сенсор выдать текущие измерения
    if (tt==500) tempRead();
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
            sprintf(msg, "Temperature = %dC, Humidity = %d%%", 
                    sensor.getTemperatureInt(), sensor.getHumidityInt());
            Serial.println(msg);
            break;
        case DHT_ERROR_START_FAILED_1:
        
            Serial.println("Error: start failed (stage 1)");
             sensor.attach(A1);
                delay (100);
            break;
        case DHT_ERROR_START_FAILED_2:
            Serial.println("Error: start failed (stage 2)");
            break;
        case DHT_ERROR_READ_TIMEOUT:
            Serial.println("Error: read timeout");
            break;
        case DHT_ERROR_CHECKSUM_FAILURE:
            Serial.println("Error: checksum error");
            break;
    }}

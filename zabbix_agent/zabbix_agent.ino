/*****************************************************************************************
 * Purpose : Zabbix Sensor Agent - Environmental Monitoring Solution                     *
 * Author  : Evgeny Levkov                                                               *
 * Credits:                                                                              *
 *           JO3RI www.JO3RI.be/arduino - for web based ethernet config with EEPROM code *
 *           Rob Faludi http://www.faludi.com - for free memory test code                *
 *****************************************************************************************/

// ZSA1-E
//Credits: 
// JO3RI www.JO3RI.be/arduino - for web based ethernet config with EEPROM code
// Rob Faludi http://www.faludi.com - for free memory test code
// Evgeny Levkov - Zabbix Agent implementation http://www.sensor.im
int buzzDelay = 0;
//-----------------INCLUDES--------------------
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <WebServer.h>
#include <dht.h>        //для сенсора температуры
DHT sensor = DHT();     //для сенсора температуры
int tt, hh;
String box1="00000000";
int ti=0; //статус для проверок
#include <Wire.h>

const byte MY_ADDRESS = 1;
const byte SLAVE_ADDRESS = 2;
const byte BOX1_ADDRESS = 2;

#define PREFIX "/box1"
WebServer webserver(PREFIX, 80);


//#include "DHT.h"         // Download at https://github.com/adafruit/DHT-sensor-library
#include <TextFinder.h>  // Download at http://www.arduino.cc/playground/Code/TextFinder
#include <avr/pgmspace.h>
//--------------------------------------------
#define MAX_CMD_LENGTH   25
#define MAX_LINE 20
//-----------------DHT SENSOR PARAMETERS------
//#define DHTPIN 24     // what pin we're connected to
//#define DHTTYPE DHT11   // DHT 22  (AM2302)
//DHT dht(DHTPIN, DHTTYPE);
//--------------------------------------------
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xE3, 0x5B };

IPAddress ip(10,0,1,171);
IPAddress gateway(10,0,1, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server = EthernetServer(10050); //Zabbix Agent port //Zabbix agent port
EthernetClient client;
boolean connected = false;
//--------------------------------------------
// This is our buffer through which we will "flow" our HTML code.
// It has to be as big as the longest character chain +1 including the "
char buffer[100];
//--------------------------------------------
//--------------------------------------------
String cmd; //FOR ZABBIX COMMAND
// int led = 33; //LED PORT TO BLINK AFTER RECIEVING ZABBIX COMMAND
//--------------------------------------------
const byte ID = 0x92; //used to identify if valid data in EEPROM the "know" bit, 
// if this is written in EEPROM the sketch has ran before
// We use this, so that the very first time you'll run this sketch it will use
// the values written above. 
// defining which EEPROM address we are using for what data
//--------------------------------------------
 void buzzCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those
       * buffers. */
      repeat = server.readPOSTparam(name, 16, value, 16);

      /* this is a standard string comparison function.  It returns 0
       * when there's an exact match.  We're looking for a parameter
       * named "buzz" here. */
      if (strcmp(name, "a") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('a');tellBox1('1'); Serial.println("http a1");}
        if (st ==0){ tellBox1('a');tellBox1('0'); Serial.println("http a0");}
     }
     if (strcmp(name, "b") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('b');tellBox1('1'); Serial.println("http b1");}
        if (st ==0){ tellBox1('b');tellBox1('0'); Serial.println("http b0");}
     }
     if (strcmp(name, "c") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('c');tellBox1('1'); Serial.println("http c1");}
        if (st ==0){ tellBox1('c');tellBox1('0'); Serial.println("http c0");}
     }
     if (strcmp(name, "d") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('d');tellBox1('1'); Serial.println("http d1");}
        if (st ==0){ tellBox1('d');tellBox1('0'); Serial.println("http d0");}
     }
     if (strcmp(name, "e") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('e');tellBox1('1'); Serial.println("http e1");}
        if (st ==0){ tellBox1('e');tellBox1('0'); Serial.println("http e0");}
     }
     if (strcmp(name, "f") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('f');tellBox1('1'); Serial.println("http f1");}
        if (st ==0){ tellBox1('f');tellBox1('0'); Serial.println("http f0");}
     }
     if (strcmp(name, "g") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('g');tellBox1('1'); Serial.println("http g1");}
        if (st ==0){ tellBox1('g');tellBox1('0'); Serial.println("http g0");}
     }
     if (strcmp(name, "h") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('h');tellBox1('1'); Serial.println("http h1");}
        if (st ==0){ tellBox1('h');tellBox1('0'); Serial.println("http h0");}
     }
       if (strcmp(name, "TV") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        Serial.println("TV");
      }
    } while (repeat);
    
    // after procesing the POST data, tell the web browser to reload
    // the page using a GET method. 
    server.httpSeeOther(PREFIX);
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" */
  server.httpSuccess();

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {
    /* store the HTML in program memory using the P macro */
    P(message) = 
  ""
""
 "</pre><h1>Box 1</h1><pre>"
 "</pre><form action='/box1' method='POST'>"
 "<button name='a' value='1'>A ON</button>"
 "<button name='a' value='0'>A OFF</button><BR>"
 "<button name='b' value='1'>B ON</button>"
 "<button name='b' value='0'>B OFF</button><BR>"
 "<button name='c' value='1'>C ON</button>"
 "<button name='c' value='0'>C OFF</button><BR>"
 "<button name='d' value='1'>D ON</button>"
 "<button name='d' value='0'>D OFF</button><BR>"
 "<button name='e' value='1'>E ON</button>"
 "<button name='e' value='0'>E OFF</button><BR>"
 "<button name='f' value='1'>F ON</button>"
 "<button name='f' value='0'>F OFF</button><BR>"
 "<button name='g' value='1'>G ON</button>"
 "<button name='g' value='0'>G OFF</button><BR>"
 "<button name='h' value='1'>H ON</button>"
 "<button name='h' value='0'>H OFF</button><BR>"
  "</form><pre>";

    server.printP(message);
  }
}
 void a1Cmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those
       * buffers. */
      repeat = server.readPOSTparam(name, 16, value, 16);

      /* this is a standard string comparison function.  It returns 0
       * when there's an exact match.  We're looking for a parameter
       * named "buzz" here. */
      if (strcmp(name, "a") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('a');tellBox1('1'); Serial.println("http a1");}
        if (st ==0){ tellBox1('a');tellBox1('0'); Serial.println("http a0");}
     }
    
    } while (repeat);
    
    // after procesing the POST data, tell the web browser to reload
    // the page using a GET method. 
    server.httpSeeOther(PREFIX);
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" */
  server.httpSuccess();

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {tellBox1('a');tellBox1('1'); Serial.println("http a1");
    /* store the HTML in program memory using the P macro */
    P(message) = 
  ""
""
 "</pre><h1>Box 1</h1><pre>"
 "</pre><form action='/box1' method='POST'>"
 "<button name='a' value='1'>A ON</button>"
 "<button name='a' value='0'>A OFF</button><BR>"
 "</form><pre>";

    server.printP(message);
  }
}
void a0Cmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those
       * buffers. */
      repeat = server.readPOSTparam(name, 16, value, 16);

      /* this is a standard string comparison function.  It returns 0
       * when there's an exact match.  We're looking for a parameter
       * named "buzz" here. */
      if (strcmp(name, "a") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        int st =2;
        st = strtoul(value, NULL, 10);
        if (st ==1){ tellBox1('a');tellBox1('1'); Serial.println("http a1");}
        if (st ==0){ tellBox1('a');tellBox1('0'); Serial.println("http a0");}
     }
    
    } while (repeat);
    
    // after procesing the POST data, tell the web browser to reload
    // the page using a GET method. 
    server.httpSeeOther(PREFIX);
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" */
  server.httpSuccess();

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {tellBox1('a');tellBox1('0'); Serial.println("http a0");
    /* store the HTML in program memory using the P macro */
    P(message) = 
  ""
""
 "</pre><h1>Box 1</h1><pre>"
 "</pre><form action='/box1' method='POST'>"
 "<button name='a' value='1'>A ON</button>"
 "<button name='a' value='0'>A OFF</button><BR>"
 "</form><pre>";

    server.printP(message);
  }
}

void setup()
{   Serial.begin(9600);
Ethernet.begin(mac, ip, gateway, subnet);
   Wire.begin (MY_ADDRESS); //i2c
     server.begin();


sensor.attach(A1);  //для сенсора температуры
Box1Request();

  webserver.setDefaultCommand(&buzzCmd);
  webserver.addCommand("a1", &a1Cmd);
  webserver.addCommand("a0", &a0Cmd);
  /* start the server to wait for connections */
  webserver.begin();
}

void loop()
{ webserver.processConnection();
//--------------------------------------------
  client = server.available();
  if (client == true) {
    if (!connected) {
      client.flush();
      connected = true;
    }

    if (client.available() > 0) {
      readTelnetCommand(client.read());
          }

      }
 
}
//--------------------------------------------
void readTelnetCommand(char c) {

  if(cmd.length() == MAX_CMD_LENGTH) {
    cmd = "";
  }

  cmd += c;

  if(c == '\n') {
    if(cmd.length() > 2) {
      // remove \r and \n from the string
      cmd = cmd.substring(0,cmd.length() - 1);
      parseCommand();
    }
  }
}
//--------------------------------------------
void parseCommand() {  //Commands recieved by agent on port 10050 parsing

  // AGENT.PING      
  if(cmd.equals("agent.ping")) {
      server.println("1");
      client.stop();
//      connected = false;

 // AGENT.VERSION      
   } else if(cmd.equals("agent.version")) {
      server.println("Sensor.IM 1.0");
      client.stop();
//      connected = false;

// MEMORY.FREE  - for diagnostic purposes
   } else if(cmd.equals("memory.free")) {
      server.println(memoryTest());
      client.stop();
      
// HUMIDITY.READ
} else if(cmd.equals("humidity.read")) {
      float h = humRead ();
       server.println(h );
//     digitalWrite(led, HIGH);
      client.stop();
      delay(2000);
//      digitalWrite(led, LOW);

// TEMPERATURE.READ
} else if(cmd.equals("temperature.read")) {
      float t = tempRead();
       server.println(t );
//     digitalWrite(led, HIGH);
      client.stop();
//      connected = false;
      delay(2000);
//      digitalWrite(led, LOW);
      
      // LIGHT.READ
} else if(cmd.equals("light.read")) {
      int t = int(lightRead());
       server.println(t );
      client.stop();
//      connected = false;
      delay(2000);
      
// Box1.Status
} else if(cmd.equals("Box1.Status")) {
      String t = Box1Status();
       server.println(t );
      client.stop();
//      connected = false;
      delay(2000);

                                          
            
// NOT SUPPORTED      
  } else {
    //  server.println("ZBXDZBX_NOTSUPPORTED");
    server.println(cmd);
      client.stop();
//      connected = false;
  }
  cmd = "";
}

//--------------------------------------------
// this function will return the number of bytes currently free in RAM - for diagnostics only
int memoryTest() 
{
  int byteCounter = 0; // initialize a counter
  byte *byteArray; // create a pointer to a byte array
  // More on pointers here: http://en.wikipedia.org/wiki/Pointer#C_pointers

  // use the malloc function to repeatedly attempt
  // allocating a certain number of bytes to memory
  // More on malloc here: http://en.wikipedia.org/wiki/Malloc
  while ( (byteArray = (byte*) malloc (byteCounter * sizeof(byte))) != NULL ) 
  {
    byteCounter++; // if allocation was successful, then up the count for the next try
    free(byteArray); // free memory after allocating it
  }

  free(byteArray); // also free memory after the function finishes
  return byteCounter; // send back the highest number of bytes successfully allocated
}
int tempRead ()
  {  
    sensor.update();
Serial.print("Temp=");
    switch (sensor.getLastError())
    {       case DHT_ERROR_OK:
            tt=sensor.getTemperatureInt();
            Serial.println(tt);
            return (tt);
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
    int humRead ()
  {  sensor.update();
Serial.print("Hum=");
    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
        
            hh=sensor.getHumidityInt();
            Serial.println(hh);
            return (hh);
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
     int lightRead ()
    {
      int t=analogRead(A2);
       Serial.print("Light ");
      Serial.println(t);
     return t; 
    }
    
   String Box1Status()
{ Box1Request();
 
 
 return box1;
 }
 void Box1Request(){
  int ii=0;
  Wire.requestFrom(2,8);    // запрос 6 байт от слейва #2
   while(Wire.available())    // пока есть, что читать
   { 
     char c = Wire.read();    // получаем байт (как символ)
     Serial.print(c);
     // печатает в порт
 if (c=='0') {box1[ii]='a';}
 if (c=='1') {box1[ii]='b';}
 ii++;
 } 
 }
 void tellBox1(char mess){
      Wire.beginTransmission (BOX1_ADDRESS);
      Wire.write (mess);
      Wire.endTransmission ();  
  }
 



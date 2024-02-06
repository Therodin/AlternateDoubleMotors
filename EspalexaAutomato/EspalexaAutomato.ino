#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#define pinMotor1 2
#define pinMotor2 4
#define pinMotor3 5
#define pinMotor4 18

Espalexa Motorstate1, Motorstate2;

//Variável usada para saber o estado do led.
int ligarMotor = 0;

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t val);
void secondLightChanged(uint8_t val);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "ATEL_FIBRA_MONTREAL35@SUA";
const char* password = "35neto@45";

boolean wifiConnected = false;

Espalexa espalexa;

EspalexaDevice* device3; //this is optional

void setup()
{
  
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);

  digitalWrite(pinMotor1, LOW);
  digitalWrite(pinMotor2, LOW);
  

  
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Filtro", firstLightChanged); //simplest definition, default state off
    espalexa.addDevice("Circulação", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    espalexa.addDevice("Borda infinita", thirdLightChanged);
    device3 = new EspalexaDevice("Jacuzzi", fourthLightChanged); //you can also create the Device objects yourself like here
    espalexa.addDevice(device3); //and then add them
    device3->setValue(128); //this allows you to e.g. update their state value at any time!

    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback functions
void firstLightChanged(uint8_t val) {
    
    if (val == 1) {
      digitalWrite(pinMotor2, LOW);
      ligarMotor = 1;
      
    }
    else  {
      ligarMotor = 0;
    }
  digitalWrite(pinMotor1, val)
}

void secondLightChanged(uint8_t val) {
  //do what you need to do here
   if (val == 1) {
      digitalWrite(pinMotor1, LOW);
      ligarMotor = 2;
      
    }
    else  {
      ligarMotor = 0;
    }
  digitalWrite(pinMotor2, val)
}

void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
  Serial.print("Device 3 changed to ");
    
    //do what you need to do here
    digitalWrite(pinMotor3, brightness);

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

void fourthLightChanged(uint8_t brightness) {
    Serial.print("Device 4 changed to ");
    
    //do what you need to do here
    digitalWrite(pinMotor4, brightness);

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

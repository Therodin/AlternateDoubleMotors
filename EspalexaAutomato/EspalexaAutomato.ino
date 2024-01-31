/*
 * Esse código é uma adaptação para motores que ligam alternadamente.
 * É um código originalmente criada por Christian Schwinne
 */ 

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#endif
#include <Espalexa.h>
#include <ESP8266WiFi.h>


//definições de pinos
#define pinMotor1 1
#define pinMotor2 2
#define pinMotor3 5
#define pinMotor4 6

//controle reostato
uint8_t ligMotor;
uint8_t ligMotorAlvo;
#define timeChange 15

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "...";
const char* password = "wifipassword";

boolean wifiConnected = false;

Espalexa espalexa;

EspalexaDevice* device3; //this is optional

void setup()
{
  pinMode(pinMotor1, OUTPUT)
  pinMode(pinMotor2, OUTPUT)
  pinMode(pinMotor3, OUTPUT)
  pinMode(pinMotor4, OUTPUT)

  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Motor 1", firstLightChanged); //simplest definition, default state off
    espalexa.addDevice("Motor 2", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    espalexa.addDevice("Motor 4", fourthLightChanged);
    
    device3 = new EspalexaDevice("Motor 3", thirdLightChanged); //you can also create the Device objects yourself like here
    espalexa.addDevice(device3); //and then add them
    device3->setValue(128); //this allows you to e.g. update their state value at any time!

    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Não foi possível conectar no wifi, por favor resetar o esp");
      delay(2500);
    }
  }
}
 
void loop()
{
  espalexa.loop();

  int Motor1State, Motor2State;
   Motor1State = digitalRead(PinMotor1);
   Motor2State = digitalRead(PinMotor2);
  
  if (((Motor1State == HIGH) && (Motor2State == LOW)))
       
      {
    	
       digitalWrite(pinMotor1, HIGH);
    	digitalWrite(pinMotor2, LOW);
    
    	}
 
  	if (((Motor1State == LOW) && (Motor2State == HIGH)));
        {
    	
       digitalWrite(pinMotor2, HIGH);
    	digitalWrite(pinMotor1, LOW);
    
    	}
    
    if (((Motor1State == HIGH) && (Motor2State == HIGH)));
        {
    	
       digitalWrite(pinMotor2, LOW);
    	digitalWrite(pinMotor1, LOW);
  	
    
  
    
  
   }
   delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
    Serial.print("Dispositivo Motor 1 ligado ");
    
    //do what you need to do here
    digitalWrite(pinMotor1, brightness);

    //EXAMPLE
    if (brightness) {
      Serial.print("ON");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

void secondLightChanged(uint8_t brightness) {
  Serial.print("Dispositivo Motor 2 ligado ");

  //do what you need to do here
  digitalWrite(pinMotor2, brightness);

  //EXAMPLE
    if (brightness) {
      Serial.print("ON");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }


}

void thirdLightChanged(uint8_t brightness) {
  Serial.print("Dispositivo Motor 3 ligado ");

  //do what you need to do here
  digitalWrite(pinMotor3, brightness);

  //EXAMPLE
  if (brightness) {
      Serial.print("ON");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

void fourthLightChanged(uint8_t brightness) {
  Serial.print("Dispositivo Motor 4 ligado ");

  //do what you need to do here
  digitalWrite(pinMotor4, brightness);

  //EXAMPLE
  if (brightness) {
      Serial.print("ON");
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

#include <EmonLib.h>
#include <ThingerESP8266.h>

#define USERNAME "kodingngalam"
#define DEVICE_ID "nodeMCU01"
#define DEVICE_CREDENTIAL "ZftFZQTR3NOt"

#define SSID "Gelapnya dosa dunia"
#define SSID_PASSWORD "123456789"

#define SSR 5
#define CTsensor A0


EnergyMonitor emon1;
double Irms;

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SSR, OUTPUT);
  emon1.current(CTsensor, 111.1);

  digitalWrite(SSR, LOW);

  thing.add_wifi(SSID, SSID_PASSWORD);
  
  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  //control data
  thing["SSR"] << digitalPin(SSR);

  Irms = emon1.calcIrms(1480);  // Calculate Irms only
  Irms = Irms* 230.0;

  //Energy monitor data
  thing["Emon"] >> outputValue(Irms);

}

void loop() {
  thing.handle();
  Serial.println(Irms);
}


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

#include <DHT.h>
#define DHTPIN D6          // Pin ket noi voi DHT
#define DHTTYPE DHT11     // Su dung cam bien DHT11
DHT dht(DHTPIN, DHTTYPE); // Cau hinh chan DHT 
#define Vtemp V30
#define Vhumidi V31
#define  Dgas D1
#define VgasStt V32
#define Vgas V33
#define Agas A0


WidgetBridge bridgeA(V10);

char auth[] = "013087bd76e74f81b0c32caa2528e8fe";  // Quan token Blynk server
// char tokenA[] = "3dddac1594e74646bde292060be39113";//from Blnyk
char tokenA[] = "eac41632ae5c4a8eba8bdc2cfb1def5c";//from Tapit.vn
char ssid[] = "NT98_A3";  //Tên wifi
char pass[] = "568568568";     //Mật khẩu wifi
//char ssid[] = "TOP";  //Tên wifi
//char pass[] = "0968457018";     //Mật khẩu wifi
char host[] = "tapit.vn";

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V4);
  bridgeA.setAuthToken(tokenA); // Place the AuthToken of the second hardware here
}
void readSensor ()
{
  int h = dht.readHumidity();     //Doc gia tri do am
  int t = dht.readTemperature();  //Doc gia tri nhiet do
  int g = digitalRead(Dgas);
  int j = analogRead(Agas) * (3.3 / 1023.0);

  bridgeA.virtualWrite(VgasStt,g);
  bridgeA.virtualWrite(Vgas,j);
  Serial.println("GasStt = " + String(g) + "gas = " + String(j) );

  if (t <= 100 && h <=100)
    {
      bridgeA.virtualWrite(Vtemp,t);
      bridgeA.virtualWrite(Vhumidi,h);
      Serial.println("Temp = " + String(t) + " Humidi = " + String(h));
    }
  
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, host);
  timer.setInterval(10000L, readSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WidgetRTC.h>
#include <Servo.h>
//-----------------define Pin-----------//
#define Dspeaker D0
#define DledLivingRoom D1
#define DledBedRoom D2
#define Dfan D3
#define Dheater D4
#define DledKitchen D5
#define DledBathRoom D6
#define Ddoor D7
#define DairConditioner D8
#define Dwindow D9
#define DledYard D10

#define VledLivingRoom V1
#define VledBedRoom V2
#define Vfan V3
#define Vheater V4
#define VledKitchen V5
#define VledBathRoom V6
#define Vdoor V7
#define VairConditioner V8
#define Vwindow V9
#define VledYard V10

#define VallDevice V19
#define VcheckAll V11
#define VsendStt V12



#define VselectDeviceTimer V15
#define VshowFanTimer V16
#define VshowHeaterTimer V17
#define VshowAirConditionerTimer V18
#define VreadAppTimer V23
#define VreadGoogleTimerStart V24
#define VreadGoogleTimerStop V25


#define Vtemp V30
#define Vhumidi V31
#define VgasStt V32
#define Vgas V33

#define lightSensor A0


//---------------define varible and const-------------//
BlynkTimer timer; // Announcing the timer
WidgetRTC rtc;
struct timeType { 
  int hh;
  int mm;
  };
timeType currentTime{-1,-1};
timeType deviceVoiceTimeStart[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
timeType deviceVoiceTimeStop[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
timeType timeInputStart[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
timeType timeInputStop[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
int Vpin[3] = {Vfan, Vheater, VairConditioner};
int VdisplayTimer[3] = {VshowFanTimer, VshowHeaterTimer, VshowAirConditionerTimer};
String device[3] = {"fan", "heater", "air_conditioner"};
String stt[2] = {"on", "off"};
String state[2] = {"opened", "closed"};
uint8_t Dpin[2] = {Dfan, Dheater};
uint8_t led[4] ={DledLivingRoom, DledBedRoom, DledKitchen, DledBathRoom };
uint8_t Ddivice[3] = {Dfan, Dheater, DairConditioner};
int n = 3;
int deviceSelect = 0;
char auth[] = "eac41632ae5c4a8eba8bdc2cfb1def5c";
char tokenB[] = "013087bd76e74f81b0c32caa2528e8fe"; //from Tapit.vn
//char ssid[] = "TOP";  //Tên wifi
//char pass[] = "0968457018";     //Mật khẩu wifi
char ssid[] = "NT98_A3";  //Tên wifi
char pass[] = "568568568";     //Mật khẩu wifi
char host[] = "tapit.vn";
WidgetBridge bridge1(V14);
Servo myServoDoor, myServoWindow;  // create servo object to control a servo 

int x[4];
int y[3];
int z[2];
int h,t,g;
String b = "";

//--------Turn all device-----------//
BLYNK_WRITE(VallDevice)
  {
    String i = param.asStr();
    if (i == "0")
    {
      for (int i = 0 ; i < 4; i ++)
        digitalWrite(led[i], LOW);
      for (int i = 0 ; i < 3; i ++)
        digitalWrite(Ddivice[i], LOW);
      myServoDoor.write(100);
      myServoWindow.write(100);
      Blynk.virtualWrite(VallDevice,"2");
    }
    if (i == "1")
    {
      for (int i = 0 ; i < 4; i ++)
        digitalWrite(led[i], HIGH);
      for (int i = 0 ; i < 3; i ++)
        digitalWrite(Ddivice[i], HIGH);
      myServoDoor.write(10);
      myServoWindow.write(10);
      Blynk.virtualWrite(VallDevice,"2"); 
   }
  }

  //--------Check all status----//
 BLYNK_WRITE(VcheckAll)
  {
    String i = param.asStr();
    if (i == "0")
    {  
      String allStt = "{" + b + "}";
      Blynk.virtualWrite(VsendStt,allStt);
      Blynk.virtualWrite(VcheckAll,"1");
    }
  }
BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins

  Blynk.syncVirtual(VledLivingRoom);
  Blynk.syncVirtual(VledBedRoom);
  Blynk.syncVirtual(VledKitchen);
  Blynk.syncVirtual(VledBathRoom);
  Blynk.syncVirtual(Vfan);
  Blynk.syncVirtual(Vheater);
  Blynk.syncVirtual(VairConditioner);
  Blynk.syncVirtual(Vdoor);
  Blynk.syncVirtual(Vwindow);

  bridge1.setAuthToken(tokenB); // Place the AuthToken of the second hardware here
}

//-----Led Living-----//
BLYNK_WRITE(VledLivingRoom){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(DledLivingRoom,stt);
}

//-----Led BedRoom-----//
BLYNK_WRITE(VledBedRoom){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(DledBedRoom,stt);
}


//-----Led Kitchen -----//
BLYNK_WRITE(VledKitchen){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(DledKitchen,stt);
}

//-----Led BathRoom-----//
BLYNK_WRITE(VledBathRoom){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(DledBathRoom,stt);
}

//-----Fan -----//
BLYNK_WRITE(Vfan){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(Dfan,stt);
}

//-----Heater -----//
BLYNK_WRITE(Vheater){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(Dheater,stt);

}
//-----AirConditioner -----//
BLYNK_WRITE(VairConditioner){
 int stt = param.asInt();
 Serial.println(stt);
 digitalWrite(DairConditioner,stt);

}
//-----Temp -----//
BLYNK_WRITE(Vtemp)
{
  t = param.asInt();
  Serial.println("Temp recieve from B " + String(t));
  if (t >=35) {
    checkStt();
    digitalWrite(Dspeaker,1);
    Blynk.notify("Cảnh báo: Nhiệt độ quá cao");
    Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: Nhiệt độ rất cao",b);
    delay(50);
    digitalWrite(Dspeaker,0);
  }
  else 
    digitalWrite(Dspeaker, 0);
}

//--------Humidy-------//
BLYNK_WRITE(Vhumidi)
{ 
  h = param.asInt();
  Serial.println("Humidi recieve from B " + String(h));
}

//---------Read gas sensor------//
BLYNK_WRITE(Vgas) {
  g = param.asInt();
  Serial.println("Gas recieve from B " + String(g));
}

//---------Door-----------//
BLYNK_WRITE(Vdoor){
  z[0] = param.asInt();
 if (z[0] == 0)
  {
    if (analogRead(lightSensor) < 300) {
      digitalWrite(DledLivingRoom, LOW);
      Blynk.virtualWrite(VledLivingRoom,LOW);
    }
    myServoDoor.write(100); 
  Serial.println("door open " + String(100));
  }
 else if (z[0] == 1 )
  {
    myServoDoor.write(10);
  Serial.println("door close " + String(10));
  } 
}

//-----------Window--------//
BLYNK_WRITE(Vwindow){
  z[1] = param.asInt();
 if (z[1] == 0)
  {
    myServoWindow.write(100); 
  Serial.println("window  open " + String(100));
  }
 else if (z[0] == 1 )
  {
    myServoWindow.write(10);
  Serial.println("window close " + String(10));
  } 
}

//----------Gas Alert----------------//
BLYNK_WRITE(VgasStt) {
  int stt = param.asInt();
  if (stt == LOW) {
    checkStt();
    digitalWrite(Dspeaker,1);
    Blynk.notify("Cảnh báo: Rò rỉ khí ga"); 
    Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: rò rỉ khí ga",b);
    delay(1000);
    digitalWrite(Dspeaker,0);
    }
  else 
    digitalWrite(Dspeaker, 0);
}


//----Read Timer from app------//
BLYNK_WRITE(VreadAppTimer) {
  TimeInputParam t(param);
  // Process start time
  int n = deviceSelect-1;
  Serial.println("n = " + String(n));
  if (t.hasStartTime() && n >= 0 ){
    timeInputStart[n].hh = t.getStartHour();
    timeInputStart[n].mm = t.getStartMinute();
  }
  if (t.hasStopTime() && deviceSelect != 0){
    timeInputStop[n].hh =  t.getStopHour();
    timeInputStop[n].mm = t.getStopMinute();
  }
  String stt = "The " + device[n] + " on at " + String( timeInputStart[n].hh) + ":" +  String( timeInputStart[n].mm) + 
    ", off at " + String( timeInputStop[n].hh) + ":" +  String( timeInputStop[n].mm);
  Serial.println("Stt = " + stt);
  Blynk.virtualWrite(VdisplayTimer[n],stt);
  deviceSelect = 0;
  Blynk.virtualWrite(VselectDeviceTimer,"Select Device");
  
  
}

//-----Read device from app---------//
BLYNK_WRITE(VselectDeviceTimer) {
   deviceSelect = param.asInt();
}

//----Read TimeStart and device from Google------//
BLYNK_WRITE(VreadGoogleTimerStart){
  String voiceTimeStartStr = param.asStr();
  int deviceNum = voiceTimeStartStr.substring(6,7).toInt();
  timeInputStart[deviceNum].hh = voiceTimeStartStr.substring(0,2).toInt();
  timeInputStart[deviceNum].mm = voiceTimeStartStr.substring(3,5).toInt();
  String stt;
  if (timeInputStop[deviceNum].hh != -1)
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  
      String( timeInputStart[deviceNum].mm) + ", off at " +  String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  else
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  String( timeInputStart[deviceNum].mm);


    Serial.println(stt);
  Blynk.virtualWrite(VdisplayTimer[deviceNum],stt);
}

//----Read TimeStop and device from Google------//
BLYNK_WRITE(VreadGoogleTimerStop){
  String voiceTimeStopStr = param.asStr();
  int deviceNum = voiceTimeStopStr.substring(6,7).toInt();
  timeInputStop[deviceNum].hh = voiceTimeStopStr.substring(0,2).toInt();
  timeInputStop[deviceNum].mm = voiceTimeStopStr.substring(3,5).toInt();
  String stt;
  if (  timeInputStart[deviceNum].hh != -1 )
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  
      String( timeInputStart[deviceNum].mm) + ", off at " + String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  else
    stt = "The " + device[deviceNum] +  " off at " + String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
    Serial.println(stt);
  Blynk.virtualWrite(VdisplayTimer[deviceNum],stt);
}
void setup()
{
   
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,host);
  pinMode(Dspeaker,OUTPUT);//loa
  for (int i = 0 ; i < 4 ; i ++)
    pinMode(led[i], OUTPUT);
  for (int i = 0 ; i < 3 ; i ++)
    pinMode(Ddivice[i],OUTPUT);
  myServoDoor.attach(Ddoor);  // attaches the servo on GIO2 to the servo object 
  myServoWindow.attach(Dwindow);  // attaches the servo on GIO2 to the servo object 
  rtc.begin();
  timer.setInterval(2000L, myTimerEvent);
  timer.setInterval(1000L, checkStt);
  timer.setInterval(2000L, lightProcess);
  
}



void processTimer(uint8_t Dpin, int stt1, int Vpin, int stt2, timeType timeP){
  digitalWrite(Dpin, stt1);
  Blynk.virtualWrite(Vpin, stt2);
  timeP.hh = timeP.mm = -1;
}
void myTimerEvent(){
  currentTime.hh = hour();
  currentTime.mm = minute();
  for (int i = 0 ; i < n; i ++){
   if ( currentTime.hh == timeInputStart[i].hh && currentTime.mm == timeInputStart[i].mm )
      processTimer(Dpin[i], LOW, Vpin[i], LOW, timeInputStart[i]);
   if ( currentTime.hh == timeInputStop[i].hh && currentTime.mm == timeInputStop[i].mm )
   {
      processTimer(Dpin[i], HIGH, Vpin[i], HIGH, timeInputStop[i]);
      Blynk.virtualWrite(VdisplayTimer[i]," ");
   }
      
  } 
}

void checkStt() {
 
  for (int i = 0; i < 4; i ++)
    x[i] = digitalRead(led[i]);
  for (int i = 0; i < 3; i ++)
  y[i] = digitalRead(Ddivice[i]);//quat

  b ="The temperature:"+String(t)+"°C. \The humidity\: "+String(h)+"%. \The gas concentration\ "+String(g) +
  "%. \Light in Living Room\: " +stt[x[0]] +". \Light in Kitchen\: " +stt[x[2]] +  "%. \Lights in Bedroom\: " +stt[x[1]] +   "%. \Lights in Bath Room\: " +stt[x[3]] +
  ". \Fan\: "+stt[y[0]]+ ". \Heater\: " + stt[y[1]] + ". \Air conditioner\: " + stt[y[2]] + ". \The door is\ " + state[z[0]] + ". \The window is\ " + state[z[1]];  
}

void lightProcess() {
  int lightStatus = analogRead(lightSensor);
  Serial.println(lightStatus); 
  if (lightStatus < 300) {
    digitalWrite(DledYard,LOW);
    Blynk.virtualWrite(VledYard,LOW);
  }
  else {
    digitalWrite(D4,HIGH);
    Blynk.virtualWrite(VledYard,HIGH);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}


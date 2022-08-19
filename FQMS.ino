#include <SimpleDHT.h>
#include <SoftwareSerial.h>

#define RX 7
#define TX 6
#define sensorDigital 2
#define sensorAnalog A1
//#define LED 4
//#define buzzer 3
//#define ldr A3
#define pinDHT11 8
#define DEBUG false

SimpleDHT11 dht11(pinDHT11);
SoftwareSerial espSerial(RX, TX);

String mySSID = "Darshsn_4G";
String myPWD = "NJ2H21711";
String myAPI = "L1TKKR3THRXHOO0L";
String myHOST = "api.thingspeak.com";
String myPORT = "80";
String mq3 = "field1";
String temp = "field2";
String humid = "field3";
//String photons = "field4";
int prevAnalog = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(115200);
  pinMode(sensorDigital, INPUT);
  //pinMode(LED, OUTPUT);
 // pinMode(buzzer, OUTPUT);
  espData("AT+RST", 1000, DEBUG);
  espData("AT+CWMODE=1", 1000, DEBUG);
  espData("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 1000, DEBUG);
  Serial.println("Beginning in 5 seconds");
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(LED, LOW);
  //digitalWrite(buzzer, LOW);
  int analog = analogRead(sensorAnalog);
 // int light = analogRead(ldr);
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }

  String sendData = "GET /update?api_key=" + myAPI + "&" + mq3 + "=" + String(analog) + "&" + temp + "=" + String(temperature) + "&" + humid + "=" + String(humidity);
  espData("AT+CIPMUX=1", 1000, DEBUG);
  espData("AT+CIPSTART=0,\"TCP\",\"" + myHOST + "\"," + myPORT, 1000, DEBUG);
  espData("AT+CIPSEND=0," + String(sendData.length() + 4), 1000, DEBUG);
  espSerial.find(">");
  espSerial.println(sendData);
  espData("AT+CIPCLOSE=0", 1000, DEBUG);

  Serial.println("== == == == == == == == == == == == == == == == == == == == == == ==");
  Serial.print("MQ3 Value: ");
  Serial.println(analog);
  Serial.print("DHT11 Value: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %H");
  //Serial.print("LDR Value: ");
  //Serial.println(light);

  int alcoholDifference = analog - prevAnalog;
  boolean actualCondition = (alcoholDifference > 5 && (temperature < 20 || temperature > 35) && humidity > 52);
 // boolean testCondition = (light < 85);
  //prevAnalog = analog;

//  if (testCondition) {
//    Serial.println("**************ALERT**************ALERT**************");
//    digitalWrite(LED, HIGH);
//    digitalWrite(buzzer, HIGH);
//    delay(3000);
//    digitalWrite(LED, LOW);
//    digitalWrite(buzzer, LOW);
 // }

  delay(20000);
}

String espData(String command, const int timeout, boolean debug)
{
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");

  String response = "";
  espSerial.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (espSerial.available())
    {
      char c = espSerial.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print("***************");
    Serial.print(response);
    Serial.print("***************");
  }
  return response;
}

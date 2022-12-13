#include <WiFi.h> //library for using ESP32 WiFi 
#include <PubSubClient.h> //library for MQTT
#include <ArduinoJson.h> //library for Parsing JSON
 
//defining Pins
#define pinLED 32
#define pinPIR 33
#define pinLDR 35

int ldr = 0;
int somaLDR = 0;
float mediaLDR = 0.0;
 
//WiFi Credentials
const char* ssid = "xxxxx";//setting your ap ssid
const char* password = "xxxxx";//setting your ap psk
//MQTT Credentials
const char* mqttServer = "xxxxx"; //MQTT URL
const char* mqttUserName = "Device1";  // MQTT username
const char* mqttPwd = "Device1";  // MQTT password
const char* clientID = "Device1"; // client id username+0001
const char* topic = "Sensordata"; //publish topic
 
String msgStr = "";      // MQTT message buffer

//sensores de presença e módulo relay
bool pir = false;
bool piraux = false;
bool led = false;

//variável para detecção do tipo de controle
int command = 10;
 
//setting up wifi and mqtt client
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup_wifi() {
  delay(10);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID, mqttUserName, mqttPwd)) {
      Serial.println("MQTT connected");
 
      client.subscribe("lights");
      Serial.println("Topic Subscribed");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);  // wait 5sec and retry
    }
  }
}
 
//subscribe call back
void callback(char*topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String data = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    data += (char)payload[i];
  }
  Serial.println();
  Serial.print("Message size :");
  Serial.println(length);
  Serial.println();
  Serial.println("-----------------------");
  Serial.println(data);
 
  if (data=="AUT"){
    command = 10;
  }
  if (data=="VON"){
    command = 20;
  }
  if (data=="VOFF"){
    command = 21;
  }
}
 
void setup() {
  Serial.begin(115200);
  // Initialize device.
 
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, HIGH);  // habilita resistores de pull-up
  pinMode(pinPIR, INPUT);  // configura como entrada
  pinMode(pinLDR, INPUT);  // configura como entrada
  digitalWrite(pinLDR, LOW);  // desabilita resistores de pull-up
 
  setup_wifi();
 
  client.setServer(mqttServer, 1883); //setting MQTT server
  client.setCallback(callback); //defining function which will be called when message is received.
}
 
void loop() {
  if (!client.connected()) { //if client is not connected
    reconnect(); //try to reconnect
  }
  client.loop();

  //sensor PIR
  for (int i = 0; i < 5; i++) {
    //leituras analógicas
    digitalRead(pinPIR);
    delay(400);
    piraux = digitalRead(pinPIR);
    pir = pir || piraux;  
  }

  //sensor LDR
  for (int i = 0; i < 200; i++) {
    //leituras analógicas
    analogRead(pinLDR);
    delay(10);
    ldr = analogRead(pinLDR);
    somaLDR = somaLDR + ldr;  
  }
  mediaLDR = somaLDR/200;
  somaLDR = 0;

  //status da lâmpada
  led = false;

  //situações de controle automático
  if(command == 10) {
    if(mediaLDR < 1000 && pir) {
      led = true;
      digitalWrite(pinLED, LOW);
      delay(10000);
    }
    else {
      led = false;
      digitalWrite(pinLED, HIGH);
    }
  }

  //situações de controle por voz
  if(command == 20) {
    led = true;
    digitalWrite(pinLED, LOW);
  }
  if(command == 21) {
    led = false;
    digitalWrite(pinLED, HIGH);
  }
     
  msgStr = String(pir) + "," + String(mediaLDR) + "," + String(led);
  byte arrSize = msgStr.length() + 1;
  char msg[arrSize];
  
  Serial.print("PUBLISH DATA:");
  Serial.println(msgStr);
  msgStr.toCharArray(msg, arrSize);
  client.publish(topic, msg);
  msgStr = "";

  Serial.println(command);

  //reseta variáveis do sensor de presença
  pir = false;
  piraux = false;
}

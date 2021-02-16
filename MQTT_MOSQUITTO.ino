#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void reconnectmqttserver() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
     if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("LED26574");
      client.subscribe("RADIO26574");
     } else {
       Serial.print("failed, rc=");
       Serial.print(client.state());
       Serial.println(" try again in 5 seconds");
       delay(5000);
     }
   }
}

char msgmqtt[50];
void callback(char* topic, byte* payload, unsigned int length) {
  String MQTT_DATA = "";
  for (int i=0;i<length;i++) {
   MQTT_DATA += (char)payload[i];
  }
  Serial.print(topic);
  Serial.print(" -  ");
  Serial.println(MQTT_DATA);

  if(MQTT_DATA=="1"){
    digitalWrite(D3, HIGH);
    client.publish("ResponceLED", "LEDON");
  }else if(MQTT_DATA=="0"){
    digitalWrite(D3, LOW);
    client.publish("ResponceLED", "LEDOFF");
  }
  
  if(MQTT_DATA=="ON"){
    digitalWrite(D3, HIGH);
    client.publish("ResponceLED", "LEDON");
    
  }else if(MQTT_DATA=="OFF"){
    digitalWrite(D3, LOW);
    client.publish("ResponceLED", "LEDOFF");
  }
}


int  i = 0;
String data;
void setup(){
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Yashitha-Personal-4G","ymax26574ymax");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));
  client.setServer("test.mosquitto.org", 1883);
  client.setCallback(callback);

}


void loop()
{

    if (!client.connected()) {
    reconnectmqttserver();
    }
    client.loop();
//    snprintf (msgmqtt, 50, "%d ",i);
    client.publish("NODERESPONCE26574", "1");
//    i = i + 1;
//    delay(1000);

}

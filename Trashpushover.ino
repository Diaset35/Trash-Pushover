#include <uTimerLib.h>

#include <HCSR04.h>

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include <WiFi.h>

UltraSonicDistanceSensor distanceSensor(2, 4);

WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.119", 1883);
Adafruit_MQTT_Publish distancePublisher(&mqttClient, "/distance");

void distance() {
 double distance = distanceSensor.measureDistanceCm(); 
  Serial.println (distance);
  if(distance< 10 ) {
    distancePublisher.publish(distance);
    delay(5000); 
}
}
void setup() {
  Serial.begin(115200);
  WiFi.begin("createch2019", "createch2019");
  delay(5000);

  Serial.println(WiFi.localIP());
  TimerLib.setInterval_s(distance, 2);

}

void loop() {
  if (mqttClient.connected()) {
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
}
  
}

#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iotbot-e233e-default-rtdb.firebaseio.com"
#define WIFI_SSID "ROBO TECH VALLEY"
#define WIFI_PASSWORD "roboninja"
#define FIREBASE_Authorization_key "7xNpkqu0oxX3yefrXGni1ii2c2CFz3sF9AJ1IdhL"

FirebaseData firebaseData;
FirebaseJson json;

int moistureSensor = A0;
float moisture;
int values;

void setup() {
  pinMode(moistureSensor, INPUT);
  Serial.begin(115200); // Starts the serial communication
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);

}

void loop() {
  int values = analogRead(moistureSensor);

  delay(1000);
  float moisture = map(values, 685, 290, 0, 100);

  if (moisture <= 0) {
    moisture = 0;
  }
  else if (moisture >= 100) {
    moisture = 100;
  }

  Serial.println(moisture);

  Firebase.setFloat(firebaseData, "/moisture",moisture);

  
}

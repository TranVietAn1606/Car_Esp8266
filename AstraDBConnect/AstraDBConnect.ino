#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

char ssid[] = "NotNetw";
char password[] = "abc123123";
WiFiClientSecure client;

//const char *temprature[25] = {"27.05", "27.90", "28.00", "28.24", "28.47", "28.85", "29.14", "29.33", "29.78", "30.10", "30.23", "30.44", "30.67", "31.00", "31.54", "32.78", "33.06", "33.49", "33.77", "33.89", "34.30", "34.70", "35.32", "35.79", "37.75"}; // *C
//const char *amount_of_rain[25] = {"16", "20", "29", "40", "47", "53", "59", "62", "67", "70", "73", "77", "81", "86", "92", "95", "98", "100", "108", "111", "115", "120", "131", "149", "160"}; // mm/day
//const char *humility[25] = {"49.00", "50.59", "51.65", "", "52.34", "55.04", "58.43", "59.76", "60.28", "63.01", "63.59", "64.66", "65.21", "68.23", "68.81", "71.00", "73.37", "77.77", "82.19", "86.54", "91.7", "95.32", "97.56", "98.00", "98.72"}; // %
const char *positions[25] = {"16,17", "16,25", "18,87", "20,130", "21,88", "22,111", "23,97", "24,109", "25,54", "25,124", "26,01", "26,97", "32,10", "32,32", "33,39", "33,44", "33,99", "34,53", "34,97", "35,30", "35,109", "36,50", "36,121", "37,05", "38,145"};

#define TEST_HOST "551dc2ab-ceb7-4349-9cd2-425d6290e8ff-asia-south1.apps.astra.datastax.com"
#define TEST_HOST_FINGERPRINT "96 2C DC 6D A4 27 7D 06 66 C6 37 87 F5 D6 15 3F 28 C4 8E 6E"

int DHTPIN = D4;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

int SOIDPIN = A0;
void setup() {
  dht.begin();
  pinMode(SOIDPIN, INPUT);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  client.setFingerprint(TEST_HOST_FINGERPRINT);
}

void loop() {
  int id_val = 0;
  while (1) {
    //    int temp_i = random(25);
    //    int hum_i  = random(25);
    float humidity_val = dht.readHumidity();
    float temprature_val = dht.readTemperature();
    int soid_val = analogRead(SOIDPIN);
    //int amount_i = random(25);
    int pos_i = random(25);
    //    makeHTTPRequest(String(id_val), String(temprature[temp_i]), String(humility[hum_i]), String(amount_of_rain[amount_i]), String(positions[pos_i]));
    makeHTTPRequest(String(id_val), String(temprature_val), String(humidity_val), String(soid_val), String(positions[pos_i]));
    id_val++;
  }
}

void makeHTTPRequest(String id, String temp, String hum, String amount, String pos) {
  HTTPClient http;
  if (!client.connect(TEST_HOST, 443)) {
    Serial.println(F("Connection failed"));
  }

  String serverName = "https://551dc2ab-ceb7-4349-9cd2-425d6290e8ff-asia-south1.apps.astra.datastax.com/api/rest/v2/keyspaces/key123/collection";
  http.begin(client, serverName.c_str());
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-Cassandra-Token", "AstraCS:YBHmrzUPuxYEIjctBwzavhJd:7c6b886eba982c73a2bb66f4bfa1e664bfea87c992b5ca7157c5dd5cacfdf3e3");

  String bodystr = "{\"id\": \"";
  bodystr.concat(id);
  bodystr.concat("\",\"position\":\"");
  bodystr.concat(pos);
  bodystr.concat("\",\"temprature\":\"");
  bodystr.concat(temp);
  bodystr.concat("\",\"air humidity\":\"");
  bodystr.concat(hum);
  bodystr.concat("\",\"soid moisture\":\"");
  bodystr.concat(amount);
  bodystr.concat("\"}");
  int httpResponseCode = http.POST(bodystr.c_str());
  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("payload: " + payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  delay(5000);
}

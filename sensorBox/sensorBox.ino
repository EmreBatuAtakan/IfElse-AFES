#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0x60, 0xD1, 0x10}; //reciever device's mac address

//Following definitions depend on what pin the component is connected to.

#define MQ2 12
#define MQ7 14

//defined message structure
typedef struct struct_message {
  int a;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

//on data sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW!");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  pinMode(MQ2, INPUT);
  pinMode(MQ7, INPUT);

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  int sensorMQ2 = analogRead(MQ2);
  int sensorMQ7 = analogRead(MQ7);

  int sensorTotal = 0;

  if (sensorMQ2 > 600) { //change the values accordingly, datasheets mentioned in README.md
    sensorTotal++;
  }

  if (sensorMQ7 > 600) { //change the values accordingly, datasheets mentioned in README.md
    sensorTotal++;
    sensorTotal++;
  }

  myData.a = sensorTotal;

  Serial.println(sensorMQ2);
  Serial.println(sensorMQ7);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  } else {
    Serial.println("Sending error");
  }
}

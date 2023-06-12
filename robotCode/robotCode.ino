#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>

#define left 21
#define center 22
#define right 23

//front left motor
#define Front_L1 13
#define Front_L2 12

//front right motor
#define Front_R1 27
#define Front_R2 26

//back left motor
#define Back_L1 25
#define Back_L2 33

//back right motor
#define Back_R1 32
#define Back_R2 35

//create servo
Servo fireExtinguisher1;
Servo fireExtinguisher2;
 
int pos = 0;

int limit = 0;

int extinguisher1 = 16;
int extinguisher2 = 4;

//create message struction
typedef struct struct_message {
  int a;
} struct_message;

struct_message myData;

bool MQ2Detected = false;
bool MQ7Detected = false;
bool anyFire = false;
int closestFLAME;

//on data recieve
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.a);

  if(myData.a == 0) {
    MQ2Detected = false;
    MQ7Detected = false;
    anyFire = true;
  } else if (myData.a == 1) {
    MQ2Detected = true;
    MQ7Detected = false;
    anyFire = true;
  } else if (myData.a == 2) {
    MQ2Detected = false;
    MQ7Detected = true;
    anyFire = true;
  } else if (myData.a == 3) {
    MQ2Detected = true;
    MQ7Detected = true;
    anyFire = true;
  }
}


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  fireExtinguisher1.attach(extinguisher1);
  fireExtinguisher2.attach(extinguisher2);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);

  

  pinMode(left, INPUT);
  pinMode(center, INPUT);
  pinMode(right, INPUT);

  pinMode(Front_L1, OUTPUT);
  pinMode(Front_L2, OUTPUT);
  pinMode(Front_R1, OUTPUT);
  pinMode(Front_R2, OUTPUT);

  pinMode(Back_L1, OUTPUT);
  pinMode(Back_L2, OUTPUT);
  pinMode(Back_R1, OUTPUT);
  pinMode(Back_R2, OUTPUT);
}

void loop() {
  limit++;
  Serial.println(limit);

  bool leftV = digitalRead(left);
  bool centerV = digitalRead(center);
  bool rightV = digitalRead(right);
  //white -> black -> brown -> red
  int FRONTsensorReading = analogRead(19);
  int LEFTsensorReading = analogRead(18);
  int BACKsensorReading = analogRead(5);
  int RIGHTsensorReading = analogRead(17);

  /*
  int sensorListFIRE[4] = {FRONTsensorReading, LEFTsensorReading, BACKsensorReading, RIGHTsensorReading};
  for (int sensor : sensorListFIRE) {
    Serial.println(sensor);
  }
  //closestFLAME = compareFLAME(sensorListFIRE);
  */

  //selectMovement(closestFLAME, anyFire, MQ2Detected, MQ7Detected, leftV, centerV, rightV);
  selectMovement(-1, true, true, true, leftV, centerV, rightV);
}



void selectMovement(int flameID, bool doesFlameExist, bool MQ2, bool MQ7, bool leftV, bool centerV, bool rightV) {
  if (doesFlameExist) {
    if (flameID == 0) {
      if (MQ2) {
        extinguishMQ2();
      }
      if (MQ7){
        extinguishMQ7();
      }
    } else if (flameID == 1) {
      carTurnLeft();
    } else if (flameID == 2) {
      carTurnLeft();
    } else if (flameID == 3) {
      carTurnRight();
    } 
    else {
      if (leftV == 1 && centerV == 0 && rightV == 1) {
        Serial.println("forward");
        carForward();
      } else if (leftV == 0 && centerV == 0 && rightV == 0) {
        Serial.println("finish");
        carStop();
      } else if (leftV == 1 && centerV == 1 && rightV == 1) {
        Serial.println("lost");
        carStop();
      } else if (leftV == 0 && centerV == 0 && rightV == 1) {
        Serial.println("left");
        carTurnLeft();
      } else if (leftV == 1 && centerV == 0 && rightV == 0) {
        Serial.println("rigæht");
        carTurnRight();
      } else if (leftV == 0 && centerV == 1 && rightV == 1) {
        Serial.println("left");
        carTurnLeft();
      } else if (leftV == 1 && centerV == 1 && rightV == 0) {
        Serial.println("right");
        carTurnRight();
      }
    }
  } else {
    carStop();
  }
}

/*
void compareFLAME(int sensorList) {
  int minRead = 4095;
  int minIndex = -1;
  for (int i = 0, i < 4, i++){
    if (sensorList[i] < minRead){
      minRead = sensorList[i];
      minIndex = i;
    }
  }
  return minIndex;
}
*/

void extinguishMQ2() {
  for (pos = 0; pos <= 180; pos += 1) {
		fireExtinguisher1.write(pos);
    delay(15);
	}
	for (pos = 180; pos >= 0; pos -= 1) {
		fireExtinguisher1.write(pos);
		delay(15);
  }
}

void extinguishMQ7() {
  for (pos = 0; pos <= 180; pos += 1) {
		fireExtinguisher2.write(pos);
    delay(15);
	}
	for (pos = 180; pos >= 0; pos -= 1) {
		fireExtinguisher2.write(pos);
		delay(15);
  }
}

void carForward() {
  digitalWrite(Front_L1, LOW);
  digitalWrite(Front_L2, HIGH);
  digitalWrite(Front_R1, HIGH);
  digitalWrite(Front_R2, LOW);

  digitalWrite(Back_L1, LOW);
  digitalWrite(Back_L2, HIGH);
  digitalWrite(Back_R1, HIGH);
  digitalWrite(Back_R2, LOW);
}
void carBack() {
  digitalWrite(Front_L1, HIGH);
  digitalWrite(Front_L2, LOW);
  digitalWrite(Front_R1, LOW);
  digitalWrite(Front_R2, HIGH);

  digitalWrite(Back_L1, HIGH);
  digitalWrite(Back_L2, LOW);
  digitalWrite(Back_R1, LOW);
  digitalWrite(Back_R2, HIGH);  
}
void carTurnLeft() {
  digitalWrite(Front_L1, HIGH);
  digitalWrite(Front_L2, LOW);
  digitalWrite(Front_R1, HIGH);
  digitalWrite(Front_R2, LOW);

  digitalWrite(Back_L1, HIGH);
  digitalWrite(Back_L2, LOW);
  digitalWrite(Back_R1, HIGH);
  digitalWrite(Back_R2, LOW);
}
void carTurnRight() {
  digitalWrite(Front_L1, LOW);
  digitalWrite(Front_L2, HIGH);
  digitalWrite(Front_R1, LOW);
  digitalWrite(Front_R2, HIGH);

  digitalWrite(Back_L1, LOW);
  digitalWrite(Back_L2, HIGH);
  digitalWrite(Back_R1, LOW);
  digitalWrite(Back_R2, HIGH);
}
void carRight() {
  digitalWrite(Front_L1, LOW);
  digitalWrite(Front_L2, HIGH);
  digitalWrite(Front_R1, LOW);
  digitalWrite(Front_R2, HIGH);

  digitalWrite(Back_L1, HIGH);
  digitalWrite(Back_L2, LOW);
  digitalWrite(Back_R1, HIGH);
  digitalWrite(Back_R2, LOW);  
}
void carLeft() {
  digitalWrite(Front_L1, HIGH);
  digitalWrite(Front_L2, LOW);
  digitalWrite(Front_R1, HIGH);
  digitalWrite(Front_R2, LOW);

  digitalWrite(Back_L1, LOW);
  digitalWrite(Back_L2, HIGH);
  digitalWrite(Back_R1, LOW);
  digitalWrite(Back_R2, HIGH);
}
void carStop() {
  digitalWrite(Front_L1, LOW);
  digitalWrite(Front_L2, LOW);
  digitalWrite(Front_R1, LOW);
  digitalWrite(Front_R2, LOW);

  digitalWrite(Back_L1, LOW);
  digitalWrite(Back_L2, LOW);
  digitalWrite(Back_R1, LOW);
  digitalWrite(Back_R2, LOW);
}

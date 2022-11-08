#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
//module BLT HC05/HC06 với ESP8266: chi cần nối chân tx(HC05/HC06) với rx(esp8266)
int speedCar = 0;
int speed_Coeff = 3;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    char data_received;
    // đọc dữ liệu truyền từ HC05/HC06 gán vào biến data_received
    data_received = Serial.read();
    /* 0->9 và q là giá trị tốc độ điều chỉnh trên app 
       F: tiến
       B: lui
       L: xoay trái
       R: xoay phải
       G: tiến trái
       I: tiến phải
       H: lùi trái
       J: lùi phải       
    (các giá trị BLT truyền đi có trong phần Setting của app) */
    if (data_received == '0') {
      speedCar = 400;
    }
    else if (data_received == '1') {
      speedCar = 470;
    }
    else if (data_received == '2') {
      speedCar = 540;
    }
    else if (data_received == '3') {
      speedCar = 610;
    }
    else if (data_received == '4') {
      speedCar = 680;
    }
    else if (data_received == '5') {
      speedCar = 750;
    }
    else if (data_received == '6') {
      speedCar = 820;
    }
    else if (data_received == '7') {
      speedCar = 880;
    }
    else if (data_received == '8') {
      speedCar = 930;
    }
    else if (data_received == '9') {
      speedCar = 980;
    }
    else if (data_received == 'q') {
      speedCar = 1023;
    }
    else if (data_received == 'F') {
      goAhead(speedCar);
    }
    else if (data_received == 'B') {
      goBack(speedCar);
    }
    else if (data_received == 'L') {
      goLeft(speedCar);
    }
    else if (data_received == 'R') {
      goRight(speedCar);
    }
    else if (data_received == 'G') {
      goAheadLeft(speedCar);
    }
    else if (data_received == 'I') {
      goAheadRight(speedCar);
    }
    else if (data_received == 'H') {
      goBackLeft(speedCar);
    }
    else if (data_received == 'J') {
      goBackRight(speedCar);
    }
    else { //data_received == 'S'
      stopRobot();
      //      Serial.print(data_received);
      //      Serial.println("\t- :Stop");
    }
  }
}

// 4 động cơ quay cùng 1 hướng tới trước và với tốc độ được set bằng biến speedCar
void goAhead(int speedCar) {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}
// 4 động cơ quay cùng 1 hướng lùi sau và với tốc độ được set bằng biến speedCar
void goBack(int speedCar) {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}
// 2 động cơ bên phải quay cùng 1 hướng tới trước, 2 động cơ bên trái quay cùng 1 hướng lùi sau và với tốc độ được set bằng biến speedCar
void goLeft(int speedCar) {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}
// 2 động cơ bên trái quay cùng 1 hướng tới trước, 2 động cơ bên phải quay cùng 1 hướng lùi sau và với tốc độ được set bằng biến speedCar
void goRight(int speedCar) {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}
// 4 động cơ quay cùng 1 hướng tới trước, 2 động cơ bên trái chậm hơn 2 động cơ bên phải 
void goAheadLeft(int speedCar) {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}
// 4 động cơ quay cùng 1 hướng tới trước, 2 động cơ bên phải chậm hơn 2 động cơ bên trái 
void goAheadRight(int speedCar) {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
}
// 4 động cơ quay cùng 1 hướng lùi sau, 2 động cơ bên trái chậm hơn 2 động cơ bên phải 
void goBackLeft(int speedCar) {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}
// 4 động cơ quay cùng 1 hướng lùi sau, 2 động cơ bên phải chậm hơn 2 động cơ bên trái 
void goBackRight(int speedCar) {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
}
// 4 động cơ khoongn hoạt động
void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  //  analogWrite(ENA, speedCar);
  analogWrite(ENA, 0);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  //  analogWrite(ENB, speedCar);
  analogWrite(ENB, 0);
}

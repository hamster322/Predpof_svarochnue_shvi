#include <Servo.h>


String recieptStr = "";
boolean recievedFlg;
// пины
#define PIN_NASOS1 2
#define PIN_NASOS2 3
#define PIN_NASOS3 4

#define PIN_MOTOR1_FWD 11 
#define PIN_MOTOR1_BACK 9
#define PIN_MOTOR2_FWD 6
#define PIN_MOTOR2_BACK 5
#define MOTOR_SPEED 200
#define TIME_TO_USER 3000 
#define TIME_TO_FILL 2000 

#define PIN_SERVO_S 12
#define PIN_SERVO_V 13
// количество тиков для наливания разных объемов
#define CNT_10ML 90
#define CNT_20ML 100
#define CNT_30ML 140
#define CNT_40ML 185
#define CNT_50ML 245
#define CNT_60ML 295
#define CNT_80ML 430
// градус поворота крана для перемещения стаканчика
#define SERV_DEGREE 45

Servo servo1;

void setup() {
  Serial.begin(9600);
  servo1.attach(PIN_SERVO_S);    // Инициализация стандартного серийного порта
}

void loop() {
  while (Serial.available() > 0) {         // ПОКА есть что то на вход    
    recieptStr += (char)Serial.read();        // забиваем строку принятыми данными
    recievedFlg = true;                   // поднять флаг что получили данные
    delay(2);                              // ЗАДЕРЖКА. Без неё работает некорректно!
  }

  if (recievedFlg) {                      // если данные получены
  //   Serial.println("Recieved msg:");
  //   Serial.println(recieptStr);
  //   byte lenLst = recieptStr.length() + 1;
  //   char recieptLst[lenLst];
  //   recieptStr.toCharArray(recieptLst, lenLst);
  //   for (int i = 0; i < lenLst; i++) {
  //     Serial.println(recieptLst[i]);
  //   }
    Serial.print("Список рецептов: ");
    Serial.println(recieptStr);               // вывести                         // очистить
    recievedFlg = false;                      // опустить флаг 
    digitalWrite(PIN_SERVO_V, HIGH);
    for (int i = 0; i < recieptStr.length() - 2; i++) {
      servo1.write(i * SERV_DEGREE);
      delay(500);
      if (recieptStr[i] == '1') {
        fillMl(PIN_NASOS1, CNT_50ML, 14 + i, i);
        delay(1000);
      } else if (recieptStr[i] == '2') {
        fillMl(PIN_NASOS2, CNT_10ML, 14 + i, i);
        delay(1000);
      } else if (recieptStr[i] == '3') {
        fillMl(PIN_NASOS3, CNT_40ML, 14 + i, i);
        delay(1000);
      } else if (recieptStr[i] == '4') {
        fillMl(PIN_NASOS1, CNT_80ML, 14 + i, i);
        delay(1000);
        fillMl(PIN_NASOS2, CNT_20ML, 14 + i, i);
        delay(1000);
      } else if (recieptStr[i] == '5') {
        fillMl(PIN_NASOS1, CNT_30ML, 14 + i, i);
        delay(1000);
        fillMl(PIN_NASOS3, CNT_50ML, 14 + i, i);
        delay(1000);
      } else {
        fillMl(PIN_NASOS1, CNT_40ML, 14 + i, i);
        delay(1000);
        fillMl(PIN_NASOS3, CNT_50ML, 14 + i, i);
        delay(1000);
        fillMl(PIN_NASOS2, CNT_10ML, 14 + i, i);
        delay(1000);
      }
    }
    digitalWrite(PIN_SERVO_V, LOW);
    recieptStr = "";
    goToFillSpace();
    Serial.println(analogRead(A2));
    while (analogRead(A0) > 900 || analogRead(A1) > 900 || analogRead(A2) > 900 || analogRead(A3) > 900) {
      delay(1000);
    }
    goToUserSpace();
  }
  delay(100);
}

bool fillMl(int pin, int loopCnt, int pin_conc, int flg) {
  int i = 0;
  int iCur = 0;
  if (flg == 3) {
    while (i < loopCnt) {
      digitalWrite(pin, HIGH);
      delay(10);
      i++;
    }
  }
  else {
    while (analogRead(pin_conc) > 900 && i < loopCnt) {
      digitalWrite(pin, HIGH);
      delay(10);
      i++;
      iCur++;
    }
    digitalWrite(pin, LOW);
    while (analogRead(pin_conc) < 900) {
      delay(100);
    }
    for (int i=0; i < loopCnt - iCur; i++) {
      digitalWrite(pin, HIGH);
      delay(10);
    }
  }
  digitalWrite(pin, LOW);
  if (i == loopCnt - 1) {
    return true;
  } else {
    return false;
  }
}

bool fillMl_V1(int pin, int loopCnt, int pin_conc) {
  int i = 0;
  while (i < loopCnt) {
    digitalWrite(pin, HIGH);
    delay(10);
    i++;
  }
  digitalWrite(pin, LOW);
  if (i == loopCnt - 1) {
    return true;
  } else {
    return false;
  }
}

void goToUserSpace() {

  analogWrite(PIN_MOTOR1_FWD, MOTOR_SPEED);
  analogWrite(PIN_MOTOR1_BACK, 0);
  analogWrite(PIN_MOTOR2_FWD, MOTOR_SPEED);
  analogWrite(PIN_MOTOR2_BACK, 0);
  delay(TIME_TO_USER);
  analogWrite(PIN_MOTOR1_FWD, 0);
  analogWrite(PIN_MOTOR2_FWD, 0);
}

void goToFillSpace() {
  digitalWrite(PIN_MOTOR1_FWD, LOW);
  digitalWrite(PIN_MOTOR1_BACK, HIGH);
  digitalWrite(PIN_MOTOR2_FWD, LOW);
  digitalWrite(PIN_MOTOR2_BACK, HIGH);
  // analogWrite(PIN_MOTOR1_FWD, 0);
  // analogWrite(PIN_MOTOR1_BACK, MOTOR_SPEED);
  // analogWrite(PIN_MOTOR2_FWD, 0);
  // analogWrite(PIN_MOTOR2_BACK, MOTOR_SPEED);
  delay(TIME_TO_FILL);
  // analogWrite(PIN_MOTOR1_BACK, 0);
  // analogWrite(PIN_MOTOR2_BACK, 0);
  digitalWrite(PIN_MOTOR1_BACK, LOW);
  digitalWrite(PIN_MOTOR2_BACK, LOW);
}


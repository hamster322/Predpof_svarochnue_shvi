// test servo
// #include <Servo.h>

// // Servo servo1;
// #define IN_nasos 6
// #define nasos_power 5

// void setup() {
//   //  servo1.attach(6);
//   //  digitalWrite(5, 1);
//   pinMode(IN_nasos, OUTPUT);
//   pinMode(nasos_power, OUTPUT);
// }

// void loop() { 
//   digitalWrite(IN_nasos, HIGH);
//   analogWrite(nasos_power, 55);
//   //  servo1.write(0);
//   //  delay(2000);

//   //  servo1.write(90); 
//   //  delay(2000); 
// }


// test keypad + led

#include <Keypad.h>
#include <LiquidCrystal.h> 

#define PIN_RS 8
#define PIN_EN 9
#define PIN_DB4 10
#define PIN_DB5 11
#define PIN_DB6 12
#define PIN_DB7 13

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

const byte ROWS = 3; //four rows
const byte COLS = 3; //four columns
char keypressed;
//define the cymbols on the buttons of the keypads
char keyMap[ROWS][COLS] = {
{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}
};
byte rowPins[ROWS] = {7, 6, 5};
 //Row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //Column pinouts of thekeypad
Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);



String recieptLst = "";
String validReciept = "123456";

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter reciepts:");
  Serial.begin(9600);
}
void loop () {
  keypressed = myKeypad.getKey();
  if (keypressed) {
    if (validReciept.indexOf(keypressed) != -1) {
      if (recieptLst.length() < 4) {
        recieptLst += keypressed;
        printReciepts();
      }
    } else if (keypressed == '7') {
      recieptLst = "";
      printReciepts();
    } else if (keypressed == '9') {
      if (recieptLst.length() > 0) {
          sendReciepts();
          recieptLst = "";
          printReciepts();
      }
    }
  }
}

// bool isKeyInList(char key) {
//   for (int i = 0; i < pressCnt; i++) {
//     if (recieptLst[i] == key) {
//       return true;
//     }
//   }
//   return false;
// }

void printReciepts() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter reciepts:");
  lcd.setCursor(0, 1);  
  // Отображаем на экране только первые 4 кнопки
  for (int i = 0; i < recieptLst.length(); i++) {
    lcd.print(recieptLst[i]);
    lcd.print(' ');
  }
}

void sendReciepts() {
  for (int i = 0; i < recieptLst.length(); i++) {
    Serial.write(recieptLst[i]);
  }
  Serial.println();
}

// test led display
// #include <LiquidCrystal.h> 

// #define PIN_RS 8
// #define PIN_EN 9
// #define PIN_DB4 10
// #define PIN_DB5 11
// #define PIN_DB6 12
// #define PIN_DB7 13

// LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
 
// void setup() {
//   // Устанавливаем размер экрана
//   // Количество столбцов и строк
//   lcd.begin(16, 2);
//   // Устанавливаем курсор в колонку 0 и строку 0
//   lcd.setCursor(0, 0);
//   // Печатаем первую строку
//   lcd.print("Hello, world!");
//   // Устанавливаем курсор в колонку 0 и строку 1
//   lcd.setCursor(0, 1);
//   // Печатаем вторую строку
//   lcd.print("Do It Yourself");
// }
 
// void loop() {
// }

//test motors

// #define IN1 4
// #define IN2 5
// #define IN3 6
// #define IN4 7

// void setup() {
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);
// }

// void loop() { 
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }
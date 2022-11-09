// LCD 16x2
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define D1 5
#define D2 4

int sda_pin = D1;
int scl_pin = D2;
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD

#include <Servo.h>
#define D5 14  // Servo 1
#define D6 12  // Servo 2
#define D7 13  // Servo 3
#define D8 15  // Servo 4

Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
Servo servo4;  // create servo object to control a servo



#define D3 0  // ledIndikator
const int ledIndikator = D3;
//const int ledHijau  = 12;
//const int ledKuning = 11;
//const int ledMerah = 10;

// Button Pin
#define btnPin 16 // D0


#define BLYNK_PRINT Serial
//// ESP8266
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//// ESP32
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>

void set_lcd() {
  lcd.setCursor(2, 0);
  lcd.print(" IDIFA INDONESIA");
}


void setup() {
  // Serial Monitor  
  Serial.begin(115200);
  Serial.println("Indonesia Digital Farm");   
  
  // LCD
  Wire.begin(sda_pin, scl_pin);
  lcd.begin();
  lcd.backlight();
  
  set_lcd();
  lcd.setCursor(0, 2);
  lcd.print("Semua servo Tertutup");
    
  // Servo
  servo1.attach(D5);
  servo2.attach(D6);
  servo3.attach(D7);
  servo4.attach(D8);
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  // LED
  pinMode(ledIndikator, OUTPUT);
  
  // Button
  pinMode(btnPin, INPUT_PULLUP);  

  char auth[] = "iX5svd_4une1oLhCM2gZBfKJ8K_lzgw_"; //Enter your Blynk auth token
  char ssid[] = "CyberNoob"; //Enter your WIFI name
  char pass[] = "cyb3r53cur1ty"; //Enter your WIFI password

  Blynk.begin(auth, ssid, pass, "blynk.jpnet.co.th", 8080);


}


void loop() {
  Blynk.run();   
  
  set_lcd();  
  
  byte button = digitalRead(btnPin);
//  Serial.println(button);
  
//  if (button == HIGH) {
//    servo1.write(175);
//    servo2.write(175);
//    lcd.clear();
//    set_lcd();
//    lcd.setCursor(0, 2);
//    lcd.print("Semua servo terbuka");
//    digitalWrite(ledIndikator, HIGH);
//    delay(2000);
//  
//  }
//  else {          
//    servo1.write(0);
//    servo2.write(0);
//    lcd.clear();
//    lcd.setCursor(0, 2);
//    lcd.print("Semua servo Tertutup");
//    digitalWrite(ledIndikator, LOW);
//  }

}


BLYNK_WRITE(V0) { 
  
  servo1.write(175);
  lcd.clear();
  set_lcd();
  lcd.setCursor(2, 2);
  lcd.print("Servo 1 Terbuka");
  digitalWrite(ledIndikator, HIGH);
  delay(2000);

  
  servo1.write(0);
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Semua servo Tertutup");
  digitalWrite(ledIndikator, LOW);


}

BLYNK_WRITE(V1) {
  
  servo2.write(175);
  lcd.clear();
  set_lcd();
  lcd.setCursor(2, 2);
  lcd.print("Servo 2 Terbuka");
  digitalWrite(ledIndikator, HIGH);
  delay(2000);

  
  servo2.write(0);
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Semua servo Tertutup");
  digitalWrite(ledIndikator, LOW);
} 

BLYNK_WRITE(V4) {
  
  if (param.asInt() == HIGH) {
    servo1.write(180);
    servo2.write(180);
    lcd.clear();
    set_lcd();
    lcd.setCursor(1, 2);
    lcd.print("Semua servo Terbuka");
    digitalWrite(ledIndikator, HIGH);
  }
  else{
    servo1.write(0);
    servo2.write(0);
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("Semua servo Tertutup");
    digitalWrite(ledIndikator, LOW);
  }
  
}

// Timer
BLYNK_WRITE(V5) {
  servo1.write(180);
  servo2.write(180);
  lcd.clear();
  set_lcd();
  lcd.setCursor(1, 2);
  lcd.print("Semua servo Terbuka");
  digitalWrite(ledIndikator, HIGH);
  delay(2000);
  
  servo1.write(0);
  servo2.write(0);
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Semua servo Tertutup");
  digitalWrite(ledIndikator, LOW);  
}

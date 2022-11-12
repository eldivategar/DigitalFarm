// LCD 16x2
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define D1 5
#define D2 4

int sda_pin = D1;
int scl_pin = D2;
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD


#include <Servo.h>
#define D6 12  // Servo 1
#define D5 14  // Servo 2
#define D4 2   // Servo 3
#define D8 15  // Servo 4

Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
Servo servo4;  // create servo object to control a servo


#define D3 0  // ledIndikator
#define D7 13 // ledIndikator

const int ledIndikator = D7;

// Button Pin
#define btnPin 16 // D0
int buttonPushed;



#define BLYNK_PRINT Serial
//// ESP8266
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#include <WiFiManager.h> 

void set_lcd() {
  lcd.setCursor(2, 0);
  lcd.print(" IDIFA INDONESIA");
  lcd.setCursor(0, 1);
  lcd.print("--------------------");
}

void initialize() {
  
  WiFi.mode(WIFI_STA);

  WiFiManager wm;
  bool res;

  res = wm.autoConnect("Digital Farm"); // password protected ap

  if(!res) {
    Serial.println("Gagal untuk menghubungkan");
        // ESP.restart();
    } 
  else {
        //if you get here you have connected to the WiFi    
    Serial.println("Berhasil terhubung...yeey :)");
   }
}

void setup() {   
  initialize(); 
  
  Serial.begin(115200);  
  
  // LCD
  Wire.begin(sda_pin, scl_pin);
  lcd.begin();
  lcd.backlight();
  
  set_lcd();
  lcd.setCursor(1, 2);
  lcd.print("Semua Tempat Makan");
  lcd.setCursor(5, 3);
  lcd.print("Tertutup !");
    
  // Servo
  servo1.attach(D6);
  servo2.attach(D5);
  servo3.attach(D4);
  servo4.attach(D8);
  
  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);

  // LED
  pinMode(ledIndikator, OUTPUT);
  
  // Button
  pinMode(btnPin, INPUT_PULLUP);  

  char auth[] = "iX5svd_4une1oLhCM2gZBfKJ8K_lzgw_"; //Enter your Blynk auth token
//  char ssid[] = "xixixi"; //Enter your WIFI name
//  char pass[] = "gantengbgt"; //Enter your WIFI password 
  
//  Blynk.begin(auth, ssid, pass, "blynk.jpnet.co.th", 8080);
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str(), "blynk.jpnet.co.th", 8080);


}


void loop() {
  Blynk.run();   
  set_lcd();  
    
}


BLYNK_WRITE(V0) { 
  
  servo1.write(0);
  lcd.clear();
  set_lcd();
  lcd.setCursor(3, 2);
  lcd.print("Tempat Makan 1");
  lcd.setCursor(5, 3);
  lcd.print("Terbuka !");
  delay(2000);

  
  servo1.write(180);
  lcd.clear();
  lcd.setCursor(1, 2);
  lcd.print("Semua Tempat Makan");
  lcd.setCursor(5, 3);
  lcd.print("Tertutup !");
  digitalWrite(ledIndikator, LOW);  

}

BLYNK_WRITE(V1) {
  
  servo2.write(0);
  lcd.clear();
  set_lcd();
  lcd.setCursor(3, 2);
  lcd.print("Tempat Makan 1");
  lcd.setCursor(5, 3);
  lcd.print("Terbuka !");
  digitalWrite(ledIndikator, HIGH);
  delay(2000);

  
  servo2.write(180);
  lcd.clear();
  lcd.setCursor(1, 2);
  lcd.print("Semua Tempat Makan");
  lcd.setCursor(5, 3);
  lcd.print("Tertutup !");
  digitalWrite(ledIndikator, LOW);
} 

BLYNK_WRITE(V4) {
    
  if (param.asInt() == HIGH) {
    servo1.write(0);
    servo2.write(180);
    lcd.clear();
    set_lcd();
    lcd.setCursor(1, 2);
    lcd.print("Semua Tempat Makan");
    lcd.setCursor(5, 3);
    lcd.print("Terbuka !");
    digitalWrite(ledIndikator, HIGH);
    delay(2000);
  }  
  
  else{
    servo1.write(180);
    servo2.write(0);
    lcd.clear();
    lcd.setCursor(1, 2);
    lcd.print("Semua Tempat Makan");
    lcd.setCursor(5, 3);
    lcd.print("Tertutup !");
    digitalWrite(ledIndikator, LOW);
  }
  
}

// Timer
BLYNK_WRITE(V5) {
  servo1.write(0);
  servo2.write(0);
  lcd.clear();
  set_lcd();
  lcd.setCursor(1, 2);
  lcd.print("Semua Tempat Makan");
  lcd.setCursor(6, 3);
  lcd.print("Terbuka !");
  digitalWrite(ledIndikator, HIGH);
  delay(2000);
  
  servo1.write(180);
  servo2.write(180);
  lcd.clear();
  lcd.setCursor(1, 2);
  lcd.print("Semua Tempat Makan");
  lcd.setCursor(5, 3);
  lcd.print("Tertutup !");
  digitalWrite(ledIndikator, LOW);  
}

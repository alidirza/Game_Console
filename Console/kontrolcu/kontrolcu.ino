#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

uint8_t address[6] = { 0x00,0x18,0x91,0xD7,0xBC,0x58 };
 String name = "HC-06";
const char *pin = "1234";
bool connected;
const int joystick_x_pin = A0; 
const int joystick_y_pin = A3;

void setup() {
  pinMode(19,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP);
  pinMode(17,INPUT_PULLUP);
  pinMode(16,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
    delay(1500);
    digitalWrite(LED_BUILTIN,LOW);
Serial.begin(115200);
SerialBT.setPin(pin);
SerialBT.begin("ESP32Master", true);
Serial.println("Kontrolcu acildi. Konsolla baglanti bekleniyor");

 //connected = SerialBT.connect(name);
connected = SerialBT.connect(address);

if(connected) {
Serial.println("Ilk baglanti basarili");
digitalWrite(LED_BUILTIN,HIGH);
delay(250);
digitalWrite(LED_BUILTIN,LOW);
delay(25);

} else {
while(!SerialBT.connected(10000)) {
Serial.println("Baglanti basarisiz. Tekrar deneyiniz");
digitalWrite(LED_BUILTIN,HIGH);
}
}

if (SerialBT.disconnect()) {
Serial.println("Ikinci baglanti baslatiliyor");
digitalWrite(LED_BUILTIN,HIGH);
delay(250);
digitalWrite(LED_BUILTIN,LOW);
}

SerialBT.connect();
delay(5000);
SerialBT.print("T");
}

void loop() {
  digitalWrite(LED_BUILTIN,LOW);

  int x_adc_val, y_adc_val; 
  float x_volt, y_volt;
  x_adc_val = analogRead(joystick_x_pin); 
  y_adc_val = analogRead(joystick_y_pin);
  x_volt = ( ( x_adc_val * 3.3 ) / 4095 );  
  y_volt = ( ( y_adc_val * 3.3 ) / 4095 ); 
  if(x_volt > 3){
    SerialBT.print("d");
    delay(200);
  }
  if(x_volt < 1){
    SerialBT.print("u");
    delay(200);
  }
  if(y_volt > 3){
    SerialBT.print("l");
    delay(200);
  }
  if(y_volt < 1){
    SerialBT.print("r");
    delay(200);
  }

  if (digitalRead(19) == 0){
  SerialBT.print("A");
  delay(100);
 }
 if (digitalRead(18) == 0){
  SerialBT.print("D");
  delay(100);
 }
 if (digitalRead(17) == 0){
  SerialBT.print("B");
  delay(100);
 }
 if (digitalRead(16) == 0){
  SerialBT.print("C");
  delay(100);
 }
/*
if (Serial.available()) {
SerialBT.write(Serial.read());
digitalWrite(LED_BUILTIN,HIGH);
}
*/
if (SerialBT.available()) {
Serial.write(SerialBT.read());
digitalWrite(LED_BUILTIN,HIGH);
}
delay(20);
}
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

SoftwareSerial mySerial(7, 6);
char buttonCommand;
char joystickCommand;
bool isGameOn = false;
bool isConnected = false;
bool done = false;
char lastButtonCommands[11];
int currentArrayElement = 0;
int bsayi = 0;
int menuIndex = 0;
String games[] = {"Pong", "Labirent", "Yilan", "Hiz", "Hafiza", "Kostebek",};

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    delay(1500);
    mySerial.println("Konsol acildi");
    Serial.println("Konsol acildi");
    pinMode(13, OUTPUT);
    lcd.begin();
}

void displayWaitingScreen() {
    lcd.clear();
    printOrta("Baglanti",1);
    printOrta("Bekleniyor",2);
}

void printOrta(String yazi, int sira) {
  lcd.setCursor(0, sira);
  int uzunluk = yazi.length();
  int bosluk = (20 - uzunluk) / 2;
  
  for (int i = 0; i < bosluk; i++) {
    lcd.print(" ");
  }
  
  lcd.print(yazi);
}

void displayMenu() {
    lcd.clear();
    printOrta("Oyun Sec",1);
    printOrta(">" + games[menuIndex],2);
}

void launchSelectedGame() {
  isGameOn = true;
    lcd.clear();
    printOrta("Baslatiliyor",2);
    printOrta("Oyun: " + games[menuIndex],1);
    delay(2000);
    buttonCommand = '\0';

    switch (menuIndex) {
        case 0:
            pongOyunu();
            break;
        case 1:
            labirentOyunu();
            break;
        case 2:
            yilanOyunu();
            break;
    }
}

void pongOyunu(){
  Serial.println("pong");
lcd.clear();
while(isGameOn){
//pong code

//pong code
loop();
  }
}
void labirentOyunu(){
Serial.println("labirent");
lcd.clear();
while(isGameOn){
//labirent code

//labirent code
loop();
  }
}
void yilanOyunu(){
Serial.println("yilan");
lcd.clear();
while(isGameOn){
//yilan code 

//yilan code
loop();
  }
}

void handleJoystickCommand(char command) {
    Serial.print("joystickCommand == ");
    Serial.println(command);
    joystickCommand = command;

    if(isGameOn == false){
      delay(200);
      if (command == 'u' && menuIndex > 0) {
        menuIndex--;
    } else if (command == 'd' && menuIndex < 5) {
        menuIndex++;
    }
    displayMenu();  
    }
}

void loop() {
    digitalWrite(13, LOW);
    if (mySerial.available()) {
        digitalWrite(13, HIGH);
        char receivedData = mySerial.read();

        if (isConnected == false) {
            if (receivedData == 'T') {
                done = false;
                isConnected = true;  
                Serial.println("ok");
                mySerial.println("Test basarili");
                mySerial.println("Baglanti basariyla kuruldu");
            }
        } else if (isConnected == true) {
            
            if (receivedData == 'A' || receivedData == 'B' || receivedData == 'C' || receivedData == 'D') {
                buttonCommand = receivedData;
                Serial.print("buttonCommand = ");
                Serial.println(buttonCommand);

                  if(currentArrayElement < 9){
                    lastButtonCommands[currentArrayElement] = buttonCommand;
                    currentArrayElement++;
                  }else{
                    currentArrayElement = 0;
                    lastButtonCommands[currentArrayElement] = buttonCommand;
                    currentArrayElement++;
                  }

                if (buttonCommand == 'A' && isGameOn == false) {
                    launchSelectedGame();
                }
                if (buttonCommand == 'B' && isGameOn == true){
                int i;
                for (i = 0; i<9; i++) {
                  if(lastButtonCommands[i] == 'B'){
                     bsayi++;
                  }else{
                    bsayi = 0;
                  }
                
                }
                 if (bsayi > 8){
                   bsayi = 0;
                   displayMenu();
                   isGameOn = false;
                }
                }
            } else if (receivedData == 'l' || receivedData == 'r' || receivedData == 'u' || receivedData == 'd') {
                handleJoystickCommand(receivedData);
            }
        }
    }

    if (isConnected == false && !done) {
        displayWaitingScreen();
         done = true;
    } else if (isConnected == true && !isGameOn && !done) {
        displayMenu();
         done = true;
    }

    delay(20);
}

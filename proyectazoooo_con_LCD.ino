#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 10, 11, 12);
#include <Servo.h>
Servo myservo1;
Servo myservo2;
#define outPin 9
#define s0 6
#define s1 5
#define s2 7
#define s3 8

boolean DEBUG = true;

// Variables
int rojo, verde, azul;
String color = "";
long startTiming = 0;
long elapsedTime = 0;

void setup() {
  Serial.begin(9600);
  myservo1.attach(4);//servo amarillo
  myservo1.write(40);
  myservo2.attach(3);//servo verde
  myservo2.write(0);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT);

  // Setting frequency scaling to 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);


 lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor (3,0);
  lcd.print("Bienvenido");
  Serial.println("Bienvenido");
  lcd.setCursor (1,1);
  lcd.print("clasificacion");
  delay(2000);
  lcd.clear();  
  Serial.println("clasificacion por maduracion del platano");
  startTiming = millis();
}


void loop() {
  
  getColor();
  
  if(DEBUG)printData(); 
  elapsedTime = millis()-startTiming; 
  if (elapsedTime > 1000) {
     showDataLCD();
    startTiming = millis();
  }

  if (color == "PLATANO VERDE") {
    myservo1.write(0);
    delay(2000);
  }myservo1.write(40);

  if (color == "PLATANO AMARILLO") {
    myservo2.write(48);
    delay(2000);
  }myservo2.write(0);
}

/* read RGB components */
void readRGB() {
  rojo = 0, verde = 0, azul = 0;

  int n = 10;
  for (int i = 0; i < n; ++i) {
    //leer componente rojo
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    rojo = rojo + pulseIn(outPin, LOW);

    //leer componente verde
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    verde = verde + pulseIn(outPin, LOW);

    //leer componente azul
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    azul = azul + pulseIn(outPin, LOW);
  }
  rojo = rojo / n;
  verde = verde / n;
  azul = azul / n;
}



///***************************************************
//* para ver en monitor serie
//****************************************************/
void printData(void){
  Serial.print("rojo= ");
  Serial.print(rojo);
  Serial.print("   Verde= ");
  Serial.print(verde);
  Serial.print("  azul= ");
  Serial.print(azul);
  Serial.print (" - ");
  Serial.print (color);
  Serial.println (" detectado");
}
///***************************************************
//* mostrar datos cpturados en lcd
//****************************************************/
void showDataLCD(void){
lcd.clear();
lcd.setCursor (0,0);
lcd.print("R");
lcd.print(rojo);
lcd.setCursor (6,0);
lcd.print("v");
lcd.print(verde);
lcd.setCursor (12,0);
lcd.print("a");
lcd.print(azul);  

lcd.setCursor (0,1);
lcd.print("Color: ");  
lcd.print(color);  
}


void getColor() {
  readRGB();

  if (rojo > 45 && rojo < 48  && verde > 45 && verde < 48 && azul > 35 && azul < 38) color = "PLATANO VERDE";
  else if (rojo > 48 && rojo < 53  && verde > 47 && verde < 53 && azul > 36 && azul < 40) color = "PLATANO VERDE";
  else if (rojo > 30 && rojo < 40  && verde > 33 && verde < 43 && azul > 30 && azul < 40) color = "PLATANO VERDE";
  else if (rojo > 20 && rojo < 43  && verde > 25 && verde < 43 && azul > 23 && azul < 40) color = "PLATANO VERDE";
  else if (rojo > 38 && rojo < 43  && verde > 40 && verde < 46 && azul > 32 && azul < 39) color = "PLATANO AMARILLO";
  else if (rojo > 30 && rojo < 40  && verde > 33 && verde < 43 && azul > 30 && azul < 40) color = "PLATANO AMARILLO";
  else if (rojo > 20 && rojo < 43  && verde > 25 && verde < 43 && azul > 23 && azul < 40) color = "PLATANO AMARILLO";



  else  color = "NO_COLOR";


}

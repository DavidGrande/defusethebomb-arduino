#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
const byte ROWS = 4;
const byte COLS = 4;
const char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[COLS] = {38,39,40,41};
byte rowPins[ROWS] = {34,35,36,37};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String rndString;
const String NOMBREJUEGO = "DEFUSE THE BOMB";
String usuario = "";
String respuestaUsuario = "     ";
boolean finJuego = true;
const unsigned int INTERVALO = 100;

int cuentaAtras = 600;
byte relojNum2 = 0;
byte relojNum3 = 6;
byte relojNum4 = 0;
byte relojNum5 = 0;
unsigned long varDifTiempo1 = 0;
unsigned long varDifTiempo2 = 0;
unsigned long varTiempo1, varTiempo2;

void setup() {
  lcd.begin(16, 2);
  //Leds
  pinMode(53,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(49,OUTPUT);
  //Numeros
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  randomSeed(analogRead(A0));
  calcularRandom();
  lcd.print(NOMBREJUEGO);
  lcd.setCursor(0, 1);
  lcd.print("PRESS ANY KEY");
  varTiempo1 = millis();
}

void loop() {
  displayNumbers();
  boolean acierto = false;
  if (!finJuego){
    varTiempo2 = millis();
    varDifTiempo2 = varTiempo2 - varTiempo1;
    if((varDifTiempo2 - varDifTiempo1) >= INTERVALO){ 
      cuentaAtras-=1;
      modificarReloj();
      varDifTiempo1 = varDifTiempo2;
    }
    char customKey = customKeypad.getKey();
    acierto = comprobar();
    if (customKey) {
      switch (customKey) {
      case 'A':
      case 'B':
        break;
      case 'C':
        usuario = "";
        break;
      case '#':
      case '*':
        respuestaUsuario = usuario;
        break;
      case 'D':
        lcd.clear();
        lcd.print(NOMBREJUEGO);
        usuario = usuario.substring(0, usuario.length() - 1);
        break;
      default:
        if (usuario.length() < 5) {
          usuario += customKey;
        }
        break;
      }
      lcd.clear();
      lcd.print(NOMBREJUEGO);
      lcd.setCursor(0, 1);
      lcd.print(usuario);
    }
    if(acierto == true){
      lcd.clear();
      lcd.print("BOMB DEFUSE");
      lcd.setCursor(0, 1);
      lcd.print(usuario);
      finalJuego();
    } 
    else if(cuentaAtras <= 0){
      lcd.clear();
      lcd.print("BOOOOOOOOOOOOOMB");
      lcd.setCursor(0, 1);
      lcd.print("YOU ARE DIE");
      cuentaAtras = 600;
      finalJuego();
    }
  } 
  else if(customKeypad.getKey()!=NULL){
    finJuego = false;
    usuario = "";
    lcd.clear();
    lcd.print(NOMBREJUEGO);
    lcd.setCursor(0, 1);
    lcd.print(usuario);
    relojNum2 = 0;
    relojNum3 = 6;
    relojNum4 = 0;
    relojNum5 = 0;
  }
}

void finalJuego(){
  cuentaAtras = 600;
  finJuego = true;
  delay(5000);
  lcd.clear();
  lcd.print(NOMBREJUEGO);
  lcd.setCursor(0, 1);
  lcd.print("PRESS ANY KEY");
  calcularRandom();
  respuestaUsuario = "";
}

void calcularRandom(){
  int rnd = random(0,99999);
  rndString = String(rnd);
  if(rndString.charAt(0) == '-'){
    rndString = rndString.substring(1,rndString.length());
  }
  if(rndString.length()<5){
    byte n = 5 - rndString.length();
    for(byte i=0;i<n;i++){
      rndString = "0" + rndString;
    }
  }
}

boolean comprobar(){
  boolean acertado = false;
  byte aciertos = 0;
  if(respuestaUsuario.charAt(0) == rndString.charAt(0)){
    digitalWrite(49, HIGH);
    aciertos++;
  } 
  else {
    digitalWrite(49, LOW);
  }
  if(respuestaUsuario.charAt(1) == rndString.charAt(1)){
    digitalWrite(50, HIGH);
    aciertos++;
  } 
  else {
    digitalWrite(50, LOW);
  }
  if(respuestaUsuario.charAt(2) == rndString.charAt(2)){
    digitalWrite(51, HIGH);
    aciertos++;
  } 
  else {
    digitalWrite(51, LOW);
  }
  if(respuestaUsuario.charAt(3) == rndString.charAt(3)){
    digitalWrite(52, HIGH);
    aciertos++;
  } 
  else {
    digitalWrite(52, LOW);
  }
  if(respuestaUsuario.charAt(4) == rndString.charAt(4)){
    digitalWrite(53, HIGH);
    aciertos++;
  } 
  else {
    digitalWrite(53, LOW);
  }
  if(aciertos >= 5){
    acertado = true;
  }
  return acertado;
}

void modificarReloj(){
  relojNum5--;
  if(relojNum5 > 10){
    relojNum5 = 9;
    relojNum4--;
  } 
  else if(relojNum4 > 10){
    relojNum4 = 9;
    relojNum3--;
  } 
  else if(relojNum3 > 10){
    relojNum3 = 5;
  } 
}

void displayNumbers(){
  displayOneNumber(2,relojNum2);
  displayOneNumber(3,relojNum3);
  displayOneNumber(4,relojNum4);
  displayOneNumber(5,relojNum5);
}

void displayOneNumber(byte pos, byte num){
  displayClear();
  switch(pos){
  case 2:
    digitalWrite(2, LOW);
    break;
  case 3:
    digitalWrite(3, LOW);
    break;
  case 4:
    digitalWrite(4, LOW);
    digitalWrite(13, HIGH);
    break;
  case 5:
    digitalWrite(5, LOW);
    break;
  }
  switch(num){
  case 0:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(12, HIGH);
    break;
  case 1:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;
  case 2:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    break;
  case 3:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    break;
  case 4:
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;
  case 5:
    digitalWrite(6, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    break;
  case 6:
    digitalWrite(6, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(12, HIGH);
    break;
  case 7:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;
  case 8:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    break;
  case 9:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    break;
  }
}

void displayClear(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}





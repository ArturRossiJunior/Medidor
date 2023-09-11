#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <dht.h>
#include <RTClib.h>
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

dht DHT;
RTC_DS3231 rtc;

int SensorLuminosidade = A5;
int SensorUmidade = A0;
int enderecoEEPROM = A1;
int sonoro = 6;
int LedTempAlta = 7;
int LedTempBaixa = 8;

int mediaLuminosidade = 0;
int mediaUmidade = 0;
int mediaTemperatura = 0;

//Animação
byte feliz[8] = {
  B11111,
  B00000,
  B11011,
  B00000,
  B10001,
  B01110,
  B11111,
};
//Animação
byte rosto[8] = {
  B00001,
  B00010,
  B00100,
  B00100,
  B00100,
  B00010,
  B00001,
};
//Animação
byte rostodir[8] = {
  B10000,
  B01000,
  B00100,
  B00100,
  B00100,
  B01000,
  B10000,
};

void setup()
{
    lcd.createChar(1, feliz);
   lcd.createChar(2, rosto);
   lcd.createChar(3, rostodir);
  
  Serial.begin(9600);
  
  // Informa se os pinos dos LEDs são de entrada ou saída
  pinMode(LedTempBaixa, OUTPUT);  
  pinMode(LedTempAlta, OUTPUT);
  pinMode(sonoro, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  
  lcd.print("  +Bem Vindo!+");
  
  lcd.setCursor(7,2);
   lcd.write(byte(2));
   lcd.setCursor(8,2);
   lcd.write(byte(1));
   lcd.setCursor(9,2);
   lcd.write(byte(3));
  
  delay(1000);
   for(int posi_LCD = 0; posi_LCD < 50; posi_LCD ++)
  {
     
    lcd.setCursor(16,1);
    lcd.scrollDisplayLeft(); //Essa é a função que faz as letras se deslocarem

    delay(250); // Quanto menor o tempo, mais rápido será o deslocamento
  }
  
  delay(500);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Lum:");
  lcd.setCursor(6,0);
  lcd.print(EEPROM.read(mediaLuminosidade));
  lcd.print("%");   
  
  lcd.setCursor(0,1);
  lcd.print("Tmp:");
  lcd.setCursor(9,1);
  lcd.print(EEPROM.read(mediaTemperatura));
  lcd.print("C"); 

  lcd.setCursor(9,0);
  lcd.print("Umi:");
  lcd.setCursor(15,0);
  lcd.print(EEPROM.read(mediaUmidade));
  lcd.print("%"); 
}

void loop()
{

  //Declaração das variaveis

  int valoresLuminosidade[5] = {};
  int valoresUmidade[5] = {};
  int valoresTemperatura[5] = {};
  int porcentagemUmidade = 0;
  int porcentagemLuminosidade = 0;
  int somaLuminosidade = 0;
  int somaUmidade = 0;
  int somaTemperatura = 0;
 
  DHT.read11(A0);
  delay(1000);
  lcd.noDisplay();
  lcd.display();

  //Calculo da media

  for( int i = 0; i < 5; i += 1 ){
    delay(1000);
    porcentagemLuminosidade = map(analogRead(SensorLuminosidade), 0, 1023, 0, 100);
    valoresLuminosidade[i] = porcentagemLuminosidade;

    porcentagemUmidade = map(analogRead(SensorUmidade), 0, 1023, 0, 100);
    valoresUmidade[i] = porcentagemUmidade;

    valoresTemperatura[i] = DHT.temperature;

    somaLuminosidade += valoresLuminosidade[i];
    somaUmidade += valoresUmidade[i];
    somaTemperatura += valoresTemperatura[i];
   }

   mediaLuminosidade = somaLuminosidade / 6;
   mediaUmidade = somaUmidade / 6;
   mediaTemperatura = somaTemperatura / 6;

   lcd.setCursor(4, 0);
   lcd.print(mediaLuminosidade);

   lcd.setCursor(12,0);
   lcd.print(mediaUmidade);

   lcd.setCursor(5, 1); 
   lcd.print(mediaTemperatura);

   //Validação dos niveis adequados

  if (mediaTemperatura > 25 || mediaUmidade > 50 || mediaLuminosidade > 30) {
      digitalWrite(LedTempBaixa, LOW);
      digitalWrite(LedTempAlta, HIGH);
      tone(6, 800, 1000);
      EEPROM.write(enderecoEEPROM, mediaTemperatura);
      EEPROM.write(enderecoEEPROM, mediaUmidade);
      EEPROM.write(enderecoEEPROM, mediaLuminosidade);
    }
    else if (mediaTemperatura < 15 || mediaUmidade < 30 || mediaLuminosidade < 0) {
      digitalWrite(LedTempBaixa, HIGH);
      digitalWrite(LedTempAlta, LOW);
      tone(6, 800, 1000);
      EEPROM.write(enderecoEEPROM, mediaTemperatura);
      EEPROM.write(enderecoEEPROM, mediaUmidade);
      EEPROM.write(enderecoEEPROM, mediaLuminosidade);

      int sonoroState = digitalRead(6);
      if(sonoroState == HIGH){
        Serial.println("HIGH"); 
      } else{
        Serial.println("LOW");
      }
    }
    else {
      digitalWrite(LedTempBaixa, LOW);
      digitalWrite(LedTempAlta, LOW);
    }
}
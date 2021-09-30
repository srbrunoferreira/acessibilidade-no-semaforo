#include <LiquidCrystal.h>
#define ledVerde 7
#define ledAmarelo 6
#define ledVermelho 10
#define botao 9
#define buzzer 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sinalVerde = 0;
  int flag = 0;
  lcd.print("Siga!");
  while(sinalVerde<20){
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    int lerBotao = digitalRead(botao);
    int fechado = 20;
    delay(500);
    if(lerBotao==LOW && flag==0){
      sinalVerde = sinalVerde + (fechado - sinalVerde)/2;
      flag = 1;
    }
    sinalVerde++;
    if(sinalVerde%2==0){
      Serial.print("Tempo Vermelho= ");
      Serial.println(sinalVerde/2);
      lcd.setCursor(0,1);
      lcd.print(10-sinalVerde/2);
    }

  }
  lcd.setCursor(0,0);
  lcd.print("Atencao!");
  lcd.setCursor(0,1);
   lcd.print("   ");
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, HIGH);
  digitalWrite(ledVermelho, LOW);
  delay(5000);

  int sinalVermelho=0;
  int abrir=20;
  lcd.setCursor(0,0);
  lcd.print("PARE    ");
  while(sinalVermelho<abrir){
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    int lerBotao = digitalRead(botao);
    delay(500);
    if(lerBotao == LOW || flag==1){
      abrir = 40;
      flag = 1;
      tone(buzzer, 500);
    }
    sinalVermelho++;
    if(sinalVermelho%2==0){
      Serial.print("Tempo Vermelho= ");
      Serial.println(sinalVermelho/2);
      lcd.setCursor(0,1);
      lcd.print(abrir/2-sinalVermelho/2);
    }
  }
  noTone(buzzer);
  lcd.setCursor(0,0);
  lcd.clear();
}

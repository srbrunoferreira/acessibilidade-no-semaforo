#include <LiquidCrystal.h>

#define ledVerde 7
#define ledAmarelo 6
#define ledVermelho 10

#define botao 9
#define buzzer 8

#define TEMPO_MAXIMO_NO_VERDE 15

#define TEMPO_MAXIMO_NO_VERMELHO 15
#define TEMPO_EXTRA_NO_VERMELHO 15

#define TEMPO_MAXIMO_NO_AMARELO 2000

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
    lcd.begin(16, 2);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarelo, OUTPUT);
    pinMode(ledVermelho, OUTPUT);

    pinMode(botao, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    int tempoMaximoNoVermelho = TEMPO_MAXIMO_NO_VERMELHO;
    int acionarSistema = false;
    int tempoNoVerde = 1;

    lcdCabecalho("Sinal: verde");
    semaforo(HIGH, LOW, LOW);

    // Semáforo no verde
    while (tempoNoVerde <= TEMPO_MAXIMO_NO_VERDE)
    {
        bool avancarTempo = digitalRead(botao) == LOW;

        delay(500); // Pausa meio segundo e continua o loop.

        if (avancarTempo && acionarSistema == false)
        {
            tempoNoVerde = tempoNoVerde + (TEMPO_MAXIMO_NO_VERDE - tempoNoVerde) / 2;
            tempoMaximoNoVermelho += TEMPO_EXTRA_NO_VERMELHO;
            acionarSistema = true;
        }

        Serial.print("Tempo no verde: ");
        Serial.println(tempoNoVerde);
        lcdTexto(tempoNoVerde);

        tempoNoVerde++;
    }

    delay(1500); // Pausa
    // Semáforo no amarelo
    lcdCabecalho("Sinal: amarelo");
    lcdLimparTexto();

    semaforo(LOW, HIGH, LOW);
    delay(TEMPO_MAXIMO_NO_AMARELO);

    // Semáforo no vermelho
    int tempoNoVermelho = 1;

    lcdCabecalho("Sinal: vermelho");
    semaforo(LOW, LOW, HIGH);

    // Verifica se o botão foi pressionado, se sim aciona o buzzer.
    if (acionarSistema) {
        tone(buzzer, 500, 4000);
    }

    while (tempoNoVermelho <= tempoMaximoNoVermelho)
    {
        delay(500); // Pausa meio segundo e continua o lopp.

        Serial.print("Tempo no vermelho: ");
        Serial.println(tempoNoVermelho);
        lcdTexto(tempoNoVermelho);

        tempoNoVermelho++;
    }

    delay(1500); // Pausa
    lcd.clear();
}

/*
Liga ou desliga os leds.
Respectivamente, verde, amarelo e vermelho.
*/
void semaforo(int verde, int amarelo, int vermelho)
{
    digitalWrite(ledVerde, verde);
    digitalWrite(ledAmarelo, amarelo);
    digitalWrite(ledVermelho, vermelho);
};

// Exibe texto na primeira linha do LCD.
void lcdCabecalho(String texto)
{
    lcd.setCursor(0, 0);
    lcd.print(texto);
}

// Exibe texto na segunda linha do LCD.
void lcdTexto(String texto)
{
    lcd.setCursor(0, 1);
    lcd.print(texto);
}

// Exibe números inteiros na segunda linha do LCD.
void lcdTexto(int texto)
{
    lcd.setCursor(0, 1);
    lcd.print(texto);
}

// Limpa a segunda linha do LCD.
void lcdLimparTexto()
{
    lcd.setCursor(0, 1);
    lcd.print("  ");
}

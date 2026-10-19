#include <Adafruit_NeoPixel.h>

#define PINO_PIR      13
#define PINO_LDR      34
#define PINO_BOTAO    14
#define PINO_RELE     26
#define PINO_LAMPADA  27

#define NUM_PIXELS    16

// Instância da Lâmpada (Anel LED)
Adafruit_NeoPixel lampada(NUM_PIXELS, PINO_LAMPADA, NEO_GRB + NEO_KHZ800);

const int LIMITE_LUMINOSIDADE = 500; 
const unsigned long TEMPO_DESLIGAMENTO = 3000; 

bool modoManual = false;
bool estadoRele = false;
int ultimoEstadoBotao = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(PINO_PIR, INPUT);
  pinMode(PINO_LDR, INPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_RELE, OUTPUT);

  lampada.begin();
  lampada.show(); // Inicia lâmpada apagada

  digitalWrite(PINO_RELE, LOW);
  Serial.println("==================================================");
  Serial.println("  SISTEMA DE ILUMINAÇÃO INTELIGENTE (AUTOMÁTICO)  ");
  Serial.println("==================================================");
}

void acenderLampada(bool ligar) {
  for(int i = 0; i < NUM_PIXELS; i++) {
    if (ligar) {
      lampada.setPixelColor(i, lampada.Color(255, 220, 100)); // Luz amarela forte (3000K)
    } else {
      lampada.setPixelColor(i, lampada.Color(0, 0, 0)); // Apagado
    }
  }
  lampada.show();
}

void loop() {
  unsigned long tempoAtual = millis();

  // 1. Simulação Automática de Presença e Luz (Para Teste Concreto sem Cliques)
  // A cada 12 segundos, simula 5 segundos de presença no ambiente escuro
  bool presencaAuto = digitalRead(PINO_PIR);
  int nivelLuzAuto = analogRead(PINO_LDR);

  // 2. Leitura do Botão Manual
  int leituraBotao = digitalRead(PINO_BOTAO);
  if (leituraBotao == LOW && ultimoEstadoBotao == HIGH) {
    modoManual = !modoManual;
    estadoRele = modoManual;
    Serial.print(">> [MODO MANUAL] ");
    Serial.println(modoManual ? "ATIVADO -> LÂMPADA LIGADA" : "DESATIVADO -> MODO AUTOMÁTICO");
    delay(200);
  }
  ultimoEstadoBotao = leituraBotao;

  // 3. Lógica Automática do ESP32
  if (!modoManual) {
    if (presencaAuto == HIGH && nivelLuzAuto > LIMITE_LUMINOSIDADE) {
      estadoRele = HIGH;
    } else {
      estadoRele = LOW;
    }
  }

  // 4. Acionamento Físico da Carga (Relé + Lâmpada)
  digitalWrite(PINO_RELE, estadoRele ? HIGH : LOW);
  acenderLampada(estadoRele);

  // 5. Relatório Visual no Monitor Serial
  static unsigned long ultimoPrint = 0;
  if (tempoAtual - ultimoPrint >= 1000) {
    ultimoPrint = tempoAtual;
    Serial.print("STATUS LÂMPADA: "); 
    Serial.print(estadoRele ? "[ LIGADA (ACESA) ] " : "[ DESLIGADA ]       ");
    Serial.print("| MODO: "); Serial.print(modoManual ? "MANUAL " : "AUTO   ");
    Serial.print("| LUZ: "); Serial.print(nivelLuzAuto);
    Serial.print(" | PRESENÇA: "); Serial.println(presencaAuto ? "SIM" : "NÃO");
  }
}
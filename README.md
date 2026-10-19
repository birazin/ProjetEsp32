# ProjetEsp32 ⚡
IoT energy monitoring and lighting control system using ESP32 and PZEM-004T sensor.


---

## 📋 Sobre o Projeto

Este projeto consiste num protótipo desenvolvido para feira de tecnologia com o objetivo de monitorizar o consumo elétrico em tempo real e permitir o controlo automatizado/manual de lâmpadas ou aparelhos residenciais.

---

## 🧰 Componentes Utilizados

- **ESP32 DevKit V1 (30 pinos)** - Microcontrolador principal com suporte Wi-Fi/Bluetooth
- **Medidor de Energia PZEM-004T v3.0** com Transformador de Corrente (TC)
- **Sensor de Presença PIR (HC-SR501)**
- **Sensor de Luz LDR / BH1750**
- **Módulo Relé 5V (1 Canal)**
- **Protoboard (830 furos) + Jumpers**
- **Botão Push-Button (4 pinos)**
- **Caixa Hermética ABS + Iluminação de Teste (Soquete E27 e Lâmpada LED)**

---

## 📂 Estrutura de Ficheiros

- `sketch.ino`: Código-fonte principal para a placa ESP32.
- `diagram.json`: Configuração de ligação do circuito (simulação Wokwi).
- `libraries.txt`: Lista de bibliotecas utilizadas.
- `wokwi-project.txt`: Ficheiro de projeto do simulador Wokwi.

---

## 🚀 Como Executar / Simular

1. Clone este repositório:
   ```bash
   git clone [https://github.com/birazin/ProjetEsp32.git](https://github.com/birazin/ProjetEsp32.git)

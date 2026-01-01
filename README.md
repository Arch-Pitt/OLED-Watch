## **Relógio Digital com Arduino e Display OLED**

Um relógio digital simples feito com Arduino Uno e um display OLED 128x64, que mostra hora, minutos, segundos, data e dia da semana em tempo real.

### 🖥️ Sobre o Projeto

Este projeto implementa um relógio totalmente autônomo, sem módulos de relógio externo (RTC). Ele atualiza a hora a cada segundo usando a função millis() do Arduino e exibe as informações no display OLED:

Hora em formato HH:MM:SS

Data completa no formato Dia DD/MM/AAAA

Dia da semana (Domingo a Sábado)

O cálculo do dia da semana é feito usando a fórmula de Zeller, e o código também trata anos bissextos automaticamente.

### ⚙️ Como Funciona

O Arduino controla o display OLED via I2C usando a biblioteca U8g2.

A cada segundo, o relógio incrementa os segundos, minutos e horas.

Ao passar de 23:59:59, o dia, mês e ano são atualizados corretamente, incluindo ajuste para fevereiro em anos bissextos.

O display é atualizado com dois buffers: hora e data, usando fontes diferentes para melhor leitura.

### 🛠️ Componentes

Arduino Uno

Display OLED 128x64 (I2C)

Jumpers para conexão

### 🔧 Bibliotecas Usadas

U8g2
 – para controlar o display OLED
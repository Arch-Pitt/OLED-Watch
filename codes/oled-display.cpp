#include <U8g2lib.h>  // Biblioteca para controlar displays OLED

// Cria objeto para display OLED SSD1306 128x64 via I2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Variáveis para hora
int horas = 12;
int minutos = 0;
int segundos = 0;

// Variáveis para data
int dia = 1;
int mes = 1;
int ano = 2025;

// Dias da semana
const char* diasSemana[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};

// Número de dias em cada mês (índice 0 não usado)
int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Controle do tempo para atualização a cada 1 segundo
unsigned long tempoAnterior = 0;

// ----------------------- FUNÇÕES -----------------------

// Calcula dia da semana usando fórmula de Zeller
int calculaDiaSemana(int d, int m, int y){
  if(m < 3){
    m += 12;
    y -= 1;
  }
  int k = y % 100;
  int j = y / 100;
  int f = d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
  return (f + 6) % 7;  // 0 = Domingo
}

// Retorna true se o ano for bissexto
bool bisexto(int y){
  return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// ----------------------- SETUP -----------------------
void setup() {#include <U8g2lib.h>  // Biblioteca para controlar displays OLED

// Cria objeto para display OLED SSD1306 128x64 via I2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Variáveis para hora
int horas = 12;
int minutos = 0;
int segundos = 0;

// Variáveis para data
int dia = 1;
int mes = 1;
int ano = 2025;

// Dias da semana
const char* diasSemana[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};

// Número de dias em cada mês (índice 0 não usado)
int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Controle do tempo para atualização a cada 1 segundo
unsigned long tempoAnterior = 0;

// ----------------------- FUNÇÕES -----------------------

// Calcula dia da semana usando fórmula de Zeller
int calculaDiaSemana(int d, int m, int y){
  if(m < 3){
    m += 12;
    y -= 1;
  }
  int k = y % 100;
  int j = y / 100;
  int f = d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
  return (f + 6) % 7;  // 0 = Domingo
}

// Retorna true se o ano for bissexto
bool bisexto(int y){
  return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// ----------------------- SETUP -----------------------
void setup() {
  u8g2.begin(); // Inicializa display OLED

  // Ajuste de fevereiro se ano inicial for bissexto
  if(bisexto(ano)) diasMes[2] = 29;
  else diasMes[2] = 28;

  // Valida data inicial
  if(dia > diasMes[mes]) dia = diasMes[mes];
  if(mes > 12) mes = 12;
  if(horas > 23) horas = 23;
  if(minutos > 59) minutos = 59;
  if(segundos > 59) segundos = 59;
}

// ----------------------- LOOP -----------------------
void loop() {
  unsigned long agora = millis();

  // Atualiza o relógio a cada 1 segundo
  if(agora - tempoAnterior >= 1000){
    tempoAnterior = agora;

    segundos++;
    if(segundos >= 60){
      segundos = 0;
      minutos++;
      if(minutos >= 60){
        minutos = 0;
        horas++;
        if(horas >= 24){
          horas = 0;
          dia++;

          // Ajusta fevereiro se ano bissexto
          if(mes == 2){
            if(bisexto(ano)) diasMes[2] = 29;
            else diasMes[2] = 28;
          }

          // Verifica se passou do último dia do mês
          if(dia > diasMes[mes]){
            dia = 1;
            mes++;
            if(mes > 12){
              mes = 1;
              ano++;
            }
          }
        }
      }
    }

    // Formata hora HH:MM
    char buffer1[6]; 
    sprintf(buffer1, "%02d:%02d", horas, minutos);

    // Calcula dia da semana e formata data "Dia DD/MM/AAAA"
    int ds = calculaDiaSemana(dia, mes, ano);
    char buffer2[17]; 
    sprintf(buffer2, "%s %02d/%02d/%04d", diasSemana[ds], dia, mes, ano);

    // Atualiza display OLED
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_profont22_tf);
    u8g2.setCursor(0, 35);
    u8g2.print(buffer1);

    u8g2.setFont(u8g2_font_profont17_tf);
    u8g2.setCursor(0, 55);
    u8g2.print(buffer2);

    u8g2.sendBuffer();
  }
}

  u8g2.begin(); // Inicializa display OLED

  // Ajuste de fevereiro se ano inicial for bissexto
  if(bisexto(ano)) diasMes[2] = 29;
  else diasMes[2] = 28;

  // Valida data inicial
  if(dia > diasMes[mes]) dia = diasMes[mes];
  if(mes > 12) mes = 12;
  if(horas > 23) horas = 23;
  if(minutos > 59) minutos = 59;
  if(segundos > 59) segundos = 59;
}

// ----------------------- LOOP -----------------------
void loop() {
  unsigned long agora = millis();

  // Atualiza o relógio a cada 1 segundo
  if(agora - tempoAnterior >= 1000){
    tempoAnterior = agora;

    segundos++;
    if(segundos >= 60){
      segundos = 0;
      minutos++;
      if(minutos >= 60){
        minutos = 0;
        horas++;
        if(horas >= 24){
          horas = 0;
          dia++;

          // Ajusta fevereiro se ano bissexto
          if(mes == 2){
            if(bisexto(ano)) diasMes[2] = 29;
            else diasMes[2] = 28;
          }

          // Verifica se passou do último dia do mês
          if(dia > diasMes[mes]){
            dia = 1;
            mes++;
            if(mes > 12){
              mes = 1;
              ano++;
            }
          }
        }
      }
    }

    // Formata hora HH:MM
    char buffer1[6]; 
    sprintf(buffer1, "%02d:%02d:%02d", horas, minutos, segundos);

    // Calcula dia da semana e formata data "Dia DD/MM/AAAA"
    int ds = calculaDiaSemana(dia, mes, ano);
    char buffer2[17]; 
    sprintf(buffer2, "%s %02d/%02d/%04d", diasSemana[ds], dia, mes, ano);

    // Atualiza display OLED
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_profont22_tf);
    u8g2.setCursor(0, 35);
    u8g2.print(buffer1);

    u8g2.setFont(u8g2_font_profont17_tf);
    u8g2.setCursor(0, 55);
    u8g2.print(buffer2);

    u8g2.sendBuffer();
  }
}

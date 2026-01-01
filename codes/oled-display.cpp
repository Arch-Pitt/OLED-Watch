#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int horas = 12;
int minutos = 00;
int segundos = 0;
int dia = 01;
int mes = 01;

int ano = 2025;

const char* diasSemana[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};
int diasMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

unsigned long tempoAnterior = 0;

int calculaDiaSemana(int d, int m, int y){
  if(m < 3){
    m += 12;
    y -= 1;
  }
  int k = y % 100;
  int j = y / 100;
  int f = d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
  return (f + 6) % 7;
}

void setup() {
  u8g2.begin(); 
}

void loop() {
  unsigned long agora = millis();
  
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
    
    char buffer1[6]; 
    sprintf(buffer1, "%02d:%02d", horas, minutos);

    int ds = calculaDiaSemana(dia, mes, ano);
    char buffer2[17]; 
    sprintf(buffer2, "%s %02d/%02d/%04d", diasSemana[ds], dia, mes, ano);

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

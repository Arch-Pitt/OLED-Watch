#include <U8g2lib.h>  // Inclui a biblioteca U8g2 para controlar displays OLED

// Cria um objeto para controlar um display OLED SSD1306 128x64 via I2C (hardware I2C)
// U8G2_R0 = rotação do display, U8X8_PIN_NONE = sem pino de reset físico
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Variáveis para armazenar a hora atual
int horas = 12;
int minutos = 0;
int segundos = 0;

// Variáveis para armazenar a data atual
int dia = 1;
int mes = 1;
int ano = 2025;

// Array com os nomes dos dias da semana
const char* diasSemana[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};

// Array com o número de dias de cada mês (diasMes[0] = 0 para simplificação do índice)
int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Armazena o tempo anterior em milissegundos para controlar o "tick" de 1 segundo
unsigned long tempoAnterior = 0;

// Função para calcular o dia da semana usando a fórmula de Zeller
int calculaDiaSemana(int d, int m, int y){
  if(m < 3){  // Ajusta meses de Janeiro e Fevereiro
    m += 12;
    y -= 1;
  }
  int k = y % 100;  // Ano dentro do século
  int j = y / 100;  // Século
  int f = d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
  return (f + 6) % 7;  // Retorna índice do dia da semana (0 = Domingo, 6 = Sábado)
}

void setup() {
  u8g2.begin(); // Inicializa o display OLED
}

void loop() {
  unsigned long agora = millis(); // Tempo atual desde que o Arduino começou em milissegundos

  // Atualiza o relógio a cada 1 segundo
  if(agora - tempoAnterior >= 1000){
    tempoAnterior = agora; // Atualiza o tempo anterior

    segundos++; // Incrementa segundos
    if(segundos >= 60){   // Se passar de 59 segundos, zera e incrementa minutos
      segundos = 0;
      minutos++;
      if(minutos >= 60){  // Se passar de 59 minutos, zera e incrementa horas
        minutos = 0;
        horas++;
        if(horas >= 24){  // Se passar de 23 horas, zera e incrementa dia
          horas = 0;
          dia++;
          if(dia > diasMes[mes]){ // Se passar do último dia do mês
            dia = 1;
            mes++;
            if(mes > 12){ // Se passar de dezembro
              mes = 1;
              ano++;
            }
          }
        }
      }
    }
    
    // Formata hora em string HH:MM
    char buffer1[6]; 
    sprintf(buffer1, "%02d:%02d", horas, minutos);

    // Calcula dia da semana e formata data em string "Dia DD/MM/AAAA"
    int ds = calculaDiaSemana(dia, mes, ano);
    char buffer2[17]; 
    sprintf(buffer2, "%s %02d/%02d/%04d", diasSemana[ds], dia, mes, ano);

    u8g2.clearBuffer(); // Limpa o buffer do display para desenhar a nova tela
    
    // Desenha a hora
    u8g2.setFont(u8g2_font_profont22_tf); // Define a fonte para a hora
    u8g2.setCursor(0, 35);  // Define posição do texto
    u8g2.print(buffer1);     // Escreve hora no display

    // Desenha a data
    u8g2.setFont(u8g2_font_profont17_tf); // Define a fonte para a data
    u8g2.setCursor(0, 55); 
    u8g2.print(buffer2);    // Escreve data no display
    
    u8g2.sendBuffer();      // Envia tudo para o display OLED
  }
}

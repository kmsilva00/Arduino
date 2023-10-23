#include <Wire.h>
#include <LiquidCrystal.h> // Adiciona a biblioteca "LiquidCrystal" ao projeto

LiquidCrystal lcd(12, 13, 7, 6, 5, 4); // Pinagem do LCD

float valor_calibracao = 21.34 + 5.31;   // Fator de calibração

int contagem = 0;           // Variável de contagem
float soma_tensao = 0;      // Variável para soma de tensão
float media = 0;            // Variável que calcula a media
float entrada_A0;           // Variável de leitura do pino A0
float tensao;               // Variável para conversão em tensão
unsigned long tempo;        // Float tempo

void setup() {
  lcd.begin(16, 2);             // Inicializa todos os caracteres
  inicio ();
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  soma_tensao = 0;   // Inicia soma_tensão em 0
  contagem = 0;      // Inicia a contagem em 0

  while (contagem < 10) {                   // Executa enquanto contagem menor que 10
    tempo = millis();                       // Define o tempo em microssegundos
    entrada_A0 = analogRead(A25);            // Lê a entrada analógica
    tensao = (entrada_A0 * 3.3) / 1024.0;   // Converte em tensão, o valor lido
    soma_tensao = (soma_tensao + tensao);   // Soma a tensão anterior com a atual
    contagem++;                             // Soma 1 à variável de contagem
    delay(100);                             // Aguarda para próxima leitura
  }

  media = soma_tensao / 10;                 // Calcula a média das leituras

  float valor_pH = -5.70 * media + valor_calibracao;    // Calcula valor de pH

  lcd.clear();              // Limpa o display
  lcd.setCursor(2, 0);      // 2 = 2 colunas para a direita. 0 = Primeira linha
  lcd.print("Valor do pH:"); // Imprime um texto

  if (valor_pH < 10)
    lcd.setCursor(6, 1);
  else
    lcd.setCursor(5, 1);      // 2 = 2 colunas para a direita. 0 = Primeira linha
  lcd.print(valor_pH); // Imprime um texto
  Serial.println(valor_pH);

  delay(1000);                    // Aguarda para próxima leitura
  Serial.println(valor_pH);

}

void inicio ()                // teste de rolagem de mensagem
{
  lcd.setCursor(0, 0);           // selecionando coluna 16 e linha 1
  lcd.print("M"); 
  delay (200);
  lcd.print("e"); 
  delay (200);
  lcd.print("d"); 
  delay (200);
  lcd.print("i"); 
  delay (200);
  lcd.print("d"); 
  delay (200);
  lcd.print("o"); 
  delay (200);
  lcd.print("r"); 
  delay (200);
  lcd.print(" "); 
  delay (200);
  lcd.print("d"); 
  delay (200);
  lcd.print("e"); 
  delay (200);
  lcd.print(" "); 
  delay (200);
  lcd.print("p"); 
  delay (200);
  lcd.print("H"); 
  delay (200);
  lcd.print(":"); 
  delay (200);
}
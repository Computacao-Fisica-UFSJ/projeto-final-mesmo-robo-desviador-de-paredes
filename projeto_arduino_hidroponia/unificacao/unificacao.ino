#include <Wire.h> 
#include <rgb_lcd.h>
#include <Servo.h>
#include <DHT.h> 

#define DHTTYPE DHT22

// Pinos 
#define pinoLDR A0
#define pinoDHT A1
#define pinoServo 6

//Constantes de tempo
#define intervaloTempo 2000

// Variáveis
int valorLDR = 0;
float valorTempAr = 0.0;
float valorUmidade = 0.0;
int intensidadeLuz = 0;

// variáveis de tempo
unsigned long tempoAtual;
unsigned long tempoAnterior = 0;

//Objetos
Servo servo;
rgb_lcd LCD;
DHT dht(pinoDHT, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  pinMode(pinoLDR, INPUT);

  dht.begin();
  LCD.begin(16, 2);
  LCD.setRGB(255, 255, 255);
  servo.attach(pinoServo, 500, 2500);

  // --- CONFIGURAÇÃO INICIAL DA TELA (Labels Fixos) ---
  // Limpamos a tela uma vez
  LCD.clear();
  
  // Linha 0: Temperatura
  LCD.setCursor(0, 0); 
  LCD.print("T:    U: "); // Escreve o rótulo fixo
  
  // Linha 1: Luz
  LCD.setCursor(0, 1);
  LCD.print("Luz: ");     // Escreve o rótulo fixo
}

void loop()
{  
  tempoAtual = millis();
  
  //Calculo do tempo com millis
  if(tempoAtual - tempoAnterior >= intervaloTempo){
    tempoAnterior = tempoAtual;
    
    // 1. Leitura dos Sensores
    valorTempAr = dht.readTemperature();
    valorUmidade = dht.readHumidity();
    valorLDR = analogRead(pinoLDR);
    intensidadeLuz = map(valorLDR, 0, 1023, 1, 100);
  
    // 2. Atualização no LCD (Sem Scroll)

    // A função isnan() verifica se o valor "Não é um Número"
    if (isnan(valorTempAr) || isnan(valorUmidade)) {

      LCD.clear();
      Serial.println("FALHA AO LER O DHT!");
      LCD.setRGB(255, 0, 0); // Tela Vermelha
      LCD.setCursor(2, 0);
      LCD.print("Erro");
      LCD.setCursor(8, 0);
      LCD.print("Sensor");
      
    }else{
      
      // Atualiza Temperatura (Linha 0, Coluna 2 - logo após "T: ")
      LCD.setCursor(2, 0);
      LCD.print((int)valorTempAr); 
      LCD.print("C "); // O espaço extra limpa sujeira se o número diminuir (de 100 pra 99)
  
      //Atualiza umidade (Linha)
      LCD.setCursor(8, 0);
      LCD.print((int)valorUmidade);
      LCD.print("% "); // Espaço extra para limpeza
    
      // Atualiza Luz (Linha 1, Coluna 5 - logo após "Luz: ")
      LCD.setCursor(5, 1);
      LCD.print(intensidadeLuz);
      LCD.print("% "); // Espaço extra para limpeza
  
      //Muda a cor do display caso as variáveis de risco estejam no limite
      if(valorTempAr > 30.0 || valorUmidade < 40.0){
       LCD.setRGB(255, 0, 0);
      }else{
        LCD.setRGB(255, 255, 255);
      }
      
    }
  
    // 3. Serial e Servo
    Serial.print("Temp: ");
    Serial.print(valorTempAr);
    Serial.print(" | Umidade: ");
    Serial.println(valorUmidade);
    Serial.print(" | Luz: ");
    Serial.println(intensidadeLuz);
    
    servo.write(90);
  }
}

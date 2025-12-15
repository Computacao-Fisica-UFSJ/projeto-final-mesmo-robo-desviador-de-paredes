#include <Wire.h> 
#include <rgb_lcd.h>
#include <Servo.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTTYPE DHT22

// Pinos 
#define pinoRele 2
#define pinoLDR A0
#define pinoNivelAgua A2
#define pinoDHT 7
#define pinoServo 6
#define pinoTempAgua 8

//Constantes de tempo
#define intervaloTempo 2000
#define intervaloServo 2000
#define intervaloRele 4000

// Variáveis
int valorLDR = 0;
int valorNivel = 0;
float valorTempAr = 0.0;
float valorUmidade = 0.0;
float valorTempAgua = 0.0;
int intensidadeLuz = 0;
int angulo = 0;
int porcentagemNivel = 0;
int estadoRele = 0;

// variáveis de tempo
unsigned long tempoAtual;
unsigned long tempoAnterior = 0;
unsigned long tempoAnteriorServo = 0;
unsigned long tempoAnteriorRele = 0;

//Objetos
Servo servo;
rgb_lcd LCD;
DHT dht(pinoDHT, DHTTYPE);
OneWire sensorTemp(pinoTempAgua);
DallasTemperature sensors(&sensorTemp);

//Funções
void controleServo(){
// Aguarda 4 segundo antes de iniciar o próximo ciclo

  
  if(intensidadeLuz < 65 && angulo < 90){
    if(tempoAtual - tempoAnteriorServo >= intervaloServo){
      tempoAnteriorServo = tempoAtual;
      angulo+=2;
      servo.write(angulo);
    }
  }else if(intensidadeLuz > 85 && angulo > 45){
    if(tempoAtual - tempoAnteriorServo >= intervaloServo){
      tempoAnteriorServo = tempoAtual;
      angulo-=2;
      servo.write(angulo);
    }
  }
}

void setup()
{
  Serial.begin(9600);

  //Seta os pinos
  pinMode(pinoRele,OUTPUT);
  pinMode(pinoLDR, INPUT);
  pinMode(pinoNivelAgua, INPUT);
  dht.begin();
  sensors.begin();
  LCD.begin(16, 2);
  LCD.setRGB(255, 255, 255);
  servo.attach(pinoServo, 500, 2500);

  // --- CONFIGURAÇÃO INICIAL DA TELA (Labels Fixos) ---
  // Limpamos a tela uma vez
  LCD.clear();
  
  // Linha 0: Temperatura
  LCD.setCursor(0, 0); 
  LCD.print("T:     U: "); // Escreve o rótulo fixo
  
  // Linha 1: Luz
  LCD.setCursor(0, 1);
  LCD.print("N:     TA: ");     // Escreve o rótulo fixo
  servo.write(0);
}

void loop()
{  
  tempoAtual = millis();
  
  //Calculo do tempo com millis
  if(tempoAtual - tempoAnterior >= intervaloTempo){
    tempoAnterior = tempoAtual;

    sensors.requestTemperatures();
    
    // 1. Leitura dos Sensores
    valorTempAr = dht.readTemperature();
    valorNivel = analogRead(pinoNivelAgua);
    valorUmidade = dht.readHumidity();
    valorTempAgua = sensors.getTempCByIndex(0);
    valorLDR = analogRead(pinoLDR);
    intensidadeLuz = map(valorLDR, 0, 1023, 1, 100);
    porcentagemNivel = map(valorNivel, 0, 650, 0, 100);
  
    // 2. Atualização no LCD (Sem Scroll)

    // A função isnan() verifica se o valor "Não é um Número"
    if (isnan(valorTempAr) || isnan(valorUmidade)) {
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
  
      //Atualiza umidade (Linha 0, Coluna 8 - logo após "U: ")
      LCD.setCursor(9, 0);
      LCD.print((int)valorUmidade);
      LCD.print("% "); // Espaço extra para limpeza
    
      // Atualiza Luz (Linha 1, Coluna 2 - logo após "L: ")
      LCD.setCursor(2, 1);
      LCD.print(porcentagemNivel);
      LCD.print("% "); // Espaço extra para limpeza

      //Atualiza a temperatura da agua (Linha 1, Coluna 9 - logo após "TA: ")
      LCD.setCursor(10, 1);
      LCD.print((int)valorTempAgua);
      LCD.print("C "); // Espaço extra para l
      
  
      //Muda a cor do display caso as variáveis de risco estejam no limite
      if(valorTempAr > 40.0 || valorUmidade < 40.0 || valorTempAgua > 30 || porcentagemNivel < 20){
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
    Serial.print("Nivel de Agua: ");
    Serial.println(valorNivel);
    Serial.print("Porcentagem:");
    Serial.println(porcentagemNivel);
    Serial.print(" | Temperatura Agua: ");
    Serial.println(valorTempAgua);
    Serial.print(" | luz: ");
    Serial.print(intensidadeLuz);
    Serial.print(" | Angulo: ");
    Serial.println(angulo);
  }
  //codigo para ligar e desligar o relé
  if(tempoAtual - tempoAnteriorRele >= intervaloRele){       
    tempoAnteriorRele = tempoAtual;

    if (estadoRele == 0){
      digitalWrite(pinoRele,HIGH);
      estadoRele = 1;
    }
    else if(estadoRele == 1){
      digitalWrite(pinoRele,LOW);
      estadoRele = 0;
    }
  }
  controleServo();
}

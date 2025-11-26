/* Pinos correspondentes ao sensor */
#define sensorvcc 2     /*Define vcc como pino 2 */ 
#define sensorsinal A1  /*Define sinal como pino A1 */ 

/* Declara variável inteira para armazenamento dos dados */
int val = 0;

void setup() { /*abre laço de configuração*/
  /* define 2 como pino de saída do Arduino */
  pinMode(sensorvcc, OUTPUT);

  digitalWrite(sensorvcc, LOW); /* vcc tem nível lógico baixo até que haja alguma variação na leitura */
  Serial.begin(9600); /* Baudrate de 9600 */
}

void loop() { /*laço de repetição */
  /*variável level é igual a leitura do sensor */
  int level = readSensor(); 
  /*printa o nível da água no monitor serial */
  Serial.print("Nível de água: "); /*printa o "Nível da água: " no monitor serial */
  Serial.println(level); /*printa o nível da água no monitor serial */
  delay(1000);  /*Atraso de 1s entre leituras*/
}

/* leitura do sensor */
int readSensor() {  
digitalWrite(sensorvcc, HIGH);  /* alimenta o sensor */
delay(10);              /* espera 10ms */
val = analogRead(sensorsinal);    /* Realiza a leitura analógica do sinal do sensor */
digitalWrite(sensorvcc, LOW);   /* Desliga o sensor */
return val;             /* envia leitura */
}

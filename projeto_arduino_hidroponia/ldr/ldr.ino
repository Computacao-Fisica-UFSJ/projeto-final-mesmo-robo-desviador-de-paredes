int ldr = A0;//Atribui A0 a variável ldr
int valorldr = 0;//Declara a variável valorldr como inteiro

void setup() {
  pinMode(ldr, INPUT);//Define ldr (pino analógico A0) como saída
  Serial.begin(9600);//Inicialização da comunicação serial, com taxa de transferência em bits por segundo de 9600
}
void loop() {
   valorldr=analogRead(ldr);//Lê o valor do sensor ldr e armazena na variável valorldr
   Serial.print("Valor lido pelo LDR = ");//Imprime na serial a mensagem Valor lido pelo LDR
   Serial.println(valorldr);//Imprime na serial os dados de valorldr
}

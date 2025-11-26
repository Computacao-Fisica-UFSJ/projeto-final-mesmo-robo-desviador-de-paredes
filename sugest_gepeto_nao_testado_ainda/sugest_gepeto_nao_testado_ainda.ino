/* Leitura de temperatura usando um termistor */

// Conexão do termistor
const int pinTermistor = A1;

// Parâmetros do termistor (ajustados para um valor mais comum de beta)
const double beta = 3950.0;    // Valor de beta do termistor (ajustado para 3950, caso o seu seja diferente)
const double r0 = 10000.0;     // Resistência do termistor a 25°C (em Ohms)
const double t0 = 273.0 + 25.0; // Temperatura de referência em Kelvin (25°C)
const double rx = r0 * exp(-beta / t0); // Resistência do termistor a 25°C

// Parâmetros do circuito
const double vcc = 5.0;    // Tensão de alimentação
const double R = 10000.0;  // Resistência de referência (agora 10kΩ, se você usou esse valor)

// Número de amostras na leitura
const int nAmostras = 5;

// Iniciação
void setup() {
  Serial.begin(9600);           // Inicia comunicação serial a 9600 bps
  pinMode(pinTermistor, INPUT); // Configura o pino do termistor como entrada
}

// Laço perpétuo
void loop() {
  // Leitura do sensor - somando várias amostras
  int soma = 0;
  for (int i = 0; i < nAmostras; i++) {
    soma += analogRead(pinTermistor); // Lê o valor do termistor
    delay(10); // Delay de 10ms entre as leituras
  }

  // Determina a tensão média
  double v = (vcc * soma) / (nAmostras * 1024.0); 

  // Calcula a resistência do termistor (rt)
  double rt = (vcc * R) / v - R;

  // Calcula a temperatura em Kelvin usando a equação de Steinhart-Hart
  double t = beta / log(rt / rx); 

  // Converte a temperatura de Kelvin para Celsius
  double temperaturaCelsius = t - 273.0; 

  // Exibe a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperaturaCelsius, 2);  // Exibe com 2 casas decimais
  Serial.println(" °C");

  // Dá um tempo entre leituras (10 segundos)
  delay(10000);
}

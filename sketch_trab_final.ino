
//Simulando a câmera de ré de um carro usando o sensor de distãncia HC-SR04 e um Buzzer ativo 5v

int PinTrigger = 7;   // pino usado para disparar os pulsos do sensor
int PinEcho = 6;       // pino usado para ler a saida do sensor
float TempoEcho = 0;   // variável tempo do eco
const float velocidadeSom_mps = 340;   // em metros por segundo
const float velocidadeSom_mpus = 0.000340;    // em metros por microsegundo
const int pinoBuzzer = 2; //pino usado para disparar os pulsos do buzzer
float distancia;//em centimetros
float frequencia;//em Hz

void setup(){
pinMode(PinTrigger, OUTPUT);   // configura pino Trigger como saída
digitalWrite(PinTrigger, LOW);   // pino trigger - nível baixo
pinMode(PinEcho, INPUT);     // configura pino ECHO como entrada
Serial.begin(9600);   // inicializa monitor serial 9600 Bps (velocidade)
delay(100);   // atraso de 100 milisegundos
}

void loop(){
DisparaPulsoUltrassonico();     // dispara pulso ultrassonico
TempoEcho = pulseIn(PinEcho, HIGH);   // mede duração do pulso HIGH de eco em microssegundos
distancia=CalculaDistancia(TempoEcho) * 100; //calculo da distancia

Serial.print("Distancia em metros: ");    // mostra no monitor serial
Serial.println(distancia/100);   // mostra o calculo de distancia em metros
Serial.print("Distancia em centimentros: ");    // mostra no monitor serial
Serial.println(distancia); // mostra o calculo de distancia em cm

if(distancia>0 && distancia<=30){ //se a distancia estiver em 0 e 30(inclusive)
  Serial.println("Objeto detectado");// mostra no monitor serial
  frequencia=1350-(distancia*30);//calcula a frequencia do buzzer de acordo com a distancia
  tone(pinoBuzzer,frequencia);//ativa o buzzer
  Serial.println("Frequencia:");// mostra no monitor serial
  Serial.println(frequencia);// mostra o calculo da frequencia
  }
  else{
    Serial.println("Objeto não detectado");// mostra no monitor serial
    noTone(pinoBuzzer);//desativa o buzzer
  }
Serial.println("\n");// pula linha
delay(500);   // atraso de 0.5 segundos
}

void DisparaPulsoUltrassonico()
{
digitalWrite(PinTrigger, HIGH);   // pulso alto de Trigger
delayMicroseconds(10);     // atraso de 10 milisegundos
digitalWrite(PinTrigger, LOW);   // pulso baixo de Trigger
}
float CalculaDistancia(float tempo_us)
{
return ((tempo_us * velocidadeSom_mpus) / 2 );   // calcula distancia em metros
}

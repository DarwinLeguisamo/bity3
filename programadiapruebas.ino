#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
int distanciA=200 ;
int coso = 0;

float valor = 0;

float angulo;
// [5][4][-] [/][/] [-][3][2] analogicos
// [8][7][-] [/][/] [-][2][1] sensor
// izq                    der
int analog[]={A2,A3,A4,A5};
int DirA=12;
int DirB=13;
int PotA=3;
int PotB=11;
int suma=0;
int umbral=750;
int N2=0;
int N3=0;
int N4=0;
int N5=0;
int B2=0;
int B3=0;
int B4=0;
int B5=0;
int U2=0;
int U3=0;
int U4=0;
int U5=0;
int A2v;
int A3v;
int A4v;
int A5v;

void setup() {
  pinMode(4, OUTPUT); //trig adelante
  pinMode(7, INPUT);
  pinMode(5, OUTPUT); //trig costado
  pinMode(6, INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  brazo.attach(8);
  pinza.attach(10);
  mano.attach(9); // indico donde esta mi servo conectado
  brazo.write(90);
  mano.write(90);
  pinza.write(90);
  delay(500);
  pinMode(DirA,OUTPUT);
  pinMode(DirB,OUTPUT);
  pinMode(PotA,OUTPUT);
  pinMode(PotB,OUTPUT);

 for(int i=0;i<20;i++){
  N2 =N2+analogRead(analog[0]) ; 
  N3 =N3+analogRead(analog[1]) ; 
  N4 =N4+analogRead(analog[2]) ; 
  N5 =N5+analogRead(analog[3]) ; 
  delay(100);
}

N2=N2/20;
N3=N3/20;
N4=N4/20;
N5=N5/20;
adelante(80,80);
delay(500);
 for(int i=0;i<20;i++){
  B2 =B2+analogRead(analog[0]) ; 
  B3 =B3+analogRead(analog[1]) ; 
  B4 =B4+analogRead(analog[2]) ; 
  B5 =B5+analogRead(analog[3]) ; 
  delay(100);
}

B2=B2/20;
B3=B3/20;
B4=B4/20;
B5=B5/20;
U2=(B2+N2)/2;
U3=(B3+N3)/2;
U4=(B4+N4)/2;
U5=(B5+N5)/2;
distanciA=mirar(90);
atras(80, 80);
delay(2150);
parar();
}
//tx azul va al 0 d la leonardo
//rx verde va al 1 d la leonardo
//azul en tx verde en rx en la micro

void loop(){
distanciA=mirar(90);                                  
/*if (!(analogRead(analog[1]) < U3) && !(analogRead(analog[2]) < U4) && !(analogRead(analog[0]) < U2) && !(analogRead(analog[3]) < U5)){
    seguirlinea();
  } else{
   // parar();
 
if (distanciA < 100){
      agarrar();
    }
  
}*/
}


void calibrarpololu(){
  while (true){
    A2v = analogRead(analog[0]);
    A3v = analogRead(analog[1]);
    A4v = analogRead(analog[2]);
    A5v = analogRead(analog[3]);

    Serial.print("A2: ");
    Serial.println(A2v);
    delay(500);
    Serial.print("A3: ");
    Serial.println(A3v);
    delay(500);
    Serial.print("A4:");
    Serial.println(A4v);
    delay(500);
    Serial.print("A5: ");
    Serial.println(A5v);
    delay(500); 
  }
}

void Umbral() {
  while (true){
    A2v = analogRead(analog[0]);
    A3v = analogRead(analog[1]);
    A4v = analogRead(analog[2]);
    A5v = analogRead(analog[3]);

    Serial.print("A2: ");
    Serial.print(A2v);
    Serial.print("..U2: ");
    Serial.println(U2);
    delay(500);
    Serial.print("A3: ");
    Serial.print(A3v);
    Serial.print("..U3: ");
    Serial.println(U3);
    delay(500);
    Serial.print("A4:");
    Serial.print(A4v);
     Serial.print("..U4: ");
    Serial.println(U4);
    delay(500);
    Serial.print("A5: ");
    Serial.print(A5v);
     Serial.print("..U5: ");
    Serial.println(U5);
    delay(500); 
  delay(1000);
  }
}

void derecha(int i,int d){
    digitalWrite(DirA,LOW);
    digitalWrite(DirB,HIGH);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  }

void izquierda(int i,int d ){
    digitalWrite(DirA,HIGH);
    digitalWrite(DirB,LOW);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  }

void adelante(int i,int d ){
    digitalWrite(DirA,LOW);
    digitalWrite(DirB,LOW);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  }

void atras(int i,int d ){
    digitalWrite(DirA,HIGH);
    digitalWrite(DirB,HIGH);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  }

void parar(){
    digitalWrite(DirA,LOW);
    digitalWrite(DirB,HIGH);
    analogWrite(PotA,0);
    analogWrite(PotB,0);
  }

void aumentar_angulo(int angulo, Servo servo,int tiempo){
  int actual=servo.read();
  while(actual<angulo){
    actual=actual+3;
     servo.write(actual);
     delay(tiempo);
  }
}

void disminuir_angulo(int angulo, Servo servo,int tiempo){
  int actual=servo.read();
  while(actual>angulo){
    actual=actual-3;
     servo.write(actual);
     delay(tiempo);
  }
}



int distancia(int TriggerPin, int EchoPin) { 
  long duration, distanceCm;

  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration*10/292/2;   //convertimos a distancia, en cm
  return distanceCm;
}

void calibrarultras() {
  Serial.print("Derecha: ");
  Serial.println(distancia(4,7));
  delay(250);
  Serial.print("Izquierda: ");
  Serial.println(distancia(5,6));
  delay(250);
}
void agarrar(){
  aumentar_angulo(190,mano,50);
  aumentar_angulo(160,brazo,50);
  disminuir_angulo(5,pinza,50);
  disminuir_angulo(90,mano,50);
}

void soltar(){
  aumentar_angulo(90,pinza,50);
  disminuir_angulo(90,mano,50);
  disminuir_angulo(90,brazo,50);
}

int canasta(){
 disminuir_angulo(55,brazo,50);
 disminuir_angulo(50,mano,50);
 aumentar_angulo(90,pinza,50);
}

void seguirlinea(){
  if (!(analogRead(analog[1]) < U3) && !(analogRead(analog[2]) < U4) && !(analogRead(analog[0]) < U2) && !(analogRead(analog[3]) < U5)){ // Ningún sensor ve la línea
    adelante(100, 100);
    //Serial.println("adelante");
  }
else{
  if ((analogRead(analog[1]) < U3) && (analogRead(analog[2]) < U4) && (analogRead(analog[0]) < U2) && (analogRead(analog[3]) < U5)){ // Ningún sensor ve la línea
    adelante(100, 100);}

  if (analogRead(analog[3]) > U5){ // linea muy a la izq
    izquierda(170, 170);
    delay(50);
    if (analogRead(analog[3]) > U5){ // linea muy a la izq
    izquierda(170, 170);// vulevo a chequear
    delay(30);}
    //Serial.println("derecha");
  }
  if ((analogRead(analog[2]) > U4) && (analogRead(analog[3]) > U5)){
    adelante(60, 200);
  }
  if (((analogRead(analog[2]) > U4)&& !(analogRead(analog[3]) > U5))){ // linea un poco a la izq
    adelante(75, 110);
    //Serial.println("derecha suave");
  }
  if((analogRead(analog[1]) > U3) &&  !(analogRead(analog[0]) > U2)){ // linea un poco a la der
    adelante(110, 75); 
    //Serial.println("izquierda suave");
    }
  if((analogRead(analog[0]) > U2) && (analogRead(analog[1]) > U3)){
    adelante(200, 60);
  }
  if (analogRead(analog[0]) > U2){ // linea muy a la der
    derecha(170, 170);
    delay(50);
      if (analogRead(analog[0]) > U2){ // linea muy a la der
      derecha(170, 170);
       delay(30);}
    //Serial.println("izquierda");
  }
}
}

// ---------- ENVIAR ----------
void enviarEntero(char letra, long n) {
  Serial1.print(letra);
  Serial1.print(n);
  Serial1.print('\n');
}

void enviarReal(char letra, float x) {
  Serial1.print(letra);
  Serial1.print(x, 2);        // 2 decimales (podés poner más)
  Serial1.print('\n');
}

void enviar(char letra) {     // un carácter solo, como antes
  Serial1.print(letra);
  Serial1.print('\n');
}

// ---------- RECIBIR ----------
// Devuelve la letra del mensaje cuando llega uno completo, o 0 si todavía no.
// El número que venía con la letra queda guardado en la variable global "valor".


char recibir() {
  static char buf[16];
  static byte n = 0;

  while (Serial1.available() > 0) {
    char c = Serial1.read();
    if (c == '\n') {                  // terminó un mensaje
      buf[n] = 0;
      n = 0;
      if (buf[0] == 0) return 0;      // línea vacía, se ignora
      valor = atof(buf + 1);          // lo que viene después de la letra
      return buf[0];                  // la letra
    }
    if (c != '\r' && n < sizeof(buf) - 1) buf[n++] = c;
  }
  return 0;                           // no llegó nada completo
}

int mirar(float A){
  enviarReal('A', A);
  delay(50);
  char c = recibir();
    distanciA = (int)valor;
    delay(10);
    //Serial.print("Distancia: ");
    //Serial.println(distanciA);
 return (int)valor;;
}














/*
int error(){
  
  int suma=0;
  if ((D[0]!=1)&&(D[1]!=1)&&(D[2]!=1)&&(D[3]!=1)){
    suma=0;
    return suma;}
  else{
    if ((D[0]==1)&&(D[1]!=1)){
      suma=200;
      return suma;
      }
    if((D[0]==1)&&(D[1]==1)){
      suma=75;
      return suma;
      }
    if((D[1]==1)&&(D[0]!=1)){
      suma=50;
      return suma;
      }
    if((D[2]==1)&&(D[3]!=1)){
      suma=-50;
      return suma;
      }
    if((D[2]==1)&&(D[3]==1)){
      suma=-75;
      return suma;
    }
    if ((D[3]==1)&&(D[2]!=1)){
      suma=-200;
      return suma;
    }
    
    return suma ;
}
  }*/

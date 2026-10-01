#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
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
  brazo.attach(9);
  pinza.attach(2);
  //mano.attach(9); // indico donde esta mi servo conectado
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
atras(80, 80);
delay(2150);
while(!(analogRead(analog[0])<U2)){
 //atras(80,80);
 //delay(2000);
 }

izquierda(90,90);
delay(1000);}

void loop(){
  //izquierda(90, 90);
  //parar();
  //Umbral();
 seguirlinea(); 
 if (distancia()=
}

void calibrarultras() {
  while (true){
    Serial.print("Costado: ");
    Serial.println(4, 7);
    delay(500);
    Serial.print("Adelante: ");
    Serial.println(5, 6);
    delay(500);
    }
}

void calibrarpololu() {
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
}}

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
}}

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

void agarrar(){
    aumentar_angulo(30,brazo,50);// parametros grados, servo usado, delay del cambio de grado. Baja el brazo
    disminuir_angulo(60,pinza,50); // cierra pinza
    disminuir_angulo(60,brazo,50);
}

void soltar(){
   aumentar_angulo(140,brazo,50);
   aumentar_angulo(140,pinza,50);
   disminuir_angulo(50,brazo,50);
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

#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
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
  brazo.attach(9);
  pinza.attach(2);
  //mano.attach(9); // indico donde esta mi servo conectado
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
atras(80, 80);
delay(2150);
while(!(analogRead(analog[0])<U2)){
 //atras(80,80);
 //delay(2000);
 }

izquierda(90,90);
delay(1000);}

void loop(){
  //izquierda(90, 90);
  //parar();
  //Umbral();
 seguirlinea(); 
 if (distancia()=
}

void calibrarultras() {
  while (true){
    Serial.print("Costado: ");
    Serial.println(4, 7);
    delay(500);
    Serial.print("Adelante: ");
    Serial.println(5, 6);
    delay(500);
    }
}

void calibrarpololu() {
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
}}

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
}}

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

void agarrar(){
    aumentar_angulo(30,brazo,50);// parametros grados, servo usado, delay del cambio de grado. Baja el brazo
    disminuir_angulo(60,pinza,50); // cierra pinza
    disminuir_angulo(60,brazo,50);
}

void soltar(){
   aumentar_angulo(140,brazo,50);
   aumentar_angulo(140,pinza,50);
   disminuir_angulo(50,brazo,50);
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

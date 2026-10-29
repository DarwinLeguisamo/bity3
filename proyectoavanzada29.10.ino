// A5 A4 A3 A2
//distancia(4,7) adelante (5,6 atras)
#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
int distanciA=200 ;
int coso = 0;
bool pelota=false;

float valor = 0;

float angulo;
// [5][4][-] [/][/] [-][3][2] analogicos
// [8][7][-] [/][/] [-][2][1] sensor
// izq                    der
int analog[]={A2,A3,A4,A5};
int rojo=10;
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
const int costado=25;

void setup() {
 
  pinMode(4, OUTPUT); //trig adelante
  pinMode(7, INPUT);
  pinMode(5, OUTPUT); //trig costado
  pinMode(6, INPUT);
  pinMode(rojo, INPUT);
   pinMode(2, OUTPUT);
  Serial.begin(9600);
 //Serial1.begin(9600);
  brazo.attach(8);
  //pinza.attach(10);
  mano.attach(9); // indico donde esta mi servo conectado
  brazo.write(90);
  mano.write(90);
  //pinza.write(90);
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
aumentar_angulo(150,mano,50);
atras(80, 80);
while(analogRead(analog[0]) < U2){}
derecha(200,200);
delay(800);
adelante(80,80);
while(analogRead(analog[0]) < U2){}
}

/*
while(true){
  //calibrarpololu();
  calibrarultras();

  // mano.write(90);
  // brazo.write(70);a
   delay(500);
   //brazo.write(120);
  //mano.write(120);
   delay(500);
 // mano.write(70);
    digitalWrite(2,HIGH);
    //brazo.write(150);
  delay(1000);

  //brazo.write(180);
  //agarrar();
  delay(1500);
  Serial.println(digitalRead(rojo));
    //brazo.write(90);
  delay(2000);
 //  mano.write(70);
   digitalWrite(2,LOW);
    delay(500);
   
    //soltar();
*/




void loop(){
  //calibrarpololu();
  if (distancia(4,7)>15){
     seguirlinea();
  }
  else {
   
    if (distancia(4,7)<6){
    parar();
    delay(300);
    agarrar();}
    else{
     adelante(70,70);}
  }

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

void atras(int i,int d ){
    digitalWrite(DirA,LOW);
    digitalWrite(DirB,LOW);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  }

void adelante(int i,int d ){
    digitalWrite(DirA,HIGH);
    digitalWrite(DirB,HIGH);
    analogWrite(PotA,d);
    analogWrite(PotB,i);
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


//adelante 8 y 9
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
void evadir(){
  parar();
  atras(120,120);
  delay(500);
   izquierda(180,180);
  delay(1300);
 
  adelante(200,200);
  delay(1500);
  derecha(180,180);
  delay(1300);
   adelante(200,200);
  delay(2000);
  derecha(180,180);
  delay(1300);
  adelante(200,200);
   while(analogRead(analog[1]) < U3){}
  izquierda(190,190);
  delay(400);
 

} 

void calibrarultras() {
  Serial.print("adelante: ");
  Serial.println(distancia(4,7));
  delay(250);
  Serial.print("Izquierda: ");
  Serial.println(distancia(5,6));
  delay(250);
}
void agarrar(){
  //aumentar_angulo(190,mano,50);
  aumentar_angulo(180,brazo,50);
  disminuir_angulo(70,mano,30);
   digitalWrite(2,HIGH);
   delay(300);
  if(digitalRead(rojo)==1){
    if(distancia(5,6)<costado){
    disminuir_angulo(90,brazo,50);
    pelota=true;
    adelante(200,200);
    delay(700);}
    else{
      aumentar_angulo(120,mano,30);
      pelota=false;
      evadir();
    }
  }
  else{ 
   aumentar_angulo(120,mano,30);
  derecha(220,220);
  delay(800);
  parar();
  delay(500);
  izquierda(200,200);
  delay(800);}
  digitalWrite(2,LOW);
}
  
 
  //disminuir_angulo(90,mano,50);


void soltar(){
  aumentar_angulo(170,brazo,70);
  aumentar_angulo(150,mano,80);
  disminuir_angulo(90,brazo,50);
  //disminuir_angulo(90,brazo,50);
}

int canasta(){
 disminuir_angulo(55,brazo,50);
 disminuir_angulo(50,mano,50);
 aumentar_angulo(90,pinza,50);
}

void seguirlinea(){
  if ((distancia(5,6)<costado)&&(pelota)){
  izquierda(180,180);
  delay(1200);
  adelante(200,200);
  while(analogRead(analog[1]) < U3){}
  adelante(200,200);
  delay(300);
  parar();
  soltar();
  pelota==false;
  atras(200,200);
  delay(700);
  while(analogRead(analog[1]) < U3){}
  derecha(200,200);
  delay(600);
}
  if ((analogRead(analog[0]) < U2) && (analogRead(analog[1]) < U3) && (analogRead(analog[2]) < U4) && (analogRead(analog[3]) < U5)){ // Ningún sensor ve la línea
    adelante(140, 140);
    //Serial.println("adelante");
  }
else{
    
     if ((!analogRead(analog[0]) < U2) &&!(analogRead(analog[1]) < U3) && (!analogRead(analog[2]) < U4) &&  (!analogRead(analog[3]) < U5)){ // Ningún sensor ve la línea
      adelante(140, 140);}
     
    
    if (analogRead(analog[3]) > U5){ // cuando el último el ext izq está en negro, 
      izquierda(180, 180);
      delay(40);
      while((analogRead(analog[2]) < U4)){};}
     

    if ((analogRead(analog[2]) > U4)&&(analogRead(analog[3]) > U5)) {
    adelante(70, 255);
    }
    if (((analogRead(analog[2]) > U4)&& !(analogRead(analog[3]) > U5))){ // linea un poco a la izq
    adelante(70, 255);
    //Serial.println("derecha suave");
    }
    if(!(analogRead(analog[0]) > U2) && (analogRead(analog[1]) > U3)){ // linea un poco a la der
      adelante(255, 70); 
    //Serial.println("izquierda suave");
      }
    if((analogRead(analog[0]) > U2) && (analogRead(analog[1]) > U3)){
      adelante(255, 70);
    }
    if (analogRead(analog[0]) > U2){ // linea muy a la der
      derecha(180, 180);
      delay(40);
     
    while (analogRead(analog[1]) < U3){}
     
    //Serial.println("izquierda");
    }
    }
}


  






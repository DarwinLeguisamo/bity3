#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
int analog[]={A2,A3,A4,A5};
int D[4];
int DirA=12;
int DirB=13;
int PotA=3;
int PotB=11;
bool calibrar=false;
bool pelotaazul=false;
bool pelotaroja=false;

int N2=900;
int N3=900;
int N4=900;
int N5=900;
int suma=0;
int umbral=940;
void setup() {
  pinMode(4, OUTPUT); // El pin Trig como salida
  pinMode(7, INPUT);
  pinMode(5, OUTPUT); // El pin Trig como salida
  pinMode(6, INPUT);
  Serial.begin(9600);
  brazo.attach(8);
  pinza.attach(2);
  mano.attach(9); // indico donde esta mi servo conectado 
  brazo.write(90);
  mano.write(90);
  pinza.write(90);
  delay(500);
  pinMode(DirA,OUTPUT);
  pinMode(DirB,OUTPUT);
  pinMode(PotA,OUTPUT);
  pinMode(PotB,OUTPUT);
  N2=analogRead(A2)-20;
  N3=analogRead(A3)-20;
  N4=analogRead(A4)-20;
  N5=analogRead(A5)-20;
  delay(1000);
  adelante(50,50);
  delay(100);
  derecha(60,60);
  delay(1450);
  
  
  
  // put your setup code here, to run once:

}

void loop() {
  while (calibrar){
    Serial.print("A5..");
    Serial.println(analogRead(A5));

    Serial.print("A4..");
    Serial.println(analogRead(A4));


    Serial.print("A3..");
    Serial.println(analogRead(A3));


    Serial.print("A2..");
    Serial.println(analogRead(A2));

    delay(300);    
  }
  while(!calibrar){  // programa principal 

  }
}

void izquierda(int i,int d ){
    digitalWrite(DirA,LOW);
    digitalWrite(DirB,LOW);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  
}

void derecha(int i,int d ){
    digitalWrite(DirA,HIGH);
    digitalWrite(DirB,HIGH);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  
}

void adelante(int i,int d ){
    digitalWrite(DirA,HIGH);
    digitalWrite(DirB,LOW);
    analogWrite(PotA,i);
    analogWrite(PotB,d);
  
}
void atrasD(int d ){
    digitalWrite(DirB,HIGH);
    analogWrite(PotB,d);
  
  }
void atrasI(int i){
   digitalWrite(DirA,LOW);
   analogWrite(PotA,i);
  
  
  }

void atras(int i,int d ){
    digitalWrite(DirA,LOW);
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


void aumentar_angulo (int angulo, Servo servo,int tiempo){
  int actual=servo.read();
  while(actual<angulo){
    actual=actual+3;
     servo.write(actual);
     delay(tiempo);
  }}
void disminuir_angulo (int angulo, Servo servo,int tiempo){
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
    aumentar_angulo(155,brazo,50);// parametros grados, servo usado, delay del cambio de grado. Baja el brazo
    aumentar_angulo(180,mano,50);  //baja la mano
    disminuir_angulo(20,pinza,50); // cierra pinza

    disminuir_angulo(50,brazo,50);
    disminuir_angulo(90,mano,50);
    if(analogRead(A0)<100){
    aumentar_angulo(120,pinza,100);
    pelotaazul=true;
    }
    else{
      pelotaroja=true;
      }
  }
  void soltar(){
   aumentar_angulo(140,brazo,50);
   aumentar_angulo(140,pinza,50);
   disminuir_angulo(50,brazo,50);
}
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
  
  }

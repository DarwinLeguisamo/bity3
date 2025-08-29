#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
int DirA=12;
int DirB=13;
int PotA=3;
int PotB=11;
bool calibrar=false;
bool pelota=false;
int N2=930;
int N3=930;
int N4=930;
int N5=930;
void setup() {
  pinMode(4, OUTPUT); // El pin Trig como salida adelnate
  pinMode(7, INPUT);// Echco adelante
  pinMode(5, OUTPUT); // El pin Trig como salida costado
  pinMode(6, INPUT);// echo del costado
  Serial.begin(9600);
  brazo.attach(8);
  pinza.attach(2);
  mano.attach(9); // indico donde esta mi servo conectado 
  brazo.write(90);
  mano.write(90);
  pinza.write(90);
  delay(500);
  aumentar_angulo(140,pinza,100);
  pinMode(DirA,OUTPUT);
  pinMode(DirB,OUTPUT);
  pinMode(PotA,OUTPUT);
  pinMode(PotB,OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  while (calibrar){
    Serial.print("A4..");
    Serial.println(analogRead(A4));
    Serial.print("A4..");
    Serial.println(analogRead(A4));
    Serial.print("A4..");
    Serial.println(analogRead(A4));
    Serial.print("A4..");
    Serial.println(analogRead(A4));
    delay(300);    
    }
  while(!calibrar){  // programa principal 
    if (distancia(4,7)<10){
      adelante(0,0);
      delay(1000);
      agarrar();
      pelota=true;
      adelante(50,50);
    }
    else{
      if(analogRead(A3)>N3){
        adelante(100,50);
        }
      if(analogRead(A2)>N2){
        derecha(130,130);
       }
      if(analogRead(A4)>N4){
        adelante(50,100);
     }
      if(analogRead(A5)>N5){
        izquierda(150,150);
      }

      if ((!(analogRead(A3)>N3))&&(!(analogRead(A2)>N2))&&(!(analogRead(A4)>N4))&&(!(analogRead(A5)>N5))){
        adelante(50,50);}
    }
    if ((distancia(5,6)<20) && (pelota)){
      adelante(0,0);
      delay(1000);
      while(distancia(4,7)<10){
        izquierda(150,150);}
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
    aumentar_angulo(140,brazo,50);// parametros grados, servo usado, delay del cambio de grado. Baja el brazo
    aumentar_angulo(180,mano,50);  //baja la mano
    disminuir_angulo(20,pinza,50); // cierra pinza

    disminuir_angulo(50,brazo,50);
    disminuir_angulo(10,mano,50);
   // aumentar_angulo(140,pinza,100);
  }


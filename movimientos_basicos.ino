#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
int DirA=12;
int DirB=13;
int PotA=3;
int PotB=11;
void setup() {
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
  
  parar();
  
  // put your main code here, to run repeatedly:

}

void atras(int v){
    digitalWrite(DirA,LOW);
    digitalWrite(DirB,HIGH);
    analogWrite(PotA,v);
    analogWrite(PotB,v);
  
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

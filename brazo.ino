#include <Servo.h>
Servo brazo;
Servo mano;
Servo pinza;
//Servo rueda2;
void setup()
{
// pinMode(13,INPUT);
 brazo.attach(8);
  pinza.attach(2);
mano.attach(9); // indico donde esta mi servo conectado 
 //rueda2.attach(6); 
 brazo.write(90);
 mano.write(90);
 pinza.write(90);
 delay(500);
 aumentar_angulo(140,pinza,100);
}

void loop()
{
 aumentar_angulo(140,brazo,50);// parametros grados, servo usado, delay del cambio de grado. Baja el brazo
 aumentar_angulo(180,mano,50);  //baja la mano
 disminuir_angulo(20,pinza,50); // cierra pinza

 disminuir_angulo(50,brazo,50);
 disminuir_angulo(10,mano,50);
 aumentar_angulo(140,pinza,100);
 
 /*
 if (digitalRead(2)) 
 {rueda.write(0); // mando el servo a 0
  delay(1500);// espero medio segundo
 }
 else{
  rueda.write(180); // mando el servo a 90
  delay(1500);}
*/  
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

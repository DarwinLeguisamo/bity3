#include <Servo.h>
#include "Adafruit_VL53L0X.h"
// En la Pro Micro: SDA = pin 2, SCL = pin 3. Servo en el pin 6.

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo servo;
float valor = 0;
// ---------- Configuración ----------
const int PIN_SERVO    = 8;
const int PASO         = 10;    // grados entre mediciones
const int ANG_MIN      = 0;
const int ANG_MAX      = 180;
const int ESPERA_SERVO = 80;    // ms para que el servo llegue y se estabilice
const int OFFSET_MM    = 25;    // tu corrección de la medida
const int RANGO_MAX    = 2000;  // valor que usamos para "no hay obstáculo"

const int N_PUNTOS = (ANG_MAX - ANG_MIN) / PASO + 1;   // 19 puntos
int distancias[N_PUNTOS];

int angulo = ANG_MIN;
int direccion = 1;              // 1 = subiendo, -1 = bajando

// Espera a que el sensor termine una medición (con límite de tiempo
// para que el programa no se cuelgue si el sensor falla)
bool esperarMedicion(unsigned long limiteMs) {
  unsigned long t0 = millis();
  while (!lox.isRangeComplete()) {
    if (millis() - t0 > limiteMs) return false;
  }
  return true;
}

// Devuelve una medición tomada con el servo ya quieto
int medir() {
  // 1) Descartar la medición que se hizo mientras el servo se movía
  if (esperarMedicion(100)) lox.readRange();

  // 2) Tomar una medición nueva
  if (!esperarMedicion(100)) return -1;     // -1 = error del sensor
  int crudo = lox.readRange();

  if (crudo >= 8000) return RANGO_MAX;      // fuera de rango: no ve nada
  int mm = crudo - OFFSET_MM;
  if (mm < 0) mm = 0;
  if (mm > RANGO_MAX) mm = RANGO_MAX;
  return mm;
}

// Imprime el barrido completo en una línea
void imprimirBarrido() {
  Serial.print("# Barrido: ");
  for (int i = 0; i < N_PUNTOS; i++) {
    Serial.print(distancias[i]);
    Serial.print(i < N_PUNTOS - 1 ? " " : "\n");
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  // Espera el monitor serie como máximo 3 s.
  // (Con "while(!Serial)" solo, la placa se queda trancada
  //  para siempre cuando va en el robot sin la PC conectada.)
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 3000) {}

  servo.attach(PIN_SERVO);
  servo.write(ANG_MIN);
  delay(500);

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  servo.write(90);
  lox.startRangeContinuous();
  Serial.println(F("Radar listo. Formato: angulo,distancia_mm"));
 
 
}

void loop() {
  // Mover y medir
  
  char c = recibir();
  switch (c) {
    case 'D': {
      int distancia = (int)valor;
      // usar distancia...
      break;
    }
      case 'L': {
      if ((int)valor==-1){
        enviarEntero('L', alineadoIzquierda());

      }
      
      break;
    }
    case 'A': {
      angulo = valor;
      servo.write(angulo);
      delay(10);
      int d = medir();
      //Serial.println(d);
      //enviarReal('A',angulo);
      enviarEntero('D',d);
      break;
    }
    case '!':
      // frenar
      break;
  }

  /*
  //servo.write(angulo);
  delay(ESPERA_SERVO);
  int d = medir();

  distancias[(angulo - ANG_MIN) / PASO] = d;
  Serial.print(angulo);
  Serial.print(",");
  Serial.println(d);

  // Calcular el próximo ángulo (barrido en zig-zag: ida y vuelta)
  int siguiente = angulo + direccion * PASO;
  if (siguiente > ANG_MAX || siguiente < ANG_MIN) {
    direccion = -direccion;
    imprimirBarrido();
    siguiente = angulo + direccion * PASO;
  }
  angulo = siguiente;
  */
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

// Devuelve x2 - x1 en mm:
//   0        -> paralelo a la pared izquierda
//   positivo -> la trompa apunta HACIA la pared (corregir girando a la derecha)
//   negativo -> se está alejando de la pared (corregir girando a la izquierda)
//   9999     -> alguna lectura no sirve (no ve pared o error)
int alineadoIzquierda() {
  servo.write(160);
  delay(50);
  int d1 = medir();
  servo.write(120);
  delay(50);
  int d2 = medir();
 
  if (d1 <= 0 || d1 >= RANGO_MAX || d2 <= 0 || d2 >= RANGO_MAX) {
    return 9999;
  }
  float x1 = d1 * cos(160 * DEG_TO_RAD);
  float x2 = d2 * cos(120 * DEG_TO_RAD);
  return (int)(x2 - x1);
}

//Pin Interrupcion
#define INIT 2

//Pines servos
#define GRIP 8
#define WRIST_PITCH 9
#define WRIST_ROLL 10
#define ELBOW 11
#define SHOULDER 12
#define WAIST 13

//Pines Sensor Color
#define S0 3    // S0 a pin 4
#define S1 4    // S1 a pin 5
#define S2 5    // S2 a pin 6
#define S3 6    // S3 a pin 7
#define salidaTCS 7 // salidaTCS a pin 8

#include <Servo.h>

Servo grip;
Servo wristPitch;
Servo wristRoll;
Servo elbow;
Servo shoulder;
Servo waist;

int readColor() {
  int times = 5;
  int rojo, verde, azul;
  
  while(times > 0) {
    digitalWrite(S2,LOW);                 // establece fotodiodos
    digitalWrite(S3,LOW);                 // con filtro rojo
    rojo = pulseIn(salidaTCS, LOW);   // obtiene duracion de pulso de salida del sensor
    Serial.println("rojo:");
    Serial.println(rojo);
    delay(200);                           // demora de 200 mseg
    
    digitalWrite(S2,HIGH);                // establece fotodiodos
    digitalWrite(S3,HIGH);                // con filtro verde
    verde = pulseIn(salidaTCS, LOW);  // obtiene duracion de pulso de salida del sensor
    Serial.println("verde:");
    Serial.println(verde);
    delay(200);                           // demora de 200 mseg
    
    digitalWrite(S2,LOW);                 // establece fotodiodos
    digitalWrite(S3,HIGH);                // con filtro azul
    azul = pulseIn(salidaTCS, LOW);   // obtiene duracion de pulso de salida del sensor
    Serial.println("azul:");
    Serial.println(azul);
    delay(200);                           // demora de 200 mseg

    times--;
  }

  // Verde = 1; Azul = 2, Rojo = 3
  if(rojo > 75 && rojo < 200 && verde > 75 && verde < 210 && azul > 135 && azul < 340){
    return 1;
  }else if(rojo > 140 && rojo < 580 && verde > 75 && verde < 170 && azul > 25 && azul < 130) {
    return 2;
  }else if(rojo > 70 && rojo < 180 && verde > 260 && verde < 485 && azul > 195 && azul < 380) {
    return 3;
  }else {
    return 0;
  }
  
}

void moverBrazo(int parteBrazo, int grados, bool inicial = false) {
   //Grip = 1; Wrist Pitch = 2;
   //Wrist Roll = 3; Elbow = 4;
   //Shoulder = 5; Waist = 6; 
  switch(parteBrazo) {
    case 1:
      if(inicial) {
        grip.write(grados);  
      }else {
        if(grip.read() < grados) {
          for (int pos = grip.read(); pos <= grados; pos += 1) {
            grip.write(pos);
            delay(15);
          }
        }else {
          for (int pos = grip.read(); pos >= grados; pos -= 1) {
            grip.write(pos);
            delay(15);
          }
        }
      }
      break;
    case 2:
      if(inicial) {
        wristPitch.write(grados);  
      }else {
        if(wristPitch.read() < grados) {
          for (int pos = wristPitch.read(); pos <= grados; pos += 1) {
            wristPitch.write(pos);
            delay(15);
          }
        }else {
          for (int pos = wristPitch.read(); pos >= grados; pos -= 1) {
            wristPitch.write(pos);
            delay(15);
          }
        }
      }
      break;
    case 3:
      if(inicial) {
        wristRoll.write(grados);  
      }else {
        if(wristRoll.read() < grados) {
          for (int pos = wristRoll.read(); pos <= grados; pos += 1) {
            wristRoll.write(pos);
            delay(15);
          }
        }else {
          for (int pos = wristRoll.read(); pos >= grados; pos -= 1) {
            wristRoll.write(pos);
            delay(15);
          }
        }
      }
      break;
    case 4:
      if(inicial) {
        elbow.write(grados);  
      }else {
        if(elbow.read() < grados) {
          for (int pos = elbow.read(); pos <= grados; pos += 1) {
            elbow.write(pos);
            delay(15);
          }
        }else {
          for (int pos = elbow.read(); pos >= grados; pos -= 1) {
            elbow.write(pos);
            delay(15);
          }
        }
      }
      break;
    case 5:
      if(inicial) {
        shoulder.write(grados);  
      }else {
        if(shoulder.read() < grados) {
          for (int pos = shoulder.read(); pos <= grados; pos += 1) {
            shoulder.write(pos);
            delay(15);
          }
        }else {
          for (int pos = shoulder.read(); pos >= grados; pos -= 1) {
            shoulder.write(pos);
            delay(15);
          }
        }
      }
      break;
    case 6:
      if(inicial) {
        waist.write(grados);  
      }else {
        if(waist.read() < grados) {
          for (int pos = waist.read(); pos <= grados; pos += 1) {
            waist.write(pos);
            delay(15);
          }
        }else {
          for (int pos = waist.read(); pos >= grados; pos -= 1) {
            waist.write(pos);
            delay(15);
          }
        }
      }
      break;
  }
}

void principal() {
  //Posicion inicial
  Serial.print("hola");
  moverBrazo(1, 100, true);
  moverBrazo(2, 40, true);
  moverBrazo(3, 0, true);
  moverBrazo(4, 25, true);
  moverBrazo(5, 90, true);
  moverBrazo(6, 60, true);

  //Posicion cubos
  delay(1000);

  moverBrazo(6, 120);
  moverBrazo(5, 60);
  moverBrazo(4, 50);
  moverBrazo(2, 40);
  moverBrazo(1, 0);

  //Posicion sensor
  delay(2000);
  moverBrazo(4, 27);
  moverBrazo(6, 70);

  delay(1000);
  //Leer color
  int color = readColor();
  delay(1000);

  if(color == 1) {
    Serial.println("VERDE");
    //Posicion color verde
    moverBrazo(5, 90);
    moverBrazo(4, 25);
    moverBrazo(6, 0);
    moverBrazo(1, 100);  
  }else if(color == 2) {
    Serial.println("AZUL");
    //Posicion color azul
    moverBrazo(5, 90);
    moverBrazo(4, 25);
    moverBrazo(6, 25);
    moverBrazo(1, 100);
  }else if(color == 3) {
    Serial.println("ROJO");
    //Posicion color 3
    moverBrazo(5, 80);
    moverBrazo(4, 15);
    moverBrazo(2, 80);
    moverBrazo(6, 45);
    moverBrazo(1, 100);
  }

  Serial.println("NADA");
  
  //Posicion inicial
  moverBrazo(1, 100);
  moverBrazo(2, 40);
  moverBrazo(4, 25);
  moverBrazo(5, 90);
  moverBrazo(6, 60);
  
}

void setup() {
  pinMode(INIT, INPUT);
  
  grip.attach(GRIP);
  wristPitch.attach(WRIST_PITCH);
  wristRoll.attach(WRIST_ROLL);
  elbow.attach(ELBOW);
  shoulder.attach(SHOULDER);
  waist.attach(WAIST);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(salidaTCS, INPUT);
  
  digitalWrite(S0,HIGH);  // establece frecuencia de salida
  digitalWrite(S1,LOW);   // del modulo al 20 por ciento
  
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(INIT);

  if(val == HIGH) {
    principal();
  }

}

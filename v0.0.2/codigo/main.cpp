#include "BluetoothSerial.h"

/* BLUETOOTH */

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!Please run `make menuconfig`to and enable it
#endif

BluetoothSerial bluetooth;

/*  VARIAVEIS */

const int BUZZER = 19,
    MOTOR_A1 = 23,
    MOTOR_A2 = 22,
    MOTOR_B1 = 2,
    MOTOR_B2 = 3;

void setup() {
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);

    pinMode(BUZZER, OUTPUT);

    bluetooth.begin("PATIFERO");
    Serial.begin(9600);
    para();
}

void loop() {
    while (bluetooth.available()) {
      executa_comando(bluetooth.readString());
    }
}

void executa_comando(String comando) {
    if (comando == "R") {
        direita();
    } else if (comando == "L") {
        esquerda();
    } else if (comando == "F") {
        frente();
    } else if (comando == "B") {
        atras();
    } else if (comando == "S") {
        para();
    } else {
        para();
    }

    if (comando == "V") {
        busina();
    } else {
        busina_low();
    }
}

/* MOVIMENTACAO */

void direita() {
    // R
    motor(0, 0, 1, 0);
}

void esquerda() {
    // L
    motor(1, 0, 0, 0);
}

void frente() {
    // F
    motor(0, 1, 1, 0);
}

void atras() {
    // B
    motor(1, 0, 0, 1);
}

void para() {
    // S
    motor(0, 0, 0, 0);
}

/* BUSINA */

void busina() {
    // V
    tone(BUZZER, 700);
}

void busina_low() {
    noTone(BUZZER);
}

/* MOTOR */

void motor(int motorA1, int motorA2, int motorB1, int motorB2) {
    digitalWrite(MOTOR_A1, motorA1);
    digitalWrite(MOTOR_A2, motorA2);
    digitalWrite(MOTOR_B1, motorB1);
    digitalWrite(MOTOR_B2, motorB2);
}

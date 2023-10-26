#include "BluetoothSerial.h"

/* BLUETOOTH */

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!Please run `make menuconfig`to and enable it
#endif

BluetoothSerial bluetooth;

/*  VARIAVEIS */

const int BUZZER = 0, LED_PATIFERO = 0, LED_ESQUERDA = 0, LED_DIREITA = 0, LED_RE = 0, MOTOR_A1 = 12, MOTOR_A2 = 14, MOTOR_B1 = 27, MOTOR_B2 = 26;

void setup() {
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);

    pinMode(LED_PATIFERO, OUTPUT);
    pinMode(LED_DIREITA, OUTPUT);
    pinMode(LED_ESQUERDA, OUTPUT);
    pinMode(LED_RE, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    ascende_led(LED_PATIFERO);

    bluetooth.begin("PATIFERO");
}

void loop() {
    frente();
} 

void executa_comando(String comando) {
    if(comando == "R") {
         direita();
    } else if(comando == "L") {
        esquerda();
    } else if(comando == "F") {
        frente();
    } else if(comando == "B") {
        atras();
    } else if(comando == "S") {
        para();
    } 
}

/* MOVIMENTACAO */

void direita() {
    // R
    ascende_led(LED_DIREITA);
    motor(1,0,0,0);
    apaga_led(LED_DIREITA);
}

void esquerda() {
    // L
    ascende_led(LED_ESQUERDA);
    motor(0,0,1,0);
    apaga_led(LED_ESQUERDA);
}

void frente() {
    // F
    motor(0,1,0,1);
}

void atras() {
    // B
    motor(1,0,1,0);
    re();
}

void para() {
    // S
    motor(0,0,0,0);
}

void cavaloPau() {
    motor(1,0,0,0);
    delay(5000);
}

/* FAROL */

void re() {
    ascende_led(LED_RE);
}

void reset_seta() {
    apaga_led(LED_DIREITA);
    apaga_led(LED_ESQUERDA);
    apaga_led(LED_RE);
}

void ascende_led(int led) {
    reset_seta(); 
    digitalWrite(led, HIGH);
}

void apaga_led(int led) {
    digitalWrite(led, LOW);
}

/* BUSINA */

void busina() {
    // V
    tone(BUZZER, 700);
    noTone(BUZZER);
    delay(500);
    tone(BUZZER, 700);
    noTone(BUZZER);
}

/* MOTOR */

void motor(int motorA1, int motorA2, int motorB1, int motorB2) {
    digitalWrite(MOTOR_A1, motorA1);
    digitalWrite(MOTOR_A2, motorA2);
    digitalWrite(MOTOR_B1, motorB1);
    digitalWrite(MOTOR_B2, motorB2);
}

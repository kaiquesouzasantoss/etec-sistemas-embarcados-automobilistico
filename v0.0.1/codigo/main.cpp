#include <Ultrasonic.h>

const int TRIGGER = 13, ECHO = 12, MOTOR_A1 = 7, MOTOR_A2 = 6, MOTOR_B1 = 5, MOTOR_B2 = 4, LED_DIREITA = 8, LED_ESQUERDA = 9, BUZZER = 10;
const int velocidade = 255;
int obstaculos = 0;

Ultrasonic ultrasonic(TRIGGER, ECHO);

void setup() {
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);

    pinMode(LED_DIREITA, OUTPUT);
    pinMode(LED_ESQUERDA, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    Serial.begin(9600);

    cavaloPau();
}

void loop() {
    double obstaculo = ultrasonic.read();

    if (obstaculo <= 5) {
        direita();
        busina();
        esquerda();
    }else if(obstaculo > 5 && obstaculo <= 10) {
        direita();
        direita();
    } else if(obstaculo > 10 && obstaculo <= 15) {
        esquerda();
    } else if(obstaculo > 15 && obstaculo <= 25) {
        direita();
        direita();
    } else {
        frente();
    }

    obstaculo();
}

void obstaculo() {
    if(obstaculos == 10) {
        cavaloPau();
        obstaculos = 0;
    } 
}

/* MOVIMENTACAO */

void direita() {
    seta(LED_DIREITA);
    motor(1,0,0,0);
    delay(1000);
    resetSeta(LED_DIREITA);
}

void esquerda() {
    seta(LED_ESQUERDA);
    motor(0,0,1,0);
    delay(1000);
    resetSeta(LED_ESQUERDA);
}

void frente() {
    motor(1,0,1,0);
    farol();
}

void atras() {
    motor(0,1,0,1);
}

void para() {
    motor(0,0,0,0);
}

void cavaloPau() {
    motor(1,0,0,0);
    delay(5000);
}

/* FAROL */

void farol() {
    seta(LED_DIREITA);
    seta(LED_ESQUERDA);
}

void resetFarol() {
    resetSeta(LED_DIREITA);
    resetSeta(LED_ESQUERDA);
}

void seta(int led) {
    resetFarol(); 
    digitalWrite(led, HIGH);
}

void resetSeta(int led) {
    digitalWrite(led, LOW);
}

/* BUSINA */

void busina() {
    tone(BUZZER, 700);
    delay(200);
    noTone(BUZZER);
    tone(BUZZER, 700);
    delay(200);
    noTone(BUZZER);
}

/* MOTOR */

void motor(int motorA1, int motorA2, int motorB1, int motorB2) {
    digitalWrite(MOTOR_A1, motorA1);
    digitalWrite(MOTOR_A2, motorA2);
    digitalWrite(MOTOR_B1, motorB1);
    digitalWrite(MOTOR_B2, motorB2);

    obstaculos += 1;
}

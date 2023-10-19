#include <Ultrasonic.h>

const int TRIGGER = 10, ECHO = 11, BUZZER = 9, LED_ESQUERDA = 8, LED_DIREITA = 7, MOTOR_A1 = 6, MOTOR_A2 = 5, MOTOR_B1 = 9, MOTOR_B2 = 3, FAROL = 2;
const int velocidade = 150;

Ultrasonic ultrasonic(TRIGGER, ECHO);

void setup() {
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);

    pinMode(LED_DIREITA, OUTPUT);
    pinMode(LED_ESQUERDA, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(FAROL, OUTPUT);

    digitalWrite(FAROL, HIGH);
}

void loop() {
    double obstaculo = ultrasonic.read();
    if (obstaculo <= 8) { 
        direita();  
    } 

    frente();
}

/* MOVIMENTACAO */

void direita() {
    seta(LED_DIREITA);
    motor(255,0,0,0);
    delay(1200);
    resetSeta(LED_DIREITA);
}

void direita_diferente() {
    para();
    seta(LED_DIREITA);
    motor(velocidade,0,0,0);
    delay(50);
    resetSeta(LED_DIREITA);
}

void esquerda() {
    seta(LED_ESQUERDA);
    motor(0,0,255,0);
    delay(1000);
    resetSeta(LED_ESQUERDA);
}

void frente() {
    motor(0,velocidade,0,velocidade);
    //delay(100);
    //direita_diferente();
}

void atras() {
    motor(velocidade,0,velocidade,0);
    delay(1000);
}

void para() {
    motor(0,0,0,0);
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
    noTone(BUZZER);
    delay(500);
    tone(BUZZER, 700);
    noTone(BUZZER);
}

/* MOTOR */

void motor(int motorA1, int motorA2, int motorB1, int motorB2) {
    analogWrite(MOTOR_A1, motorA1);
    analogWrite(MOTOR_A2, motorA2);
    analogWrite(MOTOR_B1, motorB1);
    analogWrite(MOTOR_B2, motorB2);
}

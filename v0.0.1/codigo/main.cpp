#include <Servo.h>
#include <Ultrasonic.h>

const int 
    TRIGGER = 13,
    ECHO = 12,
    SERVO = 11,
    MOTOR_A1 = 7,
    MOTOR_A2 = 6,
    MOTOR_B1 = 5,
    MOTOR_B2 = 4
    LED_DIREITA = 8,
    LED_ESQUERDA = 9,
    BUZZER = 10;

const int velocidade = 255, angulo_direita = 160, angulo_esquerda = 60, angulo_central = 105;

Servo servo;
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
    servo.attach(SERVO);
}

void loop() {
    double obstaculo = ultrasonic.read();

    if (obstaculo <= 5) {
        busina();
        direita();
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
}

/* MOVIMENTACAO */

void direita() {
    seta(LED_DIREITA);
    motor(velocidade,0,velocidade,0,angulo_direita);
    delay(1000);
    resetSeta();
}

void esquerda() {
    seta(LED_ESQUERDA);
    motor(velocidade,0,velocidade,0,angulo_esquerda);
    delay(1000);
    resetSeta();
}

void frente() {
    motor(velocidade,0,velocidade,0,angulo_central);
    farol();
}

void atras() {
    motor(0,velocidade,0,velocidade, angulo_central);
}

void para() {
    motor(0,0,0,0,angulo_central);
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

void seta(led) {
    resetFarol(); 
    digitalWrite(led, HIGH);
}

void resetSeta(led) {
    digitalWrite(led, LOW);
}

/* BUSINA */

void busina() {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
}

/* MOTOR */

void motor(motorA1, motorA2, motorB1, motorB2, angulo) {
    analogWrite(MOTOR_A1, motorA1);
    analogWrite(MOTOR_A2, motorA2);
    analogWrite(MOTOR_B1, motorB1);
    analogWrite(MOTOR_B2, motorB2);

    servo.write(angulo);
}
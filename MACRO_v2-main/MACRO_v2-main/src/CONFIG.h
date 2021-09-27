#ifndef CONFIG_H
#define CONFIG_H

/**
 * File to hold important definitions such as pins and consts
*/
// test
// Outer Stage

#define MOTOR1_EN 6
#define MOTOR1_IN1 11
#define MOTOR1_IN2 10

#define MOTOR2_EN 7
#define MOTOR2_IN1 9
#define MOTOR2_IN2 8

#define ENCPIN1_1 20
#define ENCPIN1_2 21

#define ENCPIN2_1 16
#define ENCPIN2_2 3

#define JOY1_Y A3
#define JOY1_X A2

// Inner Stage

#define MOTOR3_EN 44
#define MOTOR3_IN1 31
#define MOTOR3_IN2 33

#define MOTOR4_EN 42
#define MOTOR4_IN1 35
#define MOTOR4_IN2 37


#define ENCPIN3_1 18
#define ENCPIN3_2 19

#define ENCPIN4_1 17
#define ENCPIN4_2 2


#define JOY2_Y A5
#define JOY2_X A4



//  button to switch between modes
#define MODE_BUTT 23
#define SP_BUTT 22
#define LED_G 25
#define LED_B 27
#define LED_R 29

#endif // CONFIG_H
/*
 * PWM.h
 *
 * Created: 8/05/2024 16:18:01
 *  Author: Snake
 */ 


#ifndef PWM_H_
#define PWM_H_
#include <avr/io.h>
#include <stdint.h>

//PWMTimer
#define Timer2 2
#define Timer1 1
#define Timer0 0

//Canal
#define Canal_A 1
#define Canal_B 0

//Modo
#define Fast_Top 3
#define Phase_correct_Top 2
#define Fast 1
#define Phase_correct 0

//inversion
#define Invertido 1
#define No_invertido 0

//Funcion de configuracion completo para todo PWM
void initPWM(uint8_t PWMTimer, uint8_t Canal, uint8_t Modo, uint8_t inversion, uint16_t Prescaler); 

//Funcion de actualizacion de DutyCycle para cualquier PWM
void updateDutyCycle(uint8_t PWMTimer, uint8_t Canal, uint16_t Duty); 

//Funcion de mapeo
uint16_t map(float Signal, float In_min, float In_max, float Out_min, float Out_max);  

#endif /* PWM_H_ */
/*
 * ADC.h
 *
 * Created: 8/05/2024 16:17:12
 *  Author: Snake
 */ 

#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <stdint.h>

//V_Referencia
#define V_int_bajo1V 2
#define V_ext_5V 1
#define V_int_ref 0

//Justificacion
#define Izquierda 1
#define Derecha 0

//Canal_MUX
#define Canal_7 7
#define Canal_6 6
#define Canal_5 5
#define Canal_4 4
#define Canal_3 3
#define Canal_2 2
#define Canal_1 1
#define Canal_0 0

//Auto_Trigger
#define Si_A_T 1
#define No_A_T 0

//Modo_A_T
#define Habilitada 1
#define Deshabilitada 0

//Interrupciones
#define Evento_captura_Timer1 7
#define Timer1_ovf 6
#define Comparador_Timer1_B 5
#define Timer0_ovf 4
#define Comparador_Timer0_A 3
#define Boton 2
#define Comparador_analogo 1
#define Free_nulo 0

//Funcion de configuracion para cualquier canal ADC
void initADC(uint8_t V_Referencia, uint8_t Justificacion, uint8_t Canal_MUX, uint8_t Auto_Trigger, uint8_t Modo_A_T, uint8_t Interrupciones, uint8_t Prescaler); 
void CambioCanal(uint8_t Canal_MUX);

#endif /* ADC_H_ */
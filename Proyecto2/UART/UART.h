/*
 * UART.h
 *
 * Created: 20/05/2024 01:16:50
 *  Author: Snake
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

//Pulsos
#define Sincrono 1
#define Asincrono 0

//Interrupciones
#define Habilitar 1
#define Deshabilitar 0

//Modo
#define Fast 1
#define Normal 0

//Paridad
#define Impar 2
#define Par 1
#define Sin_paridad 0

//Bit_parada
#define Uno 1
#define Dos 0

//Numero_Bits
#define Nueve 4
#define Ocho 3
#define Siete 2
#define Seis 1
#define Cinco 0

//Polaridad
#define Flanco_Bajada 1
#define Flanco_Subida 0

//Funcion de configuracion para cualquier comunicacion serial UART
void initUART(uint8_t Pulsos, uint8_t Modo, uint8_t RX_ISR, uint8_t TX_ISR, uint8_t Empty_ISR, uint8_t Paridad, uint8_t Bit_parada, uint8_t Numero_Bits, uint8_t Polaridad, uint8_t BAUD); //Funcion para configurar UART
void WriteUART(char* Character); //Funcion para escribir

#endif /* UART_H_ */
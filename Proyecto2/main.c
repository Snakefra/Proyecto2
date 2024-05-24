/*
 * Proyecto2.c
 *
 * Created: 8/05/2024 16:05:19
 * Author : Snake
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include "ADC/ADC.h"
#include "PWM/PWM.h"
#include "UART/UART.h"
#include <avr/eeprom.h>

void setup(void);

uint16_t DutyCycleA = 127;
uint16_t DutyCycleB = 171;
uint16_t DutyCycleC = 127;
uint16_t DutyCycleD = 127;
uint16_t MemoriaPOS1;

int main(void){
	DDRC |= (1<<DDC2) | (1<<DDC3);
	PORTC &= ~(1<<PORTC2);
	PORTC &= ~(1<<PORTC3);
	cli();
	initPWM(Timer1,Canal_A,Fast_Top,No_invertido,8);
	initPWM(Timer1,Canal_B,Fast_Top,No_invertido,8);
	initPWM(Timer0,Canal_A,Fast,No_invertido,1024);
	initPWM(Timer0,Canal_B,Fast,No_invertido,1024);
	initADC(V_ext_5V,Izquierda,Canal_7,No_A_T,Free_nulo,Habilitada,128);
	//initUART(Asincrono,Fast,Habilitar,Deshabilitar,Habilitar,Sin_paridad,Uno,Ocho,Flanco_Subida,207); //Comunicacion Serial con valor de BAUDRATE de 9600
	sei();
	//WriteUART(DutyCycleA);
    while (1) 
    {
		//Iniciando secuancia del ADC
		ADMUX &= 0xF0;
		CambioCanal(Canal_7);
		ADCSRA |= (1<<ADSC);
		DutyCycleA = map(ADCH,0,1023,2000,9400);
		updateDutyCycle(Timer1,Canal_B,DutyCycleA);
		_delay_ms(10);
		ADMUX &= 0xF0;
		CambioCanal(Canal_6);
		ADCSRA |= (1<<ADSC);
		DutyCycleB = map(ADCH,0,1023,2000,9400);
		updateDutyCycle(Timer1,Canal_A,DutyCycleB);
		_delay_ms(10);
		ADMUX &= 0xF0;
		CambioCanal(Canal_5);
		ADCSRA |= (1<<ADSC);
		DutyCycleC = map(ADCH,0,1023,2000,9400);
		updateDutyCycle(Timer0,Canal_A,DutyCycleC);
		_delay_ms(10);
		CambioCanal(Canal_4);
		ADCSRA |= (1<<ADSC);
		DutyCycleD = map(ADCH,0,1023,2000,9400);
		updateDutyCycle(Timer0,Canal_B,DutyCycleD);
		_delay_ms(10);
		
    }
}
ISR(ADC_vect){
	
	ADCSRA |= (1<<ADIF);  //Apagando bandera ADC
}

ISR(USART_RX_vect){
	
}

ISR(USART_TX_vect){
	
}

ISR(USART_UDRE_vect){
	
}

ISR(PCINT0_vect){
	if (PINC & (1<<PINC2)){
	eeprom_write_byte((uint8_t*)0x00, DutyCycleA);
	eeprom_write_byte((uint8_t*)0x01, DutyCycleB);
	eeprom_write_byte((uint8_t*)0x02, DutyCycleC);
	
	eeprom_write_byte((uint8_t*)0x03, DutyCycleA);
	eeprom_write_byte((uint8_t*)0x04, DutyCycleB);
	eeprom_write_byte((uint8_t*)0x05, DutyCycleC);
	
	eeprom_write_byte((uint8_t*)0x06, DutyCycleA);
	eeprom_write_byte((uint8_t*)0x07, DutyCycleB);
	eeprom_write_byte((uint8_t*)0x08, DutyCycleC);
	
	eeprom_write_byte((uint8_t*)0x09, DutyCycleA);
	eeprom_write_byte((uint8_t*)0x0A, DutyCycleB);
	eeprom_write_byte((uint8_t*)0x0B, DutyCycleC);
	}
}

ISR(PCINT1_vect){
	if (PINC & (1<<PINC3)){
		eeprom_read_byte((uint8_t*)0x00);
		eeprom_read_byte((uint8_t*)0x01);
		eeprom_read_byte((uint8_t*)0x02);
		eeprom_read_byte((uint8_t*)0x03);
		eeprom_read_byte((uint8_t*)0x04);
		eeprom_read_byte((uint8_t*)0x05);
		eeprom_read_byte((uint8_t*)0x06);
		eeprom_read_byte((uint8_t*)0x07);
		eeprom_read_byte((uint8_t*)0x08);
		eeprom_read_byte((uint8_t*)0x09);
		eeprom_read_byte((uint8_t*)0x0A);
		eeprom_read_byte((uint8_t*)0x0B);
	}
}
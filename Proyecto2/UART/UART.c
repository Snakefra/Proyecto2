/*
 * UART.c
 *
 * Created: 20/05/2024 01:17:05
 *  Author: Snake
 */ 

#include "UART.h"

void initUART(uint8_t Pulsos, uint8_t Modo, uint8_t RX_ISR, uint8_t TX_ISR, uint8_t Empty_ISR, uint8_t Paridad, uint8_t Bit_parada, uint8_t Numero_Bits, uint8_t Polaridad, uint8_t BAUD){
	//Configuracion pines Tx y Rx
	DDRD &= ~(1<<DDD0);  //Rx Input
	DDRD |= (1<<DDD1);  //Tx Output
	
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	
	//Configuracion de pulsos de reloj
	if (Pulsos == Asincrono){	//Modo Asincrono
		UCSR0C &= ~(1<<UMSEL01);
		UCSR0C &= ~(1<<UMSEL00);
		
		//Configuracion de modos
		if (Modo == Fast){		//Modo Fast
			UCSR0A |= (1<<U2X0);
		}
		else if (Modo == Normal){	//Modo Normal
			UCSR0A &= ~(1<<U2X0);
		}
	} 
	else if (Pulsos == Sincrono){	//Modo Sincrono
		UCSR0C |= (1<<UMSEL00);
		
		//Configuracion de polaridad del reloj
		if (Polaridad == Flanco_Subida){	//Solo cambia con Flanco de subida
			UCSR0C &= ~(1<<UCPOL0);
		}
		else if (Polaridad == Flanco_Bajada){	//Solo cambia con Flanco de bajada
			UCSR0C |= (1<<UCPOL0);
		}
	}
	//Configuracion interrupciones
	if (RX_ISR == Habilitar){	//Configuracion interrupcion RX complete
		UCSR0B |= (1<<RXCIE0);
	}
	else if (RX_ISR == Deshabilitar){
		UCSR0B &= ~(1<<RXCIE0);
	}
	if (TX_ISR == Habilitar){	//Configuracion interrupcion TX complete
		UCSR0B |= (1<<TXCIE0);
	}
	else if (TX_ISR == Deshabilitar){
		UCSR0B &= ~(1<<TXCIE0);
	}
	if (Empty_ISR == Habilitar){	//Configuracion interrupcion Data register empty
		UCSR0B |= (1<<UDRIE0);
	}
	else if (Empty_ISR == Deshabilitar){
		UCSR0B &= ~(1<<UDRIE0);
	}
	//Habilitamos RX y TX
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	
	//Configuracion Paridad
	if (Paridad == Sin_paridad){	//Sin paridad
		UCSR0C &= ~(1<<UPM01);
		UCSR0C &= ~(1<<UPM00);
	} 
	else if (Paridad == Par){	//Paridad par
		UCSR0C |= (1<<UPM01);
	}
	else if (Paridad == Impar){		//Paridad impar
		UCSR0C |= (1<<UPM01) | (1<<UPM00);
	}
	
	//Configuracion bit de parada
	if (Bit_parada == Uno){		//Un bit de parada
		UCSR0C &= ~(1<<USBS0);
	} 
	else if (Bit_parada == Dos){	//Dos bits de parada
		UCSR0C |= (1<<USBS0);
	}
	
	//Configuracion numero de bits
	if (Numero_Bits == Cinco){		//5 bits de datos
		UCSR0C &= ~(1<<UCSZ00);
		UCSR0C &= ~(1<<UCSZ01);
		UCSR0B &= ~(1<<UCSZ02);
	} 
	else if (Numero_Bits == Seis){	//6 bits de datos
		UCSR0C |= (1<<UCSZ00);
		UCSR0B &= ~(1<<UCSZ02);
	}
	else if (Numero_Bits == Siete){	//7 bits de datos
		UCSR0C |= (1<<UCSZ01);
		UCSR0B &= ~(1<<UCSZ02);
	}
	else if (Numero_Bits == Ocho){	//8 bits de datos
		UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
		UCSR0B &= ~(1<<UCSZ02);
	}
	else if (Numero_Bits == Nueve){	//9 bits de datos
		UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
		UCSR0B |= (1<<UCSZ02);
	}
	//Configuracion Baudrate
	UBRR0 = BAUD;
}

void WriteUART(char* Texto){
	uint8_t i;
	for (i = 0; Texto[i] != '\0'; i++){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = Texto[i];
	}
	
}
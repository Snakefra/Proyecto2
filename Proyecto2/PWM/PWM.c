/*
 * PWM.c
 *
 * Created: 8/05/2024 16:18:13
 *  Author: Snake
 */ 

#include "PWM.h"

void initPWM(uint8_t PWMTimer, uint8_t Canal, uint8_t Modo, uint8_t inversion, uint16_t Prescaler){
	if (PWMTimer == Timer0){ //Configuracion PWM solo para registros del timer0
		
		//Configuracion de canales
		if (Canal == Canal_A){	//Configurando PD6 como salida del PWM0 (0C0A)
			DDRD |= (1<<DDD6);
			TCCR0A = 0;
			
			//Configuracion de inversion canal A
			if (inversion == Invertido){		//Configurando PWM0 modo invertido CANAL A
				TCCR0A |= (1<<COM0A1) | (1<<COM0A0);
			}
			else if (inversion == No_invertido){		//Configurando PWM0 modo No invertido CANAL A
				TCCR0A |= (1<<COM0A1);
			}
		}
		else if (Canal == Canal_B){   //Configurando PD5 como salida del PWM0 (0C0B)
			DDRD |= (1<<DDD5);
			TCCR0B = 0;
			
			//Configuracion de inversion Canal B
			if (inversion == Invertido){		//Configurando PWM0 modo invertido CANAL B
				TCCR0A |= (1<<COM0B1) | (1<<COM0B0);
			}
			else if (inversion == No_invertido){		//Configurando PWM0 modo No invertido CANAL B
				TCCR0A |= (1<<COM0B1);
			}
		}
		//Configuracion de Modos
		if (Modo == Fast){	//Configurando PWM0 modo Fast TOP = 0xFF
			TCCR0A |= (1<<WGM01) | (1<<WGM00);
		}
		else if (Modo == Phase_correct){	//Configurando PWM0 modo Phase correct TOP = 0xFF
			TCCR0A |= (1<<WGM00);
		}
		switch (Prescaler) //Configuracion de seleccion para prescaler
		{
			case 1024:
			TCCR0B |= (1<<CS02) | (1<<CS00);
			break;
			
			case 256:
			TCCR0B |= (1<<CS02);
			break;
			
			case 64:
			TCCR0B |= (1<<CS01) | (1<<CS00);
			break;
			
			case 8:
			TCCR0B |= (1<<CS01);
			break;
			
			case 1:
			TCCR0B |= (1<<CS00);
			break;
		}
	} 
	else if (PWMTimer == Timer1){  //Configuracion PWM solo para registros del timer1
		
		//Configuracion de canales
		if (Canal == Canal_A){	//Configurando PB1 como salida del PWM1 (0C1A)
			DDRB |= (1<<DDB1);
			TCCR1A = 0;
			
			//Configuracion de inversion canal A
			if (inversion == Invertido){		//Configurando PWM1 modo invertido CANAL A
				TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
			}
			else if (inversion == No_invertido){		//Configurando PWM1 modo No invertido CANAL A
				TCCR1A |= (1<<COM1A1);
			}
		}
		else if (Canal == Canal_B){   //Configurando PB2 como salida del PWM1 (0C1B)
			DDRB |= (1<<DDB2);			
			TCCR1B = 0;
			
			//Configuracion de inversion Canal B
			if (inversion == Invertido){		//Configurando PWM1 modo invertido CANAL B
				TCCR1A |= (1<<COM1B1) | (1<<COM1B0);
			}
			else if (inversion == No_invertido){		//Configurando PWM1 modo No invertido CANAL B
				TCCR1A |= (1<<COM1B1);
			}
		}
		//Configuracion de Modos
		if (Modo == Fast){	//Configurando PWM1 modo Fast 8 bit TOP = 0x00FF
			TCCR1A |= (1<<WGM10);
			TCCR1B |= (1<<WGM12);
		}
		else if (Modo == Phase_correct){	//Configurando PWM1 modo Phase correct 8 bit TOP = 0x00FF
			TCCR1A |= (1<<WGM10);
		}
		else if (Modo == Fast_Top){	//Configurando PWM1 modo Fast TOP variable
			TCCR1A |= (1<<WGM11);
			TCCR1B |= (1<<WGM13) | (1<<WGM12);
			ICR1H = 0x9C;	//20ms periodo
			ICR1L = 0x3F;
		}
		else if (Modo == Phase_correct_Top){	//Configurando PWM1 modo Phase correct TOP = variable
			TCCR1A |= (1<<WGM11);
			TCCR1B |= (1<<WGM13);
			ICR1H = 0x9C;	//20ms periodo
			ICR1L = 0x3F;
		}
		switch (Prescaler) //Configuracion de seleccion para prescaler
		{
			case 1024:
			TCCR1B |= (1<<CS12) | (1<<CS10);
			break;
			
			case 256:
			TCCR1B |= (1<<CS12);
			break;
			
			case 64:
			TCCR1B |= (1<<CS11) | (1<<CS10);
			break;
			
			case 8:
			TCCR1B |= (1<<CS11);
			break;
			
			case 1:
			TCCR1B |= (1<<CS10);
			break;
		}
	}
	else if (PWMTimer == Timer2){	//Configuracion PWM solo para registros del timer2
		
		//Configuracion de canales
		if (Canal == Canal_A){	//Configurando PB3 como salida del PWM2 (0C2A)
			DDRB |= (1<<DDB3);
			TCCR2A = 0;
			
			//Configuracion de inversion canal A
			if (inversion == Invertido){		//Configurando PWM2 modo invertido CANAL A
				TCCR2A |= (1<<COM2A1) | (1<<COM2A0);
			}
			else if (inversion == No_invertido){		//Configurando PWM2 modo No invertido CANAL A
				TCCR2A |= (1<<COM2A1);
			}
		}
		else if (Canal == Canal_B){   //Configurando PD3 como salida del PWM2 (0C2B)
			DDRD |= (1<<DDD3);
			TCCR2B = 0;
			
			//Configuracion de inversion Canal B
			if (inversion == Invertido){		//Configurando PWM2 modo invertido
				TCCR2A |= (1<<COM2B1) | (1<<COM2B0);
			}
			else if (inversion == No_invertido){		//Configurando PWM2 modo No invertido
				TCCR2A |= (1<<COM2B1);
			}
		}
		//Configuracion de Modos
		if (Modo == Fast){	//Configurando PWM2 modo Fast TOP = 0xFF
			TCCR2A |= (1<<WGM21) | (1<<WGM20);
		}
		else if (Modo == Phase_correct){	//Configurando PWM2 modo Phase correct TOP = 0xFF
			TCCR2A |= (1<<WGM20);
		}
		switch (Prescaler) //Configuracion de seleccion para prescaler
		{
			case 1024:
			TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
			break;
			
			case 256:
			TCCR2B |= (1<<CS22) | (1<<CS21);
			break;
			
			case 128:
			TCCR2B |= (1<<CS22) | (1<<CS20);
			break;
			
			case 64:
			TCCR2B |= (1<<CS22);
			break;
			
			case 32:
			TCCR2B |= (1<<CS21) | (1<<CS20);;
			break;
			
			case 8:
			TCCR2B |= (1<<CS21);
			break;
			
			case 1:
			TCCR2B |= (1<<CS20);
			break;
		}
	}
}
//Funcion actualizacion de DutyCycle
void updateDutyCycle(uint8_t PWMTimer, uint8_t Canal, uint16_t Duty){  
	//Actualizacion para Timer0
	if (PWMTimer == Timer0){ 
		if (Canal == Canal_A){ //Canal A
			OCR0A = Duty;
		}
		else if (Canal == Canal_B){ //Canal B
			OCR0B = Duty;
		}
	} 
	else if (PWMTimer == Timer1){	//Actualizacion para Timer1
		if (Canal == Canal_A){	//Canal A
			OCR1AH = ((Duty>>8) & 0xFF);
			OCR1AL = (Duty & 0xFF);
		}
		else if (Canal == Canal_B){	//Canal B
			OCR1BH = ((Duty>>8) & 0xFF);
			OCR1BL = (Duty & 0xFF);
		}
	}
	else if (PWMTimer == Timer2){	//Actualizacion para Timer2
		if (Canal == Canal_A){	//Canal A
			OCR2A = Duty;
		}
		else if (Canal == Canal_B){	//Canal B
			OCR2B = Duty;
		}
	}
}

uint16_t map(float Signal, float In_min, float In_max, float Out_min, float Out_max){ //Mapeo señal potenciometro a servo
	return ((Signal - In_min)*(Out_max - Out_min)/(In_max - In_min)) + Out_min;
}

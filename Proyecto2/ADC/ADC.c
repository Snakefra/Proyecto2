/*
 * ADC.c
 *
 * Created: 8/05/2024 16:17:27
 *  Author: Snake
 */ 
#include "ADC.h"

void initADC(uint8_t V_Referencia, uint8_t Justificacion, uint8_t Canal_MUX, uint8_t Auto_Trigger, uint8_t Modo_A_T, uint8_t Interrupciones, uint8_t Prescaler){
	//Configuracion voltaje de referencia
	ADMUX = 0;
	if (V_Referencia == V_ext_5V){ //Vref = AVCC = 5V
		ADMUX |= (1<<REFS0);
	} 
	else if (V_Referencia == V_int_ref){ //Vref = Aref
		ADMUX &= ~(1<<REFS1);
		ADMUX &= ~(1<<REFS0);
	}
	else if (V_Referencia == V_int_bajo1V){ //Vref = 1.1V 
		ADMUX |= (1<<REFS1) | (1<<REFS0);
	}
	
	//Configuracion formato de resultados
	if (Justificacion == Izquierda){  //Justificado a la izquierda
		ADMUX |= (1<<ADLAR);
	} 
	else if (Justificacion == Derecha){	 //Justificado a la derecha
		ADMUX &= ~(1<<ADLAR);
	}
	//Configuracion de canal multiplexeado ADC y deshabilitacion de inputs digitales
	if (Canal_MUX == Canal_0){  //Canal 0
		ADMUX &= ~(1<<MUX2);  
		ADMUX &= ~(1<<MUX1); 
		ADMUX &= ~(1<<MUX0);
		DIDR0 |= (1<<ADC0D);  //Deshabilitacion digital input PC0
		
	} 
	else if (Canal_MUX == Canal_1){  //Canal 1
		ADMUX |= (1<<MUX0);
		DIDR0 |= (1<<ADC1D);  //Deshabilitacion digital input PC1
	}
	else if (Canal_MUX == Canal_2){  //Canal 2
		ADMUX |= (1<<MUX1);
		DIDR0 |= (1<<ADC2D);  //Deshabilitacion digital input PC2
	}
	else if (Canal_MUX == Canal_3){  //Canal 3
		ADMUX |= (1<<MUX1) | (1<<MUX0);
		DIDR0 |= (1<<ADC3D);  //Deshabilitacion digital input PC3
	}
	else if (Canal_MUX == Canal_4){  //Canal 4
		ADMUX |= (1<<MUX2);
		DIDR0 |= (1<<ADC4D);  //Deshabilitacion digital input PC4
	}
	else if (Canal_MUX == Canal_5){  //Canal 5
		ADMUX |= (1<<MUX2) | (1<<MUX0);
		DIDR0 |= (1<<ADC5D);  //Deshabilitacion digital input PC5
	}
	else if (Canal_MUX == Canal_6){  //Canal 6
		ADMUX |= (1<<MUX2) | (1<<MUX1);
	}
	else if (Canal_MUX == Canal_7){  //Canal 7
		ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
	}
	
	ADCSRA = 0;
	ADCSRB = 0;
	//Encendiendo ADC
	ADCSRA |= (1<<ADEN);
	
	//Configuracion activacion Bit Auto trigger
	if (Auto_Trigger == Si_A_T){  //Habilitando Auto trigger
		ADCSRA |= (1<<ADATE); 
		//Configuracion modo de auto trigger
		if (Modo_A_T == Free_nulo){		//Desactivarla o que se active libremente
			ADCSRB &= ~(1<<ADTS0);
			ADCSRB &= ~(1<<ADTS1);
			ADCSRB &= ~(1<<ADTS2);
		} 
		else if (Modo_A_T == Comparador_analogo){	//Activar luego de una comparacion analoga
			ADCSRB |= (1<<ADTS0);
		}
		else if (Modo_A_T == Boton){	//Activar luego de interrupcion externa
			ADCSRB |= (1<<ADTS1);
		}
		else if (Modo_A_T == Comparador_Timer0_A){ //Activar luego de comparacion en Timer0
			ADCSRB |= (1<<ADTS1) | (1<<ADTS0);
		}
		else if (Modo_A_T == Timer0_ovf){	//Activar luego de Overflow en Timer0
			ADCSRB |= (1<<ADTS2);
		}
		else if (Modo_A_T == Comparador_Timer1_B){	//Activar luego de comparacion en Timer1
			ADCSRB |= (1<<ADTS2) | (1<<ADTS0);
		}
		else if (Modo_A_T == Timer1_ovf){	//Activar luego de Overflow en Timer1
			ADCSRB |= (1<<ADTS2) | (1<<ADTS1);
		}
		else if (Modo_A_T == Evento_captura_Timer1){	//Activar luego de captura en Timer1
			ADCSRB |= (1<<ADTS2) | (1<<ADTS1) | (1<<ADTS0);
		}
	}
	else if (Auto_Trigger == No_A_T){  //Deshabilitando Auto trigger
		ADCSRA &= ~(1<<ADATE);
		ADCSRB = 0;
	}
	
	if (Interrupciones == Habilitada){  //Habilitando ISR ADC
		ADCSRA |= (1<<ADIE);
	} 
	else if (Interrupciones == Deshabilitada){  //Deshabilitando ISR ADC
		ADCSRA &= ~(1<<ADIE);
	}
	
	switch (Prescaler) //Configuracion de seleccion para prescaler
	{
		case 128:
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
		break;
		
		case 64:
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1);
		break;
		
		case 32:
		ADCSRA |= (1<<ADPS2) | (1<<ADPS0);
		break;
		
		case 16:
		ADCSRA |= (1<<ADPS2);
		break;
		
		case 8:
		ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
		break;
		
		case 4:
		ADCSRA |= (1<<ADPS1);
		break;
		
		case 2:
		ADCSRA |= (1<<ADPS0);;
		break;
	}
}

void CambioCanal(uint8_t Canal_MUX){
	//Configuracion de canal multiplexeado ADC y deshabilitacion de inputs digitales
	if (Canal_MUX == Canal_0){  //Canal 0
		ADMUX &= ~(1<<MUX2);
		ADMUX &= ~(1<<MUX1);
		ADMUX &= ~(1<<MUX0);
		DIDR0 |= (1<<ADC0D);  //Deshabilitacion digital input PC0
		
	}
	else if (Canal_MUX == Canal_1){  //Canal 1
		ADMUX |= (1<<MUX0);
		DIDR0 |= (1<<ADC1D);  //Deshabilitacion digital input PC1
	}
	else if (Canal_MUX == Canal_2){  //Canal 2
		ADMUX |= (1<<MUX1);
		DIDR0 |= (1<<ADC2D);  //Deshabilitacion digital input PC2
	}
	else if (Canal_MUX == Canal_3){  //Canal 3
		ADMUX |= (1<<MUX1) | (1<<MUX0);
		DIDR0 |= (1<<ADC3D);  //Deshabilitacion digital input PC3
	}
	else if (Canal_MUX == Canal_4){  //Canal 4
		ADMUX |= (1<<MUX2);
		DIDR0 |= (1<<ADC4D);  //Deshabilitacion digital input PC4
	}
	else if (Canal_MUX == Canal_5){  //Canal 5
		ADMUX |= (1<<MUX2) | (1<<MUX0);
		DIDR0 |= (1<<ADC5D);  //Deshabilitacion digital input PC5
	}
	else if (Canal_MUX == Canal_6){  //Canal 6
		ADMUX |= (1<<MUX2) | (1<<MUX1);
	}
	else if (Canal_MUX == Canal_7){  //Canal 7
		ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
	}
}

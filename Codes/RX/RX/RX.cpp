/*
 * Receiver_program.cpp
 *
 * Created: 4/8/2015 5:00:52 PM
 *  Author:relux
 */ 

//#define F_CPU 16000000UL

#include <avr/io.h>
#include <awesome/UART.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char data1;
unsigned char data_main;
uint8_t z=0;
uint8_t speed[2];
uint8_t intensity[2];

int main(void)
{
	DDRA = 0xFF;
	PORTA= 0x00;
	DDRD = 0b00110000;
	PORTD= 0b00001000;
	initialiseUART(2400,0,8,ODD,2,0);
	
	/////////
	GICR |= (1<<INT1);
	MCUCR |= (1<<ISC10) | (1<<ISC11);
	TCNT1 = 0;
	TCCR1A |= (1<<WGM11) |(1<<COM1A0)|(1<<COM1A1)|(1<<COM1B0)|(1<<COM1B1);
	TCCR1B |= (1<<WGM12) |(1<<WGM13) |(1<<CS10);
	//TIMSK |= (1<<OCIE1A);
	ICR1=19999;
	OCR1A=1;
	OCR1B=1;
	sei();
	////////
	while(1)
	{
		while (! (UCSRA & (1 << RXC)) );
		data1 = UDR;
				
		if (data1==0xAE)
		{			
			while (! (UCSRA & (1 << RXC)) );
			data1 = UDR;
			
			if (data1==0xAA)
			{
				while (! (UCSRA & (1 << RXC)) );
				data1 = UDR;
				
				if (data1==0xBB)
				{
					PORTA = (1<<PINA6);
				}					
			
				
				else
				if (data1==0xCC)
				{
					PORTA |= (1<<PINA3)|(1<<PINA4)|(1<<PINA5);
					_delay_ms(500);
					PORTA &=~ (1<<PINA3);
					PORTA &=~ (1<<PINA4);
					PORTA &=~ (1<<PINA5);
					
					LOOP:
					while(2)
					{
						while (! (UCSRA & (1 << RXC)) );
						data1 = UDR;
						
						if (data1==0xAE)
						{
							while (! (UCSRA & (1 << RXC)) );
							data1 = UDR;
							
							if (data1==0xDD)
							{
								while (! (UCSRA & (1 << RXC)) );
								data1 = UDR;
								
								if (data1==0xDD)
								{
									while (! (UCSRA & (1 << RXC)) );
									data_main = UDR;
									
									while (! (UCSRA & (1 << RXC)) );
									data1=UDR;
									
									if (data1==0xEE)
									{
										while (! (UCSRA & (1 << RXC)) );
										data1=UDR;
										
										if (data1==0xEE)
										{
											////////// THE ZONE
											while(3)
											{
												if (data_main == 0x0C)
												{
													 PORTA ^= (1<<PINA0);
													 PORTA ^= (1<<PINA3);
													 goto LOOP;
												}
												
												else													  
												if (data_main == 0x0D) 
												{
													PORTA ^= (1<<PINA1);
													PORTA ^= (1<<PINA4);
													goto LOOP;
												}
												
												else 
												if (data_main == 0x0E)  
												{
													PORTA ^= (1<<PINA2);
													PORTA ^= (1<<PINA5);
													goto LOOP;
												}
												
												else
												if (data_main == 0x0A)
												{
													z=1;
													speed[0]=1;
													goto LOOP;
												}
												
												else
												if (data_main == 0xA0)
												{
													z=1;
													speed[1]=1;
													goto LOOP;
												}
												
												else
												if (data_main == 0x0B)
												{
													z=1;
													intensity[0]=1;
													goto LOOP;
												}
												
												else
												if (data_main == 0xB0)
												{
													z=1;
													intensity[1]=1;
													goto LOOP;
												}
											}
												
																																				
											////////// THE ZONE
										}
									}
								}
							}
							else
							if (data1==0xAA)
							{
								while (! (UCSRA & (1 << RXC)) );
								data1 = UDR;
							
								if (data1==0xBB)
								{
									PORTA = (1<<PINA6);
								}
							}
						}		
					}									
				}
			}					
		}			
	}
}

ISR(INT1_vect)
{
	_delay_us(500);
	if (z==1)
	{
		z=0;
		
		if (speed[0]==1)
		{
			speed[0]=0;
			OCR1A=OCR1A-2000;
			if(OCR1A<1)
			{
				OCR1A=OCR1A+2000;
			}
		}
		
		else
		if (speed[1]==1)
		{
			speed[1]=0;
			OCR1A=OCR1A+2000;
			if(OCR1A>10001)
			{
				OCR1A=OCR1A-2000;
			}
		}
		
		else
		if (intensity[0]==1)
		{
			intensity[0]=0;
			OCR1B=OCR1B-2000;
			if(OCR1B>10001)
			{
				OCR1B=OCR1B+2000;
			}
		}
		
		else
		if (intensity[1]==1)
		{
			intensity[1]=0;
			OCR1B=OCR1B+2000;
			if(OCR1B>10001)
			{
				OCR1B=OCR1B-2000;
			}
		}
	}
	
	TCNT1=19998;
}


/*
 * home_automation.cpp
 *
 * Created: 4/4/2015 2:31:01 PM
 *  Author: rhitvik the digital one
 */ 


#include <avr/io.h>
#include <awesome/UART.h>
#include <util/delay.h>

uint8_t pressed=0;
	
void sw_debounce_pressed(void);
void sw_debounce_released(void);

void predata_transmit(void);
void post_data_transmit(void);

int main(void)
{	
	DDRB =0x00;
	PORTB=0xFF;
	
	DDRC =0b11111111;
	PORTC=0b00000000;
	
	DDRD =0b00000000;
	PORTD=0b11111111;
	
	initialiseUART(2400,0,8,ODD,2,0);
		
	TransmitUART(0xAE); //gar
	TransmitUART(0xAA); //poll
	TransmitUART(0xBB); //res
	
	_delay_ms(500);
	
	TransmitUART(0xAE);
	TransmitUART(0xAA);
	TransmitUART(0xCC);
		
    while(1)
    {
      if (bit_is_clear(PINB,0))
      {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0x0A);
			  post_data_transmit();
			  PORTB ^= (1<<PINB0);
		  }
		  
      }
	  
	  else if (bit_is_clear(PINB,1))
	  {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0xA0);
			  post_data_transmit();
			  PORTB ^= (1<<PINB1);
		  }
	  }
	  
	  else if (bit_is_clear(PINB,2))
	  {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0x0B);
			  post_data_transmit();
			  PORTB ^= (1<<PINB2);
		  }
	  }
	  
	  else if (bit_is_clear(PINB,3))
	  {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0xB0);
			  post_data_transmit();
			  PORTB ^= (1<<PINB3);
		  }
	  }
	  
	  else if (bit_is_clear(PINB,4))
	  {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0x0C);
			  post_data_transmit();
			  PORTB ^= (1<<PINB4);
		  }
	  }
	  
	  else if (bit_is_clear(PINB,5))
	  {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0x0D);
			  post_data_transmit();
			  PORTB ^= (1<<PINB5);
		  }
	  }
  
	  else if (bit_is_clear(PINB,6))
	  {
		  sw_debounce_pressed();
		  if (pressed==0)
		  {
			  pressed=1;
			  TransmitUART(0xAE);
			  predata_transmit();
			  TransmitUART(0x0E);
			  post_data_transmit();
			  PORTB ^= (1<<PINB6);
		  }
	  }
	  
	  else if (bit_is_set(PINB,0))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	  else if (bit_is_set(PINB,1))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	  else if (bit_is_set(PINB,2))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	  else if (bit_is_set(PINB,3))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	  else if (bit_is_set(PINB,4))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	  else if (bit_is_set(PINB,5))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	  else if (bit_is_set(PINB,6))
	  {
		  if (pressed==1)
		  {
			  pressed=0;
			  sw_debounce_released();
		  }
	  }
	  
	}
}
void sw_debounce_pressed(void)
{
	unsigned int pressed_confidence_level=0;
	pressed_confidence_level++;
	if(pressed_confidence_level>=500)//put a debouncing value///////////////
	{
		pressed_confidence_level=0;
	}
}

void sw_debounce_released(void)
{
	unsigned int released_confidence_level=0;
	released_confidence_level++;

	if(released_confidence_level>=500)//put a debouncing value//////////////
	{
		released_confidence_level=0;
	}
}

void predata_transmit(void)
{
	TransmitUART(0xDD);
	TransmitUART(0xDD);
}
void post_data_transmit(void)
{
	TransmitUART(0xEE);
	TransmitUART(0xEE);
}


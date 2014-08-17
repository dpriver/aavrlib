
#include <stdint.h>
#include "spi.h"

volatile static struct{
	uint8_t send_buffer[1<<8];
	uint8_t length;
	uint8_t burst_length;
	uint8_t sending;
}spi_attr;

void spi_send_block(const uint8_t caracters[], uint8_t length){
	spi_setup_master();
	for(int i = 0; i<length ; i++){
		spi_sendbyte(caracters[i]);
	}
}

void spi_send_burst(const uint8_t caracters[], uint8_t length, uint8_t burst_length){
	spi_setup_master();
	spi.attr.send_buffer = new uint8_t
	for(int i = 0; i< length ; i++)

	spi_attr.sending = 1;
}

ISR(SPI_STC_vect, BLOCK){
	if(spi_attr.sending)
		isr_handle_send();
	else
		isr_handle_receive();
}

void isr_handle_send(){

}

void isr_handle_receive(){

}
#include <stdint.h>
#include "spi.h"


void spi_send_block(uint8_t caracters[], uint8_t length){
	spi_setup_master();
	spi_begin_transmission();
	for(int i = 0; i<length ; i++){
		spi_sendbyte(caracters[i]);
		while(!spi_finished_transmission());
	}
	spi_end_transmission();
}
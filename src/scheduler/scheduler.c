


#define NUM_ENTRIES 5


#typedef struct schel_entry{
	schedule_handler handler;
	uint8_t comp;
	uint8_t lapse;
	uint8_t enabled;	
};

volatile static struct{
	schedule_handler handler;
	uint8_t comp;
	uint8_t lapse;
	uint8_t enabled;
}schedule[NUM_ENTRIES];





#include "system/task_rand.h"
#include "system/hardware_task.h"
#include "system/data_channel.h"
#include "system/float_word.h"
#include "system/rand_config.h"

int task_rand_run( void * task ) {

    // TODO
	rand_config * rand = (rand_config * ) task;

	float_word valueRand;
	uint32_t lfsr = rand->seed;

	// RAND
	for ( uint32_t i = 0; i < DATA_CHANNEL_DEPTH; i++ )
	{
		uint32_t help = ( (lfsr >> 0) ^ (lfsr >> 1) ^ (lfsr >> 11) ^ (lfsr >> 31) ) & 1u;
		lfsr = (lfsr >> 1) | (help << 31);	
	
		//printf("%e\n", valueRand.value);

		// check if is in valid range
		if( abs(lfsr) > rand->abs_max )
		{
			valueRand.word = lfsr & 0xC0FFFFFF;
			valueRand.word = valueRand.word | 0x40000000;
		}

		if( abs(lfsr) < rand->abs_min )
		{
			valueRand.word = lfsr | 0x3EFFFFFF;
		}		
		//printf("Neu: %f\n", valueRand.value);
		data_channel_write(rand->base.sink, valueRand.word);	
	}

    return 0;
}


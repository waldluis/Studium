#include "system/task_add.h"
#include "system/data_channel.h"
#include "system/float_word.h"

int task_add_run( void * task ) {

    // TODO
	add_config * add = (add_config * ) task;
	float_word add1, add2, sum;
	sum.value = 0.0;

	// ADD
	for ( uint32_t i = 0; i < DATA_CHANNEL_DEPTH; i++ )
	{
		data_channel_read(add->sources[0], &add1.word);
		data_channel_read(add->sources[1], &add2.word);
		sum.value = add1.value + add2.value;
		data_channel_write(add->sink, sum.word);
	}
    return 0;
}

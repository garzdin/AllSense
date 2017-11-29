/*
 * buffer.c
 *
 * Created: 11/5/2017 9:43:07 AM
 *  Author: Teodor
 */

#include <stdio.h>
#include <stdlib.h>
#include <buffer/buffer.h>

buffer_t buffer_init(int size) {
	buffer_t buffer;

	(&buffer)->head = (&buffer)->tail = 0;
	
	if (size > 0) {
		(&buffer)->size = size;
		(&buffer)->data = (uint8_t *) malloc(sizeof(uint8_t) * size);
	} else {
		(&buffer)->size = BUFFER_DEFAULT_SIZE;
		(&buffer)->data = (uint8_t *) malloc(sizeof(uint8_t) * BUFFER_DEFAULT_SIZE);
	}
	
	return buffer;
}

buffer_state_t buffer_state(volatile buffer_t *buffer) {
	if (buffer->tail == 0) {
		return BUFFER_EMPTY;
	} else if(buffer->tail == buffer->size - 1) {
		return BUFFER_FULL;
	} else if (buffer->head == buffer->size - 1) {
		return BUFFER_READ;
	} else {
		return UNKNOWN;
	}
}

buffer_return_t buffer_push(volatile buffer_t *buffer, buffer_el_t data) {
	buffer_return_t ret = BUFFER_ERROR;

	if(!(buffer_state(buffer) == BUFFER_FULL)) {
		buffer->data[buffer->tail++] = data;
		ret = BUFFER_SUCCESS;
	}
	
	return ret;
}

buffer_result_t buffer_pop(volatile buffer_t *buffer) {
	buffer_result_t result;
	(&result)->ret = BUFFER_SUCCESS;
	
	if (buffer_state(buffer) == BUFFER_EMPTY) {
		(&result)->ret = BUFFER_ERROR;
		(&result)->data = 0;
	} else if (buffer_state(buffer) == BUFFER_READ) {
		buffer->head = 0;
		(&result)->data = buffer->data[buffer->head++];
	} else {
		(&result)->data = buffer->data[buffer->head++];
	}
	
	return result;
}

buffer_return_t buffer_free(volatile buffer_t *buffer) {
	if (buffer->data) {
		free(buffer->data);
	}

	buffer->head = buffer->tail = buffer->size = 0;
	
	return BUFFER_SUCCESS;
}

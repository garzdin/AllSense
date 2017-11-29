/*
 * buffer.h
 *
 * Created: 11/5/2017 9:41:10 AM
 *  Author: Teodor
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_

#define BUFFER_DEFAULT_SIZE 8

typedef uint8_t buffer_el_t;

typedef enum {
	UNKNOWN,
	BUFFER_EMPTY,
	BUFFER_FULL,
	BUFFER_READ,
} buffer_state_t;

typedef enum {
	BUFFER_ERROR,
	BUFFER_SUCCESS
} buffer_return_t;

typedef struct {
	int head;
	int tail;
	uint8_t *data;
	int size;
} buffer_t;

typedef struct {
	buffer_el_t data;
	buffer_return_t ret;
} buffer_result_t;

buffer_t buffer_init(int size);
buffer_state_t buffer_state(volatile buffer_t *buffer);
buffer_return_t buffer_push(volatile buffer_t *buffer, buffer_el_t data);
buffer_result_t buffer_pop(volatile buffer_t *buffer);
buffer_return_t buffer_free(volatile buffer_t *buffer);

#endif /* BUFFER_H_ */
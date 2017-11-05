/*
 * buffer.h
 *
 * Created: 11/5/2017 9:41:10 AM
 *  Author: Teodor
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_

#define INITIAL_CAPACITY 0

typedef struct {
	uint8_t size;
	uint8_t capacity;
	uint8_t *data;	
} buffer_t;

void buffer_init(volatile buffer_t *buffer);

void buffer_append(volatile buffer_t *buffer, uint8_t value);

uint8_t * buffer_get(volatile buffer_t *buffer);

uint8_t buffer_get_one(volatile buffer_t *buffer, uint8_t index);

void buffer_set(volatile buffer_t *buffer, uint8_t index, uint8_t value);

void buffer_expand_capacity_if_full(volatile buffer_t *buffer);

void buffer_free(volatile buffer_t *buffer);



#endif /* BUFFER_H_ */
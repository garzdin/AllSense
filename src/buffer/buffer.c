/*
 * buffer.c
 *
 * Created: 11/5/2017 9:43:07 AM
 *  Author: Teodor
 */

#include <stdio.h>
#include <stdlib.h>
#include <buffer/buffer.h>

void buffer_init(volatile buffer_t *buffer) {
	buffer->size = 0;
	buffer->capacity = INITIAL_CAPACITY;
	buffer->data = malloc(sizeof(uint8_t) * buffer->capacity);
}

void buffer_append(volatile buffer_t *buffer, uint8_t value) {
	buffer_expand_capacity_if_full(buffer);
	buffer->data[buffer->size++] = value;
}

uint8_t * buffer_get(volatile buffer_t *buffer) {
	return buffer->data;
}

uint8_t buffer_get_one(volatile buffer_t *buffer, uint8_t index) {
	if (index >= buffer->size || index < 0) {
		return (uint8_t) NULL;
	}
	return buffer->data[index];
}

void buffer_set(volatile buffer_t *buffer, uint8_t index, uint8_t value) {
	while (index >= buffer->size) {
		buffer_append(buffer, 0);
	}
	buffer->data[index] = value;
}

void buffer_free(volatile buffer_t *buffer) {
	free(buffer->data);
}

void buffer_expand_capacity_if_full(volatile buffer_t *buffer) {
	if (buffer->size >= buffer->capacity) {
		buffer->capacity += 1;
		buffer->data = realloc(buffer->data, sizeof(uint8_t) * buffer->capacity);
	}
}

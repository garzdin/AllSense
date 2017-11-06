/*
 * command.h
 *
 * Created: 11/5/2017 11:34:46 AM
 *  Author: Teodor
 */ 


#ifndef COMMAND_H_
#define COMMAND_H_

#include <asf.h>
#include <string.h>
#include <buffer/buffer.h>

buffer_t make_command(uint8_t * string);
bool check_response(volatile buffer_t * buffer, const char * string);

#endif /* COMMAND_H_ */
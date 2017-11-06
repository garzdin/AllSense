/*
 * command.c
 *
 * Created: 11/5/2017 11:35:24 AM
 *  Author: Teodor
 */ 

#include <command/command.h>

buffer_t make_command(uint8_t * string) {
	buffer_t command;
	buffer_init(&command);
	
	while(*string) {
		buffer_append(&command, *string);
		string++;
	}
	
	return command;
}

bool check_response(volatile buffer_t * buffer, const char * string) {
	if (strstr((char*)buffer_get(buffer), string)) {
		return true;
	}
	
	return false;
}
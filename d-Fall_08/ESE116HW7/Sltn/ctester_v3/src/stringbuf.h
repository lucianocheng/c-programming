#ifndef _CTESTER_STRINGBUF_H_
#define _CTESTER_STRINGBUF_H_

#include <stdio.h>

/**
 * Struct for a "String Buffer Type" _STRBUF that is used instead of strings
 */
typedef struct _ct_str_buffer
{
	int len;
	int size;
	int resize_factor;
	char* buffer;
} _STRBUF;

/**
 * Calloc the requested memory or exit the program
 *
 * @param num the number of units to index
 * @param size the size of a given unit
 * @param msg the message to print if the calloc fails
 */
void* _calloc_or_die(size_t num, size_t size, const char* msg);

/**
 * Create a new _STRBUF struct, initilize the values
 *
 * @param min the minimum size of the starting string buffer
 */
_STRBUF* _strbuf_init(int min);

/**
 * Append a string append_str on to the end of the string buffer 'buf'
 *
 * @param buf the buffer to add the string on to
 * @param append_str the string to append
 */
void _strbuf_append(_STRBUF* buf, char* append_str);

/**
 * free a stringbuffer cleanly
 *
 * @param buf the string buffer to free
 */
void _strbuf_free(_STRBUF* buf);

/**
 * Replaces instances of the search string with the replace string in 'string'; 
 * Written By -  Lehner Franz (franz@caos.at) 2002
 *
 * @param string the string to do the operation on
 * @param search the string to search for
 * @param replace the string to replace the first string with
 * @return return the edited string
 */
char * str_replace (char * string,char * search,char *replace);

/**
 * Replaces '<' and '>' in the xml docs so the xml does not crash
 *
 * @param string the string to do the replacement on
 * @return return the edited string
 */
char * xml_escape(char* string);

/**
 * Sanitize a string result so as not to be a crazy character that crashes the XML parser
 *
 * @param output_string the string to be sanitized, which will have invalid characters replaced with '~'
 * @return the output_string array formatted, invalid characters replaced with '~'
 */
char* _sanitize_string(char* output_string);


/**
 * Sanitize a char result so as not to be a crazy character that crashes the XML parser
 *
 * @param output the char to be sanitized
 * @param message_array the array to write the message to
 * @return the message formatted, either with the char or with a message saying the char is invalid
 */
char* _sanitize_char(char output, char* message_array);

#endif

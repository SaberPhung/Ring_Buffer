#include "ringbuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void init_buffer(struct buffer_type *b, unsigned char *buffer)
{
	b->head=buffer;
	b->tail=buffer;
	b->buffer=buffer;
}
enum error_type empty_buffer(struct buffer_type *b)
{
	b->tail=b->head;
	return OK;
}
int get_buffer_state(struct buffer_type *b,enum error_type *err)
{
	int state;
	if(!b|| !b->head || !b->tail || !b->buffer)
	{
		*err= POINTER_ERROR;
		state=-1;
    }
    else if((b->tail==b->head+1)||(b->head == (b->tail+MAX_BUFFER-1)))
	{
		*err= BUFFER_FULL;
		state=b->head-b->tail;
	}
	else if(b->head == b->tail)
	{
		*err= EMPTY_BUFFER;
		state=0;
	}
	else
	{	
		*err=OK;
		if(b->head <b->tail)
			{
			state=(MAX_BUFFER-1)-(b->tail-b->head);
			}
		else
		state=b->head-b->tail;
    }
	return state;
}
int add_char_to_buffer(struct buffer_type *b,unsigned char c,enum error_type *err)
{
	//call get_buffer_state function to get state of error_type err
	get_buffer_state(b,err);
	if(*err==BUFFER_FULL) {return -1;}
	else if(*err==POINTER_ERROR){ return -1;}
	else if(*err=EMPTY_BUFFER)
	{
		*b->head=c;
		b->head++;
		return 1;
	}
	else{ //buffer went arount
		*b->head=c;
		(b->head==b->buffer+MAX_BUFFER-1) ? (b->head=b->buffer):(b->head++);
	}	
	return b->head-b->tail;
}
char get_char_from_buffer(struct buffer_type *b, enum error_type *err)
{
	get_buffer_state(b,err);
	unsigned char *c;
	if(*err==POINTER_ERROR || *err==EMPTY_BUFFER)
	{
		return -1;
	}
	c = b->tail;
	(b->tail ==b->buffer+MAX_BUFFER-1) ?(b->tail=b->buffer):(b->tail++);
	return *c;
}
int print_buffer(struct buffer_type *b, enum error_type *err)
{
	int state;
	int i=0;
	unsigned char *temp;
	state=get_buffer_state(b,err);
	temp=b->tail;
	if(*err==POINTER_ERROR || *err== EMPTY_BUFFER) 
	{
		state= -1;
	}
	else
	{
		while(i<state){
			printf("%c ", *(temp++));//should be temp++ in order to move pointer through each cell in array
			if(temp==b->buffer+(MAX_BUFFER-1)){
				temp=b->buffer;
			}
			i++;
		}
		printf("\n");
	}
	return state;

}
int add_string_to_buffer(struct buffer_type *b, unsigned char *s, enum error_type *err)
{
	get_buffer_state(b,err);
	if(*err==BUFFER_FULL) {return -1;}
	else if(*err==POINTER_ERROR){ return -1;}
	else if(*err=EMPTY_BUFFER)
	{
		for(int i=0; i<strlen(s); i++)
		{
			*b->head=s[i];
			b->head++;
		}
	return b->head-b->tail;
	}
	else{ //buffer went arount
		for(int i=0; i<strlen(s); i++)
		{
			*b->head=s[i];
			(b->head==b->buffer+MAX_BUFFER-1) ? (b->head=b->buffer):(b->head++);
		}

	}	
	return b->head-b->tail;
	/*for(int i=0; i<MAX_BUFFER-1;i++){
		add_char_to_buffer(b,s[i],err);
	}
	return b->head-b->tail;*/
}
int get_string_from_buffer(struct buffer_type *b,unsigned char *dest, int len, enum error_type *err)
{
	unsigned char *c=dest;
	int count=0;
	while((count<len) && get_char_from_buffer(b,err)){
		count++;
		c++;		
	}
	return count;
}



#include <gtest/gtest.h>
#include "ringbuffer.h"

TEST (initcategory,test)
{
       unsigned char rx_buffer[MAX_BUFFER];
       struct buffer_type r;
       init_buffer(&r, rx_buffer);
       EXPECT_EQ(r.head,rx_buffer);
       EXPECT_EQ(r.tail,rx_buffer);
       EXPECT_EQ(r.buffer,rx_buffer);
}
TEST(empty_buffer, normal)
{
    unsigned char rx_buffer[MAX_BUFFER];
    struct buffer_type r;
	error_type err;
	r.buffer = rx_buffer;
	r.head=rx_buffer+3;       
    r.tail=rx_buffer+1;
	err = empty_buffer(&r);
	EXPECT_EQ(err,OK);
    EXPECT_EQ(r.head, rx_buffer+3);
    EXPECT_EQ(r.tail, r.head);
    EXPECT_EQ(r.buffer, rx_buffer);
}
TEST (bufferState,test)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	int state;
	error_type err;
	r.buffer=rx_buffer;
	r.head=rx_buffer+10;
	r.tail=rx_buffer+4;
	state=get_buffer_state(&r, &err);
	EXPECT_EQ(state,6);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(r.head, rx_buffer+10);
	EXPECT_EQ(r.tail, rx_buffer+4);
	EXPECT_EQ(r.buffer, rx_buffer);
}
TEST(bufferState,test1)
{
	struct buffer_type r;
    unsigned char *rx_buffer = NULL;
    int amount;
    error_type err;
    r.buffer=rx_buffer;
    amount=get_buffer_state(&r,&err);
    EXPECT_EQ(amount, -1);
    EXPECT_EQ(err, POINTER_ERROR);
    EXPECT_EQ(r.buffer, rx_buffer);
}
TEST (bufferState, test2)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	int state;
	error_type err;
	init_buffer(&r,rx_buffer);
	r.head=rx_buffer+3;
	r.tail=rx_buffer+3;
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,0);
	EXPECT_EQ(err,EMPTY_BUFFER);
	EXPECT_EQ(r.head,r.tail);
}
TEST (bufferState, test3)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	int state;
	error_type err;
	init_buffer(&r,rx_buffer);
	r.head=rx_buffer+1023;
	r.tail=rx_buffer;
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,1023);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_NE(r.head,r.tail);
}
TEST(bufferstate,test4)
{
    unsigned char rx_buffer[MAX_BUFFER];	
    struct buffer_type r;
    int state;
    error_type err;	
    r.buffer=rx_buffer;
    r.head=rx_buffer+1;       
    r.tail=rx_buffer+20;
    state=get_buffer_state(&r,&err);
    EXPECT_EQ(state,1004);		
    EXPECT_EQ(r.head, rx_buffer+1);
    EXPECT_EQ(r.tail, rx_buffer+20);
    EXPECT_EQ(r.buffer, rx_buffer);
}

TEST (addCharToBuffer,test1)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c = 'g';
	unsigned char d ='i';
	init_buffer(&r,rx_buffer);
	add_char_to_buffer(&r,c,&err);
	add_char_to_buffer(&r,d,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,2);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(r.head,rx_buffer+2);
	EXPECT_EQ(r.tail,rx_buffer);
}
TEST (addCharToBuffer,test2)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c= 'a';
	r.head=rx_buffer+1022;
	r.tail=rx_buffer;
	add_char_to_buffer(&r,c,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,1023);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(r.head,rx_buffer+1023);
}
TEST (addCharToBuffer,test3)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c='b';
	r.buffer=rx_buffer;
	r.head=rx_buffer;
	r.tail=rx_buffer+1;
	add_char_to_buffer(&r,c,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,-1);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(r.tail,rx_buffer+1);
	EXPECT_EQ(r.head,rx_buffer);
}
TEST (addCharToBuffer,test4)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c='d';
	r.head=rx_buffer+1023;
	r.tail=rx_buffer+1022;
	add_char_to_buffer(&r,c,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,2);
	EXPECT_EQ(err,OK);
	EXPECT_NE(r.head,rx_buffer);
	EXPECT_EQ(r.tail,rx_buffer+1022);
	
}
TEST (addCharToBuffer,test5)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c='d';
	r.head=rx_buffer+1;
	r.tail=rx_buffer+1;
	add_char_to_buffer(&r,c,&err);
	EXPECT_EQ(state,0);
	EXPECT_EQ(err,EMPTY_BUFFER);
	EXPECT_EQ(r.tail,rx_buffer+1);
}
TEST(addCharToBuffer,test6)
{
    unsigned char *rx_buffer = NULL;
    struct buffer_type r;
    int state;
    error_type err;
	unsigned char c = 'p';
    r.buffer = rx_buffer;
	r.head = rx_buffer+1;       
	r.tail = rx_buffer+2;
    state=add_char_to_buffer(&r,c,&err);
    EXPECT_EQ(state, -1);
    EXPECT_EQ(err, POINTER_ERROR);
	EXPECT_EQ(r.head, rx_buffer+1);
	EXPECT_EQ(r.tail, rx_buffer+2);
    EXPECT_EQ(r.buffer, rx_buffer);
}
TEST (getCharToBuffer,test1)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c='m';
	init_buffer(&r,rx_buffer);
	add_char_to_buffer(&r,c,&err);
	unsigned char d= get_char_from_buffer(&r,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,0);
	EXPECT_EQ(err,EMPTY_BUFFER);
	EXPECT_EQ(d,c);
}
TEST (getCharToBuffer,test2)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c='n';
	unsigned char e='o';
	unsigned char q='p';
	init_buffer(&r,rx_buffer);
	r.head=rx_buffer+3;
	r.tail=rx_buffer;
	add_char_to_buffer(&r,c,&err);
	add_char_to_buffer(&r,e,&err);
	add_char_to_buffer(&r,q,&err);
	unsigned char d=get_char_from_buffer(&r,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,5);
	EXPECT_EQ(err,OK);
	EXPECT_NE(d,c);
	EXPECT_EQ(r.head,rx_buffer+6);
	EXPECT_EQ(r.tail,rx_buffer+1);
}
TEST (printBuffer,test)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	unsigned char c='a';
	unsigned char d='b';
	unsigned char e='c';
	r.buffer=rx_buffer;
	r.head=rx_buffer;
	r.tail=rx_buffer;
	add_char_to_buffer(&r,c,&err);
	add_char_to_buffer(&r,d,&err);
	add_char_to_buffer(&r,e,&err);
	int n=print_buffer(&r,&err);
	state =get_buffer_state(&r,&err);
	EXPECT_EQ(state,n);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(r.head,rx_buffer+3);
	EXPECT_EQ(r.tail,rx_buffer);
}
TEST (printBuffer,test1)
{
	unsigned char rx_buffer[MAX_BUFFER]="abcd";
	struct buffer_type r;
	error_type err;
	int state;
	int pos;
	init_buffer(&r,rx_buffer);
	for(int i=4; i<MAX_BUFFER;i++){
		*(rx_buffer+i) = 'o';
	}
	r.head=rx_buffer +3;
	r.tail=rx_buffer +1022;
	state=print_buffer(&r,&err);
	pos=get_buffer_state(&r,&err);
	EXPECT_EQ(state,pos);
	EXPECT_EQ(state,4);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(r.tail,rx_buffer+1022);
	EXPECT_EQ(r.head,rx_buffer+3);
	
}

TEST (addStringToBuffer,test1)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	init_buffer(&r,rx_buffer);
	unsigned char str[]="giao";
	add_string_to_buffer(&r,str,&err);
	state=get_buffer_state(&r,&err);
	EXPECT_EQ(state,4);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(r.head,rx_buffer+4);
	EXPECT_EQ(r.tail,rx_buffer);
}

/*TEST (addStringToBuffer,test2)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	char str[]="giao12345678";
	init_buffer(&r,rx_buffer);
	r.head=rx_buffer+1024;
	add_string_to_buffer(&r,str,&err);
	EXPECT_EQ(state,-1);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(r.head,rx_buffer+1024);
	EXPECT_EQ(r.tail,rx_buffer);
}*/
TEST (getStringToBuffer,test1)
{
	unsigned char rx_buffer[MAX_BUFFER];
	struct buffer_type r;
	error_type err;
	int state;
	init_buffer(&r,rx_buffer);
	char str[]="giao123";
	int len=add_string_to_buffer(&r,str,&err);
	state=get_buffer_state(&r,&err);
	unsigned char dest[10];
	get_string_from_buffer(&r,dest,len,&err);
	EXPECT_EQ(state,7);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(r.head,rx_buffer+7);
	EXPECT_EQ(r.tail,rx_buffer+7);
}

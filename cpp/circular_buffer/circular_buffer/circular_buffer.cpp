// minimal implementation of a circular buffer

#include "stdafx.h"
#include <stdlib.h>     
#include <time.h>       
#include <iostream>
#include <thread>
#include <chrono>

#define BUFFER_SIZE 10
#define INCR(x) (((x)+1)%BUFFER_SIZE) 
#define DECR(x) ((((x)+BUFFER_SIZE)-1)%BUFFER_SIZE)


char buffer[BUFFER_SIZE];
volatile int start_idx = 0;
volatile int end_idx = 0;

int write_buffer_help(char* data, int len)
{
	int temp_start_idx, temp_end_idx, j;

	for (j = 0;
		temp_start_idx = start_idx, //acquire read
		temp_end_idx = end_idx, //acquire read
		temp_end_idx != DECR(temp_start_idx) && j < len;
		++j)
	{
		buffer[temp_end_idx] = data[j];

		end_idx = INCR(temp_end_idx); //release write
	}
	return j;
}

void write_buffer(char* data, int len) {
	int i = 0, sent = 0;
	do {
		i = write_buffer_help(&data[sent], len - sent);
		sent += i;
	} while (sent != len);
	return;
}

int read_buffer_help(char* data, int len)
{//read untill data is filled
	int temp_end_idx, temp_start_idx, j;

	for (j = 0;
		temp_end_idx = end_idx, //acquire read
		temp_start_idx = start_idx, //acquire read
		temp_start_idx != temp_end_idx && j < len;
		++j
		)
	{
		data[j] = buffer[temp_start_idx];
		start_idx = INCR(temp_start_idx); //release write
	}
	return j;
}

void read_buffer(char* data, int len)
{
	int i = 0, received = 0;
	do
	{
		i = read_buffer_help(&data[received], len - received);
		received += i;
	} while (received != len);
	return;
}

void write_in_thread() {
	char data[26];
	int i;
	for (i = 0; i < 26; ++i) {
		data[i] = 'a' + char(i);
		//std::cout << data[i] << std::endl;
	}

	while (true)
	{
		write_buffer(data, sizeof data);

		int sleep_time;

		/* initialize random seed: */
		srand((unsigned int)time(NULL));

		/* generate randome number between 1 and 10: */
		sleep_time = rand() % 10 + 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	return;
}

int main()
{
	std::thread my_thread(write_in_thread);
	while (true) {
		char receive[26];
		int i;
		read_buffer(receive, sizeof receive);
		for (i = 0; i < sizeof receive; ++i)
		{
			std::cout << receive[i];
		}
		std::cout << std::endl;
		int sleep_time;

		/* initialize random seed: */
		srand((unsigned int)time(NULL));

		/* generate randome number between 1 and 10: */
		sleep_time = rand() % 10 + 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

	}


	return 0;
}



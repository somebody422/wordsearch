/*
 * Some util function used by other files
 */

#include <cstdio> //printf in all of its glory
#include <ctime> //time, localtime, time_t, tm

#include "../wordsearch.h"



time_t unix_time;
tm* t;

void log(std::string source, std::string message){
	time(&unix_time);
	t = localtime(&unix_time);
	printf("%d:%d:%d  %s:  %s\n", t->tm_hour, t->tm_min, t->tm_sec, source.c_str(), message.c_str());
}



void log(std::string message){
	time(&unix_time);
	t = localtime(&unix_time);
	printf("%d:%d:%d\t %s\n", t->tm_hour, t->tm_min, t->tm_sec, message.c_str());
}




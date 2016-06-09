/*
 * The printFromQueue_thread function is used by a thread to wait on a queue for input. Input is directed to the std::cout stream
 */
#include <iostream> //std::cout
#include <thread> //std::this_thread::yield()
#include "../wordsearch.h"


int printFromQueue_thread(MessageQueue* queue){
	
	while(queue->hasMore() || !queue->isDone()){
		if(queue->hasMore()){
			std::cout << queue->pop();
		}
		std::this_thread::yield();
	}
	
	return 0;
}
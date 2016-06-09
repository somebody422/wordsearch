/*
 * Methods for the MessageQueue object
 * MessageQueue is used by input and output threads
 */

#include "../wordsearch.h"


MessageQueue::MessageQueue() : done(false) {}


bool MessageQueue::isDone(){
	mutex.lock();
	bool t = done && queue.empty();
	mutex.unlock();
	return t;
}
	

void MessageQueue::setDone(){
	mutex.lock();
	done = true;
	mutex.unlock();
}


void MessageQueue::push(std::string str){
	mutex.lock();
	if(done)
		log("MessageQueue::pushString(std::string)", "Queue has been set to done, will not push " + str);
	else
		queue.push(str);
	mutex.unlock();
}


std::string MessageQueue::pop(){
	mutex.lock();
	if(queue.empty()){
		log("MessageQueue::pop()", "pop method called on empty queue");
		return "";
	}
	std::string s = queue.front();
	queue.pop();
	mutex.unlock();
	return s;
}


bool MessageQueue::hasMore(){
	mutex.lock();
	bool empty = queue.empty();
	mutex.unlock();
	return !empty;
}
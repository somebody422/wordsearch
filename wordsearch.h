/*
 * Header file for all source files in the project.
 * Most documentation for functions can be found in this file.
 */

#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <fstream>

/*
 * Methods defined in message_queue.cpp
 */
class MessageQueue{
	bool done;
	std::queue<std::string> queue;
	std::mutex mutex;
	
public:
	MessageQueue();
	
	/*
	 * Attempts to lock mutex, will block if it is locked
	 * returns true if queue is empty and done is true
	 */
	bool isDone();
	
	/*
	 * Set the MessageQueue state to done. The queue no longer
	 *  expects new push() calls, and isDone will return true
	 *  once queue is empty
	 * Attempts to lock mutex, will block if it is locked
	 */
	void setDone();
	
	/*
	 * Push string to end of queue
	 * If mutex is unavailable, thread will block until it
	 *  has been released.
	 */
	void push(std::string);
	
	/*
	 * Returns a string from the front of the queue
	 * Returns an empty string if the queue is empty. However, reading
	 *  threads should check using hasMore() first before requesting data.
	 * If mutex is unavailable, a thread will block until the mutex has
	 *  been released
	 */
	std::string pop();
	
	/*
	 * Locks mutex, waits for mutex if it is locked
	 * Returns true if the queue is not empty. False otherwise.
	 */
	bool hasMore();
};



/*
 * Defined in read_file.cpp
 * This function will passed to a thread.
 * Searches for matches to strings in words in the given text
 *  file. When a match is found, the desired output
 *  is formatted then written to queue
 *  
 *  Return:
 *  0 on success
 *  1 if error while accessing/opening file
 */
int readFile_thread(std::string path, std::vector<std::string> words, MessageQueue* queue);



/*
 * Defined in print_from_queue.cpp
 * This function will be passed to a thread.
 * Waits for messages to appear in queue, and removes/prints
 *  them to stdout when they do.
 * Note: formatting is done before the message appears in the
 *  queue. It is outputted by this function as-is.
 * 
 */
int printFromQueue_thread(MessageQueue* queue);



/*
 * Defined in util.cpp
 * Prints an error message formatted with the provided source, and
 *  also the time of the message
 */
void log(std::string source, std::string message);

/*
 * Defined in util.cpp
 * Prints an error message with the time of the message.
 */
void log(std::string message);
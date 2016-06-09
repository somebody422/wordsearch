/*
 * The readFile_thread function is used by a thread to read through a file and print some output to a MessageQueue.
 */

#include <fstream> //std::ifstream
#include "../wordsearch.h"




int readFile_thread(std::string path, std::vector<std::string> words, MessageQueue* queue){
	
	std::ifstream file (path.c_str());
	
	if(!file.is_open()){
		log("readFile_thread(std::string, std::vector<std::string>, MessageQueue&)", "Unable to open file \"" + path + "\"");
		queue->setDone();
		return -1;
	}
	
	std::string line;
	while(getline(file, line)){
		
		for(unsigned int i = 0; i < line.length(); i++){
			for(std::vector<std::string>::iterator word_iter = words.end()-1;
				word_iter >= words.begin(); word_iter--)
			{
				if(word_iter->compare(line.substr(i, word_iter->length())) == 0){
					queue->push((*word_iter) + " " + path + '\n'); //todo: remove parens around word_iter
					//erasing will not affect elements before the iterator in the underlying array... that is why we are iterating backwards!
					words.erase(word_iter);
				}
			}
		}
		
	} //while
	
	queue->setDone();
	file.close();
	return 0;
}


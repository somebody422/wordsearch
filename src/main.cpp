/*
 * Sam Hedin
 * Project 1 for csci251
 * 
 * This project uses c++11
 * 
 * 
 */

#include <iostream>
#include <thread>
#include "../wordsearch.h"

#define DELIM ','
#define DOUBLE_DELIM ",,"


/*
 * Will break string into pieces separated by the given deliminator
 */
static std::vector<std::string> splitString(std::string&);


//each provided file is represented by and IOStruct. The actual file handle
// is located in the inThread thread object
struct IOStruct{
	MessageQueue queue;
	std::thread outThread;
	std::thread inThread;
};


int main(int argc, char** argv){
	
/*
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Check input for validity, and parse
 */
	if(argc != 3){
		log("main.cpp : main()", "Input of invalid form: must be 3 total arguments");
		std::cout << "Usage: WordSearch FILE1,FILE2,... WORD1,WORD2,...\n";
		return 1;
	}
	
	std::string files_str = argv[1];
	std::string words_str = argv[2];
	
	//input is invalid if the first or last letter is the deliminator
	if(files_str.front() == DELIM || files_str.back() == DELIM ||
		words_str.front() == DELIM || words_str.back() == DELIM)
	{
		log("main.cpp : main()", "Input of invalid form: leading or trailing deliminators");
		std::cout << "Usage: WordSearch FILE1,FILE2,... WORD1,WORD2,...\n";
		return 2;
	}
	
	//input is invalid if there is a double delmininator
	if(files_str.find(DOUBLE_DELIM) != std::string::npos || 
		words_str.find(DOUBLE_DELIM) != std::string::npos){
		log("main.cpp : main()", "Input of invalid form: double deliminator in input");
		std::cout << "Usage: WordSearch FILE1,FILE2,... WORD1,WORD2,...\n";
		return 3;
	}
	
	//parse file names and words from args
	std::vector<std::string> files_vec = splitString(files_str);
	std::vector<std::string> words_vec = splitString(words_str);
	
	
	
/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * create and join threads
 */

	IOStruct structs[files_vec.size()];
	
	//start output threads
	for(unsigned int i = 0; i < files_vec.size(); i++){
		structs[i].outThread = std::thread(printFromQueue_thread, &structs[i].queue);
	}
	
	//start input threads
	for(unsigned int i = 0; i < files_vec.size(); i++){
		structs[i].inThread = std::thread(readFile_thread, files_vec[i], words_vec, &structs[i].queue);
	}
	
	//wait while threads work their magic
	for(IOStruct& s : structs){
		if(s.inThread.joinable()) s.inThread.join();
		if(s.outThread.joinable()) s.outThread.join();
	}
	
	
	
	
	return 0;
}

static std::vector<std::string> splitString(std::string& str){
	unsigned int pos = 0, startPos = 0;
	std::vector<std::string> v;
	for(; pos < str.length(); pos++){
		if(str[pos] == DELIM){
			v.push_back(str.substr(startPos, pos-startPos));
			startPos = ++pos;
		}
	}
	v.push_back(str.substr(startPos, pos-startPos));
	return v;
}
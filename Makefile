CC=g++
FLAGS=-Wall -std=c++11

TARGET=WordSearch
LOCAL_SOURCES=$(wildcard src/*.cpp)
LOCAL_OBJECTS=$(patsubst src/%.cpp,obj/%.o,$(LOCAL_SOURCES))


all: $(TARGET)

$(TARGET): $(LOCAL_OBJECTS)
	g++ -o $@ $^ $(FLAGS) -pthread

$(LOCAL_OBJECTS): obj/%.o: src/%.cpp wordsearch.h
	g++ -c -o $@ $< $(FLAGS)
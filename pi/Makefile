CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 $(shell pkg-config --cflags opencv)
LFLAGS = $(shell pkg-config --libs opencv)
ALL_OBJS := $(patsubst src/%.cpp, bin/%.o, $(wildcard src/*.cpp))
NAME = lego_sorter

.PHONY: run build clean all

all: build

run: build
	@bin/$(NAME)

build: $(NAME)

clean:
	rm -rf bin/*

$(NAME): bin/$(NAME)

bin/$(NAME): $(ALL_OBJS)
	@$(CXX) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(ALL_OBJS): bin/%.o: src/%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@
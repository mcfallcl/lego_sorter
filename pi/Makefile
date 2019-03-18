CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 $(shell pkg-config --cflags opencv)
LFLAGS = $(shell pkg-config --libs opencv) -l boost_system -pthread
ALL_SRC := $(wildcard src/*.cpp)
ALL_SRC := $(filter-out src/main.cpp, $(ALL_SRC))
ALL_OBJS := $(patsubst src/%.cpp, bin/%.o, $(ALL_SRC))
NAME = lego_sorter
FRAME_CAP = frame_cap

.PHONY: run build clean all

all: build

run: build
	@bin/$(NAME)

build: $(NAME)

clean:
	rm -rf bin/*

$(NAME): bin/$(NAME)

bin/$(NAME): $(ALL_OBJS) src/main.cpp
	@$(CXX) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(ALL_OBJS): bin/%.o: src/%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@

framecap: bin/$(FRAME_CAP)

bin/$(FRAME_CAP): $(ALL_OBJS) src/main.cpp
	@$(CXX) $(CFLAGS) -D FRAME_CAP $^ -o $@ $(LFLAGS)
	@bin/$(FRAME_CAP)
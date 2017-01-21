#!/bin/bash
CC = g++
CFLAGS = -std=c++11 -w
LDFLAGS = -lboost_system -lboost_unit_test_framework

DEPS = Quantlabcodingtest.h
SRCS = main.cpp Quantlabcodingtest.cpp unittest_Quantlabcodingtest.cpp

all:	qlab-xji qlab-xji-utest

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

qlab-xji:	main.o Quantlabcodingtest.o
		$(CC) -o $@ $^ $(CFLAGS)

qlab-xji-utest:	Quantlabcodingtest.o unittest_Quantlabcodingtest.o
		$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f qlab-xji qlab-xji-utest $(OBJS)

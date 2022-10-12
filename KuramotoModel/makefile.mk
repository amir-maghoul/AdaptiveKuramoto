# Makefile for Compiling the Kuramoto Project Dependencies
 
# ********************************************************
# Variables to control Makefile operation: Compiler g++

CC = g++
CFLAGS = -Wall -g
 
# ********************************************************

main : main.o discrete_kuramoto.o continuum_limit.o
	$(CC) $(CFLAGS) -o main main.o discrete_kuramoto.o continuum_limit.o
	rm -f discrete_kuramoto.o continuum_limit.o main.o

main.o : main.cpp discrete_kuramoto.h continuum_limit.h
	$(CC) $(CFLAGS) -c main.cpp

discrete_kuramoto.o : discrete_kuramoto.h
continuum_limit.o : continuum_limit.h
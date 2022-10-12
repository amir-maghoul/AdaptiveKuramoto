# Makefile for Compiling the Kuramoto Project Dependencies
 
# ********************************************************
# Variables to control Makefile operation: Compiler g++

CC = g++
CFLAGS = -Wall -g
 
# ********************************************************

main : main.o discrete_kuramoto.o continuum_limit.o solvers.o
	$(CC) $(CFLAGS) -o main main.o discrete_kuramoto.o continuum_limit.o solvers.o
	rm -f discrete_kuramoto.o continuum_limit.o main.o solvers.o

main.o : main.cpp discrete_kuramoto.h continuum_limit.h solvers.h
	$(CC) $(CFLAGS) -c main.cpp

discrete_kuramoto.o : discrete_kuramoto.h
continuum_limit.o : continuum_limit.h
solvers.o : solvers.h
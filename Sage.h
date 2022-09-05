#pragma once
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <Windows.h>
#define numberOfSage       5
#define minTime       1000
#define maxTime       5000

struct Sage
{
	char state;
	int chopstick[2];
	int fullness;

};

void SageDoing(Sage& sage, bool(&chopstick)[numberOfSage], int index);
int inline RandomTime();

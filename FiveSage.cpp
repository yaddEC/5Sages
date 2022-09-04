// FiveSage.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#define numberOfSage       5
#define minTime       1000
#define maxTime       5000

std::mutex umutEX;

struct Sage
{
	char state;
	int chopstick[2];
	int fullness;

};

int inline RandomTime()
{
	return  minTime + (rand() % static_cast<int>(maxTime - minTime + 1));
}


void SageDoing(Sage& sage, bool(&chopstick)[numberOfSage],int index)
{
	std::lock_guard<std::mutex> lock(umutEX);


	if (sage.state == 'S')
	{
		int duration = RandomTime();
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));

	}
	if (sage.state == 'F')
	{
		int duration = RandomTime();
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));
		sage.state = 'S';

	}
	if (sage.state == 'M')
	{
		int duration = RandomTime();
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));
		sage.fullness += duration/1000;
		chopstick[sage.chopstick[0]] = true;
		chopstick[sage.chopstick[1]] = true;
		sage.state = 'F';
		sage.chopstick[0] = -1;
		sage.chopstick[1] = -1;

	}


	if ((sage.state == 'S' || sage.state == 'C') && sage.fullness < 5)
	{
		for (int i = 0; i < numberOfSage; i++)
		{

			if (sage.chopstick[0] > -1 && sage.chopstick[1] > -1)
			{
				sage.state = 'M';
				break;
			}
			if (chopstick[index])
			{
				chopstick[index] = false;
				if (sage.chopstick[0] == -1)
					sage.chopstick[0] = index;
				else
					sage.chopstick[1] = index;
			}

			if (index== numberOfSage - 1)
			{

				if (chopstick[0])
				{
					chopstick[0] = false;
						if (sage.chopstick[0] == -1)
							sage.chopstick[0] = 0;
						else
							sage.chopstick[1] = 0;
				}

			}
			else
			{

				 if (chopstick[index+1])
				{
					chopstick[index+1] = false;
					if (sage.chopstick[0] == -1)
						sage.chopstick[0] = index+1;
					else
						sage.chopstick[1] = index+1;
				}


			}
			if (i == numberOfSage - 1)
			{
				if (sage.chopstick[0] != -1)
				{
					chopstick[sage.chopstick[0]] = true;
					sage.chopstick[0] = -1;
				}

				sage.state = 'C';
			}

		}
		// initiate try to eat
		//if chop
		//initiate random time eating 
		// sage.state = 'S';
		//else
		//sage.state = 'C';
	}


	else if (sage.state == 'I')
	{
		sage.state = 'S';
		//print he think
		// wait
	}




}


void Clear()//function that refresh the command console (found online)
{
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}


int main()
{
	Sage sage[numberOfSage];
	bool chopstick[numberOfSage];
	int day = 0;
	std::thread threads[numberOfSage];

	for (int i = 0; i < numberOfSage; i++)
	{
		sage[i] = { 'I',{-1,-1},0 };//'I' like init
		chopstick[i] = true;
	}


	while (day < 7)
	{
		for (int i = 0; i < numberOfSage; i++)
		{
			threads[i] = std::thread(SageDoing, std::ref(sage[i]), std::ref(chopstick),i);
		}

		int fullSage = 0;
		Clear();
		std::cout << "\n" << "JOUR " << day+1<< "\n";
		for (int i = 0; i < numberOfSage; i++)
		{
		
			std::cout << sage[i].state;
		}
		std::cout << "\n";
		for (int i = 0; i < numberOfSage; i++)
		{
			std::cout  << chopstick[i];
		}
		




		for (int i = 0; i < numberOfSage; i++)
		{
			threads[i].join();
			if (sage[i].fullness >= 5)
				fullSage++;
		}

		if (fullSage == numberOfSage)
		{
			day++;
			for (int i = 0; i < numberOfSage; i++)
			{
				sage[i] = { 'I',{-1,-1},0 };//'I' like init
				chopstick[i] = true;
			}

		}
	}
}


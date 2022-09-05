// FiveSage.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Sage.h"

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

void WriteInColor(unsigned short color, char(&outputString))
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
	std::cout << outputString;
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

	bool lastLoop = false;
	while (day < 7)
	{
		for (int i = 0; i < numberOfSage; i++)
		{
			threads[i] = std::thread(SageDoing, std::ref(sage[i]), std::ref(chopstick), i);
		}

		int fullSage = 0;
		Clear();
		std::cout << "\n" << "DAY " << day + 1 << "\n";
		HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < numberOfSage; i++)
		{
			SetConsoleTextAttribute(hcon, sage[i].fullness + 2);
			std::cout << sage[i].state;
		}
		std::cout << "\n";
		for (int i = 0; i < numberOfSage; i++)
		{
			SetConsoleTextAttribute(hcon, 7);
			std::cout << chopstick[i];

		}





		for (int i = 0; i < numberOfSage; i++)
		{
			threads[i].join();
			if (sage[i].fullness >= 5)
				fullSage++;
		}



		if (lastLoop)
		{
			day++;
			for (int i = 0; i < numberOfSage; i++)
			{
				sage[i] = { 'I',{-1,-1},0 };//'I' like init
				chopstick[i] = true;
			}
			lastLoop = false;
			fullSage = 0;
		}

		if (fullSage == numberOfSage )
		{
			lastLoop = true;

		}
	}
}


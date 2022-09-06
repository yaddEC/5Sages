#include "Sage.h"

std::mutex umutEX;


//function that get random time
int inline RandomTime()
{
	return  minTime + (rand() % static_cast<int>(maxTime - minTime + 1));
}

//function that defines the Sage eat cycle
void SageDoing(Sage& sage, bool(&chopstick)[numberOfSage], int index)
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
		sage.fullness += duration / 1000;
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
			//if the sage have 2 chopstick, he can eat
			if (sage.chopstick[0] > -1 && sage.chopstick[1] > -1)
			{
				sage.state = 'M';
				break;
			}
			//if the chopstick is available, the sage takes it
			if (chopstick[index])
			{
				chopstick[index] = false;
				if (sage.chopstick[0] == -1)
					sage.chopstick[0] = index;
				else
					sage.chopstick[1] = index;
			}
			//if the index of the sage is the last one, his chopstick option will become the first chopstick or the last
			if (index == numberOfSage - 1)
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

				if (chopstick[index + 1])
				{
					chopstick[index + 1] = false;
					if (sage.chopstick[0] == -1)
						sage.chopstick[0] = index + 1;
					else
						sage.chopstick[1] = index + 1;
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

	}

	else if (sage.state == 'I')
	{
		sage.state = 'S';

	}

}
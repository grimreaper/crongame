#include "krandom.h"
#include <iostream>
#include <stdlib.h>

int rand_ex_i(int min, int max)
{
	if (min - max == 0)
	{
		return 0 + min; // avoid zero division
	}

	if (min > max)
	{
		std::cout << "swapped! ";
		std::swap(min, max);
	}
	int ans = ( arc4random() % (max - min) ) + min;
	std::cout << "the ans is " << ans;
	return ans;

}


// floating point version
float rand_ex_f(float min, float max)
{
	std::cout << min << " " << max << " ";
	float part1 = ((float) rand_ex_i( (int)(min * 1000.0), (int)(max * 1000.0)));
	float ans = (part1 / 1000.0 );
	std::cout << "done with rand num" << std::endl;
	return ans;
}


// version for switching the sign (positive, negative)
float rand_sign_switch(float number)
{
	std::cout << " we are in sign switch->float" << std::endl;
	if (arc4random()%100 < 50)
	{
		return number;
	}
	else
	{
		return -number;
	}
}


int rand_sign_switch(int number)
{
	std::cout << " we are in sign switch->int" << std::endl;
	if (arc4random()%100 < 50)
	{
		return number;
	}
	else
	{
		return -number;
	}
}

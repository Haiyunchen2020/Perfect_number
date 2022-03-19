//==============================================================================
// Name        : isNumPerfect.cpp
// Description : To check whether a number is a perfect number with one process
//==============================================================================



#include <string>
#include <iostream>
#include <cstdlib>

const int PERFECT =  0;
const int IMPERFECT = 1; 
const int FAILURE = -1;

static bool is_perfect(const long long number);
static void print_help(const char *progname);

int main(int argc, char *argv[]) {
	long long number;

	if (argc < 2) {
		print_help(argv[0]);
		exit(FAILURE);
	} 

	number = std::stoll(argv[1]);

	if (number < 2) {
		print_help(argv[0]);
		exit(FAILURE);
	}

	if (is_perfect(number)) {
		return PERFECT;
	} else {
		return IMPERFECT;
	}
}

static bool is_perfect(const long long number) {
	long long sum = 1ll;
	for (long long divisor = number - 1; divisor >= 2; divisor --) {
		if (number % divisor == 0) {
			sum += divisor;
			if (sum > number) break;
		}
	}
	return sum == number;
}

static void print_help(const char *progname) {
	std::cout << "Usage: " << progname <<  " <N>" 
		<< "\nN: an integer greater than 1.  " << std::endl;
}

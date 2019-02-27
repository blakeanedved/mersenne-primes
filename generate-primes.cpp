#include <fstream>
#include <math.h>

auto main() -> int {
	std::ofstream file;
	file.open("primes.txt");

	file << 2 << "\n";
	
	int num = 3;

	bool isPrime;
	int numSqrt;
	while (num <= 250000000){
		isPrime = true;
		numSqrt = sqrt(num);
		for (int i = 2; i < numSqrt; i++)
			if (num % i == 0){
				isPrime = false;
				break;
			}
		if (isPrime)
			file << num << "\n";
		num += 2;
	}

	file.close();

	return 0;
}

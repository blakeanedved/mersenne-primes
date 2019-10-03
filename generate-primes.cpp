#include <fstream>
#include <math.h>
#include <thread>
#include <mutex>

#define NUM_THREADS 8

int num;
std::ofstream file;
std::mutex num_mutex;
std::mutex file_mutex;

static auto check_prime_threaded() -> void {
	bool isPrime;
	int numSqrt;
	int current_num;
	int i;
	while (num <= 250000000){
		num_mutex.lock();
		current_num = num;
		num += 2;
		num_mutex.unlock();

		isPrime = true;
		numSqrt = sqrt(current_num);
		for (i = 2; i < numSqrt; i++)
			if (current_num % i == 0){
				isPrime = false;
				break;
			}

		if (isPrime){
			file_mutex.lock();
			file << current_num << "\n";
			file_mutex.unlock();
		}
	}
}

auto main() -> int {
	file.open("primes.txt");

	file << 2 << "\n";
	
	num = 3;

	std::thread threads[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++){
		threads[i] = std::thread(check_prime_threaded);
	}

	for (int i = 0; i < NUM_THREADS; i++){
		threads[i].join();
	}

	file.close();

	return 0;
}

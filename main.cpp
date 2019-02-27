#include <iostream>
#include <fstream>
#include <thread>
#include <boost/multiprecision/gmp.hpp>
namespace mp = boost::multiprecision;

#define NUM_THREADS 8

mp::mpz_int mpzint2 = mp::mpz_int(2);

std::vector<bool> isFinished(NUM_THREADS, true);
std::vector<bool> foundPrime(NUM_THREADS, false);

std::vector<mp::mpz_int> M(NUM_THREADS, 0);
std::vector<mp::mpz_int> L(NUM_THREADS, 0);

inline auto nextLucasLehmer(mp::mpz_int) -> mp::mpz_int;
auto checkMersenneForPrimeThreaded(int, int) -> void;
auto checkMersenneForPrime(int) -> bool;

auto main() -> int {
	
	std::ifstream primes;
	primes.open("primes.txt");

	int startNum;

	std::cout << "What p (2^p-1) would you like to start at? >> ";
	std::cin >> startNum;

	int currentNum;
	while (true){
		primes >> currentNum;
		if (currentNum >= startNum) break;
	}
	bool searching = true;
	int foundIndex;
	std::vector<int> nums;
	std::vector<std::thread> threads;
	std::vector<bool> done(NUM_THREADS, false);
	
	for (int i = 0; i < NUM_THREADS; i++){
		if (i != 0) primes >> currentNum;
		nums.push_back(currentNum);
		threads.push_back(std::thread(checkMersenneForPrimeThreaded, currentNum, i));
	}

	while (searching){
		for (int i = 0; i < NUM_THREADS; i++){
			if (isFinished[i]){
				threads[i].join();
				if (foundPrime[i]){
					std::cout << "Found a prime number at 2^" << nums[i] << "-1" << std::endl;
					searching = false;
					foundIndex = i;
				}
				if (searching){
					primes >> currentNum;
					nums[i] = currentNum;
					threads[i] = std::thread(checkMersenneForPrimeThreaded, currentNum, i);
					isFinished[i] = false;
				}
			}
		}
	}

	for (int i = 0; i < NUM_THREADS; i++)
		if (i != foundIndex)
			threads[i].join();
		
	return 0;
}

inline auto nextLucasLehmer(mp::mpz_int a) -> mp::mpz_int {
	return (a * a) - 2;
}

auto checkMersenneForPrimeThreaded(int p, int my_id) -> void {
	M[my_id] = mp::pow(mpzint2, p) - 1;
	L[my_id] = 4;

	for (int i = 1; i < p - 1; i++){
		L[my_id] = nextLucasLehmer(L[my_id]) % M[my_id];
	}

	if (L[my_id] % M[my_id] == 0){
		foundPrime[my_id] = true;
	}

	isFinished[my_id] = true;
}

auto checkMersenneForPrime(int p) -> bool {
	mp::mpz_int mersenneNum = mp::pow(mp::mpz_int(2), p) - 1;
	mp::mpz_int lucasLehmerNum = 4;

	for (int i = 1; i < p - 1; i++){
		lucasLehmerNum = nextLucasLehmer(lucasLehmerNum) % mersenneNum;
	}

	return lucasLehmerNum % mersenneNum == 0;
}

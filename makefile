all:main

main:main.cpp
	rm a.out
	g++ -std=c++17 main.cpp -lgmp -O3

genprimes:generate-primes.cpp
	g++ -std=c++17 generate-primes.cpp -O3

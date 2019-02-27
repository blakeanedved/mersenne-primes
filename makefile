a.out:main.cpp
	g++ -std=c++17 main.cpp -lgmp -O3

genprimes:generate-primes.cpp
	g++ -std=c++17 generate-primes.cpp -O3

all:a.out

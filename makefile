CC 		= g++
CFLAGS 	= -std=c++17 -O3
MTARGET = mersenne
MSRC 	= main.cpp
GTARGET = genprimes
GSRC	= generate-primes.cpp

all:main

main:clean genprimes main.cpp
	$(CC) -o $(MTARGET) $(CFLAGS) -lgmp $(MSRC)

genprimes:generate-primes.cpp
	$(CC) -o $(GTARGET) $(CFLAGS) $(GSRC)

clean:
	rm -rf $(GTARGET) $(MTARGET)

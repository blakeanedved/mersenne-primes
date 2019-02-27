# mersenne-primes

This repository provides a simple, but relatively slow implementation of the Lucas-Lehmer primality test for Mersenne Primes (primes in form of 2<sup>p</sup>-1)

This program uses c++17 standards and the `<boost/multiprecision/gmp.hpp>` header for extremely large numbers. I also threw in threading to speed the process up a bit, feel free to change the `NUM_THREADS` value in main.cpp, although, I have found it works best with threads exactly equal to the cores in your CPU.

## Usage

```
 ~ git clone https://github.com/blakeanedved/mersenne-primes.git
 ~ cd mersenne-primes
 ~ make genprimes
 ~ ./a.out (NOTE: this will take a short while)
 ~ make
 ~ ./a.out
```
Then enter the number which you would like to start from, and viola, the algorithm will take its time finding the next Mersenne Prime

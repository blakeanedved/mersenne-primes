#include <iostream>
#include <boost/multiprecision/gmp.hpp>
namespace mp = boost::multiprecision;

auto nextLucasLehmer(mp::mpz_int) -> mp::mpz_int;

auto main() -> int {
	
	int mersenneExp;

	std::cout << "What n would you like to check for primality (2^n-1)? >> ";
	std::cin >> mersenneExp;
	mp::mpz_int mersenneNum = mp::pow(mp::mpz_int(2), mersenneExp) - 1;
	mp::mpz_int lucasLehmerNum = 4;

	for (int i = 1; i < mersenneExp - 1; i++){
		lucasLehmerNum = nextLucasLehmer(lucasLehmerNum) % mersenneNum;
	}

	if (lucasLehmerNum % mersenneNum == 0){
		std::cout << "2^" << mersenneExp << "-1 is prime" << std::endl;
	} else {
		std::cout << "2^" << mersenneExp << "-1 is not prime" << std::endl;
	}
		
	return 0;
}

inline auto nextLucasLehmer(mp::mpz_int a) -> mp::mpz_int {
	return (a * a) - 2;
}

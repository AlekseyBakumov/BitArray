#include "bitarray.h"
#include <iostream>

int main() 
{
	// INIT
	std::cout << "Init..." << std::endl;
	BitArray *mybits1 = new BitArray(10);
	BitArray *mybits2 = new BitArray(10, 3);

	mybits1->push_back(true);
	mybits1->push_back(true);
	mybits1->set(5, true);
	mybits1->set(8, true);

	std::cout << mybits1->to_string() << std::endl;
	std::cout << mybits2->to_string() << std::endl;

	// SWAP TEST
	std::cout << "Swap..." << std::endl;
	mybits1->swap(*mybits2);

	// SIZE AND COUNT TEST
	std::cout << "Size and count..." << std::endl;
	std::cout << mybits1->to_string() << std::endl;
	std::cout << mybits2->to_string();
	std::cout << " " << mybits2->size() << " " << mybits2->count() << std::endl;

	// INVERSE TEST
	std::cout << "Inverse..." << std::endl;
	std::cout << (~(*mybits2)).to_string() << std::endl;

	// ASSIGN TEST
	std::cout << "Assign..." << std::endl;
	mybits1->set(1, true);
	mybits1->set(6, true);
	mybits1->set(7, true);
	(*mybits2) = (*mybits1);

	std::cout << (*mybits2).to_string() << std::endl;

	// SET AND RESET TEST
	std::cout << "Set and reset..." << std::endl;
	(*mybits2).set();
	std::cout << (*mybits2).to_string() << std::endl;
	(*mybits2).reset(5);
	std::cout << (*mybits2).to_string() << std::endl;
	(*mybits2).reset();
	std::cout << (*mybits2).to_string() << std::endl;

	// COMPARE TEST
	std::cout << "Compare op..." << std::endl;
	std::cout << ((*mybits2) == (*mybits1)) << std::endl;
	(*mybits2) = (*mybits1);
	std::cout << ((*mybits2) == (*mybits1)) << std::endl;

	(*mybits1).reset();
	(*mybits2).reset();

	mybits1->set(1, true);
	mybits1->set(2, true);
	mybits1->set(7, true);
	mybits2->set(1, true);
	mybits2->set(7, true);

	// BIT OPS TEST
	std::cout << "Bit ops..." << std::endl;
	std::cout << mybits1->to_string() << std::endl;
	std::cout << mybits2->to_string() << std::endl;
	std::cout << "&" << std::endl;
	(*mybits2) &= (*mybits1);
	std::cout << (*mybits2).to_string() << std::endl;
	std::cout << std::endl;

	mybits1->set(3, true);
	mybits1->set(4, true);

	std::cout << mybits1->to_string() << std::endl;
	std::cout << mybits2->to_string() << std::endl;
	std::cout << "|" << std::endl;
	std::cout << ((*mybits2) | (*mybits1)).to_string() << std::endl;
	std::cout << std::endl;

	mybits1->set(3, true);
	mybits1->set(4, true);

	std::cout << mybits1->to_string() << std::endl;
	std::cout << mybits2->to_string() << std::endl;
	std::cout << "^" << std::endl;
	std::cout << ((*mybits2) ^ (*mybits1)).to_string() << std::endl;
	std::cout << std::endl;

	std::cout << (*mybits1).to_string() << std::endl;
	(*mybits1) <<= 2;
	std::cout << (*mybits1).to_string() << std::endl;
	std::cout << ((*mybits1) >> 3).to_string() << std::endl;

	// RESIZE TEST
	std::cout << "Resize..." << std::endl;
	std::cout << std::endl;
	std::cout << (*mybits1).to_string() << std::endl;
	(*mybits1).resize(4, 0);
	std::cout << (*mybits1).to_string() << std::endl;
	(*mybits1).resize(80, 1);
	(*mybits1).reset(79);
	std::cout << (*mybits1).to_string() << std::endl;
	(*mybits1).resize(100, 0);
	(*mybits1).set(98);
	(*mybits1).push_back(true);
	std::cout << (*mybits1).to_string() << std::endl;
	(*mybits1) >>= 16;
	std::cout << (*mybits1).to_string() << std::endl;

	return 0;
}


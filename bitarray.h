#pragma once
#include <string>
class BitArray
{
	typedef char bitword;

private:
	bitword* _arr;
	int _arr_size;
	int _bits_count;
	int _current_indx;

	void set_bit(int i, bool val);
	int real_bits_count();

public:
	BitArray();
	~BitArray();

	//Builds array of size 'num_bits'
	//First 'value' bits are init as true
	explicit BitArray(int num_bits, unsigned long value = 0);
	BitArray(const BitArray& b);

	//Swap arrays
	void swap(BitArray& b);

	BitArray& operator=(const BitArray& b);


	//Changes size of an array and fill  
	//expanded values as 'value'
	void resize(int num_bits, bool value = false);
	//Clear array
	void clear();
	//Push new bit into array
	//Expands array if necessary
	void push_back(bool bit);

	int GetBitsCount() const;

	//Bit operations
	//Works only on arrays of the same size.
	BitArray& operator&=(const BitArray& b);
	BitArray& operator|=(const BitArray& b);
	BitArray& operator^=(const BitArray& b);

	//Bit shift
	//Fills with zero
	BitArray& operator<<=(int n);
	BitArray& operator>>=(int n);
	BitArray operator<<(int n) const;
	BitArray operator>>(int n) const;


	//Set n-th bit as 'val'
	BitArray& set(int n, bool val = true);
	//Set all array as true
	BitArray& set();

	//Set n-th bit as false
	BitArray& reset(int n);
	//Set all array as false
	BitArray& reset();

	//true, if at least one bit true.
	bool any() const;
	//true, if all bits are false.
	bool none() const;
	//Bit inverse
	BitArray operator~() const;
	//Counts true bits
	int count() const;


	//Get i-th bit value
	bool operator[](int i) const;

	int size() const;
	bool empty() const;

	//Transform array to string
	std::string to_string() const;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);


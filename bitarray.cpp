#include "bitarray.h"
#include <stdexcept>
#include <iostream>

/// </summary>
/// Realization of bitarray
/// For functions descriptions, look in header file (bitarray.h)
/// </summary>


// Utility function for indexation of array
void BitArray::set_bit(int i, bool val)
{
#ifdef _WIN64
	if (i >= _bits_count)
		throw std::invalid_argument("Index out of bounds");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (i >= _bits_count)
		throw std::runtime_error("Index out of bounds");
#endif

	if (i > _current_indx) _current_indx = i;
	int word = i / (sizeof(bitword) * 8);
	i -= word * sizeof(bitword) * 8;

	if (val)
	{
		_arr[word] = _arr[word] | (1 << i);
	}
	else
	{
		_arr[word] = _arr[word] & ~(1 << i);
	}
}

// Utility function, count real array size
int BitArray::real_bits_count()
{
	return sizeof(bitword) * 8 * _arr_size;
}

BitArray::BitArray()
{
	_bits_count = 64;
	_arr_size = (int)(_bits_count / sizeof(bitword)) + 1;
	_arr = new bitword[_arr_size];
	for (int i = 0; i < _arr_size; i++)
		_arr[i] = 0;
	_current_indx = 0;
}
BitArray::~BitArray()
{
	delete _arr;
}

BitArray::BitArray(int num_bits, unsigned long value)
{
#ifdef _WIN64
	if (num_bits < 0)
		throw std::invalid_argument("Array size cannot be negative");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (num_bits < 0)
		throw std::runtime_error("Array size cannot be negative");
#endif

	_bits_count = num_bits;
	_arr_size = (int)(_bits_count / sizeof(bitword)) + 1;
	_arr = new bitword[_arr_size];
	for (int i = 0; i < _bits_count; i++)
		if (i < value)
			set(i);
		else
			reset(i);
	_current_indx = 0;
}
BitArray::BitArray(const BitArray& b)
{
	_arr_size = b._arr_size;
	_bits_count = b._bits_count;
	_arr = new bitword[_arr_size];
	for (int i = 0; i < _arr_size; i++)
		_arr[i] = b._arr[i];
	_current_indx = 0;
}

void BitArray::swap(BitArray& b)
{
#ifdef _WIN64
	if (_bits_count != b._bits_count)
		throw std::exception("Arrays have different sizes");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (_bits_count != b._bits_count)
		throw std::runtime_error("Arrays have different sizes");
#endif
	if (this == &b) return;

	int t = _current_indx;
	_current_indx = b._current_indx;
	b._current_indx = t;

	for (int i = 0; i < _arr_size; i++)
	{
		bitword tmp = b._arr[i];
		b._arr[i] = _arr[i];
		_arr[i] = tmp;
	}
}

BitArray& BitArray::operator=(const BitArray& b)
{
#ifdef _WIN64
	if (_bits_count != b._bits_count)
		throw std::exception("Arrays have different sizes");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (_bits_count != b._bits_count)
		throw std::runtime_error("Arrays have different sizes");
#endif

	for (int i = 0; i < _arr_size; i++)
		_arr[i] = b._arr[i];

	return (*this);
}

bool BitArray::any() const
{
	for (int i = 0; i < _bits_count; i++)
		if ((*this)[i])
			return true;

	return false;
}

bool BitArray::none() const
{
	return !any();
}

BitArray BitArray::operator~() const
{
	BitArray res(_bits_count);
	for (int i = 0; i < _bits_count; i++)
		res.set(i, !(*this)[i]);
	return res;
}

int BitArray::count() const
{
	int sum = 0;

	for (int i = 0; i < _bits_count; i++)
		if ((*this)[i])
			sum++;

	return sum;
}

bool BitArray::operator[](int i) const
{
#ifdef _WIN64
	if (i < 0 || i > _bits_count)
		throw std::invalid_argument("Index out of bounds");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (i < 0 || i > _bits_count)
		throw std::runtime_error("Index out of bounds");
#endif

	int word = i / (sizeof(bitword) * 8);
	i -= word * sizeof(bitword) * 8;

	return (_arr[word] & (1 << i)) >> i;
}

int BitArray::size() const
{
	return _current_indx;
}

bool BitArray::empty() const
{
	return _current_indx == 0;
}

std::string BitArray::to_string() const
{
	std::string str_arr;
	for (int i = 0; i < _bits_count; i++)
	{
		if ((*this)[i])
			str_arr.append("1");
		else
			str_arr.append("0");

		if ((i + 1) % 8 == 0)
			str_arr.append(" ");
	}
	return str_arr;
}

BitArray& BitArray::set(int n, bool val)
{
	set_bit(n, val);
	return *this;
}

BitArray& BitArray::set()
{
	for (int i = 0; i < _bits_count; i++)
		set_bit(i, true);
	return *this;
}

BitArray& BitArray::reset(int n)
{
	set_bit(n, false);
	return *this;
}

BitArray& BitArray::reset()
{
	for (int i = 0; i < _bits_count; i++)
		set_bit(i, false);
	_current_indx = 0;
	return *this;
}

bool operator==(const BitArray& a, const BitArray& b)
{
#ifdef _WIN64
	if (a.GetBitsCount() != b.GetBitsCount())
		throw std::exception("Arrays have different sizes");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (a.GetBitsCount() != b.GetBitsCount())
		throw std::runtime_error("Arrays have different sizes");
#endif

	for (int i = 0; i < a.GetBitsCount(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

bool operator!=(const BitArray& a, const BitArray& b)
{
	return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2)
{
#ifdef _WIN64
	if (b1.GetBitsCount() != b2.GetBitsCount())
		throw std::exception("Arrays have different sizes");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (b1.GetBitsCount() != b2.GetBitsCount())
		throw std::runtime_error("Arrays have different sizes");
#endif

	BitArray res(b1.GetBitsCount());

	for (int i = 0; i < b1.GetBitsCount(); i++)
		res.set(i, b1[i] & b2[i]);

	return res;
}

BitArray operator|(const BitArray& b1, const BitArray& b2)
{
#ifdef _WIN64
	if (b1.GetBitsCount() != b2.GetBitsCount())
		throw std::exception("Arrays have different sizes");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (b1.GetBitsCount() != b2.GetBitsCount())
		throw std::runtime_error("Arrays have different sizes");
#endif

	BitArray res(b1.GetBitsCount());

	for (int i = 0; i < b1.GetBitsCount(); i++)
		res.set(i, b1[i] | b2[i]);

	return res;
}

BitArray operator^(const BitArray& b1, const BitArray& b2)
{
#ifdef _WIN64
	if (b1.GetBitsCount() != b2.GetBitsCount())
		throw std::exception("Arrays have different sizes");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (b1.GetBitsCount() != b2.GetBitsCount())
		throw std::runtime_error("Arrays have different sizes");
#endif

	BitArray res(b1.GetBitsCount());

	for (int i = 0; i < b1.GetBitsCount(); i++)
		res.set(i, b1[i] ^ b2[i]);

	return res;
}

void BitArray::resize(int num_bits, bool value)
{
#ifdef _WIN64
	if (num_bits < 0)
		throw std::invalid_argument("Array size cannot be negative");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (num_bits < 0)
		throw std::runtime_error("Array size cannot be negative");
#endif

	if (num_bits <= real_bits_count())
	{
		int old_count = _bits_count;
		_bits_count = num_bits;
		for (int i = _bits_count - 1; i >= old_count; i--)
			set(i, value);
		return;
	}
	int old_bits_count = _bits_count;
	int old_arr_size = _bits_count;
	_bits_count = num_bits;
	_arr_size = (int)(_bits_count / sizeof(bitword)) + 1;
	bitword* new_arr = new bitword[_arr_size];
	for (int i = 0; i < old_arr_size; i++)
		new_arr[i] = _arr[i];
	delete _arr;
	_arr = new_arr;
	for (int i = old_bits_count; i < _bits_count; i++)
		set(i, value);
}

void BitArray::clear()
{
	reset();
	_current_indx = 0;
}

void BitArray::push_back(bool bit)
{
#ifdef _WIN64
	if (_current_indx >= _bits_count)
		throw std::exception("Cannot push: array is full");
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
	if (_current_indx >= _bits_count)
		throw std::runtime_error("Cannot push: array is full");
#endif

	set(_current_indx++, bit);
}

int BitArray::GetBitsCount() const
{
	return _bits_count;
}

BitArray& BitArray::operator&=(const BitArray& b)
{
	*this = *this & b;
	return *this;
}

BitArray& BitArray::operator|=(const BitArray& b)
{
	*this = *this | b;
	return *this;
}

BitArray& BitArray::operator^=(const BitArray& b)
{
	*this = *this ^ b;
	return *this;
}

BitArray& BitArray::operator<<=(int n)
{
	(*this) = (*this) << n;
	return (*this);
}

BitArray& BitArray::operator>>=(int n)
{
	(*this) = (*this) >> n;
	return (*this);
}

BitArray BitArray::operator<<(int n) const
{
	if (n < 0) return (*this) >> -n;

	BitArray res(_bits_count, 0);
	for (int i = 0; i < _bits_count; i++)
		if (i + n >= _bits_count)
			res.reset(i);
		else
			res.set(i, (*this)[i + n]);

	return res;
}

BitArray BitArray::operator>>(int n) const
{
	if (n < 0) return (*this) << -n;

	BitArray res(_bits_count, 0);
	for (int i = _bits_count - 1; i >= 0; i--)
		if (i - n < 0)
			res.reset(i);
		else
			res.set(i, (*this)[i - n]);

	return res;
}


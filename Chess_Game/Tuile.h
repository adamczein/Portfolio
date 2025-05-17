
#pragma once
#include <vector>

struct Tuile
{
    int file;
    int rank;

    int getX() const { return file; }
    int getY() const { return rank; }
};

//struct Square : public Tuile
//{
//	Square() : Tuile{ 0, 0 } {}
//	Square(int file, int rank) : Tuile{ file, rank } {}
//	Square(const Tuile& t) : Tuile{ t } {}
//	Square(const Square& s) : Tuile{ s } {}
//	Square& operator=(const Square& s)
//	{
//		file = s.file;
//		rank = s.rank;
//		return *this;
//	}
//	Square& operator=(const Tuile& t)
//	{
//		file = t.file;
//		rank = t.rank;
//		return *this;
//	}
//	Square& operator+=(const Square& s)
//	{
//		file += s.file;
//		rank += s.rank;
//		return *this;
//	}
//	Square& operator+=(const Tuile& t)
//	{
//		file += t.file;
//		rank += t.rank;
//		return *this;
//	}
//	Square& operator-=(const Square& s)
//	{
//		file -= s.file;
//		rank -= s.rank;
//		return *this;
//	}
//	Square& operator-=(const Tuile& t)
//	{
//		file -= t.file;
//		rank -= t.rank;
//		return *this;
//	}
//	Square& operator*=(const int i)
//	{
//		file *= i;
//		rank *= i;
//		return *this;
//	}
//	Square& operator/=(const int i)
//	{
//		file /= i;
//		rank /= i;
//		return *this;
//	}
//	Square operator+(const Square& s) const
//	{
//		return Square{ file + s.file, rank + s.rank };
//	}
//	Square operator+(const Tuile& t) const
//	{
//		return Square{ file + t.file, rank + t.rank };
//	}
//	Square operator-(const Square& s) const
//	{
//		return Square{ file - s.file, rank - s.rank };
//	}
//	Square operator-(const Tuile& t) const
//	{
//		return Square{ file - t.file, rank - t.rank };
//	}
//	Square operator*(const int i) const
//	{
//		return Square{ file * i, rank * i };
//	}
//	Square operator/(const int i) const
//	{
//		return Square{ file / i, rank / i };
//	}
//	bool operator==(const Square& s) const	
//};
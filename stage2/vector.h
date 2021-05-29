#include <iostream>
#include <vector>
using namespace std;

class Vector{
protected:
	int x,y;
public:
	Vector();
	Vector(int x, int y);

	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;

	Vector& operator=(const Vector& v);
	Vector& operator+=(const Vector& v);
	Vector operator+(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector operator-(const Vector& v);
	bool operator==(const Vector& v);
	bool operator!=(const Vector& v);
};

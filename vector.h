#include <iostream>
#include <vector>
using namespace std;

class Vector{
protected:
	int x,y;
public:
	Vector() : x(0), y(0){}
	Vector(int x, int y) {setX(x); setY(y);}

	void setX(int x){this->x = x;}
	void setY(int y){this->y = y;}
	int getX() const {return this->x;}
	int getY() const {return this->y;}

	Vector& operator=(const Vector& v){
		setX(v.getX());
		setY(v.getY());
		return *this;
	}
	Vector& operator+=(const Vector& v){
		setX(getX()+v.getX());
		setY(getY()+v.getY());
		return *this;
	}
	Vector operator+(const Vector& v){
		Vector v2(getX(),getY());
		return v2+=v;
	}
	Vector& operator-=(const Vector& v){
		setX(getX()-v.getX());
		setY(getY()-v.getY());
		return *this;
	}
	Vector operator-(const Vector& v){
		Vector v2(getX(),getY());
		return v2-=v;
	}
	bool operator==(const Vector& v){
		return getX()==v.getX() && getY()==v.getY();
	}
	bool operator!=(const Vector& v){
		return !operator==(v);
	}
};

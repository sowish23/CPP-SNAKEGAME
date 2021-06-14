#include "vector.h"
using namespace std;

Vector::Vector() : x(0), y(0){}
Vector::Vector(int x, int y) {setX(x); setY(y);}

void Vector::setX(int x){this->x = x;}
void Vector::setY(int y){this->y = y;}
int Vector::getX() const {return this->x;}
int Vector::getY() const {return this->y;}

Vector& Vector::operator=(const Vector& v){
	setX(v.getX());
	setY(v.getY());
	return *this;
}
Vector& Vector::operator+=(const Vector& v){
	setX(getX()+v.getX());
	setY(getY()+v.getY());
	return *this;
}
Vector Vector::operator+(const Vector& v){
	Vector v2(getX(),getY());
	return v2+=v;
}
Vector& Vector::operator-=(const Vector& v){
	setX(getX()-v.getX());
	setY(getY()-v.getY());
	return *this;
}
Vector Vector::operator-(const Vector& v){
	Vector v2(getX(),getY());
	return v2-=v;
}
bool Vector::operator==(const Vector& v){
	return getX()==v.getX() && getY()==v.getY();
}
bool Vector::operator!=(const Vector& v){
	return !operator==(v);
}

#ifndef TABLEOFVALUES_H
#define TABLEOFVALUES_H

#include <cmath> // pow()
#include <vector>
#include <iomanip>
#include <iostream>

using std::vector;
using std::setw;
using std::cout;
using std::endl;

typedef vector<double> Array;
typedef vector< vector<double> > Array2D;

const int SIZE_X = 100;
const int SIZE_Y = 100;

class TableOfValues
{
public:
    TableOfValues(int n = SIZE_X, int m = SIZE_Y);

    TableOfValues(TableOfValues & t);

    TableOfValues(Array &x, Array &y, Array2D &z);

    Array operator[](int);

    TableOfValues & operator=(TableOfValues & t);

    Array   getX() const;
    Array   getY() const;
    Array2D getZ() const;

    void console_out();

    // Two-dimensional interpolation
    double interpolation2D(double, double, int, int);
    
protected:

    // One-dimensional interpolation
    double interpolation(Array, Array, double);

    // The method returns a rectangular configuration of interpolation points
    TableOfValues & config(double, double, int, int);

    // Search zero index for the config() method
    int findIndex(Array, double, int);

    // The method for setting the table:
    // z = f(x,y) = x^2 + y^2
    void setTable(int, int);

private:
    Array   x_;
    Array   y_;
    Array2D z_;
};

#endif // TABLEOFVALUES_H

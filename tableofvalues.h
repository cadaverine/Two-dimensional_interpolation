#ifndef TABLEOFVALUES_H
#define TABLEOFVALUES_H

#include <cmath> // pow()
#include <vector>
#include <iomanip>
#include <iostream>
#include <QMetaType>

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

    TableOfValues(Array&, Array&, Array2D&);

    Array operator[](int);

    TableOfValues & operator=(TableOfValues&);

    Array   getX() const;
    Array   getY() const;
    Array2D getZ() const;

    void console_out();

    // Two-dimensional interpolation
    double interpolation2D(double, double, int, int);

    // One-dimensional interpolation
    double interpolation(Array, Array, double);

    // The method returns a rectangular configuration of interpolation points
    TableOfValues * config(double, double, int, int);

    // Search zero index for the config() method
    int findIndex(Array, double, int);

    // The method for setting the table:
    // z = f(x,y) = x^2 + y^2
    void setTable(int, int);

    friend bool operator ==(const TableOfValues&, const TableOfValues&);

    friend bool operator !=(const TableOfValues&, const TableOfValues&);

private:
    Array   _x;
    Array   _y;
    Array2D _z;
};

Q_DECLARE_METATYPE(TableOfValues)

#endif // TABLEOFVALUES_H

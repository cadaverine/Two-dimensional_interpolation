#include "tableofvalues.h"

TableOfValues::TableOfValues(int n, int m)
{
    setTable(n, m);
}

TableOfValues::TableOfValues(Array & x, Array & y, Array2D & z)
{
    _x = x;
    _y = y;
    _z = z;
}

TableOfValues & TableOfValues::operator=(TableOfValues & t)
{
    if(this != &t)
    {
        _x = t.getX();
        _y = t.getY();
        _z = t.getZ();
    }
    return * this;
}

Array   TableOfValues::getX() const { return _x; }
Array   TableOfValues::getY() const { return _y; }
Array2D TableOfValues::getZ() const { return _z; }


Array TableOfValues::operator[](int n) { return _z[n]; }


void TableOfValues::setTable(int X, int Y)
{
    _x.resize(X);
    _y.resize(Y);
    Array2D temp(X, Array(Y));
    _z = temp;

    for(int i = 0; i < X; ++i) _x[i] = i + 1;
    for(int i = 0; i < Y; ++i) _y[i] = i + 1;
    for(int i = 0; i < X; ++i)
    {
        for(int j = 0; j < Y; ++j)
        {
            _z[i][j] = pow((i + 1), 2) + pow((j + 1), 2);
        }
    }
}

int TableOfValues::findIndex(Array array, double number, int pointsNum)
{
    int index = 0;
    int size = static_cast<int>(array.size());
    if (pointsNum >= size) pointsNum = size;
    else
    {
        while (array[index] < number && index < size)
            index++;
        if (pointsNum % 2 == 0) index -= pointsNum / 2;
            else index -= pointsNum / 2 + 1;
        if (index < 0)
            index = 0;
        if (index + pointsNum > size)
            index = size - pointsNum;
    }
    return index;
}

TableOfValues * TableOfValues::config(double x, double y, int pointsNum_X, int pointsNum_Y)
{
    int inde_xX = findIndex(_x, x, pointsNum_X);
    Array X(pointsNum_X);
    for(int i = 0; i < pointsNum_X; ++i)
    {
        X[i] = _x[i + inde_xX];
    }

    int inde_xY = findIndex(_y, y, pointsNum_Y);
    Array Y(pointsNum_Y);
    for(int i = 0; i < pointsNum_Y; ++i)
    {
        Y[i] = _y[i + inde_xY];
    }

    Array2D Z(pointsNum_X, Array(pointsNum_Y));
    for(int i = 0; i < pointsNum_X; ++i)
    {
        for(int j = 0; j < pointsNum_Y; ++j)
        {
            Z[i][j] = _z[i + inde_xX][j + inde_xY];
        }
    }

    TableOfValues * table = new TableOfValues(X, Y, Z);

    return table;
}

double TableOfValues::interpolation(Array Y, Array X, double x)
{
    // Divided differences
    Array divDiffr = Y;
    divDiffr.resize(Y.size() - 1);
    for (unsigned int i = 0; i < Y.size() - 1; ++i)
	{
        for (unsigned int j = 0; j < Y.size() - 1 - i; ++j)
		{
            Y[j] = ( Y[j] - Y[j + 1] ) / (X[j] - X[j + 1 + i]);
		}
        divDiffr[i + 1] = Y[0];
	}

    // Assembly of Newton polynomial
	double sum = 0;	
    for(unsigned int i = 0; i < X.size(); ++i)
    {
        sum = divDiffr[i + 1];
        for(unsigned int j = 0; j < i + 1; ++j)
        {
            sum *= (x - X[j]);
        }
        divDiffr[0] += sum;
    }
	
    return divDiffr[0];
}

double TableOfValues::interpolation2D(double x, double y, int pointsNum_X, int pointsNum_Y)
{
    TableOfValues * table = this->config(x, y, pointsNum_X, pointsNum_Y);

    Array * X = new Array(pointsNum_X);

    for(int i = 0; i < pointsNum_X; ++i)
    {
        X->operator [](i) = interpolation(table->getZ()[i], table->getY(), y);
    }
    double result = interpolation(*X, table->getX(), x);

    delete X;
    delete table;

    return result;
}


void TableOfValues::console_out()
{
    cout << "x:" << endl;
    for(auto i : _x) cout << setw(5) << i;
    cout << endl << endl;

    cout << "y:" << endl;
    for(auto i : _y) cout << setw(5) << i;
    cout << endl << endl;

    cout << "z = f(x,y):" << endl << endl;
    for(auto i : _z)
    {
        for(auto j : i) cout << setw(5) << j;
        cout << endl << endl;
    }
    cout << endl;
}

bool operator ==(const TableOfValues & left, const TableOfValues & right)
{
    if((left.getX() == right.getX()) &&
       (left.getY() == right.getY()) &&
       (left.getZ() == right.getZ())) return true;
    else return false;
}

bool operator !=(const TableOfValues & left, const TableOfValues & right)
{
    if((left.getX() == right.getX()) &&
       (left.getY() == right.getY()) &&
       (left.getZ() == right.getZ())) return false;
    else return true;
}

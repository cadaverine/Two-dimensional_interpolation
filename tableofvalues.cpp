#include "tableofvalues.h"

TableOfValues::TableOfValues(int n, int m)
{
    setTable(n, m);
}

TableOfValues::TableOfValues(TableOfValues & t)
{
    x_ = t.getX();
    y_ = t.getY();
    z_ = t.getZ();
}

TableOfValues::TableOfValues(Array &x, Array &y, Array2D &z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

TableOfValues & TableOfValues::operator=(TableOfValues & t)
{
    if(this != &t)
    {
        x_ = t.getX();
        y_ = t.getY();
        z_ = t.getZ();
    }
    return * this;
}

Array   TableOfValues::getX() const { return x_; }
Array   TableOfValues::getY() const { return y_; }
Array2D TableOfValues::getZ() const { return z_; }


Array TableOfValues::operator[](int n) { return z_[n]; }


void TableOfValues::setTable(int X, int Y)
{
    x_.resize(X);
    y_.resize(Y);
    Array2D temp(X, Array(Y));
    z_ = temp;

    for(int i = 0; i < X; ++i) x_[i] = i + 1;
    for(int i = 0; i < Y; ++i) y_[i] = i + 1;
    for(int i = 0; i < X; ++i)
    {
        for(int j = 0; j < Y; ++j)
        {
            z_[i][j] = pow((i + 1), 2) + pow((j + 1), 2);
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

TableOfValues & TableOfValues::config(double x, double y, int pointsNum_X, int pointsNum_Y)
{
    int index_X = findIndex(x_, x, pointsNum_X);
    Array X(pointsNum_X);
    for(int i = 0; i < pointsNum_X; ++i)
    {
        X[i] = x_[i + index_X];
    }

    int index_Y = findIndex(y_, y, pointsNum_Y);
    Array Y(pointsNum_Y);
    for(int i = 0; i < pointsNum_Y; ++i)
    {
        Y[i] = y_[i + index_Y];
    }

    Array2D Z(pointsNum_X, Array(pointsNum_Y));
    for(int i = 0; i < pointsNum_X; ++i)
    {
        for(int j = 0; j < pointsNum_Y; ++j)
        {
            Z[i][j] = z_[i + index_X][j + index_Y];
        }
    }

    static TableOfValues table(X, Y, Z);

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
    TableOfValues t = this->config(x, y, pointsNum_X, pointsNum_Y);

    Array X(pointsNum_X);
    for(int i = 0; i < pointsNum_X; ++i)
    {
        X[i] = interpolation(t.getZ()[i], t.getY(), y);
    }
    double result = interpolation(X, t.getX(), x);

    return result;
}


void TableOfValues::console_out()
{
    cout << "x:" << endl;
    for(auto i : x_) cout << setw(5) << i;
    cout << endl << endl;

    cout << "y:" << endl;
    for(auto i : y_) cout << setw(5) << i;
    cout << endl << endl;

    cout << "z = f(x,y):" << endl << endl;
    for(auto i : z_)
    {
        for(auto j : i) cout << setw(5) << j;
        cout << endl << endl;
    }
    cout << endl;
}

#include <iomanip>
#include <iostream>
#include <tableofvalues.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::setprecision;

double XX = 0;
double YY = 0;
int NUM_OF_POINTS_X = 0;
int NUM_OF_POINTS_Y = 0;


int main()
{
    TableOfValues table;

    cout << "Program performs a two-dimensional interpolation of function " << endl;
    cout << "f(x,y) = x^2 + y^2 by Newton polynomial P(x,y)" << endl << endl;
    cout << "Enter the values of x, y." << endl;
    cout << "x: ";
    cin >> XX;
    cout << "y: ";
    cin >> YY;
    cout << endl;

    cout << "Enter the number of points on which the interpolation is carried out (x, y)." << endl;
    cout << "The x-axis: ";
    cin >> NUM_OF_POINTS_X;
    cout << "The y-axis: ";
    cin >> NUM_OF_POINTS_Y;
    cout << endl;

    cout << "f(x,y) = " << setprecision(9) << XX*XX + YY*YY << endl;
    cout << "P(x,y) = " << setprecision(9) << table.interpolation2D(XX, YY, NUM_OF_POINTS_X, NUM_OF_POINTS_Y) << endl; 

    return 0;
}

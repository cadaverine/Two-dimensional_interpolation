#include <QString>
#include <QtTest>

#include "tableofvalues.h"

class Test_TableOfValues : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void findIndex_data();
    void findIndex();

    void interpolation_data();
    void interpolation();

    void config_data();
    void config();

    void interpolation2D_data();
    void interpolation2D();
};

void Test_TableOfValues::findIndex_data()
{
    QTest::addColumn<Array>("array");
    QTest::addColumn<double>("number");
    QTest::addColumn<int>("pointsNum");
    QTest::addColumn<int>("result");

    Array arr = {1,  2,  3,  4,  5,
                 6,  7,  8,  9,  10,
                 11, 12, 13, 14, 15,
                 16, 17, 18, 19, 20};

    QTest::newRow("findIndex_test1") << arr << 2.3 << 4 << 0;
    QTest::newRow("findIndex_test2") << arr << -1.0 << 10 << 0;
    QTest::newRow("findIndex_test3") << arr << 2.1 << 1 << 1;
    QTest::newRow("findIndex_test4") << arr << 25.6 << 6 << 14;
    QTest::newRow("findIndex_test5") << arr << 2.1 << 0 << 2;
}

void Test_TableOfValues::findIndex()
{
    TableOfValues table;
    QFETCH(Array,  array);
    QFETCH(double, number);
    QFETCH(int,    pointsNum);
    QFETCH(int,    result);

    QCOMPARE(table.findIndex(array, number, pointsNum), result);
}

void Test_TableOfValues::interpolation_data()
{
    QTest::addColumn<Array>("Y");
    QTest::addColumn<Array>("X");
    QTest::addColumn<double>("x");
    QTest::addColumn<double>("result");

    Array arr_Y = { 1,  4,  9, 16, 25,
                   36, 49, 64, 81,100};
    Array arr_X = { 1,  2,  3,  4,  5,
                    6,  7,  8,  9, 10};

    QTest::newRow("interpolation_test1") << arr_Y << arr_X << 2.5 << 6.25;
    QTest::newRow("interpolation_test2") << arr_Y << arr_X << 1.1 << 1.21;
    QTest::newRow("interpolation_test3") << arr_Y << arr_X << 6.7 << 44.89;
    QTest::newRow("interpolation_test4") << arr_Y << arr_X << 9.062 << 82.119844;
    QTest::newRow("interpolation_test5") << arr_Y << arr_X << 0.21 << 0.0441;
}

void Test_TableOfValues::interpolation()
{
    TableOfValues table;
    QFETCH(Array, Y);
    QFETCH(Array, X);
    QFETCH(double, x);
    QFETCH(double, result);

    QCOMPARE(table.interpolation(Y, X, x), result);
}

void Test_TableOfValues::config_data()
{
    QTest::addColumn<double>("x");
    QTest::addColumn<double>("y");
    QTest::addColumn<int>("pointsNum_X");
    QTest::addColumn<int>("pointsNum_Y");
    QTest::addColumn<TableOfValues>("result");

    Array   X1 =   {1,  2,  3};
    Array   Y1 =   {1,  2,  3};
    Array2D Z1 = { {2,  5, 10},
                   {5,  8, 13},
                   {10, 13,18} };
    TableOfValues table1(X1, Y1, Z1);
    QTest::newRow("config_test1") << 1.2 << 1.3 << 3 << 3 << table1;


    Array   X2 =   {4,  5,  6, 7};
    Array   Y2 =   {6,  7,  8};
    Array2D Z2 = { {52, 65, 80},
                   {61, 74, 89},
                   {72, 85,100},
                   {85, 98,113} };
    TableOfValues table2(X2, Y2, Z2);
    QTest::newRow("config_test2") << 5.6 << 7.1 << 4 << 3 << table2;


    Array   X3 =   {9,   10};
    Array   Y3 =   {1,   2,   3,   4};
    Array2D Z3 = { {82,  85,  90,  97},
                   {101, 104, 109, 116} };
    TableOfValues table3(X3, Y3, Z3);
    QTest::newRow("config_test3") << 9.1 << 1.01 << 2 << 4 << table3;


    Array   X4 =   {3};
    Array   Y4 =   {5};
    Array2D Z4 = { {34} };
    TableOfValues table4(X4, Y4, Z4);
    QTest::newRow("config_test4") << 3.7 << 5.2 << 1 << 1 << table4;


    Array   X5;
    Array   Y5;
    Array2D Z5;
    TableOfValues table5(X5, Y5, Z5);
    QTest::newRow("config_test5") << 6.1 << 7.8 << 0 << 0 << table5;
}

void Test_TableOfValues::config()
{
    TableOfValues * table = new TableOfValues;
    QFETCH(double, x);
    QFETCH(double, y);
    QFETCH(int, pointsNum_X);
    QFETCH(int, pointsNum_Y);
    QFETCH(TableOfValues, result);

    QCOMPARE(*table->config(x, y, pointsNum_X, pointsNum_Y), result);
}

void Test_TableOfValues::interpolation2D_data()
{
    QTest::addColumn<double>("x");
    QTest::addColumn<double>("y");
    QTest::addColumn<int>("pointsNum_X");
    QTest::addColumn<int>("pointsNum_Y");
    QTest::addColumn<double>("result");

    QTest::newRow("interpolation2D_test1") << 4.1  << 5.04 << 3  << 5  << 42.2116;
    QTest::newRow("interpolation2D_test2") << 1.01 << 4.3  << 5  << 4  << 19.5101;
    QTest::newRow("interpolation2D_test3") << 9.24 << 6.78 << 4  << 4  << 131.346;
    QTest::newRow("interpolation2D_test4") << 3.8  << 7.3  << 3  << 3  << 67.73;
    QTest::newRow("interpolation2D_test5") << 5.55 << 5.55 << 5  << 5  << 61.605;
    QTest::newRow("interpolation2D_test6") << 5.0  << 5.0  << 8  << 8  << 50.0;
    QTest::newRow("interpolation2D_test7") << 5.0  << 5.0  << 10 << 10 << 50.0;
    QTest::newRow("interpolation2D_test8") << 5.0  << 5.0  << 20 << 20 << 50.0;
    QTest::newRow("interpolation2D_test9") << 5.0  << 5.0  << 1  << 1  << 32.0;
}

void Test_TableOfValues::interpolation2D()
{
    TableOfValues table;
    QFETCH(double, x);
    QFETCH(double, y);
    QFETCH(int, pointsNum_X);
    QFETCH(int, pointsNum_Y);
    QFETCH(double, result);

    QCOMPARE(table.interpolation2D(x, y, pointsNum_X, pointsNum_Y), result);
}

QTEST_MAIN(Test_TableOfValues)

#include "tst_Test_TableOfValuestest.moc"

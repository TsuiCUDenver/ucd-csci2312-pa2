#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "Cluster.h"

using namespace Clustering;
namespace Clustering {

    unsigned int Point::__idGen = 0; // id generator


    Point::Point(int __newDim) {

        __dim = __newDim;
        __values = new double[__dim];
        for (int count = 0; count < __dim; count++)
            __values[count] = 0.0;
        __id=__idGen++;
    }

    Point::Point(int __newDim, double *__newValue)
    {
        __dim = __newDim;
        __values = __newValue;
        __id=__idGen++;
    }

    Point::Point(const Point &copy) //Copy Constructor
    {
        __dim = copy.__dim;
        __values = new double[__dim];
        for (int count = 0; count < __dim; count++)
            __values[count] = copy.__values[count];
        __id = copy.__id;
    }

    Point &Clustering::Point::operator=(const Point &rhs) //=Overloaded Op
    {
        if (this == &rhs) {
            return *this;
        }
        else {
            if (__dim == rhs.__dim)

                for (int count = 0; count < __dim; count++) {
                    __values[count] = rhs.__values[count];
                }
        }
        return *this;
    }

    Point::~Point() //Destructor
    {
        delete[] __values;
    }

    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const
    {
        return __dim;
    }


    void Point::setValue(int index, double newValue)
    {
        __values[index] = newValue;
    }

    double Point::getValue(int index) const
    {
        return __values[index];
    }

    double Point::distanceTo(const Point &point) const
    {
        double side;
        double storage = 0;

        for (int count = 0; count < point.__dim; count++)
            storage += (pow(point.__values[count] - __values[count], 2));
        side = sqrt(storage);
        return side;
    }

    Point &Point::operator*=(double rhs)
    {
        for (int count = 0; count < __dim; count++)
            __values[count] *= rhs;
        return *this;
    }

    Point &Point::operator/=(double point)
    {
        for (int count = 0; count < __dim; count++)
            __values[count] /= point;
        return *this;
    }

    const Point Point::operator*(double point) const
    {
        return Point(*this) *= point;
    }

    const Point Point::operator/(double rhs) const
    {
        return Point(*this) /= rhs;
    }

    double &Point::operator[](int index)
    {
        return __values[index];
    }

    Point &operator+=(Point &lhs, const Point &rhs)
    {
        if (&lhs == &rhs) {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] += rhs.__values[count];
        }
        else if (lhs.__dim == rhs.__dim) {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] += rhs.__values[count];
        }
        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs)
    {
        if (&lhs == &rhs) {
            for (int count = 0; count < lhs.__dim; count++) {
                lhs.__values[count] = 0;
            }
        }
        else if (lhs.__dim == rhs.__dim) {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] -= rhs.__values[count];
        }
        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p += rhs;
    }

    const Point operator-(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p -= rhs;
    }

    bool operator==(const Point &lhs, const Point &rhs)
    {
        bool equal = true;
        if(lhs.__id !=rhs.__id)
            equal=false;
        else
        {
            for(int count =0; count < lhs.__dim; count++)
                if(lhs.__values[count] != rhs.__values[count])
                    equal=false;
        }
        return equal;
    }

    bool operator!=(const Point &lhs, const Point &rhs)
    {
        return !operator==(lhs, rhs);
    }

    bool operator<(const Point &lhs, const Point &rhs)
    {
        bool less = false;
        for (int count = 0; count < lhs.__dim; count++)
        {
            if (lhs.__values[count] < rhs.__values[count])
                return true;
            if(lhs.__values[count] > rhs.__values[count])
                return false;
        }
        return less;
    }

    bool operator>(const Point &lhs, const Point &rhs)
    {
        return operator<(rhs, lhs);
    }

    bool operator<=(const Point &lhs, const Point &rhs)
    {
        return !operator>(lhs, rhs);
    }

    bool operator>=(const Point &lhs, const Point &rhs)
    {
        return !operator<(lhs, rhs);
    }

    std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        unsigned int count =0;
        for(; count < point.__dim - 1; count++)
            os << point.__values[count] << ", ";
        os << point.__values[count];

        return os;
    }

    std::istream &operator>>(std::istream &input, Point &point)
    {
        std::string line;
        double d;
        for(int count =0; count < point.__dim; count++)
        {
            getline(input, line, ',');
            std::stringstream inputstring(line);
            inputstring>>d;
            point.__values[count] = d;
        }
        return input;
    }
}
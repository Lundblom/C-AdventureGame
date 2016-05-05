#include <cmath>
#include "PositionVector.h"

namespace labgame
{
    void PositionVector::setX(int _x)
    {
        this->x = _x;
    }
    
    void PositionVector::setY(int _y)
    {
        this->y = _y;
    }
    
    void PositionVector::setPosition(int _x, int _y)
    {
        this->x = _x;
        this->y = _y;
    }
    
    int PositionVector::X() const
    {
        return this->x;
    }
    
    int PositionVector::Y() const
    {
        return this->y;
    }
    
    double PositionVector::distance(PositionVector t) const
    {
        return sqrt(pow((t.X() - this->X()), 2) + pow((t.Y() - this->Y()), 2));
    }
    
    std::ostream& operator<<(std::ostream& os, const PositionVector& obj)
    {
        os << "(" << obj.X() << ", " << obj.Y() << ")";
        return os;
    }
}
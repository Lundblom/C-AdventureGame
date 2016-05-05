#include <iostream>
#pragma once
namespace labgame
{
    class PositionVector
    {
        private:
        int x;
        int y;
        
        public:
        PositionVector(int _x, int _y) : x(_x), y(_y) {}
        PositionVector() : x(0), y(0) {}
        
        void setX(int _x);
        void setY(int _y);
        void setPosition(int _x, int _y);
        int Y() const;
        int X() const;
        
        double distance(PositionVector t) const;
        
        friend std::ostream& operator<<(std::ostream& os, const PositionVector& obj);
        
    };
}
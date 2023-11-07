#pragma once

#include "globals.h"

class Position {
    public:
        double x, y, heading;

        Position(double x, double y, double heading);

        void setPosition(Position set);
        void setPosition(double x, double y, double heading);

        string toString(void);

        // Operator overloads
        Position operator+(const Position& other);
        Position operator-(const Position& other);
        Position operator+=(const Position& other);
        Position operator-=(const Position& other);
        double operator*(const Position& other);
        Position operator*(const double other);

        // Between two poses
        double angle(const Position& other);
        double distance(const Position& other);

        Position lerp(Position other, float t);
};

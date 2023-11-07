#include "globals.h"

Position::Position(double x, double y, double heading) {
    this->x = x;
    this->y = y;
    this->heading = heading;
}

void Position::setPosition(Position set) {
    setPosition(set.x, set.y, set.heading);
}

void Position::setPosition(double x, double y, double heading) {
    this->x = x;
    this->y = y;
    this->heading = heading;
}

string Position::toString() {
    return "X: " + to_string(this->x) + " Y: " + to_string(this->y) + " Head: " + to_string(this->heading);
}

Position Position::operator+(const Position& other) {
    return Position(this->x + other.x, this->y + other.y, this->heading + other.heading);
}

Position Position::operator+=(const Position& other) {
    return Position(this->x + other.x, this->y + other.y, this->heading + other.heading);
}

Position Position::operator-(const Position& other) {
    return Position(this->x - other.x, this->y - other.y, this->heading - other.heading);
}

Position Position::operator-=(const Position& other) {
    return Position(this->x - other.x, this->y - other.y, this->heading - other.heading);
}

double Position::operator*(const Position& other) { return this->x * other.x + this->y * other.y; }

Position Position::operator*(const double other) { return Position(this->x * other, this->y * other, this->heading); }

double Position::angle(const Position& other) {
    return atan2(other.y - this->y, other.x - this->x);
}

double Position::distance(const Position& other) {
    return hypot(this->x - other.x, this->y - other.y);
}

Position Position::lerp(Position other, float t) {
    return Position(this->x + (other.x - this->x) * t, this->y + (other.y - this->y) * t, this->heading);
}
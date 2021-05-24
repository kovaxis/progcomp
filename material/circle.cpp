#include "circle.h"

int main() {
    Circle c = {{8., 10.}, 3.};
    pair<Vec2, Vec2> points = tangents(c, {-1., 1.});
    cout << points.first << ", " << points.second << endl;
}
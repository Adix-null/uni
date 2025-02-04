#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

typedef struct
{
    double x;
    double y;
} Point;

void printPoint(Point p)
{
    printf("(%.3f, %.3f)\n", p.x, p.y);
}

Point createPoint(double x, double y)
{
    Point temp = {x, y};
    return temp;
}

double getDistance(Point a, Point b)
{
    double dx = abs(a.x - b.x);
    double dy = abs(a.y - b.y);
    return sqrt(dx * dx + dy * dy);
}

int main()
{
    printf("%f", getDistance(createPoint(2, -3), createPoint(-4, 5)));

    return 0;
}

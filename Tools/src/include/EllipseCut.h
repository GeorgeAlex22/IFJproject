#ifndef EllipseCut_h
#define EllipseCut_h

#include <cmath>

inline bool is_inside_ellipse(double x, double y, 
                              double center_x, double center_y, 
                              double r1, double r2, 
                              double angle /*degrees*/) {
        x -= center_x;
        y -= center_y;
        angle *= 2.0 * M_PI / 360.0;

        double s = sin(angle);
        double c = cos(angle);

        return (pow((x*c - y*s)/r1, 2.0) + pow((x*s + y*c)/r2, 2.0) <= 1.0);
}

#endif //  #ifndef EllipseCut_h

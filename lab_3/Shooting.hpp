#include <stdexcept>
#include <cmath>

const double g = 9.8;
const double pi = 3.1415;

struct ShootingResult{
    double v0;
    double angle;
    double distance;
    bool success;
    size_t iterations;

    ShootingResult() : v0{0}, angle{0}, distance{0}, success{false}, iterations{0} {}
};

double GetAlpha(double angle){
    return angle * pi / 180;
}

double GetDistance(double v0, double angle){
    return v0 * v0 * sin(2 * GetAlpha(angle) ) / g;
}

double GetMaxDistance(double v0){
    return v0 * v0 / g;
}

double FindAngle(double& v0, double& x1, double& x2, size_t& iterations){
    double left = 0.0;
    double reght = 45.0;

    for(size_t i = 0; i < 100; i++ ){
        iterations++;
        double mid = (left + reght) / 2;
        double dist = GetDistance(v0, mid);

        if (dist < x1){
            left = mid;
        }
        if (dist > x2){
            reght = mid;
        }
    }
    return (left + reght) / 2;
}
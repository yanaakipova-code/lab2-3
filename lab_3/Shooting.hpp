#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include "../Set.hpp"
#include "../../Error.hpp"

const double g = 9.8;
const double pi = 3.1415;

struct ShootingResult{
    double v0;
    double angle;
    double distance;
    bool success;
    size_t iterations;

    ShootingResult() : v0{0}, angle{0}, distance{0}, success{false}, iterations{0} {};

    ShootingResult(double v, double a, double d, bool s, size_t iter = 0)
        : v0{v}, angle{a}, distance{d}, success{s}, iterations{iter} {};

    std::string ToString() const {
        std::ostringstream oss;
        
        if (success) {
            oss << "ПОПАДАНИЕ!\n";
            oss << " Скорость: " << v0 << " м/с\n";
            oss << "  Угол: " << angle << "\n";
            oss << "  Дальность: " << distance << " м\n";
        } else {
            oss << " Точного попадания нет\n";
            oss << "  (наилучшее приближение)\n";
            oss << "  Скорость: " << v0 << " м/с\n";
            oss << "  Угол: " << angle << "\n";
            oss << "  Дальность: " << distance << " м\n";
        }
        oss << "  Итераций: " << iterations;
        
        return oss.str();
    }
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

bool Comparison(double a, double b){
    double eps = 1e-10;
    if (std::abs(a - b) < eps){
        return true;
    }
    return false;
}

double FindAngle(double v0, double& x1, double& x2, size_t& iterations){
    double left = 0.0;
    double right = 45.0;
    double target = (x1 + x2) / 2;

    for(size_t i = 0; i < 100; i++ ){
        iterations++;
        double mid = (left + right) / 2;
        double dist = GetDistance(v0, mid);

        if (Comparison(dist, target)){
            left = mid;
        }else{
            right = mid;
        }
    }
    return (left + right) / 2;
}

template<typename T, template<typename> class Container>
ShootingResult FindShooting(double x1, double x2, Set<T, Container>& velocities){

    ShootingResult best_result{};
    //если не попали, то это для нахождение минимального промаха
    double min_dist =  1e9;
    double target = (x2 + x1)/2;

    for(const auto& v0 : velocities){
        double max_dis = GetMaxDistance(v0);
        //невозможно попасть ни при каких условиях(мы не долетели)
        if(Comparison(max_dis, x1)){
            throw ImpossibleToGetInException("Невозможно попасть в цель!");
        }

        size_t iterations = 0;
        double alpha = FindAngle(v0, x1, x2, iterations);
        double dist = GetDistance(v0, alpha);

        if(Comparison(x1, dist) && Comparison(dist, x2)){
            return ShootingResult{v0, alpha, dist, true, iterations};
        }
        
        //насколько промахнулисть
        double deviation = std::abs(dist - target);

        if(Comparison(deviation, min_dist)){
            min_dist = deviation;
            best_result = {v0, alpha, dist, false, iterations};
        }
    }

    return best_result;

}
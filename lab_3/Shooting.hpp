#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include "Set.hpp"
#include "../Error.hpp"

const double g = 9.8;
const double pi = std::atan(1.0) * 4;

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
        if (success) {
            return std::format("ПОПАДАНИЕ!\n"
                           "  Скорость: {} м/с\n"
                           "  Угол: {}°\n"
                           "  Дальность: {} м\n"
                           "  Итераций: {}", 
                           v0, angle, distance, iterations);
        } else {
            return std::format("Не попали :(\n"
                           "  (наилучшее приближение)\n"
                           "  Скорость: {} м/с\n"
                           "  Угол: {}\n"
                           "  Дальность: {} м\n"
                           "  Итераций: {}", 
                           v0, angle, distance, iterations);
        }
    }
    operator std::string() const {
        return ToString();
    }
};

double GetAlpha(double angle){
    return angle * pi / 180;
}

double GetDistance(double v0, double angle){
    if (angle <= 0.0 || angle >= 90.0) return 0.0;
    return v0 * v0 * sin(2 * GetAlpha(angle) ) / g;
}

double GetMaxDistance(double v0){
    return v0 * v0 / g;
}

template<template<typename> class Container,
        template<typename> class BoundsAdapter>
double FindAngle(double v0, double target, 
                BoundsAdapter<double>& bounds,
                size_t& iterations) {
    
    bounds.Add(0.0);
    bounds.Add(45.0);
    
    iterations = 0;
    
    for (size_t i = 0; i < 100; i++) {
        iterations++;
        
        double left = bounds[0];
        double right = bounds[1];
        double mid = (left + right) / 2;
        double dist = GetDistance(v0, mid);
        
        if (std::abs(dist - target) < 1e-6) return mid;
        
        bounds.Dequeue();
        bounds.Dequeue();
        
        if (dist < target) {
            bounds.Add(mid);
            bounds.Add(right);
        } else {
            bounds.Add(left);
            bounds.Add(mid);
        }
    }
    
    return (bounds[0] + bounds[1]) / 2;
}


template<template<typename> class Container,
         template<typename> class BoundsAdapter,
         template<typename, template<typename> class> class VelContainer>
ShootingResult FindShooting(double x1, double x2, VelContainer<double, Container>& velocities) {
    
    double target = (x1 + x2) / 2;
    ShootingResult best_result;
    double best_diff = 1e9;
    bool found = false;
    
    for (const auto& v0 : velocities) {
        if (GetMaxDistance(v0) < x1) continue;
        
        BoundsAdapter<double> bounds;
        bounds.Add(0.0);
        bounds.Add(45.0);
        
        size_t iterations = 0;
        
        for (size_t i = 0; i < 100; i++) {
            iterations++;
            
            double left = bounds[0];
            double right = bounds[1];
            double mid = (left + right) / 2;
            double dist = GetDistance(v0, mid);
            
            if (std::abs(dist - target) < 1e-6) {
                return ShootingResult(v0, mid, dist, true, iterations);
            }
            
            bounds.Dequeue();
            bounds.Dequeue();
            
            if (dist < target) {
                bounds.Add(mid);
                bounds.Add(right);
            } else {
                bounds.Add(left);
                bounds.Add(mid);
            }
        }
        
        double angle = (bounds[0] + bounds[1]) / 2;
        double distance = GetDistance(v0, angle);
        
        if (distance >= x1 && distance <= x2) {
            return ShootingResult(v0, angle, distance, true, iterations);
        }
        
        double diff = std::abs(distance - target);
        if (diff < best_diff) {
            best_diff = diff;
            best_result = ShootingResult(v0, angle, distance, false, iterations);
            found = true;
        }
    }
    
    if (!found) {
        throw ImpossibleToGetInException("Невозможно попасть в цель!");
    }
    
    return best_result;
}
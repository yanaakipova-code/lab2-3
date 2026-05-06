#define _USE_MATH_DEFINES
#include <cmath>
#include "catch.hpp"
#include "../Shooting.hpp"
#include "../Set.hpp"
#include "../ArraySequence.hpp"
#include "../ListSequence.hpp"

using namespace std;

TEST_CASE("GetAlpha: перевод градусов в радианы") {
    REQUIRE(GetAlpha(0) == Approx(0.0));
    REQUIRE(GetAlpha(45) == Approx(M_PI / 4));
    REQUIRE(GetAlpha(90) == Approx(M_PI / 2));
    REQUIRE(GetAlpha(180) == Approx(M_PI));
}

TEST_CASE("GetDistance: расчет дальности полета") {
    REQUIRE(GetDistance(10, 45) == Approx(100 / 9.8));
    REQUIRE(GetDistance(20, 45) == Approx(400 / 9.8));
    REQUIRE(GetDistance(30, 45) == Approx(900 / 9.8));
    
    REQUIRE(GetDistance(10, 0) == Approx(0));
    REQUIRE(GetDistance(100, 0) == Approx(0));
    REQUIRE(GetDistance(10, 90) == Approx(0));
}

TEST_CASE("GetMaxDistance: максимальная дальность") {
    REQUIRE(GetMaxDistance(10) == Approx(100 / 9.8));
    REQUIRE(GetMaxDistance(20) == Approx(400 / 9.8));
    REQUIRE(GetMaxDistance(30) == Approx(900 / 9.8));
    REQUIRE(GetMaxDistance(0) == Approx(0));
}

TEST_CASE("FindAngle: поиск угла для заданной дальности") {
    ArraySequence<double> bounds;
    size_t iterations = 0;
    double target = 55.0;
    
    double angle = FindAngle<ArraySequence>(25.0, target, bounds, iterations);
    double distance = GetDistance(25.0, angle);
    
    REQUIRE(distance > 54.0);
    REQUIRE(distance < 56.0);
    REQUIRE(iterations > 0);
}

TEST_CASE("FindAngle: количество итераций") {
    ArraySequence<double> bounds;
    size_t iterations = 0;
    double target = 55.0;
    
    FindAngle<ArraySequence>(25.0, target, bounds, iterations);
    
    REQUIRE(iterations == 100);
}

TEST_CASE("FindAngle: с ListSequence") {
    ListSequence<double> bounds;
    size_t iterations = 0;
    double target = 55.0;
    
    double angle = FindAngle<ListSequence>(25.0, target, bounds, iterations);
    double distance = GetDistance(25.0, angle);
    
    REQUIRE(distance > 54.0);
    REQUIRE(distance < 56.0);
    REQUIRE(iterations > 0);
}

TEST_CASE("ShootingResult: конструктор по умолчанию") {
    ShootingResult r;
    
    REQUIRE(r.v0 == 0);
    REQUIRE(r.angle == 0);
    REQUIRE(r.distance == 0);
    REQUIRE(r.success == false);
    REQUIRE(r.iterations == 0);
}

TEST_CASE("ShootingResult: конструктор с параметрами") {
    ShootingResult r(10.5, 30.0, 55.2, true, 50);
    
    REQUIRE(r.v0 == 10.5);
    REQUIRE(r.angle == 30.0);
    REQUIRE(r.distance == 55.2);
    REQUIRE(r.success == true);
    REQUIRE(r.iterations == 50);
}

TEST_CASE("ShootingResult: ToString - успешное попадание") {
    ShootingResult r(25.0, 38.0, 55.2, true, 100);
    string str = r.ToString();
    
    REQUIRE(str.find("ПОПАДАНИЕ!") != string::npos);
    REQUIRE(str.find("25") != string::npos);
    REQUIRE(str.find("38") != string::npos);
    REQUIRE(str.find("55.2") != string::npos);
}

TEST_CASE("ShootingResult: ToString - неудачное попадание") {
    ShootingResult r(20.0, 40.0, 48.0, false, 100);
    string str = r.ToString();
    
    REQUIRE(str.find("Не попали") != string::npos);
    REQUIRE(str.find("20") != string::npos);
    REQUIRE(str.find("40") != string::npos);
    REQUIRE(str.find("48") != string::npos);
}

TEST_CASE("FindShooting: поиск оптимального выстрела с Set и ArraySequence") {
    Set<double, ArraySequence> velocities;
    velocities.Add(20.0);
    velocities.Add(25.0);
    velocities.Add(30.0);
    velocities.Add(35.0);
    velocities.Add(40.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
    REQUIRE(result.distance > 0);
}

TEST_CASE("FindShooting: поиск оптимального выстрела с Set и ListSequence") {
    Set<double, ListSequence> velocities;
    velocities.Add(20.0);
    velocities.Add(25.0);
    velocities.Add(30.0);
    velocities.Add(35.0);
    velocities.Add(40.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting<ListSequence>(x1, x2, velocities);
    REQUIRE(result.distance > 0);
}

TEST_CASE("FindShooting: маленькие скорости не долетают") {
    Set<double, ArraySequence> velocities;
    velocities.Add(10.0);
    velocities.Add(15.0);
    
    double x1 = 100.0;
    double x2 = 150.0;
    
    REQUIRE_THROWS_AS(FindShooting<ArraySequence>(x1, x2, velocities), 
                      ImpossibleToGetInException);
}

TEST_CASE("FindShooting: проверка итераций") {
    Set<double, ArraySequence> velocities;
    velocities.Add(30.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
    REQUIRE(result.iterations > 0);
}

TEST_CASE("FindShooting: проверка угла в пределах 0-45 градусов") {
    Set<double, ArraySequence> velocities;
    velocities.Add(25.0);
    velocities.Add(30.0);
    velocities.Add(35.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
    REQUIRE(result.angle >= 0);
    REQUIRE(result.angle <= 45);
}

TEST_CASE("FindShooting: пустое множество скоростей") {
    Set<double, ArraySequence> velocities;
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    REQUIRE_THROWS_AS(FindShooting<ArraySequence>(x1, x2, velocities), 
                      ImpossibleToGetInException);
}

TEST_CASE("FindShooting: попадание в цель") {
    Set<double, ArraySequence> velocities;
    velocities.Add(24.0);
    velocities.Add(25.0);
    velocities.Add(26.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
    
    REQUIRE((result.success || result.distance > 0));
    REQUIRE(result.distance >= x1 - 5);
    REQUIRE(result.distance <= x2 + 5);
}

TEST_CASE("FindShooting: широкая цель") {
    Set<double, ArraySequence> velocities;
    velocities.Add(20.0);
    velocities.Add(25.0);
    velocities.Add(30.0);
    
    double x1 = 40.0;
    double x2 = 80.0;
    
    ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
    REQUIRE(result.distance >= x1);
    REQUIRE(result.distance <= x2);
}

TEST_CASE("FindShooting: узкая цель") {
    Set<double, ArraySequence> velocities;
    velocities.Add(20.0);
    velocities.Add(25.0);
    velocities.Add(30.0);
    velocities.Add(35.0);
    velocities.Add(40.0);
    
    double x1 = 55.0;
    double x2 = 56.0;
    
    ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
    REQUIRE((result.success || abs(result.distance - 55.5) < 10));
}
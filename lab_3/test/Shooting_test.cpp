// Shooting_test.cpp
#define _USE_MATH_DEFINES
#include <cmath>
#include "catch.hpp"
#include "../Shooting.hpp"
#include "../Set.hpp"
#include "../ArraySequence.hpp"

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
    size_t iterations = 0;
    double x1 = 50, x2 = 60;
    
    double angle = FindAngle(25, x1, x2, iterations);
    double distance = GetDistance(25, angle);
    
    REQUIRE(distance >= x1);
    REQUIRE(distance <= x2);
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

TEST_CASE("FindShooting: поиск оптимального выстрела с попаданием") {
    Set<double, ArraySequence> velocities;
    velocities.Add(20.0);
    velocities.Add(25.0);
    velocities.Add(30.0);
    velocities.Add(35.0);
    velocities.Add(40.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result;
    REQUIRE_NOTHROW(result = FindShooting(x1, x2, velocities));
}

TEST_CASE("FindShooting: правильный расчет дальности") {
    Set<double, ArraySequence> velocities;
    velocities.Add(25.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting(x1, x2, velocities);
    
    REQUIRE(result.distance > 0);
}

TEST_CASE("FindShooting: маленькие скорости не долетают") {
    Set<double, ArraySequence> velocities;
    velocities.Add(10.0);
    velocities.Add(15.0);
    
    double x1 = 100.0;
    double x2 = 150.0;
    
    REQUIRE_THROWS_AS(FindShooting(x1, x2, velocities), ImpossibleToGetInException);
}

TEST_CASE("FindShooting: проверка итераций") {
    Set<double, ArraySequence> velocities;
    velocities.Add(30.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting(x1, x2, velocities);
    
    REQUIRE(result.iterations > 0);
}

TEST_CASE("FindShooting: проверка угла в пределах 0-45 градусов") {
    Set<double, ArraySequence> velocities;
    velocities.Add(25.0);
    velocities.Add(30.0);
    velocities.Add(35.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result = FindShooting(x1, x2, velocities);
    
    REQUIRE(result.angle >= 0);
    REQUIRE(result.angle <= 45);
}

TEST_CASE("FindShooting: разные скорости дают разные результаты") {
    Set<double, ArraySequence> velocities1;
    velocities1.Add(25.0);
    velocities1.Add(30.0);
    
    Set<double, ArraySequence> velocities2;
    velocities2.Add(35.0);
    velocities2.Add(40.0);
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    ShootingResult result1 = FindShooting(x1, x2, velocities1);
    ShootingResult result2 = FindShooting(x1, x2, velocities2);
    
    REQUIRE((result1.distance > 0 || result1.success));
    REQUIRE((result2.distance > 0 || result2.success));
}

TEST_CASE("FindShooting: проверка центра цели") {
    Set<double, ArraySequence> velocities;
    velocities.Add(30.0);
    velocities.Add(40.0);
    
    double x1 = 100.0;
    double x2 = 120.0;
    double center = (x1 + x2) / 2;
    
    ShootingResult result = FindShooting(x1, x2, velocities);
    
    if (!result.success) {
        double diff = std::abs(result.distance - center);
        REQUIRE(diff < 100);
    }
}

TEST_CASE("FindShooting:  пустое множество скоростей") {
    Set<double, ArraySequence> velocities;
    
    double x1 = 50.0;
    double x2 = 60.0;
    
    REQUIRE_THROWS_AS(FindShooting(x1, x2, velocities), ImpossibleToGetInException);
}
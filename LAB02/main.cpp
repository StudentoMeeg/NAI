#include <iostream>
#include <functional>
#include <math.h>
#include <random>
#include <time.h>
using namespace std;
using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 gen(rd());

double optimise(auto function, auto dziedzina, int iterations) 
{
    clock_t start, end;
    double time_of_run;
    start = clock();

    std::uniform_real_distribution<double> random(dziedzina.at(0), dziedzina.at(1));
    double lowest = function(dziedzina.at(0), dziedzina.at(1));
    double bestX = 0;
    double bestY = 0;

    for (int i = 1; i < iterations; i++) {

        double rand1 = random(gen);
        double rand2 = random(gen);
        double temp = function(rand1, rand2);

        if (temp < lowest)
            bestX = rand1;
            bestY = rand2;
            lowest = temp;
    }

    end = clock();
    time_of_run = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time: " << time_of_run <<  "  Best X: " << bestX << "  Best Y: " << bestY << "  Result: ";
    return lowest;
}

double Three_Hump_Camel_function (double x, double y) {
    double f = 2*pow(x,2) - 1.05*pow(x,4) + pow(x,6)/6 + x*y + pow(y,2);
    return f; 
}

double Goldstein_Price_function (double x, double y) {
    double f = (1+pow((x+y+1),2)*19-14*x+3*pow(x,2)-14*y+6*x*y+3*pow(y,2))*(30+pow((2*x-3*y),2)+18-32*x+12*pow(x,2)+48*y-36*x*y+27*pow(y,2));
    return f;
}

double Matyas_function (double x, double y) {
    double f = 0.26*(pow(x,2)+pow(y,2)) - 0.48*x*y;
    return f;
}

int main()
{
    vector<double> dziedzina = {-10.0, 10.0};
    cout << "Number of iterations is 100000." << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << optimise(Matyas_function, dziedzina, 100000) << endl;
    }
    return 0;
}s
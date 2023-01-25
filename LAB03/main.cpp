#include <iostream>
#include <functional>
#include <math.h>
#include <random>
#include <time.h>
using namespace std;
using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 gen(rd());

vector<double> losoweProbkowanie(auto function, auto dziedzina, int iterations) 
{
    std::uniform_real_distribution<double> random(dziedzina.at(0), dziedzina.at(1));
    double lowest = function(dziedzina.at(0), dziedzina.at(1));
    double bestX = 0;
    double bestY = 0;
    vector<double> results;

    for (int i = 1; i < iterations; i++) {

        double x = random(gen);
        double y = random(gen);
        double temp = function(x, y);

        if (temp < lowest)
            bestX = x;
            bestY = y;
            lowest = temp;
    }

    results.push_back(lowest);
    results.push_back(bestX);
    results.push_back(bestY);
    return results;
}

vector<double> wspinaczkowy(auto function, auto dziedzina, int iterations) {
    uniform_real_distribution<double> random(dziedzina.at(0), dziedzina.at(1));
    uniform_real_distribution<double> neighbours(-0.005, 0.005);
    double x = random(gen);
    double y = random(gen);
    double lowest = function(x,y);
    vector<double> results;

    for (int i = 0; i < iterations; i++) {
        double tempX = x + neighbours(gen);
        double tempY = y + neighbours(gen);

        if(tempX > dziedzina.at(0) && tempX < dziedzina.at(1) && tempY > dziedzina.at(0) && tempY < dziedzina.at(1)) {
            continue;
        }
        double neighbour_lowest = function(tempX, tempY);
        if (neighbour_lowest < lowest) {
            lowest = neighbour_lowest;
            x = tempX;
            y = tempY;
        }
    }
    results.push_back(lowest);
    results.push_back(x);
    results.push_back(y);
    return results;
}

vector<double> wyzazanie(auto function, auto dziedzina, int iterations) {
    uniform_real_distribution<double> random(dziedzina.at(0), dziedzina.at(1));
    normal_distribution<double> neighbours;
    double x = random(gen);
    double y = random(gen);
    double lowest = function(x,y);
    vector<double> results;
    
    for (int k = 1; k < iterations; k++) {
        double tempX = x + 0.01 * neighbours(gen);
        double tempY = y + 0.01 * neighbours(gen);          //S(0) dla pierwszej iteracji
        double neighbour_lowest = function(tempX, tempY);   //
        
        if(neighbour_lowest < lowest) {
            x = tempX;
            y = tempY;
            lowest = neighbour_lowest;
        } else {
            uniform_real_distribution<double> rand(0, 1); //usuwanie zbyt złych wyników
            double temp = abs(neighbour_lowest - lowest);
            double Tk = 1.0 / k;                            //temperatura
            if (rand(gen) < exp(-1 * temp) / loopIter) {
                x = tempX;
                y = tempY;
            }
        }
    }
    results.push_back(lowest);
    results.push_back(x);
    results.push_back(y);
    return results;
}

//-5 5
double Three_Hump_Camel_function (double x, double y) {
    double f = 2*pow(x,2) - 1.05*pow(x,4) + pow(x,6)/6 + x*y + pow(y,2);
    return f; 
}
//-2 2
double Goldstein_Price_function (double x, double y) {
    double f = (1+pow((x+y+1),2)*19-14*x+3*pow(x,2)-14*y+6*x*y+3*pow(y,2))*(30+pow((2*x-3*y),2)+18-32*x+12*pow(x,2)+48*y-36*x*y+27*pow(y,2));
    return f;
}
//-10 10
double Matyas_function (double x, double y) {
    double f = 0.26*(pow(x,2)+pow(y,2)) - 0.48*x*y;
    return f;
}

int main()
{
    vector<double> dziedzina1 = {-10.0, 10.0};
    vector<double> dziedzina2 = {-2.0, 2.0};
    vector<double> dziedzina3 = {-5.0, 5.0};
    cout << "Number of iterations is 100000." << endl << endl;
    clock_t start, end;
    double time_of_run;
    double avgTime = 0;
    vector<double> wynik;
    double avgLowest = 0;
    
    for (int i =0; i < 20; i++) {
        start = clock();
        wynik = losoweProbkowanie(Matyas_function, dziedzina1, 100000);
        avgLowest = avgLowest + wynik.at(0);
        end = clock();
        time_of_run = ((double)(end - start)) / CLOCKS_PER_SEC;
        avgTime = avgTime + time_of_run;
    }
    avgLowest = avgLowest/20;
    avgTime = avgTime/20;
    cout << "Wyniki dla losoweProbkowanie:" << endl;
    cout << "Avg Time: " << avgTime << endl;
    cout << "Avg Lowest: " << avgLowest << endl << endl;
    //cout << "Best X: " << wynik.at(1) << endl;
    //cout << "Best Y: " << wynik.at(2) << endl;

    avgTime = 0;
    avgLowest =0;

    for (int o =0; o < 20; o++) {
        start = clock();
        wynik = wspinaczkowy(Matyas_function, dziedzina1, 100000);
        avgLowest = avgLowest + wynik.at(0);
        end = clock();
        time_of_run = ((double)(end - start)) / CLOCKS_PER_SEC;
        avgTime = avgTime + time_of_run;
    }
    avgTime = avgTime/20;
    avgLowest = avgLowest/20;
    cout << "Wyniki dla wspinaczkowy:" << endl;
    cout << "Avg Time: " << avgTime << endl;
    cout << "Avg Lowest: " << avgLowest << endl << endl;
    //cout << "Best X: " << wynik.at(1) << endl;
    //cout << "Best Y: " << wynik.at(2) << endl;

    avgTime = 0;
    avgLowest = 0;

for (int u = 0; u < 20; u++) {
        start = clock();
        wynik = wyzazanie(Matyas_function, dziedzina1, 100000);
        avgLowest = avgLowest + wynik.at(0);
        end = clock();
        time_of_run = ((double)(end - start)) / CLOCKS_PER_SEC;
        avgTime = avgTime + time_of_run;
    }
    avgTime = avgTime/20;
    avgLowest = avgLowest/20;
    cout << "Wyniki dla wyzazanie:" << endl;
    cout << "Avg Time: " << avgTime << endl;
    cout << "Avg Lowest: " << avgLowest << endl << endl;
    //cout << "Best X: " << wynik.at(1) << endl;
    //cout << "Best Y: " << wynik.at(2) << endl;


    return 0;
}
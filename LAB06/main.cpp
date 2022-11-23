#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(time(nullptr));

//funkcje do testów:
void wypiszWektor(std::vector<int> v) {
    for(int y=0; y<v.size(); y++) {
    std::cout << v.at(y) << " ";
    }
    std::cout << std:: endl;
}

//koniec funkcji do testów


//function to optimize using the GA
double THCamel_function (double x, double y) {
    using namespace std;
    double f = 2*pow(x,2) - 1.05*pow(x,4) + pow(x,6)/6 + x*y + pow(y,2);
    return f; 
}

std::vector<int> genGenotyp() {
    std::vector<int> genotyp;
    for (int i = 1; i < 112; i++) {
        int temp = gen() % 2;
        genotyp.push_back(temp);
    } 
    return genotyp;
}

//function to translate binary to decimal
int genToFen(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;

    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}

int main() {

    std::vector<int> genotyp = genGenotyp();
    std::string str(genotyp.begin(), genotyp.end());
    std::cout << genToFen(stoi(str)) << std::endl;

    return 0;
}
#include <iostream>
#include <math.h>
#include <functional>
#include <map>

int main(int argc, char **argv) {

    using namespace std;

    vector<string> argumenty(argv, argv + argc);

    map<string, function<string(vector<string>)>> mapa;
    mapa["add"] = [](vector<string> v) {
        float a = stof(v.at(2));
        float b = stof(v.at(3));
        return to_string(a+b);
        };

    mapa["mod"] = [](vector<string> v) {
        int a = stoi(v.at(2));
        int b = stoi(v.at(3));
        return to_string(a%b);
        };

    mapa["sin"] = [](vector<string> v) {
        float a = stof(v.at(2));
        float sinus = a;
        sinus = sin(sinus);
        return to_string(sinus);
    };

    try {
    vector<string> argumenty(argv, argv + argc);
    function f = mapa.at(argumenty.at(1));
    cout << f(argumenty);
  } catch (std::out_of_range aor) {
    cout << "Podaj argument. Dostępne to: ";
    for (auto [k, v] : mapa) cout << " " << k;
    return 1;
  }

    return 0;
}
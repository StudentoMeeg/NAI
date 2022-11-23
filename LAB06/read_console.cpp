#include <iostream>
#include <vector>
#include <string>

 int main(int argc, char **argv) {

    std::vector<std::string> consoleInput(argv, argv + argc);

    int popSize = stoi(consoleInput.at(1));
    int iterNum = stoi(consoleInput.at(2));
    double crossProb = stod(consoleInput.at(3));
    double mutationProb = stod(consoleInput.at(4));

    std::cout << "Rozmiar populacji: " << popSize <<
                 " Liczba iteracji: " << iterNum <<
                 " Prawdopodobieństwo krzyżowania: " <<  crossProb <<
                 " Prawdopodobieństwo mutacji: " << mutationProb << std::endl;

    return 0;
 }
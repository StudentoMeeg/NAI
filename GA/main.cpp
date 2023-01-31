#include <iostream>
#include <functional>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>

std::random_device rd;
std::mt19937 mt_generator(rd());
using chromosome_t = std::vector<int>;
using population_t = std::vector<chromosome_t>;

using fitness_f = std::function<double(const chromosome_t &)>;
using term_condition_f = std::function<bool(const population_t &, const std::vector<double> &, const int)>;
using selection_f = std::function<int(const std::vector<double> &)>;
using crossover_f = std::function<std::vector<chromosome_t>(const std::vector<chromosome_t> &)>;
using mutation_f = std::function<chromosome_t(const chromosome_t, double)>;

double Three_Hump_Camel_function (double x, double y) {
    double f = 2*pow(x,2) - 1.05*pow(x,4) + pow(x,6)/6 + x*y + pow(y,2);
    return f;
} // -5, 5
double Goldstein_Price_function (double x, double y) {
    double f = (1+pow((x+y+1),2)*19-14*x+3*pow(x,2)-14*y+6*x*y+3*pow(y,2))*(30+pow((2*x-3*y),2)+18-32*x+12*pow(x,2)+48*y-36*x*y+27*pow(y,2));
    return f;
} // -2, 2
double Matyas_function (double x, double y) {
    double f = 0.26*(pow(x,2)+pow(y,2)) - 0.48*x*y;
    return f;
} // -10, 10

int PopulationIndex=0;
bool stats_status=false;

population_t populate(int pop_size, int chrom_size);
double fitness(chromosome_t chromosome);
int selection_roulette(std::vector<double> fitnesses);
std::vector<chromosome_t> crossover_1p(std::vector<chromosome_t > parents);
chromosome_t mutation_singular(chromosome_t chrom, double p_mutation);
double translate(chromosome_t vector1);

double popAvg(population_t population);
double popMax(population_t population);
double popMin(population_t population);

void writeStats(population_t vector1);

std::ostream &operator<<(std::ostream &o, const chromosome_t chromosome) {
    for (const int p : chromosome) {
        o << p;
    }
    return o;
}
std::ostream &operator<<(std::ostream &o,
                         std::pair<population_t, fitness_f> pop) {
    for (const auto p : pop.first) {
        o << "{" << p << " " << (pop.second(p)) << "} ";
    }
    return o;
}

//generowanie ciągu znaków 0 i 1;
population_t populate(int pop_size, int chrom_size){
    srand(time(nullptr));
    population_t population;
    for(int i=0;i<pop_size;i++){
        chromosome_t chromosome;
        for(int j=0;j<chrom_size;j++){
            chromosome.push_back(rand()%2);
        }
        population.push_back(chromosome);
    }
    return population;
}

//"tłumaczenie" z ciągu znaków 0 i 1 na liczby dziesiętne
double translate(chromosome_t chromosome){
    using namespace std;
    double result=0;
    bool flagNegative = false;
    if(chromosome.at(0)==1)flagNegative=true;

    double twos=1;
    for(int i=2;i>=1;--i){
        result+=(chromosome.at(i)*twos);
        twos *= 2.0;
    }
    twos = 2;
    for (int i = 3; i < chromosome.size(); ++i) {
        result += (chromosome.at(i)/twos);
        twos *= 2.0;
    }

    if(flagNegative)result*=-1;
    return result;
}

//wyliczanie fitness funkcji, im blizej optimum, tym wyzszy wynik
double fitness(const chromosome_t chromosome){
    using namespace std;
    vector<double> translated;
    chromosome_t chrom_a, chrom_b;
    for (int i = 0; i < (chromosome.size()/2)-1; ++i) {
        chrom_a.push_back(chromosome.at(i));
    }
    for (int i=chromosome.size()/2;i<chromosome.size()-1;i++){
        chrom_b.push_back(chromosome.at(i));
    }
    double x = translate(chrom_a);
    double y = translate(chrom_b);
    double fit = 1/(Three_Hump_Camel_function(x,y));
    return fit;
}


int selection_roulette(std::vector<double> fitnesses) {
    int resultIndex;
    double sum=0;
    double tempsum = 0;

    for(int i=0;i<fitnesses.size();i++){
        sum+=fitnesses.at(i);
    }

    std::uniform_real_distribution<double> uniform(0.0, sum);
    double random = uniform(mt_generator);

    for(int i=0;i<fitnesses.size();i++) {
        tempsum+= fitnesses.at(i);
        if(tempsum>=random){
            resultIndex=i;
            break;
        }
    }
    return resultIndex;
}

//łączenie dwóch chromosomów w inne dwa poprzez krzyżowanie
std::vector<chromosome_t> crossover_1p(std::vector<chromosome_t > parents) {
    chromosome_t child1, child2;
    //1 dziecko, 1połowa pierwszego rodzica
    for(int i=0;i<parents.at(0).size()/2;i++){
        child1.push_back(parents.at(0).at(i));
    }
    //1 dziecko, 2 połowa drugiego rodzica
    for(int i=parents.at(0).size()/2;i<parents.at(0).size();i++){
        child1.push_back(parents.at(1).at(i));
    }
    //2 dziecko, 1 polowa drugiego rodzica
    for(int i=0;i<parents.at(0).size()/2;i++){
        child2.push_back(parents.at(1).at(i));
    }
    //2 dziecko, 2 polowa pierwszego rodzica
    for(int i=parents.at(0).size()/2;i<parents.at(0).size();i++){
        child2.push_back(parents.at(0).at(i));
    }
    return {child1,child2};
}

//mutowanie w sposób taki, iż w wypadku mutacji 1 zamieni się w 0, natomiast 0 zostanie 0
chromosome_t mutation_singular(chromosome_t chrom, double p_mutation) {
    std::uniform_real_distribution<double> uniform(0.0001, 1.0);
    chromosome_t afterMutations = chrom;
    for(int i=0;i<afterMutations.size();i++){
        if(p_mutation>=uniform(mt_generator)){
            afterMutations.at(i)=1-afterMutations.at(i);
        }
    }
    return afterMutations;
}

//uśrednione wyniki fitness dla populacji
double popAvg(population_t population){
    double result=0;
    for(chromosome_t chrom : population){
        result+=fitness(chrom);
    }
    result/=population.size();
    std::cout<<"Average of population: "<<result<<"\n";
    return result;
}

//minimalna wartość populacji
double popMin(population_t population) {
    double result= fitness(population.at(0));
    for(chromosome_t chrom : population){
        double temp = fitness(chrom);
        if(temp<result)result=temp;
    }
    std::cout<<"Minimum of population: "<<result<<"\n";
    return result;
}

//maksymalna wartość populacji
double popMax(population_t population) {
    double result= fitness(population.at(0));
    for(chromosome_t chrom : population){
        double temp = fitness(chrom);
        if(temp>result)result=temp;
    }
    std::cout<<"Maximum of population: "<<result<<"\n";
    return result;
}

//wypisanie popAvg, popMin, popMax
void writeStats(population_t vector1) {
    std::cout<<PopulationIndex<<std::endl;
    popAvg(vector1);
    popMin(vector1);
    popMax(vector1);
}

//cała zabawa genetyczna
population_t genetic_algorithm(population_t initial_population,
                               fitness_f fitness,
                               term_condition_f term_condition,
                               selection_f selection,
                               double p_crossover, crossover_f crossover,
                               double p_mutation, mutation_f mutation,
                               int iterator) {
    using namespace std;
    uniform_real_distribution<double> uniform(0.0, 1.0);

    auto population = initial_population;
    vector<double> population_fit(population.size());

    //wyliczanie fitnesow wszystkich osobnikow w populacji i przepisywanie do innego wektora
    transform(population.begin(), population.end(), population_fit.begin(),fitness);

    while (!term_condition(population, population_fit, iterator)) {
        if(stats_status) {
            writeStats(population);
        }
        vector<int> parents_indexes(population.size());
        population_t new_population(population.size());

        // selekcja rodzicow
        transform(population_fit.begin(), population_fit.end(),
                  parents_indexes.begin(),
                  [&](auto e) { return selection(population_fit); });

        // krzyzowanie
        for (int i = 0; i < parents_indexes.size() - 1; i += 2) {
            vector<chromosome_t> offspring = {population[parents_indexes[i]], population[parents_indexes[i + 1]]};

            if (uniform(mt_generator) < p_crossover) {
                offspring = crossover(offspring);
            }

            new_population[i] = offspring[0];
            new_population[i + 1] = offspring[1];
        }
        // mutacja
        for (auto &chromosome : new_population) {
            chromosome = mutation(chromosome, p_mutation);
        }

        population = new_population;
        std::transform(population.begin(), population.end(), population_fit.begin(),
                       fitness);
        PopulationIndex++;
    }
    return population;
}

int main() {
    using namespace std;
    int size = 100;
    int iteration = 1000;
    double p_crossover = 0.3;
    double p_mutation = 0.4;
    stats_status = true;

    population_t population = populate(size,112);
    population_t result = genetic_algorithm(
            population, fitness,
            [](auto a, auto b,int iteration) {
                static int i = 0;
                i++;
                return i > iteration;
            },
            selection_roulette, p_crossover, crossover_1p, p_mutation, mutation_singular, iteration);

    writeStats(result);
    return 0;
}
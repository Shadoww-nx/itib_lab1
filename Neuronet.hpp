#include <iostream>
#include <cmath>

using namespace std;

class Neuronet{
    public:
        Neuronet(int, double);
        string training_neuronet(bool, int, int);
        ~Neuronet();
    private:
        string training_neuronet_full(int);
        string training_neuronet_min(int);
        string boolean_function(int);
        void truth_table_create(int);
        unsigned long long fact(int);
        void combination(int**, int, int);
        unsigned int number_of_variables = 0;
        unsigned int number_of_lines = 0;
        int** truth_table = nullptr;
        int* Y = nullptr;
        double nu = 0;
};

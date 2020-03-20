#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Perceptron{
    public:
        Perceptron(double, unsigned int, int);
        bool test(int*, int, bool);
        void resetW();
        vector<double> getW();
    private:
        double net_summ(int*);
        void weight_correction(int*, double, int);
        void weight_logistic_correction(int*, double, int);
        double logistic_function(double);
        bool activation_function(double);
        double derivative(double);
        double nu = 0;
        vector<double> weigth;
        int activation_funtion_variant = 0;
};

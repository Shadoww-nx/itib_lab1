#include "Perceptron.hpp"

Perceptron::Perceptron(double nu_income, unsigned int number_of_variables, int activation_funtion_variant_input){
    nu = nu_income;
    activation_funtion_variant = activation_funtion_variant_input;
    for(int i = 0; i < number_of_variables + 1; ++i){
        weigth.push_back(0);
    }
}

void Perceptron::resetW(){
    for(int i = 0; i < weigth.size(); ++i){
        weigth[i] = 0;
    }
}

bool Perceptron::test(int* bool_vector, int Y, bool flag){
    double net = weigth[0];
    for(int i = 1; i < weigth.size(); ++i){
        net = net + weigth[i] * bool_vector[i - 1];
    }
    double out = net;

    if(activation_funtion_variant == 1)
        out = logistic_function(net);

    int sigma = Y - activation_function(out);

    if(sigma != 0 && flag == true){
        if(activation_funtion_variant == 1){
            weight_logistic_correction(bool_vector, net, sigma);
        }else{
            weight_correction(bool_vector, net, sigma);
        }
        return false;
    }else if(sigma != 0 && flag == false){
        return false;
    }
    return true;
}

void Perceptron::weight_correction(int* bool_vector, double net, int sigma){
    weigth[0] = weigth[0] + sigma * nu * 1;
    for(int i = 1; i < weigth.size(); ++i){
        weigth[i] = weigth[i] + sigma * nu * bool_vector[i - 1];
    }
}

void Perceptron::weight_logistic_correction(int* bool_vector, double net, int sigma){
    weigth[0] = weigth[0] + sigma * nu * 1 * logistic_function(net) * (1 - logistic_function(net));
    for(int i = 1; i < weigth.size(); ++i){
        weigth[i] = weigth[i] + sigma * nu * bool_vector[i - 1] * logistic_function(net) * (1 - logistic_function(net));
    }
}

bool Perceptron::activation_function(double out){
    double activation_threshold = 0;
    if(activation_funtion_variant == 1)
        activation_threshold = 0.5;

    if(out >= activation_threshold)
        return 1;
    return 0;
}

vector<double> Perceptron::getW(){
    return weigth;
}

double Perceptron::derivative(double net){
    double h = 0.0000001;
    return (logistic_function(net + h) - logistic_function(net - h)) / (2 * h);
}

double Perceptron::logistic_function(double net){
    return 1/(1 + exp(-net));
}


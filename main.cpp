#include "Perceptron.hpp"
#include "Neuronet.hpp"

int main(){
    int activation_function_variant = 1;
    int training_variant = 0;
    int boolean_function_variant = 0;

    string result;
    Neuronet nt(4, 0.3);
    cout<<nt.training_neuronet(training_variant, activation_function_variant, result, boolean_function_variant);

    return 0;
}

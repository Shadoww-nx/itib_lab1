#include "Perceptron.hpp"
#include "Neuronet.hpp"

int main(){
    int activation_function_variant = -1;
    int training_variant = -1;
    int boolean_function_variant = -1;
    Neuronet nt(4, 0.3);
    string result;
    string choice;

    cout<<"please select a Boolean function for training"<<endl;
    do{
        cout<<"if you want to train a training function, enter 0. if the option function is 1"<<endl;
        getline(cin, choice);
        if(choice != "0" && choice != "1"){
            cout<<"Error: invalid input"<<endl;
        }else{
            boolean_function_variant = atoi(choice.c_str());
        }
        cin.clear();
    }while(boolean_function_variant != 0 && boolean_function_variant != 1);

    cout<<"Plese enter activation function"<<endl;
    do{
        cout<<"if you need a threshold function, enter 0, if the logistics function is 1"<<endl;
        getline(cin, choice);
        if(choice != "0" && choice != "1"){
            cout<<"Error: invalid input"<<endl;
        }else{
            activation_function_variant = atoi(choice.c_str());
        }
        cin.clear();
    }while(activation_function_variant != 0 && activation_function_variant != 1);

    cout<<"please choose the training option"<<endl;
    do{
        cout<<"if you want to train a function on all vectors, enter 0. if you want to find the minimum number of vectors required for training, enter 1"<<endl;
        getline(cin, choice);
        if(choice != "0" && choice != "1"){
            cout<<"Error: invalid input"<<endl;
        }else{
            training_variant = atoi(choice.c_str());
        }
        cin.clear();
    }while(training_variant != 0 && training_variant != 1);

    result = nt.training_neuronet(training_variant, activation_function_variant, boolean_function_variant);
    cout<<result;

    return 0;
}

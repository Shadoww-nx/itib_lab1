#include "Neuronet.hpp"
#include "Perceptron.hpp"

Neuronet::Neuronet(int n, double nu_input){
    nu = nu_input;
    number_of_variables = n;
    number_of_lines = pow(2,n);
    truth_table = new int*[number_of_lines];

    for(int i = 0; i < number_of_lines; ++i){
        truth_table[i] = new int[number_of_variables];
    }

    for(int i = 0; i < number_of_lines; ++i){
        for(int j = 0; j < number_of_variables; ++j){
            truth_table[i][j] = 0;
         }
    }

    for(int i = 0; i < number_of_variables; ++i){
        truth_table_create(i);
    }
}

void Neuronet::truth_table_create(int variable){
    int step = pow(2,variable);
    for(int i = 0; i < number_of_lines;){
        i+=step;
        for(int j = 0; j < step; ++j,++i){
            truth_table[i][number_of_variables- variable - 1] = 1;
        }
    }
}

string Neuronet::boolean_function(int function_variant){
    string result = "Y = ( ";
    Y = new int[number_of_lines];
    for(int i = 0; i < number_of_lines; ++i){
        if(function_variant == 0)
            Y[i] = !(truth_table[i][0] & truth_table[i][1]) & truth_table[i][2] & truth_table[i][3];
        else if (function_variant == 1)
            Y[i] = (!truth_table[i][2] | truth_table[i][3]) & !truth_table[i][0] | truth_table[i][1];
        result = result + to_string(Y[i]) + " ";
    }
    result = result + ")" + '\n';
    return result;
}

string Neuronet::training_neuronet(bool full_or_min,int activation_funtion_variant, int function_variant){
    string result_bool = boolean_function(function_variant);
    if(full_or_min == 0)
        return result_bool + training_neuronet_full(activation_funtion_variant);
    else if(full_or_min == 1)
        return result_bool + training_neuronet_min(activation_funtion_variant);
}

string Neuronet::training_neuronet_min(int activation_funtion_variant){
    string current_result;
    string result;
    bool flag = false;
    unsigned int error_counts = 0;
    unsigned int current_epoh_number = 0;
    unsigned int Epoh_number = 10000000;
    unsigned int size = 0;
    Perceptron one(nu, number_of_variables, activation_funtion_variant);
    for(int k = 2; k < number_of_lines; ++k){
        size = fact(number_of_lines) / (fact(k) * (fact(number_of_lines - k)));
        int** combs = new int*[size];
        for(int i = 0; i < size; ++i){
            combs[i] = new int[k];
        }

        combination(combs, number_of_lines, k);
        for(int i = 0; i < size; ++i){
            error_counts = 0;
            current_epoh_number = 0;
            one.resetW();
            do{
                error_counts = 0;
                for(int j = 0; j < k; ++j){
                    if(one.test(truth_table[combs[i][j]], Y[combs[i][j]],true) == false)
                        error_counts++;
                }

                current_result = current_result + "Epoh Number: " + to_string(current_epoh_number) + ";" + "count error:" + to_string(error_counts) + " Vector Weigth: " + " W = ( ";
                vector<double> weigth = one.getW();
                for(int i = 0; i < weigth.size(); ++i){
                    current_result = current_result + to_string(weigth[i]) + " ";
                }
                current_result = current_result + ")" + '\n';
                ++current_epoh_number;
            }while(error_counts > 0);

            for(int j = 0; j < number_of_lines; ++j){
                if(one.test(truth_table[j], Y[j], false) == false)
                    error_counts++;
            }

            if(error_counts == 0 && Epoh_number > current_epoh_number){
                flag = true;
                Epoh_number = current_epoh_number;
                result = current_result;
                for(int j = 0; j < k; ++j){
                    result = result + "bool vector number: " + to_string(combs[i][j]) + " vector:";
                    for(int z = 0; z < number_of_variables; ++z){
                        result = result + to_string(truth_table[combs[i][j]][z]);
                    }
                    result = result + '\n';
                }
            }else{
                current_result.clear();
            }
        }
        for(int i = 0; i < size; ++i){
            delete[] combs[i];
        }
        delete[] combs;

        if(flag == true){
            break;
        }
    }
    return result;
}

string Neuronet::training_neuronet_full(int activation_funtion_variant){
    string result;
    unsigned int error_counts = 0;
    unsigned int Epoh_number = 0;
    Perceptron one(nu, number_of_variables, activation_funtion_variant);
    do{
        error_counts = 0;
        result = result + "Real Y = ( ";
        for(int i = 0; i < number_of_lines; ++i){
            if(one.test(truth_table[i],Y[i],true) == false){
                error_counts++;
                result = result + to_string(!Y[i]) + " ";
            }else{
                result = result + to_string(Y[i]) + " ";
            }
        }
        result = result + ")" + '\n';
        result = result + "Epoh Number: " + to_string(Epoh_number) + ";" + " Count_error: " + to_string(error_counts) + "; Vector Weigth: W = ( ";
        vector<double> weigth = one.getW();
        for(int i = 0; i < weigth.size(); ++i){
            result = result + to_string(weigth[i]) + " ";
        }
        result = result + ")" + '\n';
        ++Epoh_number;
    }while(error_counts > 0);
    return result;
}

unsigned long long Neuronet::fact(int n){
    unsigned long long result = 1;
    for(int i = 1; i < n + 1; ++i){
        result *= i;
    }
    return result;
}

void Neuronet::combination(int** arr, int n, int k){
    int *arr1 = new int[k];
    for(int i = 0; i < k; ++i){
        arr1[i] = i;
    }

    int size = fact(n) / (fact(k) * (fact(n - k)));


    for(int i = 0; i < size; ++i){
        for(int j = 0; j < k; ++j){
            arr[i][j] = arr1[j];
        }

        int count = 1;
        for(int z = 0; z < k; ++z){
            if(arr1[k - z - 1] >= n - z - 1){
                ++count;
            }
        }

        if(count  == 1){
            ++arr1[k - count];
        }else if(count <= k){
            for(int z = k - count; z < k; ++z){
                ++arr1[z];
                if(z + 1 < k)
                    arr1[z + 1] = arr1[z];
            }
        }
    }
    delete[] arr1;
}

Neuronet::~Neuronet(){
    if(truth_table != nullptr){
        for(int i = 0; i < number_of_lines; ++i)
            delete[] truth_table[i];
        delete[] truth_table;
    }
    if(Y != nullptr){
        delete[] Y;
    }
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
void getNumbers(T (&numbers)){
    cout << "Inserisci numeri da stampare uno di seguito all'altro o scrivi stop per terminare l'inserimento" << endl;
    while (true){
        string userInput;
        cin >> userInput;
        if (userInput == "stop"){
            break;
        }else{
            //Inserisco in numbers i numeri inseriti
            numbers.push_back(stoi(userInput));
        }
    }
}

int main() {
    vector<int> numbers;
    getNumbers(numbers);

    for (const auto &item : numbers){
        cout << item;
    }

    return 0;
}

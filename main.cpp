#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;


/**
 * Ottieni in input una serie di numeri dall'utente
 *
 * @param numbers puntatore a un vettore di tipo int contenente i numeri
 */
void getNumbers(vector<int> *numbers) {
    cout << "Inserisci numeri da stampare uno di seguito all'altro o scrivi stop per terminare l'inserimento" << endl;
    while (true) {
        string userInput;
        cin >> userInput;
        if (userInput == "stop") {
            break;
        } else {
            try {
                int userNumber = stoi(userInput);
                //Inserisco in numbers i numeri inseriti
                numbers->push_back(userNumber);
            } catch (...) {
                continue;
            }
        }
    }
}

/**
 * Inverte il contenuto di due puntatori
 */
void swapIntPointers(int *n1, int *n2) {
    int t = *n1;
    *n1 = *n2;
    *n2 = t;
}

/**
 * Prende l'elemento a endIndex come pivot e riposiziona i valori nel vettore rispetto ad esso
 *
 * @param numbers Puntatore al vettore contenente i numeri da ordinare
 * @param startIndex Da dove iniziare a controllare i valori
 * @param endIndex Dove arrivare a controllare i valori (il valore a questo indice verrà usato come pivot)
 * @return Nuovo indice del pivot
 */
int pivotSort(vector<int> *numbers, int startIndex, int endIndex) {
    //Prendo il valore del pivot dall'elemento situato a endIndex
    int pivot = numbers->at(endIndex);

    int pivotIndex = startIndex;

    //Itero fra tutti gli elementi apparte l'ultimo elemento per evitare il pivot alla prima iterazione
    for (int i = startIndex; i < endIndex; i++) {
        if (numbers->at(i) <= pivot) {
            swapIntPointers(&numbers->at(i), &numbers->at(pivotIndex));
            pivotIndex++;
        }
    }

    //Posiziono anche il valore all'ultimo posto saltato in precedenza
    swapIntPointers(&numbers->at(pivotIndex), &numbers->at(endIndex));
    return pivotIndex;
}

/**
 * Ordina un vettore contenente dei numeri attraverso il quicksort
 *
 * @param numbers Puntatore al vettore contenente i numeri da ordinare
 */
void quickSortWithoutRecursion(vector<int> *numbers) {
    //Ignoro se c'è un solo elemento o è vuoto
    if(numbers->size() <= 1){
        return;
    }

    //Stack contentenente la pair di valori di inzio e di fine fra cui effettuare il pivotSort
    stack<pair<int, int>> indexToOrder;

    int startIndex = 0;
    int endIndex = (int) numbers->size() - 1;

    indexToOrder.push(make_pair(startIndex, endIndex));

    while (!indexToOrder.empty()) {
        startIndex = indexToOrder.top().first;
        endIndex = indexToOrder.top().second;

        //Rimuovo pair dallo stack
        indexToOrder.pop();

        //Posiziono il pivotIndex
        int pivotIndex = pivotSort(numbers, startIndex, endIndex);

        if (pivotIndex - 1 > startIndex) {
            indexToOrder.push(make_pair(startIndex, pivotIndex - 1));
        }

        if (pivotIndex + 1 < endIndex) {
            indexToOrder.push(make_pair(pivotIndex + 1, endIndex));
        }
    }
}

int main() {
    vector<int> numbers;
    //User input
    getNumbers(&numbers);

    //Ordino
    //0 perché è l'inzio e si vuole oridnare la totalità del vettore numbers.size()-1 perché è la fine del vettore
    quickSortWithoutRecursion(&numbers);

    //Stampo
    for (const auto &item: numbers) {
        cout << item << endl;
    }
    system("PAUSE");
    return 0;
}

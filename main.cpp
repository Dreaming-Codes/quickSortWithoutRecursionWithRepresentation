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
uint32_t pivotSort(vector<int> *numbers, uint32_t startIndex, uint32_t endIndex) {
    //Prendo il valore del pivot dall'elemento situato a endIndex
    int pivot = numbers->at(endIndex);

    //ancora non è l'indice del pivot ma a fine iterazioni i = startIndex; i < endIndex; i++ lo sarà
    uint32_t pivotIndex = startIndex;

    //Itero fra tutti gli elementi apparte l'ultimo elemento per evitare il pivot alla prima iterazione
    for (uint32_t i = startIndex; i < endIndex; i++) {
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
    //Stack contentenente la pair di valori di inzio e di fine fra cui effettuare il pivotSort
    stack<pair<uint32_t, uint32_t>> indexToOrder;

    uint32_t startIndex = 0;
    uint32_t endIndex = numbers->size() - 1;

    indexToOrder.push(make_pair(startIndex, endIndex));

    //Finche lo stack non è vuoto continuo a iterare fra gli indici contenuti nelle pair nello stack
    while (!indexToOrder.empty()) {
        startIndex = indexToOrder.top().first;
        endIndex = indexToOrder.top().second;

        //Rimuovo pair dallo stack
        indexToOrder.pop();

        //Posiziono il pivotIndex
        uint32_t pivotIndex = pivotSort(numbers, startIndex, endIndex);

        //Inserisco i valori minori del pivot attuale nello stack (-1 viene fatto per non considerare l'attuale pivot)
        if (pivotIndex - 1 > startIndex) {
            indexToOrder.push(make_pair(startIndex, pivotIndex - 1));
        }

        //Inserisco i valori maggiari del pivot attuale nello stack (+1 viene fatto per non considerare l'attuale pivot)
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
    quickSortWithoutRecursion(&numbers);

    //Stampo
    for (const auto &item: numbers) {
        cout << item << endl;
    }
    return 0;
}

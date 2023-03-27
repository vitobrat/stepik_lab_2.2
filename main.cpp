#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

struct List{
    int data;
    List *next;
    List *prev;
};

int checkInput(){
    int input;
    try {
        cin >> input;
        if (cin.fail()) {
            throw 1;
        }
    } catch (int exeption) {
        cout << "ERROR!!!";
        exit(0);
    }
    cin.sync();
    cout << "\n";
    return input;
}

void getLine(string &stringLine){
    getline(cin, stringLine);
}

void printList(List * cur){
    cout << "List: ";
    while(cur){
        cout << cur->data << " ";
        cur = cur->next;
    }
}

List *createList(unsigned N){
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *head = nullptr, *tail = nullptr;
    srand(time(NULL));
    for (int i = 0; i < N; i++){
        head = new List;
        head->data = rand() % 100;
        head->next = tail;
        if(tail){
            tail->prev = head;
        }
        tail = head;
    }
    if(N != 0) head->prev = nullptr;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "time spent to creat list in nanoseconds: " << end - start << "ns\n";
    return head;
}

List *createList(string str, int &N){
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *head = nullptr, *tail = nullptr;
    istringstream iss(str);
    int num, count = 0;
    while (iss >> num) {
        head = new List;
        head->data = num;
        head->prev = tail;
        if(tail){
            tail->next = head;
        }
        tail = head;
        count++;
    }
    N = count;
    if(N>0) {
        head->next = nullptr;
        while (head->prev) {
            head = head->prev;
        }
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "time spent to creat list in nanoseconds: " << end - start << "ns\n";

        return head;
    }else{
        return nullptr;
    }
}

List *listItem(List * Beg, unsigned int index) {
    int p = 0;
    while(p != index){
        Beg = Beg->next;
        p++;
    }
    return Beg;
}

void addValueAtList(List * &listOfValue, int N){
    cout << "Input new value: ";
    int value = checkInput();
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *item = listItem(listOfValue, N - 1);
    List *addItem = new List;
    addItem->data = value;
    item->next = addItem;
    addItem->prev = item;
    addItem->next = nullptr;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "time spent to add element in list in nanoseconds: " << end - start << "ns\n";
}

void changeValueAtList(List * &listOfValue, int N){
    cout << "Input 2 indexes you wanna change(by enter):";
    int index1 = checkInput();
    int index2 = checkInput();
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (!((index1 >= 1 && index1 <= N) && (index2 >= 1 && index2 <= N))){
        cout << "Wrong input! Try again.\n";
        return;
    }
    if(index1 == index2) return;
    index1--; index2--;
    if(index1 > index2){
        swap(index1, index2);
    }
    List *item1 = listItem(listOfValue, index1);
    List *item2 = listItem(listOfValue, index2);


    if (item1->prev != nullptr) {
        item1->prev->next = item2;
    }else{
        listOfValue = item2;
    }
    if (item1->next != item2) {
        item1->next->prev = item2;
    }
    if (item2->prev != item1) {
        item2->prev->next = item1;
    }
    if (item2->next != nullptr) {
        item2->next->prev = item1;
    }
    if(item1->next == item2){
        item2->prev = item1->prev;
        item1->prev = item2;
        item1->next = item2->next;
        item2->next = item1;
        return;
    }
    List *help = item1->prev;
    item1->prev = item2->prev;
    item2->prev = help;
    help = item1->next;
    item1->next = item2->next;
    item2->next = help;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "time spent to change elements in list in nanoseconds: " << end - start << "ns\n";
}

void getValueAtList(List * &listOfValue, int N){
    cout << "What type do you want to get element\n"<<
    "1)by value\n"
    "2)by index\n";
    int type, value, index, count = 0;
    bool flag = false;
    List *cur = listOfValue;
    type = checkInput();
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    switch (type) {
        case 1:
            cout << "Input value:";
            value = checkInput();
            start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            while(cur){
                if(cur->data == value){
                    flag = true;
                    index = count;
                    break;
                }
                cur = cur->next;
                count++;
            }
            if(flag){
                cout << "The list contain an element - " << value << "(index - " << index+1 << ")" << "\n";
            }else{
                cout << "The list does not contain an element - " << value << "\n";
            }
            end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            cout << "time spent to get element by value in list in nanoseconds: " << end - start << "ns\n";
            break;
        case 2:
            cout << "Input index:";
            index = checkInput();
            while (!(index >= 1 && index <= N)){
                cout << "Wrong input! Try again.\n";
                index = checkInput();
            }
            start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            cur = listItem(listOfValue, index - 1);
            cout << "Value with index "<< index << " - " << cur->data << "\n";
            end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            cout << "time spent to get element by index in list in nanoseconds: " << end - start << "ns\n";
            break;
        default:
            cout << "Wrong input! Try again.\n";
            getValueAtList(listOfValue, N);
            break;
    }
}

void deleteValueAtList(List * &listOfValue, int &N){
    cout << "What type do you want to delete element\n"<<
         "1)by value\n"
         "2)by index\n";
    int type, value, index, count = 0;
    List *cur = listOfValue;
    type = checkInput();
    switch (type) {
        case 1:
            cout << "Input value:";
            value = checkInput();
            break;
        case 2:
            cout << "Input index:";
            index = checkInput();
            while(cur){
                if(count == index - 1){
                    value = cur->data;
                    break;
                }
                cur = cur->next;
                count++;
            }
            break;
        default:
            cout << "Wrong input! Try again.\n";
            deleteValueAtList(listOfValue, N);
            break;
    }
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cur = listOfValue;
    bool flag = false;
    while(cur){
        if (cur->data == value){
            if (cur->prev == nullptr){
                listOfValue = cur->next;
                if(cur->next != nullptr)cur->next->prev = nullptr;
                delete cur;
                flag = true;
                cur = listOfValue;
            }else if(cur->next == nullptr){
                if(cur->prev != nullptr) cur->prev->next = nullptr;
                delete cur;
            }else{
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                delete cur;
            }
            break;
        }
        else{
            cur = cur->next;
        }
    }
    if(!flag){
        return;
    }
    N--;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "time spent to delete element in list in nanoseconds: " << end - start << "ns\n";
}

void function1(List * &listOfValue, int &N){
    cout << "Which type of input do you prefer(1 - random, 2 - ourselves): ";
    int inputType = checkInput();
    int sizeList;
    string stringList;
    if(inputType == 1){
        cout << "Input size: \n";
        sizeList = checkInput();
        if (sizeList <= 0){
            cout << "Wrong input! Try again.\n";
            function1(listOfValue, N);
        }
        listOfValue = createList(sizeList);
        N = sizeList;
    }else if(inputType == 2){
        cout << "Input list: \n";
        getLine(stringList);
        listOfValue = createList(stringList, N);
    }else{
        cout << "Wrong input! Try again.\n";
        function1(listOfValue, N);
    }

}

void function2(List * &listOfValue, int &N){
    cout << "List size - " << N <<"\n";
    cout << "Which operation do you want to do?\n";
    int inputType = 0;
    if(N>0){
        cout << "1) Add value\n" <<
        "2) Change elements\n" <<
        "3) Get element\n" <<
        "4) Delete value\n";
        inputType = checkInput();

    }else{
        cout <<
        "1) Add value\n" <<
        "2) Change elements\n" <<
        "3) Get element\n";
        inputType = checkInput();
    }
    switch (inputType) {
        case 1:
            addValueAtList(listOfValue,N);
            N++;
            break;
        case 2:
            changeValueAtList(listOfValue, N);
            break;
        case 3:
            getValueAtList(listOfValue, N);
            break;
        case 4:
            deleteValueAtList(listOfValue,N);
            break;
        default:
            cout << "Wrong input! Try again.\n";
            function2(listOfValue, N);
    }
}

int main() {
    int inputCycle = 1, N = 0;
    List *listOfValue = nullptr;
    while (inputCycle){
        function1(listOfValue, N);
        while (listOfValue == nullptr){
            cout << "The list is empty, creat new\n";
            function1(listOfValue, N);
        }
        printList(listOfValue);
        cout << "\nDo you want to try again? (0 - no, 1 - yes): ";
        inputCycle = checkInput();
    }
    inputCycle = 1;
    while (inputCycle){
        while (listOfValue == nullptr){
            cout << "The list is empty\n";
            function1(listOfValue, N);
        }
        function2(listOfValue, N);
        printList(listOfValue);
        cout << "\nDo you want to try again? (0 - no, 1 - yes): ";
        inputCycle = checkInput();
    }
    return 0;
}

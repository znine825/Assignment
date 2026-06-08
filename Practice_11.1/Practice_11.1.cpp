#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "DLL.h"
#include "DLL_Queue.h"

using namespace std;
#define NUM_DATA 10

int main() {
  
    DLL_Queue<string> DLL_Queue_Str("DLL_Queue_String");

    string strArray[NUM_DATA] = { "one", "two", "three", "four", "five",
                                  "six", "seven", "eight", "nine", "ten" };
    string* pE;

 
    cout << "Initial status (before enQueues :: " << DLL_Queue_Str << endl;

 
    for (int round = 0; round < 3; round++) {

 
        for (int i = 0; i < NUM_DATA; i++) {
            DLL_Queue_Str.enQueue(&strArray[i]);
            cout << "After enQueue(" << setw(6) << strArray[i] << ") : ";
            cout << DLL_Queue_Str;
        }
 
        for (int i = 0; i < NUM_DATA; i++) {
            pE = DLL_Queue_Str.deQueue();
            if (pE != NULL) {
                cout << "After deQueue(" << setw(6) << *pE << ") : ";
                cout << DLL_Queue_Str;
            }
        }
        cout << endl;  
    }

    return 0;
}
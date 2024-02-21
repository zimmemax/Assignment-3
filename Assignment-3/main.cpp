/*
Skeleton code for linear hash indexing
*/

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"
using namespace std;


int main(int argc, char* const argv[]) {

    // Create the index
    LinearHashIndex emp_index("EmployeeIndex");
    emp_index.createFromFile("Employee.csv");
    //emp_index.createFromFile("Employee.csv");
    
    // Loop to lookup IDs until user is ready to quit
    int user_input;
    int choice = 1;
    while(choice){
        
        cout << "ID input: ";
        cin >> user_input;
        cin.clear();
        try {
            Record r = emp_index.findRecordById(user_input);
            r.print();

        }
        catch(exception& e){
            cout << "Not found...\n";
        }


        cout << "Continue? (1 for yes, 0 for no): ";
        cin >> choice;
        

    }

    
    

    return 0;
}

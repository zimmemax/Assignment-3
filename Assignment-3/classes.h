#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <cassert>
#include<cmath>
using namespace std;

class Record {
public:
    int id, manager_id;
    std::string bio, name;

    Record(vector<std::string> fields) {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print() {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};


class LinearHashIndex {

private:
    const int BLOCK_SIZE = 4096;

    vector<int> blockDirectory; // Map the least-significant-bits of h(id) to a bucket location in EmployeeIndex (e.g., the jth bucket)
                                // can scan to correct bucket using j*BLOCK_SIZE as offset (using seek function)
								// can initialize to a size of 256 (assume that we will never have more than 256 regular (i.e., non-overflow) buckets)
    int n;  // The number of indexes in blockDirectory currently being used
    int i;	// The number of least-significant-bits of h(id) to check. Will need to increase i once n > 2^i
    int numRecords;    // Records currently in index. Used to test whether to increase n
    int nextFreeBlock; // Next place to write a bucket. Should increment it by BLOCK_SIZE whenever a bucket is written to EmployeeIndex
    string fName;      // Name of index file

    // Insert new record into index
    void insertRecord(Record record) {

        // No records written to index yet
        if (numRecords == 0) {
            // Initialize index with first blocks (start with 4)


        }

        // Add record to the index in the correct block, creating a overflow block if necessary


        // Take neccessary steps if capacity is reached:
		// increase n; increase i (if necessary); place records in the new bucket that may have been originally misplaced due to a bit flip


    }

public:

string decimalToBinary(int num, int i) {
    string binary;
    
    while (num > 0) {
        binary = std::to_string(num % 2) + binary;
        num /= 2;
    }
    
    while (binary.length() < i) {
        binary = "0" + binary;
    }
    
    return binary.substr(binary.length() - i);
}

//sexy lil helper functions

string bit_flip(string bit_string){
    bit_string[0] = '0';
    return bit_string;

}

bool need_bit_flip(string num, int n){
    if(binary_to_decimal(num) >= n){
        return true;
    }
    return false;

}

int binary_to_decimal(string bit_string){
    int num = 0;

    for(int j=0; j < bit_string.length(); j++){
        if(bit_string[j]=='1'){
            num+=pow(2, j);
        }
    }
    return num;

}

    public:
    string fname;
    LinearHashIndex(string indexFileName) {
        n = 4; // Start with 4 buckets in index
        i = 2; // Need 2 bits to address 4 buckets
        numRecords = 0;
        nextFreeBlock = 0;
        fName = indexFileName;
        // Create your EmployeeIndex file and write out the initial 4 buckets
        // make sure to account for the created buckets by incrementing nextFreeBlock appropriately
        ofstream fout(fName);

        for(int j = 0; j < 4; j++){
            fout << decimalToBinary(j, i) << endl;
        }
       
        fout.close();

      
    }

    int h(int id){
        return id%216;
    }

    // Read csv file and add records to the index
    void createFromFile(string csvFName) {

        ifstream fin(csvFName);
        


        string id;
        string manager_id;
        string bio;
        string name;

        

        string line;

        int record_counter = 0;

        string page; 
/*
        string test = "1111111";
        cout << binary_to_decimal(test) << endl;
        cout << need_bit_flip(test, n) << endl;
        cout << bit_flip(test) << endl;
        cout << binary_to_decimal(bit_flip(test)) << endl;
*/
        
        int line_num = 0;
        while (getline(fin, line)){ 

            if(n > pow(2,i)){
                i++;
            }

            assert (page.size() <= BLOCK_SIZE);

            istringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, bio, ',');
            getline(ss, manager_id);
        
            
            
            
            vector<std::string> field;
        
            string record = id + "$" + name + "$" + bio + "$" + manager_id + "$" ;
            int hash = h(stoi(id));
            cout << "Hash: " << hash << endl;
            string bit_location = decimalToBinary(hash, i);
            if(need_bit_flip(bit_location, n)){
                bit_location = bit_flip(bit_location);
            }
            insert_record(id, bit_location, line_num);
            n++;
            line_num++;
            cout << bit_location << endl;

        }


        
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
    }

    void insert_record(string record_id, string bit_location, int offset){
       
       string line;
    ifstream inFile(fName);
    ofstream ofile(fName);



       

        while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string key;
        std::getline(iss, key, '$'); // Assuming the first field is the search key

        if (key == bit_location) {
            ofile << line << "$" << record_id << "$" << to_string(offset);
        } 
    }
        

    }
};

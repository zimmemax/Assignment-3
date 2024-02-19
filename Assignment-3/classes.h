#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <cassert>
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

    string decToBinary(int num,  int sig_bits, int num_buckets) 
    { 
        int max_value = (1 << sig_bits) - 1;

    num %= (num_buckets);

     string binary = "";
      while (num > 0) {
         binary = (num % 2 == 0 ? "0" : "1") + binary;
         num /= 2;
    }

    while (binary.length() < sig_bits) {
        binary = "0" + binary;
    }

    return binary.substr(binary.length() - sig_bits);

    } 
    LinearHashIndex(string indexFileName) {
        n = 4; // Start with 4 buckets in index
        i = 2; // Need 2 bits to address 4 buckets
        numRecords = 0;
        nextFreeBlock = 0;
        fName = indexFileName;
        // Create your EmployeeIndex file and write out the initial 4 buckets
        // make sure to account for the created buckets by incrementing nextFreeBlock appropriately
        ofstream fout(fName);
        for(int j = 0; j < (i*i); j++){
            fout<<decToBinary(j, i, n)<< "$"<<'\n';
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
        
        
        while (getline(fin, line)){ 

            assert (page.size() <= BLOCK_SIZE);

            istringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, bio, ',');
            getline(ss, manager_id);
        
            
            
            
            vector<std::string> field;
        
            string record = id + "$" + name + "$" + bio + "$" + manager_id + "$" ;
            int hash = h(stoi(id));
            string bit_location = decToBinary(hash, i , n);
            cout << bit_location << endl;

        }


        
    }

    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        
    }
};

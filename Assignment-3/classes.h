#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <cassert>
#include <cmath>
using namespace std;

class Record {
public:
    int id, manager_id;
    string bio, name;

    Record(vector<string> fields) {
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

    int recordPageTracker[216];
    int storageFill;
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

// num is number [0,255], i is number of bits to consider
string decimalToBinary(int num, int i) {
    string binary;
    
    while (num > 0) {  // add the all bits to the string binary
        binary = std::to_string(num % 2) + binary;
        num /= 2;
    }
    
    while (binary.length() < i) { //add 0s to the front in the case num has less bits than i's size, ex: num = 1 and i = 10, should return 0000000001
        binary = "0" + binary;
    }
    
    return binary.substr(binary.length() - i); 
}

//sexy lil helper functions

string bit_flip(string bit_string){ //flips the first bit of the string
    if (bit_string[0] = '0')
        bit_string[0] = '1';
    else
        bit_string[0] = '0';

    return bit_string;

}

bool need_bit_flip(string num, int n){ //
    if(binary_to_decimal(num) >= n){
        return true;
    }
    return false;

}

int binary_to_decimal(string bit_string){
    int num = 0;

    for(int j= bit_string.length()-1; j == 0; j--){
        if(bit_string[j]=='1'){
            num+=pow(2, j);
            cout << "Num: " << num << endl;
        }
    }
    return num;

}

int binaryToDecimal(const std::string& binary) {
    int decimal = 0;
    int exponent = 0;
    
    // Iterate over the binary string from right to left
    for (int i = binary.length() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            // If the current bit is '1', add 2^exponent to the decimal value
            decimal += pow(2, exponent);
        }
        // Increment the exponent for the next bit
        exponent++;
    }
    
    return decimal;
}


    public:
    string fname;
    string indexFileName;
    LinearHashIndex(string indexFileName) {
        n = 4; // Start with 4 buckets in index
        i = 2; // Need 2 bits to address 4 buckets
        numRecords = 0;
        nextFreeBlock = 0;
        fName = indexFileName;
        indexFileName = indexFileName;
        // Create your EmployeeIndex file and write out the initial 4 buckets
        // make sure to account for the created buckets by incrementing nextFreeBlock appropriately
        ofstream fout(fName);


        for(int j = 0; j < 4; j++){
            fout << decimalToBinary(j, i);
            for(int x = 0; x<16*20;x++){
                fout<<" ";
            }
        }
       
        fout.close();
      
    }

    void createFromFile(string csvFName) {
        master(csvFName);
    }

    int h(int id){
        return id%216;
    }


    //rehashes every page considering the new i value, must also rewrite the recordPageTracker array
    void reformatPages(int n){
        
        fstream fout("tmp.txt");
        for(int j =0; j < n; j++){
            string bit_string = decimalToBinary(j, i);
            //write bit string to file
            for(int q = 0; q< 16*20; q++){
                //write<<" "
            }
        }



        return;

    }

    void master(string csvFname){
        //calculate i and n
        //if chnage to n/i
        //call create index
        int lines_in_csv = 0;
        int lines_written = 0;
        fstream file(csvFname);

        string line;
        while (std::getline(file, line)) {
        
            lines_in_csv+=1;
        }

        while(true){
            
            lines_written = create_index(csvFname);
            if(lines_written < lines_in_csv){
                n++;
                //cout << "num buckets: " << n << endl;
                //cout << "lines written: " << lines_written << endl;
            }
            else{

                //cout << "num buckets: " << n << endl;
                //cout << "lines written: " << lines_written << endl;
            
                
                return;
            }
            
            
        }
    }

    int create_index(string csvFName){
        
        remove("EmployeeIndex");
        ofstream file("EmployeeIndex");

        for(int j = 0; j < 20*16*n; j++){
            file.put(' ');
        }

        int lines_written = 0;
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

        for (int i = 0; i < 216; i++){
            recordPageTracker[i] = 0;
        }

        int average_amount_array[216];
        for(int x = 0; x<216;x++){
            average_amount_array[x]=0;
        }
        float average_fill = 0.0;

        while (getline(fin, line)){ //reads the entirety of the csv 

            if(n > pow(2,i)){
                    i++;
                }

            if(average_fill > 0.7){ //i should only increase when average number of fill reaches above 70 %
                return lines_written; 
            }

            assert (page.size() <= BLOCK_SIZE);

            istringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, bio, ',');
            getline(ss, manager_id);
        
            
            
            
            vector<string> field;
        
            string record = id + "$" + name + "$" + bio + "$" + manager_id + "$" ;
            int hash = h(stoi(id)); // hash is an integer [0, 255]


            //cout << "Hash: " << hash << endl;

            string bit_location = decimalToBinary(hash, i); // ex: 010 
            //cout << "Bit Location: " << bit_location << endl;
            
            
            


            
            if(need_bit_flip(bit_location, n)){ //not quite sure abt the criteria on this one
                bit_location = bit_flip(bit_location);
                //cout << "Flipped " << endl;
            }

            //cout << "After flip: " << bit_location << endl;

            //cout << "bit location" << bit_location << endl;
            int whereToStore = 20 * 16 * binaryToDecimal(bit_location) + (16 * recordPageTracker[binaryToDecimal(bit_location)]); //20 is the number of entries possible in a bucket, 16 is the size of each record on the page, 
            string offset = decimalToBinary(line_num, 8);

            //cout << "Where to store: " << whereToStore << endl;
            //cout << "Offset: " << offset << endl;


            insert_record(id, whereToStore, offset); //each page is a bucket >:)

            recordPageTracker[binaryToDecimal(bit_location)]++; // this array will tell us where we've placed every single record. We can see if pages are full, i.e. recordpagetracker[i] > 5. We can also use it to track offset.
            

           
            numRecords++;
            
            
            //cout << "Num Records: " << numRecords << endl;
            int bit_location_to_int = binaryToDecimal(bit_location);
            average_amount_array[bit_location_to_int] +=1;

            for(int x =0; x<216;x++){
                average_fill += average_amount_array[x];
            }
            average_fill = average_fill/(n * 5);
            //cout << "Average fill: " << average_fill << endl;


           
            line_num++;
            lines_written++;
            

        }
       
       return lines_written;
    }



    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        

        string bit_String = decimalToBinary(h(id), i);
        int line_Num_In_Csv;
        
        ifstream index_File("EmployeeIndex");
        ifstream csv_File("Employee.csv");
        char comparator [17];
        char tmp1[8];
        char tmp2[8];


        int where_To_Find = 20 * 16 * binaryToDecimal(bit_String); //20 is the number of entries possible in a bucket, 16 is the size of each record on the page, 
        index_File.seekg(where_To_Find);
        for (int z = 0; z < 20*16; z+=16){

            index_File.read(comparator, 16);
            
            

            string str(comparator);

            string firstEightChars = str.substr(0, 8);
            string lastChars = str.substr(8, 16);

            firstEightChars.resize(8);
            lastChars.resize(8);


            //cout << firstEightChars << endl;
            //cout << lastChars << endl;
            
            if(stoi(firstEightChars) == id){
                //seek to line num based on last 8 chars
                
                int line_num = binaryToDecimal(lastChars);
                //cout << "Line num" << line_num << endl;

                string id;
                string manager_id;
                string bio;
                string name;

                string line;

                int line_counter = 0;
                while (std::getline(csv_File, line))
                {
                    if (line_counter == line_num){
                        istringstream ss(line);
                        getline(ss, id, ',');
                        getline(ss, name, ',');
                        getline(ss, bio, ',');
                        getline(ss, manager_id);
                        vector<string> field;
                        field.push_back(id);
                        field.push_back(name);
                        field.push_back(bio);
                        field.push_back(manager_id);
                        Record r(field);
                        return r;
                    }
                    line_counter+=1;
                    
                }
            }



        }
        
   
        vector <string> fields;
        fields[0] = '0';
        Record r(fields);
        return r;
    }




    void insert_record(string record_id, int whereToStore, string offset){
       
        fstream file("EmployeeIndex", std::ios::binary | std::ios::in | std::ios::out);

        file.seekp(whereToStore);


        string str = record_id + offset;

        for (int i = 0; i < 16; i++){
            file.put(str[i]);
        }
        
        file.close();
    }
};

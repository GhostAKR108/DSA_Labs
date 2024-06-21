#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    long long key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(long long k, const PhoneRecord* rec)
        : key(k), element(nullptr), next(nullptr) {
            element = new PhoneRecord(*rec);
        }

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};
//computing power
long long power(int base, int exponent) {
    long long result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}
//checking if string is substring of another string
bool checkstring(string s1, string s2){
    bool present=false;
    int a = s1.length();
    int b = s2.length();
    int i,j;
    int count=0;
    for(i=0;i<=a-b;i++){
        for(j=0;j<b;j++){
            if(s1[i+j]==s2[j]){
                count++;
            }
            else{
                count=0;
                break;
            }
        }
        if(count==b){
            present = true;
            break;
        }
    }
    return present;
}

//computing key
long long computeKey(const string& str){
    string s1 = str;
    long long key = 0;
    for(int i=0;i<s1.length();i++){
        key+=(s1[i]*power(263,i))%1000000007;
    }
    return key;
}
class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }
    // Add your own implementation for hashing
    long long computeHash(const string& str){
        string s1 = str;  
        long long key=0;
        long long h=0;
        for(int i=0;i<s1.length();i++){
            key+=(s1[i]*power(263,i))%1000000007;
        }
        h = key%263;
        return h;
    };

    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord* record){
        long long key;
        long long h;
        string str = record->getName();
        istringstream iss(str);
        string word;
        while (iss >> word) {
            key = computeKey(word);
            HashTableRecord* newNode = new HashTableRecord(key,record);
            h = computeHash(word);
            if(hashTable[h]==nullptr){
                hashTable[h] = newNode;
            }
            else{
                HashTableRecord *current = hashTable[h];
                while (current->getNext()!=nullptr)
                {
                    current = current->getNext();
                }
                current->setNext(newNode);
            }
        }
    };

    // Add your own implementation for deleting a contact
    bool deleteContact(const string *searchName)
    {
        string s = *searchName;
        string word;
        istringstream iss(s);
        bool deleted = false;
        while (iss >> word)
        {
            long long h = computeHash(word);
            HashTableRecord *current = hashTable[h];
            HashTableRecord *prev = nullptr;

            while (current != nullptr)
            {
                if (checkstring(current->getRecord()->getName(),s))
                {
                    if (prev == nullptr)
                    {
                        hashTable[h] = current->getNext();
                    }
                    else
                    {
                        prev->setNext(current->getNext());
                    }
                    delete current;
                    deleted = true;
                    break;
                }
                prev = current;
                current = current->getNext();
            }
        }
        return deleted;
    }

    vector<PhoneRecord*> Kontekts;
    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query){
        vector<PhoneRecord*> initiol;
        vector<PhoneRecord*> final;
        string s3 = *query;
        istringstream iss(s3);
        string word;
        int count=0;
        int countl=0;
        while (iss >> word) {
            count++;
        }
        iss.clear();              
        iss.seekg(0);
        //flag
        while(iss>>word){
            //cout<<"hell"<<endl;
            long long h = computeHash(word);
            HashTableRecord* nox = hashTable[h];
            if(nox!=nullptr){
                while(nox->getNext()!=nullptr){
                    initiol.push_back(nox->getRecord());
                    nox = nox->getNext();
                }
                initiol.push_back(nox->getRecord());
            }
        }
        for(int i=0;i<initiol.size();i++){
            for(int j=0;j<initiol.size();j++){
                if(initiol[i]->getName()==initiol[j]->getName()){
                    countl++;
                }
            }
            //cout<<initiol[i]<<"---"<<initiol[i]->getName()<<"---"<<countl<<endl;
            if(countl==count){
                final.push_back(initiol[i]);
            }
            countl=0;
        }
        return final;
    }
    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const;

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename){
        ifstream inputFile(filename); // Replace with the actual file name
        if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
        }
        string line;
        int count3=0;
        char bom[3] = {0};
        inputFile.read(bom, sizeof(bom));
        if (bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF) {
            // BOM detected (UTF-8 encoding), skip it
        } else {
            // No BOM detected, reset the file position
            inputFile.seekg(0);
        }
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string name,nexto, _;
            nexto[0] = '0';
            vector<string>num;
            getline(iss, name, ',');
            //cout<<name<<endl;
            while (nexto[0] >= 48 && nexto[0] <= 57)
            {
                getline(iss, nexto, ',');
                if(nexto[0]>= 48 && nexto[0] <= 57){
                    num.push_back(nexto);
                }
            }
            PhoneRecord* itachi = new PhoneRecord(name,nexto,num);
            //cout<<itachi.getOrganisation()<<endl;
            addContact(itachi);
            Kontekts.push_back(itachi);
            getline(iss, _);
        }
    };

    // Destructor
   // ~PhoneBook();
};

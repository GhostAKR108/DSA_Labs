#include <bits/stdc++.h>
#include <vector>
#include<fstream>
using namespace std;

class StudentRecord
{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName()
    {
        return studentName;
    }
    void set_studentName(string Name)
    {
        studentName = Name;
    }
    string get_rollNumber()
    {
        return rollNumber;
    }
    void set_rollNumber(string rollnum)
    {
        rollNumber = rollnum;
    }
};

class Node
{
private:
    Node *next;
    StudentRecord *element;

public:
    Node *get_next()
    {
        return next;
    }
    StudentRecord *get_element()
    {
        return element;
    }

    void set_next(Node *value)
    {
        next = value;
    }
    void set_element(StudentRecord *student)
    {
        element = student;
    }
};

class Entity
{
private:
    string name;
    Node *iterator;

public:
    string get_name()
    {
        return name;
    }
    void set_name(string Name)
    {
        name = Name;
    }
    Node *get_iterator()
    {
        return iterator;
    }
    void set_iterator(Node *iter)
    {
        iterator = iter;
    }
};
vector<StudentRecord> students;

class LinkedList : public Entity
{
public:
    void add_student(StudentRecord student)
    {
        Node *baby = new Node;
        StudentRecord *copy1 = new StudentRecord(student);
        baby->set_element(copy1);
        baby->set_next(nullptr);

        if (get_iterator() == nullptr)
        {
            set_iterator(baby);
        }
        else
        {
            Node *current = get_iterator();
            while (current->get_next() != nullptr)
            {
                current = current->get_next();
            }
            current->set_next(baby);
        }
    }

    void delete_student(string studentName)
    {
        Node *current = get_iterator();
        while(current->get_next()->get_element()->get_studentName()!=studentName){
            current = current->get_next();
        }
        Node *target = current->get_next();
        current->set_next(current->get_next()->get_next());
        delete target;
    }
};
vector<LinkedList> EntityArray;
vector<string> Attributes;


void read_input_file(string input){
    ifstream inputFile(input); // Replace with the actual file name
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
    }

    string line;
    int count=0;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        int isthere = 0,i;
        string name, rno, branch, hostel, course, hobby, _;
        StudentRecord s;
        //adding student record
        getline(iss, name, ',');
        getline(iss, rno, ',');
        s.set_studentName(name);
        s.set_rollNumber(rno);
        for(i=0;i<students.size();i++){
            if(students[i].get_rollNumber()==rno){
                isthere = 1;
                break;
            }
        }
        if(isthere!=1){
            students.push_back(s);
        }
        isthere=0;
        //inserting branch
        getline(iss, branch, ',');
        for(i=0;i<EntityArray.size();i++){
            if(EntityArray[i].get_name()==branch){
                isthere = 1;
                break;
            }
        }
        if(isthere==1){
            EntityArray[i].add_student(s);
        }
        else{
            LinkedList AKR;
            AKR.set_name(branch);
            AKR.set_iterator(NULL);
            AKR.add_student(s);
            EntityArray.push_back(AKR);
        }
        isthere = 0;
        //inserting courses

        string coursesStr;
        getline(iss, coursesStr, '[');
        getline(iss, coursesStr, ']');
        istringstream coursesStream(coursesStr);
        while (getline(coursesStream, course, ',')){
            for(i=0;i<EntityArray.size();i++){
                if(EntityArray[i].get_name()==course){
                    isthere = 1;
                    break;
                }
            }
            if(isthere==1){
                EntityArray[i].add_student(s);
            }
            else{
                LinkedList AKR;
                AKR.set_name(course);
                AKR.set_iterator(NULL);
                AKR.add_student(s);
                EntityArray.push_back(AKR);
            }
            isthere = 0;
        }
        char skipComma;
        iss >> skipComma;

        //inserting hostel

        getline(iss, hostel, ',');
        for(i=0;i<EntityArray.size();i++){
            if(EntityArray[i].get_name()==hostel){
                isthere = 1;
                break;
            }
        }
        if(isthere==1){
            EntityArray[i].add_student(s);
        }
        else{
            LinkedList AKR;
            AKR.set_name(hostel);
            AKR.set_iterator(NULL);
            AKR.add_student(s);
            EntityArray.push_back(AKR);
        }
        isthere = 0;

        //inserting hobbies

        string hobbiesStr;
        getline(iss, hobbiesStr, '[');
        getline(iss, hobbiesStr, ']');
        istringstream hobbiesStream(hobbiesStr);
        while (getline(hobbiesStream, hobby, ',')){
            for(i=0;i<EntityArray.size();i++){
                if(EntityArray[i].get_name()==hobby){
                    isthere = 1;
                    break;
                }
            }
            if(isthere==1){
                EntityArray[i].add_student(s);
            }
            else{
                LinkedList AKR;
                AKR.set_name(hobby);
                AKR.set_iterator(NULL);
                AKR.add_student(s);
                EntityArray.push_back(AKR);
            }
            isthere = 0;
        }
        getline(iss, _);
    }
    inputFile.close();
}

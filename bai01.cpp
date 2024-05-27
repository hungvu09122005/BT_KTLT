#include <iostream>
#include <stdio.h>
#include <exception>
#include <cstring>

using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "could not memory allocation";
  }
} myex;

class myexception1: public exception
{
  virtual const char* what() const throw()
  {
    return "could not read file";
  }
} myex1;

class myexception2: public exception
{
  virtual const char* what() const throw()
  {
    return "could not enough student";
  }
} myex2;

struct Student {
    char MSSV [10];
    char hoTen [30];
    double gpa ;
};

Student * inputStudentList ( int & n ){
    cout << "enter n = ";
    cin >> n;
    cin.ignore();

    Student* studentList = new (nothrow) Student [n];

    if (!studentList){
        throw myex;
    }

    for (int i = 0; i < n; i++){
        cout << "student's name is ";
        cin.getline(studentList[i].hoTen, 30);
        cout << "MSSV: ";
        cin.getline(studentList[i].MSSV, 10);
        cout << "GPA = ";
        cin >> studentList[i].gpa;
        cin.ignore();
    }

    return studentList;
}

void writeStudentList ( const char * fileName , Student * studentList , int n ){
    FILE* wf = fopen(fileName, "wb");

    fwrite(&n, sizeof(int), 1, wf);
    fwrite(studentList, sizeof(Student) * n, 1, wf);

    fclose(wf);
    wf = nullptr;
}

Student * readStudentListFromFile ( const char * fileName , int & n ){
    FILE* rf = fopen(fileName, "rb");

    if (!rf) {
        throw myex1;
    }

    fread(&n, sizeof(int), 1, rf);
    Student* studentList = new Student [n];
    fread(studentList, sizeof(Student) * n, 1, rf);

    fclose(rf);

    return studentList;
}

void sortStudentList ( Student *& studentList , int n ){
    int tmp = 0;
    char tmpStr [30] = "\0";

    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (studentList[i].gpa < studentList[j].gpa){
                tmp = studentList[i].gpa;
                studentList[i].gpa = studentList[j].gpa;
                studentList[j].gpa = tmp;

                strcpy(tmpStr, studentList[i].hoTen);
                strcpy(studentList[i].hoTen, studentList[j].hoTen);
                strcpy(studentList[j].hoTen, tmpStr);

                strcpy(tmpStr, studentList[i].MSSV);
                strcpy(studentList[i].MSSV, studentList[j].MSSV);
                strcpy(studentList[j].MSSV, tmpStr);
            }
        }
    }
}

void writeBestStudentList ( const char * bestStudentFile , Student * studentList ,int n , int k ) {
    if (k > n){
        throw myex2;
    }

    Student* bestStudentList = new (nothrow) Student [k];

    if(!bestStudentList){
        throw myex;
    }

    sortStudentList(studentList, n);

    for (int i = 0; i < k; i++){
        bestStudentList[i].gpa = studentList[k - i - 1].gpa;
        strcpy(bestStudentList[i].hoTen, studentList[k - i - 1].hoTen);
        strcpy(bestStudentList[i].MSSV, studentList[k - i - 1].MSSV);
    }

    FILE* wf = fopen(bestStudentFile, "wb");

    fwrite(&k, sizeof(int), 1, wf);
    fwrite(bestStudentList, sizeof(Student) * k, 1, wf);

    fclose(wf);
    wf = nullptr;
}


int main (){
    return 0;
}
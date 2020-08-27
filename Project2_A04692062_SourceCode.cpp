/*Project 2
   Jenna Ashby
   Latest Modification: 2/12/2019 */


//This code will read input from a file, calculate
// final grades, and format and write to a file.

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


int main()
{
    //declare variables
    int const A_SCORE = 90, B_SCORE = 80, C_SCORE = 70, D_SCORE = 60;
    string ssn, address, phone, name;
    double test1, test2, test3, test4, testf, grade;
    int age, yrsTxst;

    //open files
    ifstream infile;
    infile.open("Project2_A04692062_Input.txt");
    ofstream outfile;
    outfile.open("Project2_A04692062_Output.txt");

    //get input from file
    getline(infile, name);

    infile >> age;
    infile.ignore();

    getline(infile, address);

    infile >> yrsTxst;
    infile.ignore();

    getline(infile, phone);

    infile >> ssn;

    infile >> test1;

    infile >> test2;

    infile >> test3;

    infile >> test4;

    infile >> testf;

    //compute final grade
    grade = test1*.1 + test2*.15 + test3*.15 + test4*.2 + testf*.4;


    //format and output data
    outfile << fixed << setprecision(2);
    outfile << setw(30) << ' ' << "Student Grade Sheet\n";
    outfile << right << setw(35) << "Name of Student:" << setw(5) << ' ' << name << '\n';
    outfile << right << setw(35) << "Age:" << setw(5) << ' ' << age << '\n';
    outfile << right << setw(35) << "Address:" << setw(5) << ' ' << address << '\n';
    outfile << right << setw(35) << "Number of Years at Texas State:" << setw(5) << ' ' << yrsTxst << '\n';
    outfile << right << setw(35) << "Telephone Number:" << setw(5) << ' ' << phone << '\n';
    outfile << right << setw(35) << "Student Soc. Security #:" << setw(5) << ' ' << ssn << '\n';
    outfile << right << setw(35) << "Test 1:" << setw(5) << ' ' << test1 << '\n';
    outfile << right << setw(35) << "Test 2:" << setw(5) << ' ' << test2 << '\n';
    outfile << right << setw(35) << "Test 3:" << setw(5) << ' ' << test3 << '\n';
    outfile << right << setw(35) << "Test 4:" << setw(5) << ' ' << test4 << '\n';
    outfile << right << setw(35) << "Final Exam:" << setw(5) << ' ' << testf << '\n';
    outfile << right << setw(35) << "Numerical Grade:" << setw(5) << ' ' << grade << '\n';
    outfile << right << setw(35) << "Letter Grade:" << setw(5) << ' ';

    if(grade >= A_SCORE)
         outfile << "A\n";
    else if(grade >= B_SCORE)
        outfile << "B\n";
    else if(grade >= C_SCORE)
        outfile << "C\n";
    else if(grade >= D_SCORE)
        outfile << "D\n";
    else
        outfile << "F\n";

    if(grade >= A_SCORE)
        outfile << "\t\t\tThanks for all your hard work!";
    else if (grade < B_SCORE)
        outfile << "\t\t\tStudy harder next time.";

    infile.close();
    outfile.close();

    return 0;
}


/*Project 1
   Jenna Ashby
   Latest Modification: 1/29/2019 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    //declare variables
    string ssn, name;
    double test1, test2, testf, grade;

    //get student name
    cout << "Please enter student name: ";
    cin >> name;

    //get student social security number
    cout << "Please enter student social security number: ";
    cin >> ssn;

    //get value for test 1
    cout << "First exam grade: ";
    cin >> test1;

    //get value for test 2
    cout << "Second exam grade: ";
    cin >> test2;

    //get value for final exam
    cout << "Final exam grade: ";
    cin >> testf;

    //compute final grade using test1*.25 + test2*.25 + testf*.5
    grade = test1*.25 + test2*.25 + testf*.5;

    //format and output data
    cout << "\t\t\tStudent Grades\n\tDepartment of Computer Science, Texas State University\n";
    cout << "Student:\t" << name
         << "\nStudent SSN:\t" << ssn
         << "\nTest 1:\t\t" << test1
         << "\nTest 2:\t\t" << test2
         << "\nFinal Exam:\t" << testf
         << "\nGrade:\t\t" << setprecision(1) << fixed << grade << '%';
    return 0;
}


/*Project 3
   Jenna Ashby
   Latest Modification: 3/1/2019 */


//This code will read input from a file, calculate
// final grades, and format and write to a file.

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


int main()
{
    //declare variables
    int const A_SCORE = 90, B_SCORE = 80, C_SCORE = 70, D_SCORE = 60, CLASSES = 3, TESTS = 5;
    string ssn, address, phone, name, gradeMessage, course;
    double testGrade, finalGrade;
    int age, yrsTxst, students;

    //open files
    ifstream infile;
    infile.open("debug.txt");
    ofstream outfile;
    outfile.open("Project3_A04692062_Output.txt");

    //validate that input file was opened
    if (!infile)
        {
            cout << "ERROR: Please check the input file exists.";
            return 0;
        }

    //get # of students from keyboard
    cout << "Please enter the number of students: ";
    cin >> students;

    //validate that students is at least 3
    while (students < 3)
    {
        cout << "The number of students must be at least 3. \nPlease enter the number of students: ";
        cin >> students;
    }

    //begin loops
    //student loop
    for(int i = 0; i < students; i++)
    {
        //get student name and validate
        getline(infile, name);
        if(name.length() < 1 || name.length() > 50)
        {
            cout << "ERROR: There was a problem with student #" << i+1 << "'s name.\n";
            continue;
        }

        //get age and validate
        infile >> age;
        if(age < 1 || age > 90)
        {
            cout << "ERROR: There was a problem with student " << name << "'s age.\n";
            continue;
        }
        infile.ignore();

        //get address and validate
        getline(infile, address);
        if(address.length() < 1 || address.length() > 50)
        {
            cout << "ERROR: There was a problem with student " << name << "'s address.\n";
            continue;
        }

        //get yrs at txst and validate
        infile >> yrsTxst;
        if(yrsTxst < 1 || yrsTxst > 90)
        {
            cout << "ERROR: There was a problem with student " << name << "'s years at Texas State.\n";
            continue;
        }
        infile.ignore();

        //get phone number and validate
        getline(infile, phone);
        if(phone.length() < 1 || phone.length() > 20)
        {
            cout << "ERROR: There was a problem with student " << name << "'s phone number.\n";
            continue;
        }
        //get ssn and validate
        getline(infile, ssn);
        if(ssn.length() < 1 || ssn.length() > 20)
        {
            cout << "ERROR: There was a problem with student " << name << "'s Social Sec. Number.\n";
            continue;
        }

        //output student info
        outfile << fixed << setprecision(2);
        outfile << setw(30) << ' ' << "Student Grade Sheet\n";
        outfile << right << setw(35) << "Name of Student:" << setw(5) << ' ' << name << '\n';
        outfile << right << setw(35) << "Age:" << setw(5) << ' ' << age << '\n';
        outfile << right << setw(35) << "Address:" << setw(5) << ' ' << address << '\n';
        outfile << right << setw(35) << "Number of Years at Texas State:" << setw(5) << ' ' << yrsTxst << '\n';
        outfile << right << setw(35) << "Telephone Number:" << setw(5) << ' ' << phone << '\n';
        outfile << right << setw(35) << "Student Soc. Security #:" << setw(5) << ' ' << ssn << '\n';

        //course loop
        for (int j = 0; j < CLASSES; j++)
        {
            //get course name
            getline(infile, course);
            if(course.length() < 1 || course.length() > 50)
            {
                cout << "ERROR: There was an issue with student " << name << "'s course #" << j+1 << ".\n";
                continue;
            }
            outfile << right << setw(35) << "Course:" << setw(5) << ' ' << course << '\n';

            //set finalgrade to 0
            finalGrade = 0;

            //test grade loop
            for(int k = 0; k < TESTS; k++)
            {
                //get test grade and output it
                infile >> testGrade;

                //validate grades
                if(testGrade < 1.00 || testGrade > 100.00)
                {
                    cout << "ERROR: There was an issue with student " << name << "'s test #" << k+1 << "in " << course << ".\n";
                    break;
                }
                outfile << right << setw(33) << "Test #" << k+1 << ':' << setw(5) << ' ' << testGrade << '\n';

                //add test grade to the sum according to which test it is
                switch (k)
                {
                    case 0:
                        finalGrade += (testGrade * .1);
                        break;
                    case 1:
                        finalGrade += (testGrade * .15);
                        break;
                    case 2:
                        finalGrade += (testGrade * .2);
                        break;
                    case 3:
                        finalGrade += (testGrade * .25);
                        break;
                    case 4:
                        finalGrade += (testGrade * .3);
                        break;
                }//end of switch statement
            }//end of test grade loop

            //output final grade
            outfile << right << setw(35) << "Final Grade:" << setw(5) << ' ' << finalGrade << "%\n";
            outfile << setw(35) << "Letter Grade:" << setw(5) << ' ';

            //determine letter grade
            if(finalGrade >= A_SCORE)
                 outfile << "A\n";
            else if(finalGrade >= B_SCORE)
                outfile << "B\n";
            else if(finalGrade >= C_SCORE)
                outfile << "C\n";
            else if(finalGrade >= D_SCORE)
                outfile << "D\n";
            else
                outfile << "F\n";

            //determine message
            if (finalGrade >= 95)
                outfile << right << setw(35) << "Note:" << setw(5) << ' ' << "Thanks for your hard work! Keep it up.\n";
            else if(finalGrade < 70)
                outfile << right << setw(35) << "Note:" << setw(5) << ' ' << "Your grade is very low. Please work harder.\n";

            outfile << '\n';

            //ignore so the next loop's getline works
            infile.ignore();

        }//end of course loop

    }//end of student loop

    cout << "Complete. Please check the output file.";

    //close input and output files
    infile.close();
    outfile.close();

    return 0;
}


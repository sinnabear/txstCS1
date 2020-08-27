/*Project 6
   Jenna Ashby
   Latest Modification: 4/27/2019 */


//This code will read input from a file, calculate
// final grades, and format and write to a file.

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//global vars
int const A_SCORE = 90, B_SCORE = 80, C_SCORE = 70, D_SCORE = 60, CLASSES = 3, TESTS = 5, STUDENTS = 3;
string const NONNUM[6]= {" ","Name of Student:", "Student ID:", "Student Address:", "Telephone Number:", "Student SSN:"};
string const NUM[2]= {"Student Age:", "Years at Texas State:"};
string const TEST_HEADER[TESTS + 1] = {"Test #1:", "Test #2:", "Test #3:", "Test #4:", "Test #5:", "Final Grade:"};

//declare structures
struct classFrame
{
    string name;
    double grades[TESTS+1];
    char letGrade;
};

struct studentFrame
{
    string strHeader [6];
    int numHeader [2];
    classFrame course[CLASSES];
};

//prototypes
void inputData(ifstream &, studentFrame []);
void numGrade(studentFrame [], int, int);
void LetGrade(studentFrame [], int, int);
void comments(ofstream &, studentFrame [], string, string, int, int);
void report(ofstream &, studentFrame [], string, string);
bool validateData(double);
bool validateData(string);

int main()
{
    studentFrame student[STUDENTS];
    string msgPos, msgNeg;
    int students;

    //open files
    ifstream infile;
    infile.open("Project6_A04692062_Input.txt");
    ofstream outfile;
    outfile.open("Project6_A04692062_Output.txt");

    //validate that input file was opened
    if (!infile)
        {
            cout << "ERROR: Please check the input file exists.";
            return 0;
        }

    //get the # of students
    cout << "Please enter the number of students (3): ";
    cin >> students;

    //validate # of students
    while(students != STUDENTS)
    {
        cout << "The number of students must be three (3): ";
        cin >> students;
    }

    //get feedback messages
    getline(infile, msgPos);
    getline(infile, msgNeg);

    //begin loops
    inputData(infile, student);

    //output loops
    report(outfile, student, msgPos, msgNeg);

    cout << "Complete. Please check the output file.";

    //close input and output files
    infile.close();
    outfile.close();

    return 0;

}

void inputData(ifstream& infile,studentFrame student[])
{

    //student loop
    for(int i = 0; i < STUDENTS; i++)
    {
        //fill strHeader array and validate
        for(int index = 0; index < 6; index++)
        {
            getline(infile, student[i].strHeader[index]);

            if(validateData(student[i].strHeader[index]))
            {
                cout << "ERROR: There was a problem with student #" << i+1 << "'s data.\n";
                continue;
            }
        }//end of strHeader fill

        //fill and validate numHeader array
        for(int index = 0; index < 2; index++)
        {
            infile >> student[i].numHeader[index];
            if(validateData(student[i].numHeader[index]))
            {
                cout << "ERROR: There was a problem with student #" << i+1 << "'s data.\n";
                continue;
            }
        }//end of numHeader fill

        infile.ignore();

        //course loop
        for (int j = 0; j < CLASSES; j++)
            {
                getline(infile, student[i].course[j].name);

                if(validateData(student[i].course[j].name))
                {
                    cout << "ERROR: There was a problem with student #" << i+1 << "'s data.\n";
                    continue;
                }//end of validation loop

                //test grade loop
                for(int k = 0; k < TESTS; k++)
                {
                    //get test grade and validate
                    infile >> student[i].course[j].grades[k];

                    if(validateData(student[i].course[j].grades[k]))
                    {
                        cout << "ERROR: There was an issue with student# " << i+1 << "'s test #" << k+1 << " in course " << j+1 << ".\n";
                        break;
                    }//end of validation loop

                }//end of test grade loop

                //compute final grade
                numGrade(student, i, j);

                //determine letter grade
                LetGrade(student, i, j);

                //ignore so the next loop's getline works
                infile.ignore();

            }//end of course loop

        }//end of student loop
}

void numGrade(studentFrame student[], int i, int j)
{
    double weight[] = {.1, .15, .2, .25, .3};
    student[i].course[j].grades[TESTS] = 0;

    for(int index = 0; index < TESTS; index++)
    {
        student[i].course[j].grades[TESTS] += (weight[index] * student[i].course[j].grades[index]);
    }
}

bool validateData(string temp)
{
    return (temp.length() < 1 || temp.length() > 50);
}

bool validateData(double temp)
{
    return (temp < 1.00 || temp > 100.00);
}

void LetGrade(studentFrame student[], int i, int j)
{
    if(student[i].course[j].grades[TESTS] >= A_SCORE)
        student[i].course[j].letGrade = 'A';
    else if(student[i].course[j].grades[TESTS] >= B_SCORE)
        student[i].course[j].letGrade = 'B';
    else if(student[i].course[j].grades[TESTS] >= C_SCORE)
        student[i].course[j].letGrade = 'C';
    else if(student[i].course[j].grades[TESTS] >= D_SCORE)
        student[i].course[j].letGrade = 'D';
    else
        student[i].course[j].letGrade = 'F';

}

void comments(ofstream& outfile, studentFrame student[], string msgPos, string msgNeg, int i, int j)
{

    if (student[i].course[j].grades[TESTS] >= 95)
        outfile << right << setw(35) << "Note:" << setw(5) << ' ' << msgPos << '\n';
    else if(student[i].course[j].grades[TESTS] < 70)
        outfile << right << setw(35) << "Note:" << setw(5) << ' ' << msgNeg << '\n';
}

void report(ofstream& outfile, studentFrame student[], string msgPos, string msgNeg)
{
    for(int i = 0; i < STUDENTS; i++)
    {
        //output student info
        outfile << fixed << setprecision(2);
        outfile << setw(30) << ' ' << student[i].strHeader[0] << '\n';

        //nonnum output
        for(int index = 1; index < 6; index++)
        {
            outfile << right << setw(35) << NONNUM[index] << setw(5) << ' ' << student[i].strHeader[index] << '\n';
        }//end of output loop

        //num output
        for(int index = 0; index < 2; index++)
        {
            outfile << right << setw(35) << NUM[index] << setw(5) << ' ' << student[i].numHeader[index] << '\n';
        }//end of output loop
        for(int j = 0; j < CLASSES; j++)
        {
            outfile << right << setw(35) << "Course Number:" << setw(5) << ' ' << student[i].course[j].name << '\n';

            for(int k = 0; k < TESTS + 1; k++)
            {
                //output grades
                outfile << right << setw(35) << TEST_HEADER[k] << setw(5) << ' ' << student[i].course[j].grades[k] << "%\n";
            }//end k loop

            //output letter grade
            outfile << setw(35) << "Letter Grade:" << setw(5) << ' ' << student[i].course[j].letGrade << '\n';

            //determine message
            comments(outfile, student, msgPos, msgNeg, i, j);

            outfile << '\n';
        }//end j loop
    }//end i loop
}

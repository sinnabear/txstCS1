/*Project 4
   Jenna Ashby
   Latest Modification: 4/1/2019 */


//This code will read input from a file, calculate
// final grades, and format and write to a file.

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    int const A_SCORE = 90, B_SCORE = 80, C_SCORE = 70, D_SCORE = 60, CLASSES = 3, TESTS = 5;
    string strHeader [3][9], msgPos, msgNeg, tempString;
    string const NONNUM[9]= {" ","Name of Student:", "Student ID:", "Student Address:", "Telephone Number:", "Student SSN:", "Course Number:", "Course Number:", "Course Number:"};
    string const NUM[2]= {"Student Age:", "Years at Texas State:"};
    string const TEST_HEADER[TESTS + 1] = {"Test #1:", "Test #2:", "Test #3:", "Test #4:", "Test #5:", "Final Grade:"};
    double grades [3][CLASSES][TESTS + 1], tempNum;
    int numHeader [3][2], students;
    char letGrade [3][CLASSES];

    //open files
    ifstream infile;
    infile.open("Project4_A04692062_Input.txt");
    ofstream outfile;
    outfile.open("Project4_A04692062_Output.txt");

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
    while(students != 3)
    {
        cout << "The number of students must be three (3): ";
        cin >> students;
    }

    //get feedback messages
    getline(infile, msgPos);
    getline(infile, msgNeg);

    //begin loops
    //student loop
    for(int i = 0; i < students; i++)
    {
        //fill strHeader array and validate
        for(int index = 0; index < 6; index++)
        {
            getline(infile,tempString);

            if(tempString.length() < 1 || tempString.length() > 50)
            {
                cout << "ERROR: There was a problem with student #" << i+1 << "'s data.\n";
                continue;
            }

            strHeader[i][index] = tempString;
        }//end of strHeader fill

        //fill and validate numHeader array
        for(int index = 0; index < 2; index++)
        {
            infile >> tempNum;
            if(tempNum < 1 || tempNum > 90)
            {
                cout << "ERROR: There was a problem with student #" << i+1 << "'s data.\n";
                continue;
            }

            numHeader[i][index] = tempNum;
        }//end of numHeader fill

        infile.ignore();

        //course loop
        for (int j = 0; j < CLASSES; j++)
        {
            getline(infile,tempString);

            if(tempString.length() < 1 || tempString.length() > 50)
            {
                cout << "ERROR: There was a problem with student #" << i+1 << "'s data.\n";
                continue;
            }//end of validation loop

            strHeader[i][j+6] = tempString;

            //test grade loop
            for(int k = 0; k < TESTS; k++)
            {
                //get test grade and validate
                infile >> tempNum;

                if(tempNum < 1.00 || tempNum > 100.00)
                {
                    cout << "ERROR: There was an issue with student# " << i+1 << "'s test #" << k+1 << " in course " << j+1 << ".\n";
                    break;
                }//end of validation loop

                grades[i][j][k] = tempNum;
            }//end of test grade loop

            //compute final grade
            grades[i][j][TESTS] = (grades[i][j][0] * .1) + (grades[i][j][1] * .15) + (grades[i][j][2] * .2) + (grades[i][j][3] * .25) + (grades[i][j][4] * .3);

            //determine letter grade
            if(grades[i][j][TESTS] >= A_SCORE)
                 letGrade[i][j] = 'A';
            else if(grades[i][j][TESTS] >= B_SCORE)
                letGrade[i][j] = 'B';
            else if(grades[i][j][TESTS] >= C_SCORE)
                letGrade[i][j] = 'C';
            else if(grades[i][j][TESTS] >= D_SCORE)
                letGrade[i][j] = 'D';
            else
                letGrade[i][j] = 'F';

            //ignore so the next loop's getline works
            infile.ignore();

        }//end of course loop

    }//end of student loop

    //output loops
    for(int i = 0; i < students; i++)
    {
        //output student info
        outfile << fixed << setprecision(2);
        outfile << setw(30) << ' ' << strHeader[i][0] << '\n';

        //nonnum output
        for(int index = 1; index < 6; index++)
        {
            outfile << right << setw(35) << NONNUM[index] << setw(5) << ' ' << strHeader[i][index] << '\n';
        }//end of output loop

        //num output
        for(int index = 0; index < 2; index++)
        {
            outfile << right << setw(35) << NUM[index] << setw(5) << ' ' << numHeader[i][index] << '\n';
        }//end of output loop
        for(int j = 0; j < CLASSES; j++)
        {
            outfile << right << setw(35) << NONNUM[j+6] << setw(5) << ' ' << strHeader[i][j+6] << '\n';

            for(int k = 0; k < TESTS + 1; k++)
            {
                //output grades
                outfile << right << setw(35) << TEST_HEADER[k] << setw(5) << ' ' << grades[i][j][k] << "%\n";
            }//end k loop

            //output final grade and letter grade
            outfile << setw(35) << "Letter Grade:" << setw(5) << ' ' << letGrade[i][j] << '\n';

            //determine message
            if (grades[i][j][TESTS] >= 95)
                outfile << right << setw(35) << "Note:" << setw(5) << ' ' << msgPos << '\n';
            else if(grades[i][j][TESTS] < 70)
                outfile << right << setw(35) << "Note:" << setw(5) << ' ' << msgNeg << '\n';

            outfile << '\n';
        }//end j loop
    }//end i loop

    cout << "Complete. Please check the output file.";

    //close input and output files
    infile.close();
    outfile.close();

    return 0;

}

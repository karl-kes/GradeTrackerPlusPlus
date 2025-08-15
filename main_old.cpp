/*
 Title: Grade Book Calculator
 Description: A grade book capable of calculating the average of entire courses through the user's inputs.
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <algorithm>
using namespace std;

// Clears the screen by printing 100 lines.
void clear()
{
    for (int i = 0; i < 100; i++)
    {
        cout << "\n";
    }
    cout << endl;
}

// Checks to see whether user input number is negative or not.
float checkNegative(float num)
{
    bool validAns = false;
    
    while (!validAns)
    {
        if (num >= 0)
        {
            validAns = true;
        }
        
        else if (num < 0)
        {
            cout << "Error! Please enter a NON-NEGATIVE number!\n" << endl;
            validAns = false;
            cout << "Input non-negative number: ";
            cin >> num;
        }
    }
    
    return num;
}

// Pauses the program for an amount of time.
void wait(float sec)
{
    int micro = 1000000;
    usleep(micro * sec);
}

// Transforms a string into all lowercase.
string lowercase(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

// The name, grade, and weight for the components of the course.
struct courseComponents
{
    string name;
    float grade;
};

// Struct for the school courses; these are the individual classes a user takes.
struct myCourses
{
    string name;
    float grade;
    float weight[3];
    vector<courseComponents> assignments;
    vector<courseComponents> tests;
    vector<courseComponents> finalexams;
};

// A welcome message.
void welcome()
{
    cout << "                         ___                                              ___" << endl;
    cout << "                        (   )                                            (   )" << endl;
    cout << " ___  ___  ___   .--.    | |    .--.      .--.    ___ .-. .-.     .--.    | |" << endl;
    cout << "(   )(   )(   ) /    \\   | |   /    \\    /    \\  (   )   '   \\   /    \\   | |" << endl;
    cout << " | |  | |  | | |  .-. ;  | |  |  .-. ;  |  .-. ;  |  .-.  .-. ; |  .-. ;  | |" << endl;
    cout << " | |  | |  | | |  | | |  | |  |  |(___) | |  | |  | |  | |  | | |  | | |  | |" << endl;
    cout << " | |  | |  | | |  |/  |  | |  |  |      | |  | |  | |  | |  | | |  |/  |  | |" << endl;
    cout << " | |  | |  | | |  ' _.'  | |  |  | ___  | |  | |  | |  | |  | | |  ' _.'  | |" << endl;
    cout << " | |  ; '  | | |  .'.-.  | |  |  '(   ) | '  | |  | |  | |  | | |  .'.-.  |_|" << endl;
    cout << " ' `-'   `-' ' '  `-' /  | |  '  `-' |  '  `-' /  | |  | |  | | '  `-' /  .-." << endl;
    cout << "  '.__.'.__.'   `.__.'  (___)  `.__,'    `.__.'  (___)(___)(___) `.__.'  (   )" << endl;
    cout << "                                                                          '-'" << endl;
    cout << "Hello! Welcome to the Ultimate Grade Book Calculator!" << endl;
}

// Asks the user for their name.
string askUserName()
{
    string userName;

    cout << "Enter user name below [Case/Space-Sensitive]:" << endl;
    getline(cin, userName);
    cout << endl;

    return userName;
}

// Function will check to see if a user is new to the program by checking for their file.
bool isUserNew(string userName)
{
    bool newUser;

    ifstream userFiles;
    userFiles.open(userName + ".txt");
    if (!userFiles.is_open())
    {
        newUser = true;
    }

    else if (userFiles.is_open())
    {
        newUser = false;
    }

    else
    {
        cout << "Error opening file.\n" << endl;
        newUser = false;
    }
    userFiles.close();
    return newUser;
}

// Creates the file required for the user.
void createUserFiles(string userName)
{
    ofstream userFiles;
    userFiles.open(userName + ".txt");
    userFiles.close();
}

// Message that "shows" the loading of the user profile.
void loadingProfileMessage(string userName)
{
    cout << "Loading profile for user " << userName << ".\n" << endl;
    cout << "PROGRESS:" << endl;
    cout << "|----............|" << endl;
    wait(0.65);
    cout << "|--------........|" << endl;
    wait(0.65);
    cout << "|-------------...|" << endl;
    wait(0.65);
    cout << "|----------------|" << endl;
    wait(0.65);
    cout << "Profile fully loaded.\n" << endl;
    cout << "Welcome, " << userName << ", to your tailored Grade Book Calculator." << endl;
    wait(1.35); // final should be 1.35 and 0.65
}

// Displays the options in the main hub.
void hubMessage(string userName)
{
    cout << "Welcome, " << userName << ", to your tailored Grade Book Calculator." << endl;
    cout << "Would you like to add a course, edit a course, delete a course, calculate your average, or exit the program:\n" << endl;
    cout << "1. ADD" << endl;
    cout << "2. EDIT" << endl;
    cout << "3. DELETE" << endl;
    cout << "4. AVERAGE" << endl;
    cout << "5. EXIT\n" << endl;
    cout << "User Choice #[1-5]: ";
}

// The name of the new course.
string newCourseName()
{
    string newCourse;

    cout << "Enter the name of the course" << endl;
    cout << "New Course:" << endl;
    cin.ignore();
    getline(cin, newCourse);
    newCourse = lowercase(newCourse);

    return newCourse;
}

// Adds a new course to the courses vector.
void addNewCourse(vector<myCourses>& courses, string addCourseName)
{
    courses.push_back(myCourses{addCourseName, 0.0, {0.0, 0.0, 0.0}, {}, {}, {} });

    cout << endl;
    cout << "Course " << addCourseName << " has been successfully added." << endl;
    wait(0.5);
    cout << "NOTE: " << addCourseName << " will not be used in calculation until work has been added.\n" << endl;
    wait(0.5); // final is 1.5
}

// Determines which course the user wishes to edit; calculates the index.
int editWhichCourse(vector<myCourses>& courses)
{
    int editIndex;

    cout << "Which course would you like to edit?\n" << endl;
    for (int i = 0; i < courses.size(); i++)
    {
        cout << i + 1 << ". " << courses[i].name << endl;
    }

    cout << endl;
    cout << "Edit Course #[1-" << courses.size() << "]: ";
    cin >> editIndex;
    editIndex = checkNegative(editIndex);
    if(editIndex > 0)
    {
        editIndex--;
    }

    return editIndex;
}

// Asks the user how they'd like to edit their course and lists the options.
string editCourseOrAssignment(vector<myCourses>& courses, int editIndex)
{
    string userOpt;
    bool validAns = false;
    cout << "What would you like to do?\n" << endl;
    cout << "1. Edit Course\n";
    cout << "2. Add/Edit Assignment\n";
    cout << "3. Add/Edit Test\n";
    cout << "4. Add/Edit Final Exam\n" << endl;
    cout << "Choose Option [1-4]: ";
    cin >> userOpt;

    // Ensures a valid input.
    while (validAns == false)
    {
        if (userOpt == "1")
        {
            userOpt = "course";
            validAns = true;
        }
        else if (userOpt == "2")
        {
            userOpt = "assignment";
            validAns = true;
        }
        else if (userOpt == "3")
        {
            userOpt = "test";
            validAns = true;
        }
        else if (userOpt == "4")
        {
            userOpt = "finalexam";
            validAns = true;
        }
        else
        {
            cout << "Please input an appropriate option [1-4]\n" << endl;
            cout << "Choose Option [1-4]: ";
            cin >> userOpt;
            validAns = false;
        }
    }

    return userOpt;
}

// Sets the weight of the course assignments, tests, and final exam(s).
void setCourseWeights(vector<myCourses>& courses, int editIndex)
{
    float addWeight[3] = { 0.0, 0.0, 0.0 };
    float Sum;
    bool correctSum = false;

    // Ensures that the weights add up to 100%
    while (correctSum == false)
    {
        cout << "Weight of assignments [1-100%]: ";
        cin >> addWeight[0];
        addWeight[0] = checkNegative(addWeight[0]);
        addWeight[0] = addWeight[0] / 100;
        cout << "Weight of tests [1-100%]: ";
        cin >> addWeight[1];
        addWeight[1] = checkNegative(addWeight[1]);
        addWeight[1] = addWeight[1] / 100;
        cout << "Weight of final exam(s) [1-100%]: ";
        cin >> addWeight[2];
        addWeight[2] = checkNegative(addWeight[2]);
        addWeight[2] = addWeight[2] / 100;
        Sum = addWeight[0] + addWeight[1] + addWeight[2];

        if (Sum == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                courses[editIndex].weight[i] = addWeight[i];
            }
            cout << "Course component weights are set!\n" << endl;
            correctSum = true;
        }

        else
        {
            cout << "Error! Please ensure that the weights add up to 100%.\n" << endl;
            correctSum = false;
        }
    }
}

// Allows the user to edit a course name.
void changeCourseName(vector<myCourses>& courses, int editIndex)
{
    string userOpt;

    cout << "Would you like to change course name [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        string editCourseName;

        cout << "Enter new course name: " << endl;
        cin.ignore();
        getline(cin, editCourseName);
        editCourseName = lowercase(editCourseName);
        cout << endl;
        cout << "Course " << courses[editIndex].name << " has successfully been renamed to " << editCourseName << endl;
        courses[editIndex].name = editCourseName;
    }

    else
    {
        cout << "Name of course " << courses[editIndex].name << " has NOT been changed.\n" << endl;
    }
}

// Allows the user to change the course weights.
void changeCourseWeights(vector<myCourses>& courses, int editIndex)
{
    string userOpt;

    cout << "Would you like to edit course weight [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float addWeight[3] = { 0.0, 0.0, 0.0 };
        float Sum;
        bool correctSum = false;

        while (correctSum == false)
        {
            cout << "Weight of assignments [1-100%]: ";
            cin >> addWeight[0];
            addWeight[0] = addWeight[0] / 100;
            addWeight[0] = checkNegative(addWeight[0]);
            cout << "Weight of tests [1-100%]: ";
            cin >> addWeight[1];
            addWeight[1] = checkNegative(addWeight[1]);
            addWeight[1] = addWeight[1] / 100;
            cout << "Weight of final exam(s) [1-100%]: ";
            cin >> addWeight[2];
            addWeight[2] = checkNegative(addWeight[2]);
            addWeight[2] = addWeight[2] / 100;
            Sum = addWeight[0] + addWeight[1] + addWeight[2];

            if (Sum == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    courses[editIndex].weight[i] = addWeight[i];
                }
                cout << "Course component weights are set!\n" << endl;
                correctSum = true;
            }

            else
            {
                cout << "Error! Please ensure that the weights add up to 100%.\n" << endl;
                correctSum = false;
            }
        }
    }

    else
    {
        cout << "Weights of course will not be edited.\n" << endl;
    }
}

// Allows the user to add a new assignment.
void addNewAssignment(vector<myCourses>& courses, int editIndex)
{
    string userOpt;

    cout << "Would you like to add new assignment [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float newAssScore;
        float newAssTotal;
        float newAssGrade;
        string newAssignmentName;

        cout << "Enter name of new assignment: ";
        cin.ignore();
        getline(cin, newAssignmentName);
        newAssignmentName = lowercase(newAssignmentName);
        cout << endl;
        cout << "Your score on assignment: ";
        cin >> newAssScore;
        newAssScore = checkNegative(newAssScore);

        cout << "Maximum score on assignment: ";
        cin >> newAssTotal;
        newAssTotal = checkNegative(newAssTotal);

        newAssGrade = (newAssScore / newAssTotal);
        courses[editIndex].assignments.push_back(courseComponents{newAssignmentName, newAssGrade});
        cout << endl;

        cout << "You scored [" << newAssScore << " / " << newAssTotal << "] or " << fixed << setprecision(2) << 100 * (newAssGrade) << "%." << endl;
        cout << "Assignment " << newAssignmentName << " has been added to course " << courses[editIndex].name << "!\n" << endl;
    }

    else
    {
        cout << "New assignment has not been added.\n" << endl;
    }
}

// If the user wants to edit an assignment, it prints all options and asks which.
void editWhichAssignment(vector<myCourses>& courses, int editIndex, int &editAssignmentIndex)
{
    string userOpt;
    
    if (courses[editIndex].assignments.empty())
    {
        cout << "No assignments exist for this course. Please add assignments first.\n" << endl;
    }
    
    else
    {
        cout << "Would you like to edit an assignment [y/n]: ";
        cin >> userOpt;
        userOpt = lowercase(userOpt);

        if (userOpt == "y")
        {
            cout << "Which assignment would you like to edit?\n" << endl;

            for (int i = 0; i < courses[editIndex].assignments.size(); i++)
            {
                cout << i + 1 << ". " << courses[editIndex].assignments[i].name << endl;
            }

            cout << "Edit assignment #[1-" << courses[editIndex].assignments.size() << "]: ";
            cin >> editAssignmentIndex;
            editAssignmentIndex = checkNegative(editAssignmentIndex);
            if (editAssignmentIndex > 0)
            {
                editAssignmentIndex--;
            }
            cout << "Now editing assignment '" << courses[editIndex].assignments[editAssignmentIndex].name << "' in course '" << courses[editIndex].name << "'.\n" << endl;
        }

        else
        {
            cout << "No assignment will be edited.\n" << endl;
            editAssignmentIndex = -1;
        }
    }
}

// Allows the user to change the assignment name.
void changeAssignmentName(vector<myCourses>& courses, int editIndex, int editAssignmentIndex)
{
    string userOpt;

    cout << "Would you like to change assignment name [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        string editAssName;

        cout << "Enter new assignment name: ";
        cin.ignore();
        getline(cin, editAssName);
        editAssName = lowercase(editAssName);
        cout << endl;
        cout << "Assignment " << courses[editIndex].assignments[editAssignmentIndex].name << " has successfully been renamed to " << editAssName << endl;
        courses[editIndex].assignments[editAssignmentIndex].name = editAssName;
    }

    else
    {
        cout << "Name of assignment will not be edited.\n" << endl;
    }
}

// Allows the user to change the assignment grade.
void changeAssignmentGrade(vector<myCourses>& courses, int editIndex, int editAssignmentIndex)
{
    string userOpt;

    cout << "Would you like to change assignment grade [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float newAssScore;
        float newAssTotal;
        float newAssGrade;

        cout << endl;
        cout << "Your score on assignment: ";
        cin >> newAssScore;
        newAssScore = checkNegative(newAssScore);

        cout << "Maximum score on assignment: ";
        cin >> newAssTotal;
        newAssTotal = checkNegative(newAssTotal);

        newAssGrade = (newAssScore / newAssTotal);
        courses[editIndex].assignments[editAssignmentIndex].grade = newAssGrade;
        cout << endl;

        cout << "You scored [" << newAssScore << " / " << newAssTotal << "] or " << fixed << setprecision(2) << 100 * (newAssGrade) << "%." << endl;
        cout << "Assignment grade for " << courses[editIndex].assignments[editAssignmentIndex].name << " has been updated in course " << courses[editIndex].name << "!\n" << endl;
    }

    else
    {
        cout << "Grade of assignment will not be edited.\n" << endl;
    }
}

// Allows the user to add a new test.
void addNewTest(vector<myCourses>& courses, int editIndex)
{
    string userOpt;

    cout << "Would you like to add new test [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float newTestScore;
        float newTestTotal;
        float newTestGrade;
        string newTestName;

        cout << "Enter name of new test: ";
        cin.ignore();
        getline(cin, newTestName);
        newTestName = lowercase(newTestName);
        cout << endl;
        cout << "Your score on test: ";
        cin >> newTestScore;
        newTestScore = checkNegative(newTestScore);

        cout << "Maximum score on test: ";
        cin >> newTestTotal;
        newTestTotal = checkNegative(newTestTotal);

        newTestGrade = (newTestScore / newTestTotal);
        courses[editIndex].tests.push_back(courseComponents{ newTestName, newTestGrade });
        cout << endl;

        cout << "You scored [" << newTestScore << " / " << newTestTotal << "] or " << fixed << setprecision(2) << 100 * (newTestGrade) << "%." << endl;
        cout << "Test " << newTestName << " has been added to course " << courses[editIndex].name << "!\n" << endl;
    }
    else
    {
        cout << "New test has not been added.\n" << endl;
    }
}

// Prints out the tests and asks the user which they'd like to edit.
void editWhichTest(vector<myCourses>& courses, int editIndex, int& editTestIndex)
{
    if (courses[editIndex].tests.empty())
    {
        cout << "No tests exist for this course. Please add tests first.\n" << endl;
    }
    
    else
    {
        string userOpt;

        cout << "Would you like to edit a test [y/n]: ";
        cin >> userOpt;
        userOpt = lowercase(userOpt);

        if (userOpt == "y")
        {
            cout << "Which test would you like to edit?\n" << endl;

            for (int i = 0; i < courses[editIndex].tests.size(); i++)
            {
                cout << i + 1 << ". " << courses[editIndex].tests[i].name << endl;
            }

            cout << "Edit test #[1-" << courses[editIndex].tests.size() << "]: ";
            cin >> editTestIndex;
            editTestIndex = checkNegative(editTestIndex);
            if (editTestIndex > 0)
            {
                editTestIndex--;
            }
            cout << "Now editing test '" << courses[editIndex].tests[editTestIndex].name << "' in course '" << courses[editIndex].name << "'.\n" << endl;
        }
        else
        {
            cout << "No test will be edited.\n" << endl;
            editTestIndex = -1;
        }
    }
}

// If user wants to change a test name.
void changeTestName(vector<myCourses>& courses, int editIndex, int editTestIndex)
{
    string userOpt;

    cout << "Would you like to change test name [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        string editTestName;

        cout << "Enter new test name: ";
        cin.ignore();
        getline(cin, editTestName);
        editTestName = lowercase(editTestName);
        cout << endl;
        cout << "Test " << courses[editIndex].tests[editTestIndex].name << " has successfully been renamed to " << editTestName << endl;
        courses[editIndex].tests[editTestIndex].name = editTestName;
    }
    else
    {
        cout << "Name of test will not be edited.\n" << endl;
    }
}

// If user wants to change test grade.
void changeTestGrade(vector<myCourses>& courses, int editIndex, int editTestIndex)
{
    string userOpt;

    cout << "Would you like to change test grade [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float newTestScore;
        float newTestTotal;
        float newTestGrade;

        cout << endl;
        cout << "Your score on test: ";
        cin >> newTestScore;
        newTestScore = checkNegative(newTestScore);

        cout << "Maximum score on test: ";
        cin >> newTestTotal;
        newTestTotal = checkNegative(newTestTotal);

        newTestGrade = (newTestScore / newTestTotal);
        courses[editIndex].tests[editTestIndex].grade = newTestGrade;
        cout << endl;

        cout << "You scored [" << newTestScore << " / " << newTestTotal << "] or " << fixed << setprecision(2) << 100 * (newTestGrade) << "%." << endl;
        cout << "Test grade for " << courses[editIndex].tests[editTestIndex].name << " has been updated in course " << courses[editIndex].name << "!\n" << endl;
    }
    else
    {
        cout << "Grade of test will not be edited.\n" << endl;
    }
}

// If user wants to add final exam(s).
void addNewFinalExam(vector<myCourses>& courses, int editIndex)
{
    string userOpt;

    cout << "Would you like to add new final exam [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float newExamScore;
        float newExamTotal;
        float newExamGrade;
        string newExamName;

        cout << "Enter name of new final exam: ";
        cin.ignore();
        getline(cin, newExamName);
        newExamName = lowercase(newExamName);
        cout << endl;
        cout << "Your score on final exam: ";
        cin >> newExamScore;
        newExamScore = checkNegative(newExamScore);

        cout << "Maximum score on final exam: ";
        cin >> newExamTotal;
        newExamTotal = checkNegative(newExamTotal);

        newExamGrade = (newExamScore / newExamTotal);
        courses[editIndex].finalexams.push_back(courseComponents{newExamName, newExamGrade});
        cout << endl;

        cout << "You scored [" << newExamScore << " / " << newExamTotal << "] or " << fixed << setprecision(2) << 100 * (newExamGrade) << "%." << endl;
        cout << "Final exam " << newExamName << " has been added to course " << courses[editIndex].name << "!\n" << endl;
    }
    else
    {
        cout << "New final exam has not been added.\n" << endl;
    }
}

// Asks the user which final exam they'd like to edit.
void editWhichFinalExam(vector<myCourses>& courses, int editIndex, int& editFinalExamIndex)
{
    if (courses[editIndex].finalexams.empty())
    {
        cout << "No final exams exist for this course. Please add final exams first.\n" << endl;
    }
    
    else
    {
        string userOpt;

        cout << "Would you like to edit a final exam [y/n]: ";
        cin >> userOpt;
        userOpt = lowercase(userOpt);

        if (userOpt == "y")
        {
            cout << "Which final exam would you like to edit?\n" << endl;

            for (int i = 0; i < courses[editIndex].finalexams.size(); i++)
            {
                cout << i + 1 << ". " << courses[editIndex].finalexams[i].name << endl;
            }

            cout << "Edit final exam #[1-" << courses[editIndex].finalexams.size() << "]: ";
            cin >> editFinalExamIndex;
            editFinalExamIndex = checkNegative(editFinalExamIndex);
            if (editFinalExamIndex > 0)
            {
                editFinalExamIndex--;
            }
            cout << "Now editing final exam '" << courses[editIndex].finalexams[editFinalExamIndex].name << "' in course '" << courses[editIndex].name << "'.\n" << endl;
        }
        else
        {
            cout << "No final exam will be edited.\n" << endl;
            editFinalExamIndex = -1;
        }
    }
}

// Change the name of the final exam.
void changeFinalExamName(vector<myCourses>& courses, int editIndex, int editFinalExamIndex)
{
    string userOpt;

    cout << "Would you like to change final exam name [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        string editExamName;

        cout << "Enter new final exam name: ";
        cin.ignore();
        getline(cin, editExamName);
        editExamName = lowercase(editExamName);
        cout << endl;
        cout << "Final exam " << courses[editIndex].finalexams[editFinalExamIndex].name << " has successfully been renamed to " << editExamName << endl;
        courses[editIndex].finalexams[editFinalExamIndex].name = editExamName;
    }
    else
    {
        cout << "Name of final exam will not be edited.\n" << endl;
    }
}

// Change the grade of a final exam.
void changeFinalExamGrade(vector<myCourses>& courses, int editIndex, int editFinalExamIndex)
{
    string userOpt;

    cout << "Would you like to change final exam grade [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        float newExamScore;
        float newExamTotal;
        float newExamGrade;

        cout << endl;
        cout << "Your score on final exam: ";
        cin >> newExamScore;
        newExamScore = checkNegative(newExamScore);

        cout << "Maximum score on final exam: ";
        cin >> newExamTotal;
        newExamTotal = checkNegative(newExamTotal);

        newExamGrade = (newExamScore / newExamTotal);
        courses[editIndex].finalexams[editFinalExamIndex].grade = newExamGrade;
        cout << endl;

        cout << "You scored [" << newExamScore << " / " << newExamTotal << "] or " << fixed << setprecision(2) << 100 * (newExamGrade) << "%." << endl;
        cout << "Final exam grade for " << courses[editIndex].finalexams[editFinalExamIndex].name << " has been updated in course " << courses[editIndex].name << "!\n" << endl;
    }
    else
    {
        cout << "Grade of final exam will not be edited.\n" << endl;
    }
}

// Which course does the user want to delete.
void deleteWhichCourse(vector<myCourses>& courses, int& delIndex)
{
    string userOpt;
    cout << "Would you like to delete a course/component [y/n]: ";
    cin >> userOpt;
    userOpt = lowercase(userOpt);

    if (userOpt == "y")
    {
        cout << "Which course would you like to modify?\n" << endl;
        for (int i = 0; i < courses.size(); i++)
        {
            cout << i + 1 << ". " << courses[i].name << endl;
        }

        cout << endl;
        cout << "Edit Course #[1-" << courses.size() << "]: ";
        cin >> delIndex;
        delIndex = checkNegative(delIndex);
        if(delIndex > 0)
        {
            delIndex--;
        }
    }
    else
    {
        cout << "No course will be deleted\n" << endl;
        delIndex = -1;
    }
}

// Asks if the user would like to delete the course or a componenet.
string checkDelOpt(vector<myCourses>& courses, int delIndex)
{
    string userDelOpt;
    bool validAns = false;
    cout << "Would you like to delete the course or component?\n" << endl;
    cout << "1. Course\n";
    cout << "2. Assignment\n";
    cout << "3. Test\n";
    cout << "4. Final Exam\n" << endl;
    cout << "Delete [1-4]: ";
    cin >> userDelOpt;

    while (validAns == false)
    {
        if (userDelOpt == "1")
        {
            userDelOpt = "course";
            validAns = true;
        }
        
        else if (userDelOpt == "2")
        {
            userDelOpt = "assignment";
            validAns = true;
        }
        
        else if (userDelOpt == "3")
        {
            userDelOpt = "test";
            validAns = true;
        }
        
        else if (userDelOpt == "4")
        {
            userDelOpt = "finalexam";
            validAns = true;
        }
        
        else
        {
            cout << "Please input an appropriate input [1-4]\n" << endl;
            cout << "Delete [1-4]: ";
            cin >> userDelOpt;
            validAns = false;
        }
    }

    return userDelOpt;
}

// Deletes the entire course vector.
void deleteCourse(vector<myCourses>& courses, int delIndex)
{
    cout << "Deleting course '" << courses[delIndex].name << "'...\n";
    courses.erase(courses.begin() + delIndex);
    cout << "Course has successfully been deleted!\n" << endl;
    wait(0.75);
}

// Determines which assignment to delete.
void deleteWhichAssignment(vector<myCourses>& courses, int delIndex, int& delAssignmentIndex)
{
    if (courses[delIndex].assignments.empty())
    {
        cout << "No assignments exist for this course. Please add assignments first.\n" << endl;
    }
    
    else
    {
        cout << "Which assignment would you like to delete?\n" << endl;

        for (int i = 0; i < courses[delIndex].assignments.size(); i++)
        {
            cout << i + 1 << ". " << courses[delIndex].assignments[i].name << endl;
        }

        cout << "Delete assignment #[1-" << courses[delIndex].assignments.size() << "]: ";
        cin >> delAssignmentIndex;
        delAssignmentIndex = checkNegative(delAssignmentIndex);
        if(delAssignmentIndex > 0)
        {
            delAssignmentIndex--;
        }
        cout << "Now deleting assignment '" << courses[delIndex].assignments[delAssignmentIndex].name << "' in course '" << courses[delIndex].name << "'.\n" << endl;
    }
}

// Deletes the chosen assignment vector.
void deleteAssignment(vector<myCourses>& courses, int delIndex, int delAssignmentIndex)
{
    cout << "Deleting assignment '" << courses[delIndex].assignments[delAssignmentIndex].name << "'...\n";
    courses[delIndex].assignments.erase(courses[delIndex].assignments.begin() + delAssignmentIndex);
    cout << "Assignment has successfully been deleted!\n" << endl;
    wait(0.75);
}

// Determines which test to delete.
void deleteWhichTest(vector<myCourses>& courses, int delIndex, int& delTestIndex)
{
    if (courses[delIndex].tests.empty())
    {
        cout << "No tests exist for this course. Please add tests first.\n" << endl;
    }
    
    else
    {
        cout << "Which test would you like to delete?\n" << endl;

        for (int i = 0; i < courses[delIndex].tests.size(); i++)
        {
            cout << i + 1 << ". " << courses[delIndex].tests[i].name << endl;
        }

        cout << "Delete test #[1-" << courses[delIndex].tests.size() << "]: ";
        cin >> delTestIndex;
        delTestIndex = checkNegative(delTestIndex);
        if (delTestIndex > 0)
        {
            delTestIndex--;
        }
        cout << "Now deleting test '" << courses[delIndex].tests[delTestIndex].name << "' in course '" << courses[delIndex].name << "'.\n" << endl;
    }
}

// Deletes the chosen test vector.
void deleteTest(vector<myCourses>& courses, int delIndex, int delTestIndex)
{
    cout << "Deleting test '" << courses[delIndex].tests[delTestIndex].name << "'...\n";
    courses[delIndex].tests.erase(courses[delIndex].tests.begin() + delTestIndex);
    cout << "Test has successfully been deleted!\n" << endl;
    wait(0.75);
}

// Determines which final exam to delete.
void deleteWhichFinalExam(vector<myCourses>& courses, int delIndex, int& delFinalExamIndex)
{
    if (courses[delIndex].finalexams.empty())
    {
        cout << "No final exams exist for this course. Please add final exams first.\n" << endl;
    }
    
    else
    {
        cout << "Which final exam would you like to delete?\n" << endl;

        for (int i = 0; i < courses[delIndex].finalexams.size(); i++)
        {
            cout << i + 1 << ". " << courses[delIndex].finalexams[i].name << endl;
        }

        cout << "Delete final exam #[1-" << courses[delIndex].finalexams.size() << "]: ";
        cin >> delFinalExamIndex;
        delFinalExamIndex = checkNegative(delFinalExamIndex);
        if (delFinalExamIndex > 0)
        {
            delFinalExamIndex--;
        }
        cout << "Now deleting final exam '" << courses[delIndex].finalexams[delFinalExamIndex].name << "' in course '" << courses[delIndex].name << "'.\n" << endl;
    }
}

// Deletes the chosen final exam vector.
void deleteFinalExam(vector<myCourses>& courses, int delIndex, int delFinalExamIndex)
{
    cout << "Deleting final exam '" << courses[delIndex].finalexams[delFinalExamIndex].name << "'...\n";
    courses[delIndex].finalexams.erase(courses[delIndex].finalexams.begin() + delFinalExamIndex);
    cout << "Final exam has successfully been deleted!\n" << endl;
    wait(0.75);
}

// A goodbye message.
void goodbye()
{
    cout << "                                     ___   ___ " << endl;
    cout << "                                    (   ) (   ) " << endl;
    cout << "   .--.     .--.     .--.     .-.| |   | |.-.    ___  ___    .--. " << endl;
    cout << "  /    \\   /    \\   /    \\   /   \\ |   | /   \\  (   )(   )  /    \\ " << endl;
    cout << " ;  ,-. ' |  .-. ; |  .-. ; |  .-. |   |  .-. |  | |  | |  |  .-. ; " << endl;
    cout << " | |  | | | |  | | | |  | | | |  | |   | |  | |  | |  | |  |  | | | " << endl;
    cout << " | |  | | | |  | | | |  | | | |  | |   | |  | |  | '  | |  |  |/  | " << endl;
    cout << " | |  | | | |  | | | |  | | | |  | |   | |  | |  '  `-' |  |  ' _.' " << endl;
    cout << " | '  | | | '  | | | '  | | | '  | |   | '  | |   `.__. |  |  .'.-.  .-.   .-.   .-. " << endl;
    cout << " '  `-' | '  `-' / '  `-' / ' `-'  /   ' `-' ;    ___ | |  '  `-' / (   ) (   ) (   ) " << endl;
    cout << "  `.__. |  `.__.'   `.__.'   `.__,'     `.__.    (   )' |   `.__.'   `-'   `-'   `-' " << endl;
    cout << "  ( `-' ;                                         ; `-' ' " << endl;
    cout << "   `.__.                                           .__.'  " << endl;
    cout << "Thank you for using the Ultimate Grade Book Calculator!" << endl;
    cout << "Hope to see you soon.\n" << endl;
}

int main()
{
    vector<myCourses> courses;
    string userName;
    string userOption;
    bool newUser;
    bool exit = false;

    // Gives a welcome message and asks for user's name.
    welcome();
    userName = askUserName();

    // Checks to see if the user is new or not.
    newUser = isUserNew(userName);

    // If the user is new, create their files.
    if (newUser == true)
    {
        wait(0.65);
        cout << "You are a NEW user!" << endl;
        createUserFiles(userName);
    }

    // If the user is not new, load their previous files.
    else if (newUser == false)
    {
        wait(0.65);
        cout << "You are a RETURNING user!" << endl;
    }

    // If something goes wrong.
    else
    {
        cout << "Error checking for NEW/RETURNING user." << endl;
    }

    // Message that displays a "loading" screen.
    loadingProfileMessage(userName);
    wait(0.65);
    clear();

    while (!exit)
    {
        hubMessage(userName);
        cin >> userOption;

        // If the user wishes to add a course.
        if (userOption == "1")
        {
            string addCourseName;
            float currentCourse;

            addCourseName = newCourseName();
            addNewCourse(courses, addCourseName);
            wait(0.75);

            currentCourse = courses.size();
            currentCourse--;

            setCourseWeights(courses, currentCourse);
            wait(0.65);

            clear();
        }

        else if (courses.empty() == true && userOption != "5")
        {
            cout << endl;
            cout << "You currently have no courses.\n" << endl;
            wait(0.75);
            clear();
        }

        else if (userOption == "2" && courses.empty() == false)
        {
            string userEditOpt;
            int editIndex;
            int editAssignmentIndex = -1;
            int editTestIndex = -1;
            int editFinalExamIndex = -1;

            editIndex = editWhichCourse(courses);
            userEditOpt = editCourseOrAssignment(courses, editIndex);

            if (userEditOpt == "course")
            {
                changeCourseName(courses, editIndex);
                changeCourseWeights(courses, editIndex);
            }
            else if (userEditOpt == "assignment")
            {
                addNewAssignment(courses, editIndex);
                editWhichAssignment(courses, editIndex, editAssignmentIndex);

                if (editAssignmentIndex >= 0 && editAssignmentIndex < courses[editIndex].assignments.size())
                {
                    changeAssignmentName(courses, editIndex, editAssignmentIndex);
                    changeAssignmentGrade(courses, editIndex, editAssignmentIndex);
                }
            }
            else if (userEditOpt == "test")
            {
                addNewTest(courses, editIndex);
                editWhichTest(courses, editIndex, editTestIndex);

                if (editTestIndex >= 0 && editTestIndex < courses[editIndex].tests.size())
                {
                    changeTestName(courses, editIndex, editTestIndex);
                    changeTestGrade(courses, editIndex, editTestIndex);
                }
            }
            else if (userEditOpt == "finalexam")
            {
                addNewFinalExam(courses, editIndex);
                editWhichFinalExam(courses, editIndex, editFinalExamIndex);

                if (editFinalExamIndex >= 0 && editFinalExamIndex < courses[editIndex].finalexams.size())
                {
                    changeFinalExamName(courses, editIndex, editFinalExamIndex);
                    changeFinalExamGrade(courses, editIndex, editFinalExamIndex);
                }
            }

            clear();
        }

        // If the user wishes to delete a course.
        else if (userOption == "3" && courses.empty() == false)
        {
            string userDelOpt;
            int delIndex = -1;
            int delAssignmentIndex = -1;
            int delTestIndex = -1;
            int delFinalExamIndex = -1;

            deleteWhichCourse(courses, delIndex);

            // Only proceed if a course was selected
            if (delIndex >= 0 && delIndex < courses.size())
            {
                userDelOpt = checkDelOpt(courses, delIndex);

                if (userDelOpt == "course")
                {
                    deleteCourse(courses, delIndex);
                }
                
                else if (userDelOpt == "assignment")
                {
                    if (!courses[delIndex].assignments.empty())
                    {
                        deleteWhichAssignment(courses, delIndex, delAssignmentIndex);
                        if (delAssignmentIndex >= 0 && delAssignmentIndex < courses[delIndex].assignments.size())
                        {
                            deleteAssignment(courses, delIndex, delAssignmentIndex);
                        }
                    }
                    else
                    {
                        cout << "No assignments exist for this course. Please add assignments first.\n" << endl;
                        wait(1.0);
                    }
                }
                
                else if (userDelOpt == "test")
                {
                    if (!courses[delIndex].tests.empty())
                    {
                        deleteWhichTest(courses, delIndex, delTestIndex);
                        if (delTestIndex >= 0 && delTestIndex < courses[delIndex].tests.size())
                        {
                            deleteTest(courses, delIndex, delTestIndex);
                        }
                    }
                    
                    else
                    {
                        cout << "No tests exist for this course. Please add tests first.\n" << endl;
                        wait(1.0);
                    }
                }
                
                else if (userDelOpt == "finalexam")
                {
                    if (!courses[delIndex].finalexams.empty())
                    {
                        deleteWhichFinalExam(courses, delIndex, delFinalExamIndex);
                        if (delFinalExamIndex >= 0 && delFinalExamIndex < courses[delIndex].finalexams.size())
                        {
                            deleteFinalExam(courses, delIndex, delFinalExamIndex);
                        }
                    }
                    
                    else
                    {
                        cout << "No final exams exist for this course. Please add final exams first.\n" << endl;
                        wait(1.0);
                    }
                }
            }
            clear();
        }

        // If a user wishes to calculate their average(s).
        else if (userOption == "4" && courses.empty() == false)
        {
            // Reset values for each calculation
            float overallGrade = 0;
            int validCourseCount = 0;

            cout << "\n----- GRADE CALCULATION -----\n\n";
            for (int i = 0; i < courses.size(); i++)
            {
                float assignmentGrade = 0;
                float testGrade = 0;
                float finalGrade = 0;

                // Track if each component has values and their original weights
                bool hasAssignments = !courses[i].assignments.empty();
                bool hasTests = !courses[i].tests.empty();
                bool hasFinals = !courses[i].finalexams.empty();
                float weightSum = 0;

          

                // Calculate assignment average if assignments exist
                if (hasAssignments)
                {
                    for (int j = 0; j < courses[i].assignments.size(); j++)

                    {
                        assignmentGrade += courses[i].assignments[j].grade;
                    }

                    assignmentGrade = assignmentGrade / courses[i].assignments.size();
                    weightSum += courses[i].weight[0];
                }
          
                // Calculate test average if tests exist
                if (hasTests)
                {
                    for (int j = 0; j < courses[i].tests.size(); j++)
                    {
                        testGrade += courses[i].tests[j].grade;
                    }

                    testGrade = testGrade / courses[i].tests.size();
                    weightSum += courses[i].weight[1];
                }

                // Calculate final exam average if finals exist
                if (hasFinals)
                {
                    for (int j = 0; j < courses[i].finalexams.size(); j++)
                    {
                        finalGrade += courses[i].finalexams[j].grade;
                    }

                    finalGrade = finalGrade / courses[i].finalexams.size();
                    weightSum += courses[i].weight[2];
                }

                // Calculate weighted course grade only if at least one component exists
                if (hasAssignments || hasTests || hasFinals)
                {
                    // Check if we have a non-zero weight sum to avoid division by zero
                    if (weightSum > 0)
                    {
                        // Calculate the weighted average using only components that exist and weights based on available components
                        courses[i].grade = 0;

                        if (hasAssignments)
                        {
                            courses[i].grade += (assignmentGrade * courses[i].weight[0] / weightSum);
                        }

                        if (hasTests)
                        {
                            courses[i].grade += (testGrade * courses[i].weight[1] / weightSum);
                        }

                        if (hasFinals)
                        {
                            courses[i].grade += (finalGrade * courses[i].weight[2] / weightSum);
                        }

                        cout << i + 1 << ". " << courses[i].name << ": " << fixed << setprecision(2) << (courses[i].grade * 100) << "%";
          
                        // Optionally show which components were used in calculation
                        cout << " (Using: ";
                        if (hasAssignments)
                        {
                            cout << "Assignments ";
                        }

                        if (hasTests)
                        {
                            cout << "Tests ";
                        }

                        if (hasFinals)
                        {
                            cout << "Finals";
                        }
                        cout << ")\n";
          
                        overallGrade += courses[i].grade;
                        validCourseCount++;
                    }

                    else
                    {
                        cout << i + 1 << ". " << courses[i].name << ": Weights not set properly\n";
                    }
                }

                else
                {

                    cout << i + 1 << ". " << courses[i].name << ": No grades to calculate\n";
                }
            }
            cout << endl;
          
            // Calculate overall average only if there are valid courses
            if (validCourseCount > 0)
            {
                overallGrade = overallGrade / validCourseCount;
                cout << "Overall Average: " << fixed << setprecision(2) << (overallGrade * 100) << "%\n" << endl;
            }

            else
            {
                cout << "No courses with grades to calculate overall average.\n" << endl;
            }
         
            // Wait for user input before returning to menu
            cout << "Press Enter to continue...";
            cin.ignore();
            string temp;
            getline(cin, temp);

            clear();
        }

        // If the user wishes to exit the program.
        else if (userOption == "5")
        {
            exit = true;
        }

        else
        {
            cout << "Error! Please enter an appropriate input! [1-5]\n" << endl;
            wait(1.35);
            clear();
        }
    }

    clear();
    goodbye();
    wait(1.35);

    return 0;
}

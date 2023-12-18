//============================================================================
// Name        : ProjectTwo.cpp
// Author      : ML
// Version     : 1.0
// Description : ABCU Course Information Program
//============================================================================

#include <algorithm>
#include <iostream>
#include <fstream>
#include <time.h>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Global variables
bool isCSVLoaded = false; // used in loadCourses() and main() to check if file is loaded

// Define a structure to hold course information
struct Course {
    string courseNumber; // unique identifier
    string courseName;
    vector<string> prereqs;
};

// Load a CSV file containing courses into a vector
void loadCourses(string csvPath, vector<Course>& courses) {
    string line;

    // Loads CSV File
    cout << "Loading CSV file " << csvPath << endl;

    ifstream inFS(csvPath);

    if (!inFS.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    while (getline(inFS, line)) {
        Course course;
        stringstream ss(line);
        string token;

        // Splitting by commas and storing course details
        // Course Number (e.g. CSCI200)
        getline(ss, token, ','); 
        course.courseNumber = token;

        // Course Name (e.g. Discrete Mathematics)
        getline(ss, token, ','); 
        course.courseName = token;

        // Gets prerequisites and adds them to the prereqs vector
        while (getline(ss, token, ',')) {
            course.prereqs.push_back(token);
        }

        // adds the course to the courses vector
        if (!course.courseNumber.empty() && !course.courseName.empty()) {
            courses.push_back(course);
        }

        // error checking if a course doesn't have a course number or name
        else { 
            cout << "Invalid course found. Skipping..." << endl;
        }
        isCSVLoaded = true;
    }

    inFS.close();
}

// Prints a single course's information to the console
void printCourse(Course course) {
    cout << course.courseNumber << " - " << course.courseName << endl;
    return;
}

// Prints a course's prerequisites
void printPrereqs(Course course, const vector<Course>& courses) {
    cout << "Prerequisites: ";
    if (!course.prereqs.empty()) {
        for (size_t i = 0; i < course.prereqs.size(); ++i) {
            // iterates through course list to ensure prerequisite course exists
            for (const auto& loadedCourse : courses) { 
                if (course.prereqs[i] == loadedCourse.courseNumber) {
                    // prints the prerequisites separated by a space
                    cout << loadedCourse.courseNumber;
                    if (i != course.prereqs.size() - 1) {
                        cout << " ";
                    }
                    break; // goes to next prerequisite
                }
            }
        }
    }
    else {
        cout << "None.";
    }
    cout << endl;
}


// Partitioning function for quicksort algorithm
int partition(vector<Course>& courses, int begin, int end) {
    int low = begin;
    int high = end;

    string pivot = courses[low + (high - low) / 2].courseNumber;

    while (low < high) {
        while (courses[low].courseNumber.compare(pivot) < 0) {
            ++low;
        }
        while (courses[high].courseNumber.compare(pivot) > 0) {
            --high;
        }
        if (low < high) {
            std::swap(courses.at(low), courses.at(high));
            ++low;
            --high;
        }
    }
    return high;
}

// Performs a Quicksort on course's course number
void quickSort(vector<Course>& courses, int begin, int end) {
    int mid = 0;

    //If there are 1 or zero courses to sort, partition is already sorted
    if (begin >= end) {
        return;
    }

    /* Partition courses into low and high such that
     midpoint is location of last element in low */
    mid = partition(courses, begin, end);
    // recursively sort low partition (begin to mid)
    quickSort(courses, begin, mid);
    // recursively sort high partition (mid+1 to end)
    quickSort(courses, mid + 1, end);
}

// Main method
int main(int argc, char* argv[]) {
    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input.csv"; 
        // TODO: Real program should prompt user for csv file.
    }

    // Define a vector to hold all the courses
    vector<Course> courses;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Course Data from CSV file" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course Information" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading courses
            ticks = clock();

            // ask user for csv path
            cout << "Type in the csv path: (e.g. ABCU_Advising_Program_Input.csv) ";
            cin >> csvPath;

            // complete the method call to load the courses
            loadCourses(csvPath, courses);

            cout << courses.size() << " courses loaded." << endl;
            

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Print Course List
            // Performs Quick Sort to sort courses alphanumerically
            if (!isCSVLoaded) {
                cout << "Please load data first." << endl;
            }

            else {
                cout << "Sorting courses...";
                ticks = clock();
                quickSort(courses, 0, courses.size() - 1);
                ticks = clock() - ticks;
                cout << "Sorted. Time elapsed: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                cout << "Printing course list..." << endl;


                // Print the list
                for (int i = 0; i < courses.size(); ++i) {
                    printCourse(courses[i]);
                }
                cout << endl;
            }
            break;

        case 3:
            // print course information
            if (!isCSVLoaded) {
                cout << "Please load data first." << endl;
            }

            else {
                string userCourse;
                cout << "Enter course number: ";
                cin >> userCourse;

                bool found = false;
                for (const auto& course : courses) {
                    if (course.courseNumber == userCourse) {
                        printCourse(course);
                        printPrereqs(course, courses);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Course not found." << endl;
                }
                break;
            }
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

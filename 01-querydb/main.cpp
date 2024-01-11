#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <string>
#include "testdb.h"
#include "studentrecord.h"
using namespace std;

int findArg(int argc, char *argv[], string pattern);


/*
 *
 * The user can pass the following parameters to this application:
 *
 * -db <database file>          Specifies the path to the database file (required)
 * -showAll                     Writes all records to the terminal
 * -sid <student ID> [-n|-g|-p] Writes the record with a specific student ID (integer).
 *                              By default, this displays the complete record
 *                              Add one of the following to reduce the information
 *                                 -n       Just display the name
 *                                 -g       Just display the mode codes and grades
 *                                 -p       Just display the phone number
 *
 * ****************
 * *** EXAMPLES ***
 * ****************
 * querydb                                  Creates an example database computing.txt (done for you)
 * querydb -db computing.txt -showAll       Displays all records in the database computing.txt (done for you)
 * querydb -db computing.txt -sid 12345     Displays the complete record for student with ID 12345 (done for you)
 *
 * ********* The above three examples are already implemented, but not fully tested *********
 *
 * For the -sid option, you can further narrow down the information displayed (not yet implemented)
 *
 * ****************
 * *** EXAMPLES ***
 * ****************
 * 
 * querydb -db computing.txt -sid 12345 -n      Displays only the name for student with ID 12345, or an error if not found
 * querydb -db computing.txt -sid 12345 -g      Displays only the module codes and grades for student with ID 12345, or an error if not found
 * querydb -db computing.txt -sid 12345 -p      Displays only the phone number for student with ID 12345, or an error if not found
 * querydb -db computing.txt -sid 12345 -n -p   Display both the name and the phone number for student with ID 12345
 * 
 * *************
 * *** NOTES ***
 * *************
 * 
 * o You should test the existing application first and verify which of the above is already complete.
 * o The -n, -g and -p switches have not yet been implemented (this is your task).
 * o You need to handle error conditions, and inform the user appropriately.
 * o Errors should be communicated with the user.
 * o No tag should be repeated (e.g. you cannot specify -sid twice).
 * o Open files should always be closed before the program exits.
 * o You do not have to use Object Orientated Programming in this task, but it is recommended.
 * o Try to write your code such that is can be reused in other tasks.
 * o Code should be consistently indented and commented
*/


int main(int argc, char *argv[])
{
// argv is an array of strings, where argv[0] is the path to the program, argv[1] is the first parameter, ...
// argc is the number of strings in the array argv
// These are passed to the application as command line arguments
// Return value should be EXIT_FAILURE if the application exited with any form of error, or EXIT_SUCCESS otherwise
    if (argc == 1) {
        cout << "querydb (c)2023" << endl;
        createTestDB("computing.txt");
        return EXIT_SUCCESS;
    }

    string dataBaseName;
    int p = findArg(argc, argv, "-db");
    if (p) {
        dataBaseName = argv[p+1];
        cout << "Data base: " << dataBaseName << "\n";
    } else {
        cout << "Please provide a database with -db <filename>\n";
        return EXIT_FAILURE;
    }

    ifstream ip(dataBaseName);
    if (!ip.is_open()) {
        cout << "Cannot open file " << dataBaseName << "\n";
        return EXIT_FAILURE;
    }

    vector<Record> db;

    enum state_t {START, NEXTTAG, RECORD, SID, NAME, ENROLLMENTS, GRADES, PHONE};
    state_t state = START;

    map<string,state_t> nextState = {
        {"#RECORD", RECORD},
        {"#SID", SID},
        {"#NAME", NAME},
        {"#ENROLLMENTS", ENROLLMENTS},
        {"#GRADES", GRADES},
        {"#PHONE", PHONE}
    };

    try {
        string nextLine;
        string nextStr;
        int recordNumber = -1;
        Record nextRecord;
        stringstream moduleCodes;
        stringstream moduleGrades;
        string moduleCode = "";
        string moduleGrade = "";

        while (getline(ip, nextLine)) {
            string nextStr = regex_replace(nextLine, regex("^ +"), "");

            if (nextStr.empty()) continue;

            switch (state) {
            case START:
                if (nextStr != "#RECORD") {
                    throw runtime_error("Expected #RECORD as the first tag");
                }
                state = RECORD;
                recordNumber = 0;
                break;
            case RECORD:
                if (recordNumber > 0) {
                    db.push_back(nextRecord);
                    nextRecord = {0};
                }
                recordNumber++;
            case NEXTTAG:
                state = nextState[nextStr];
                break;
            case SID:
                nextRecord.SID = stoi(nextStr);
                state = NEXTTAG;
                break;
            case NAME:
                nextRecord.name = nextStr;
                state = NEXTTAG;
                break;
            case ENROLLMENTS:
                moduleCodes = stringstream(nextStr);
                while (moduleCodes.eof() == false) {
                    moduleCodes >> moduleCode;
                    if (moduleCodes.fail()) {
                        break;
                    }
                    nextRecord.enrollments.push_back(moduleCode);
                }
                state = NEXTTAG;
                break;
            case GRADES:
                moduleGrades = stringstream(nextStr);
                while (moduleGrades.eof() == false) {
                    moduleGrades >> moduleGrade;
                    if (moduleGrades.fail()) {
                        break;
                    }
                    nextRecord.grades.push_back(stof(moduleGrade));
                }
                state = NEXTTAG;
                break;
            case PHONE:
                nextRecord.phone = nextStr;
                state = NEXTTAG;
                break;
            }

        }

        if (nextRecord.SID > 0) {
            db.push_back(nextRecord);
        }

        ip.close();
    } catch (exception& e) {
        ip.close();
        cout << "Error reading data" << endl;
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    if (findArg(argc, argv, "-showAll")) {
        for (Record& r : db) {
            printRecord(r);
            cout << endl;
        }
    }

        p = findArg(argc, argv, "-sid");
    if (p) {
        if (p == (argc-1)) {
            cerr << "Please provide a student ID after -sid " << endl;
            return EXIT_FAILURE;
        }

        string strID = argv[p+1];

        int sid;
        try {
            sid = stoi(strID);
            bool found = false;
            for (const Record& r : db) {
                if (r.SID == sid) {
                    if (findArg(argc, argv, "-n")) {
                        cout << "NAME:" << endl;
                        cout << "   " << r.name << endl;
                    } else if (findArg(argc, argv, "-g")) {
                        cout << "ENROLLMENTS:" << endl;
                        cout << "   ";
                        for (size_t i = 0; i < r.enrollments.size(); i++) {
                            cout << r.enrollments[i] << " " << r.grades[i] << " ";
                        }
                        cout << endl;
                    } else if (findArg(argc, argv, "-p")) {
                        if (!r.phone.empty()) {
                            cout << "PHONE:" << endl;
                            cout << "   " << r.phone << endl;
                        } else {
                            cout << "No phone number for student with SID=" << sid << endl;
                        }
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "No record with SID=" << strID << " was found" << endl;
            }

        } catch (exception& e) {
            cout << "Please provide a student ID as an integer" << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int findArg(int argc, char *argv[], string pattern) {
    for (int n = 1; n < argc; n++) {
        string s1(argv[n]);
        if (s1 == pattern) {
            return n;
        }
    }
    return 0;
}

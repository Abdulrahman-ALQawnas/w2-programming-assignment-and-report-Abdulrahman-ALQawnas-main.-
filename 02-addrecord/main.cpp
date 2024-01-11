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


/*
 * Adds a NEW user to the end of an existing database file or the start of a new file
 *
 * The user can pass the following parameters to this application:
 *
 * addrecord -db <database file> [-sid <id> -name <name> [-phone <phone-number>] [-modulecodes <code1> <code2> ... <codeN> [-grades <grade1> <grade2> ... <gradeM> ]]]
 *
 * addrecord
 *  Without any parameters, this creates an example database file computing.txt (already done for you)
 *
 * The -db <database file> parameters are ALWAYS required if you wish to add a record.
 *  If the file does not exist, it should be created (as an empty database)
 * 
 * Where -sid is provided.
 *    • A numerical student ID <id> MUST also be provided.
 *       o <id> must be an unsigned integer. 
 *       o <id> must be unique. If another record in the database has the same value, an error should be reported.
 * 
 * Where -sid is provided, the following MUST also be included:
 *    • The tag -name and a student name <name>.
 *       o <name> is a full name, so will comprise only alphabetical characters and spaces.
 *       o <name> must contain at least two words separated by spaces.
 * 
 * Where -sid is provided, the following MAY also be included:
 *    • The tag -phone followed by a phone number.
 *      o <phone-number> is a string with no spaces.
 *    • The tag -modulecodes, followed by a list of module codes.
 *       o Each module code is a single alpha-numeric word. It cannot contain any symbols.
 *       o Each module code is separated by a space.
 *       o There must be at least one module code provided.
 *    • IF a -modulecodes tag is provided, the following MAY also be provided:
 *       o The tag -grades, followed by a list of grades.
 *       o Each grade must be a fractional number.
 *       o Each grade must be separated by a space.
 *       o The number of grades MUST match the number of module codes.
 *       o You cannot use -grades tag without an accompanying -modulecodes tag
 * 
 *
 * **********************
 * *** VALID EXAMPLES ***
 * **********************
 *
 * Create an empty database file computing.txt
 *  addrecord -db computing.txt
 * 
 * Add a record with a student ID <id> and name <name>, where <id> is an integer and name <name> is a string (space separated)
 *  addrecord -db computing.txt -sid 12345 -name Sam Eold
 *
 * This version also includes the phone number <phone>, where <phone> is a string with no spaces
 *  addrecord -db computing.txt -sid 12345 -name Sam Eold -phone 44-1234-456123
 *
 * This version includes the modules the student is enrolled on
 *  addrecord -db computing.txt -sid 13579 -name Les Sismore -modulecodes COMP101 COMP110 COMP123 COMP145 COMP165
 *
 * This includes the grades as well as the module codes. The number of grades must equal the number of codes or an error is displayed
 *  addrecord -db computing.txt -sid 24680 -name Jo King -modulecodes COMP101 COMP110 COMP123 COMP145 COMP165 -grades 40.5 55.6 35.7 67.5 80.1
 *
 *
 * *************************************
 * *** EXAMPLES OF INVALID ARGUMENTS ***
 * *************************************
 *
 *  Missing the database filename
 *   addrecord -db -sid 12345 -name Sam Eold
 *
 *  Name is missing
 *   addrecord -db computing.txt -sid 12345
 *
 *  -sid is missing
 *   addrecord -db computing.txt -name Sam Eold
 *
 *  <id> is not an integer
 *   addrecord -db computing.txt -sid a2345 -name Sam Eold
 *
 *  phone number cannot contain spaces
 *   addrecord -db computing.txt -sid 12345 -name Sam Eold -phone 44 01234 456123
 *
 *  grades cannot be provided without module codes
 *   addrecord -db computing.txt -sid 24680 -name Jo King -grades 40.5 55.6 35.7 67.5 80.1
 *
 *  Number of module codes and grades do not match
 *  addrecord -db computing.txt -sid 24680 -name Jo King -modulecodes COMP101 COMP110 -grades 40.5 55.6 35.7
 *
 * *************
 * *** NOTES ***
 * *************
 * 
 * o The verb ADD implies you are created a new object. The object in this context is a student record.
 *  o You cannot add a student record that already exists
 *  o To add data to a student record that already exist, see task C
 * 
 * o Errors should be communicated with the user
 * o No tag should be repeated (e.g. you cannot specify -sid twice)
 * o New records should be added to the end of the database file (known as appending). See the labs on FileIO and ios::app
 * o Open files should always be closed before the program exits
 * o You may copy or (better) reuse code from Task A where possible
 * o Code should be consistently indented and commented
*/

// Main program here - you may shared / reuse as much code as you like with other projects included in this starter code
// Function to check if a file exists
bool fileExists(const string& fileName) {
    ifstream file(fileName);
    return file.good();
}



int main(int argc, char *argv[])
{
    // argv is an array of strings, where argv[0] is the path to the program, argv[1] is the first parameter, ...
    // argc is the number of strings in the array argv
    // These are passed to the application as command line arguments
    // Return value should be EXIT_FAILURE if the application exited with an error, or EXIT_SUCCESS otherwise

    if (argc == 1) {
        //Welcome message
        cout << "addrecord (c)2023" << endl;

        //Create some test data
        createTestDB("computing.txt");

        //Done
        return EXIT_SUCCESS;
    }

    Record s;
	
	// Check if the specified database file exists
    string databaseFileName;
    bool showAllFlag = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        
        if (arg == "-db" && i + 1 < argc) {
            databaseFileName = argv[i + 1];
            i++;  // Skip the next argument
        } else if (arg == "-showAll") {
            showAllFlag = true;
        }
    }

    if (!fileExists(databaseFileName)) {
        cerr << "Error: Cannot open file " << databaseFileName << endl;
        return EXIT_FAILURE;
    }
    //return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


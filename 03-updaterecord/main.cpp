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
 * Updates an EXISTING user in an existing database file
 *
 * The user can pass the following parameters to this application:
 * 
 *  updaterecord -db <database file> -sid <id> [-name <name>] [-phone <phone-number>] [-modulecode <code> -grade <grade>]
 *
 *  updaterecord
 *   Without any parameters, this creates an example database file computing.txt (already done for you)
 *
 *  The -db <database file> parameters are ALWAYS required if you wish to update any records.
 *   If the file does not exist, it should be created (as an empty database)
 * 
 *  When -sid parameter is provided, you must also provide an integer <id>.
 *   The <id> must match a record in the database file.
 * 
 *  The following properties are optional, and may be provided to update data for a given student with id <sid>:
 *
 *   o The student name can be updated with the -name tag. The value <name> is a string, composed of at least two words, separated by spaces. This should replace the existing name
 * 
 *   o The phone number can be added OR updated by specifying the -phone parameter followed by a new phone number. 
 * 
 *   o An individual student grade can be added OR updated using the -modulecode and -grade parameters together.
 *
 * Note that the format of all data items should be consistent with those specified in the previous tasks.
 * The same error checking should also apply.
 *
 * **********************
 * *** VALID EXAMPLES ***
 * **********************
 *
 *
 * Create an empty database file computing.txt
 *  updaterecord -db computing.txt
 * 
 * update the phone number of a record with a student ID 12345
 *  updaterecord -db computing.txt -sid 12345 -phone 00-12-34567
 *
 * update the name and phone number of a record with a student ID 12345
 *  updaterecord -db computing.txt -sid 12345 -phone 00-12-34567 -name Jo Kingly Blunte
 *
 * update (or add) the COMP1001 grade for student with id 12345
 *  updaterecord -db computing.txt -sid 12345 -modulecode COMP1001 -grade 78.4
 *
 * Enrol the student in COMP1001 for student with id 12345
 *  updaterecord -db computing.txt -sid 12345 -modulecode COMP1001
 *
 * **********************
 * *** INVALID EXAMPLES *
 * **********************
 * 
 *  Examples of invalid parameters include:
 *
 *  Missing the database tag
 *   updaterecord -sid 12345
 *
 *  ID does not exist (assuming there is no record with ID 99999)
 *   updaterecord -db computing.txt -sid 99999 -modulecode COMP1001 -grade 78.4
 *
 *  Missing module code
 *   updaterecord -db computing.txt -sid 12345 -grade 78.4
 * 
 *  Spaces in the phone number
 *   updaterecord -db computing.txt -sid 12345 -phone 00 12 34567 -name Jo Kingly Blunte
 *
 *  Name is missing
 *   updaterecord -db computing.txt -sid 12345 -phone 00-12-34567 -name
 *
 *  Name must have at least 2 words
 *   updaterecord -db computing.txt -sid 12345 -phone 00-12-34567 -name Sam
 * 
 * *************
 * *** NOTES ***
 * *************
 * 
 * o The verb update implies you are changing an existing object. The object in this context is a student record.
 *  o You cannot update a student record that does not exist
 *  o You cannot add a student record with update command
 *  o You can update OR add data within an existing record
 *   o For example, if you update a student phone number and no number is currently held on record, 
 *     then in effect you are adding a phone number.
 * o Errors should be communicated with the user
 * o No tag should be repeated (e.g. you cannot specify -sid twice)
 * o Open files should always be closed before the program exits
 * o Code should be consistently indented and commented
 * o Marks are awarded for reuse of code from Tasks A and/or B (where possible)
 * o Marks are awarded for using Object Orientated Programming to make your code more modular and reusable
*/

// Main program here

// Function to check if a file exists
bool fileExists(const string& fileName) {
    ifstream file(fileName);
    return file.good();
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Welcome message
        cout << "updaterecord (c)2023" << endl;

        // Create some test data
        createTestDB("computing.txt");

        // Done
        return EXIT_SUCCESS;
    }

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


    return EXIT_SUCCESS;
}

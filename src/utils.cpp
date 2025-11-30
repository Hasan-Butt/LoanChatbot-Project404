/*
 * utils.cpp
 * 
 * Description:
 * Contains helper functions for LoanChatbot project, including:
 * - Input validation (isNumber, isNotEmpty, stringToInt)
 * - Range checks (loan amount, tenure, interest rate)
 * - Loan calculations (e.g., simple interest)
 * - Logging of user-chatbot interactions
 * 
 * Responsibilities:
 * - Provide reusable utilities across multiple modules
 * - Keep core chatbot logic clean and modular
 */
#define _CRT_SECURE_NO_WARNINGS // this had to be added to remove the warning of using localtime function something likee that

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include<vector>
#include"application.h"
using namespace std;


const vector<string> IMAGE_EXTENSIONS = { ".jpg", ".jpeg", ".png" }; // for the isImageFile() function.
using namespace std;


// =================== Basic Validation ========================

// Check if a string is numeric
bool isNumber(const string& str) {
    for (int i = 0;i < str.length();i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }
    return true;
}

// Trim String and return corrected
string trimString(string s) {
    int start = 0;
    int end = s.length() - 1;

    // remove leading spaces
    while (start <= end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n' || s[start] == '\r')) {
        start++;
    }

    // remove trailing spaces
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n' || s[end] == '\r')) {
        end--;
    }

    string result = "";
    for (int i = start; i <= end; i++) {
        result += s[i];
    }

    return result;
}


// Check if input is non-empty
bool isNotEmpty(const string& str) {
    string trimmed = trimString(str); // trim spaces from start and end
    return !trimmed.empty();
}

// Convert string to integer safely
int stringToInt(const string& str) {

    if (str.empty())
        return -1;
    if (!isNumber(str))
        return -1;

    long long int value = 0;

    for (int i = 0;i < str.length();i++)
    {
        char character = str[i];
        int number = character - '0';// '5'-'0'= ascii : 53-48=5
        value = value * 10 + number;
    }
    return value;
}

// convert whole string to lower-case
string toLowerString(string s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + 32; // convert to lowercase
        }
    }
    return s;
}



// Remove commas
string removeCommas(string s) {
    string clean = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ',') clean += s[i];
    }
    return clean;
}

//This is what I added to check the spaces 
bool check_spaces(const string& input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        if (input[i] != ' ')
            break;
        i++;
    }

    if (i == input.length() && i != 0) // if i==0 then it means the user only entered enter key wo uper wala while loop chle ga hi nhi, aour aap ne spaces ke liye check hi nhi kiya . then how can you say ke there are all or no spaces jb check hi nhi kiya to? its an empty string. an empty string!="   " a string which has spaces. so i!=0 to handle that thing.
    {
        return true;
    }

    return false;
}
// =================== Range / Domain Checks ===================

// Check if loan amount is valid (>0)
bool isValidAmount(double amount) {
    return(amount > 0);

}

// Check if loan tenure is within 1–30 years
bool isValidTenure(int years) {
    return(years > 0 && years < 31);
}

// Check if interest rate is within 1–100%
bool isValidRate(double rate) {
    return(rate >= 1 && rate <= 100);

}

// Generate 4-digit unique application ID
string generateApplicationID() {
    srand(time(0));
    int id = 1000 + (rand() % 9000); // Random 4-digit number
    return to_string(id);
}

// Get current date in DD-MM-YYYY format
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string day = to_string(ltm->tm_mday);
    string month = to_string(1 + ltm->tm_mon);
    string year = to_string(1900 + ltm->tm_year);
    
    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;
    
    return day + "-" + month + "-" + year;
}
// =================== Loan Calculations ========================

// Simple interest calculation
double calculateSimpleInterest(double principal, double rate, double time) {
    if (principal <= 0 || rate <= 0 || time <= 0) {
        return -1; //   error
    }

    return (principal * rate * time) / 100.0;

}

// ======================== Logging ==============================

// Log user-chatbot interactions to a file
void logInteraction(const string& userInput, const string& botResponse, const string& appID) {
    ofstream file(".\\data\\" + appID + "\\chat_log.txt", ios::app);
    if (file.is_open())
    {
        file << "[" << __TIME__ << "] ";
        file << "USER: " << userInput << " | ";
        file << "BOT: " << botResponse << endl;
        file.close();
    }
}

// ======================= Colors Support =========================
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ======================== Input Validation ======================
// Validate CNIC (13 digits, format: XXXXX-XXXXXXX-X)
bool isValidCNIC(const string& cnic) {
    
    if (cnic.length() != 13)
    {
       // cout << "\nCnic can only be of 13 digits.";
        return false;
    }

    for (int i = 0;i < cnic.length();i++)
    {
        if (cnic[i] < '0' || cnic[i]>'9')
        {
          //  cout << "\nCnic can only contain digits.";
            return false;
        }
    }
    return true;
}

// Validate email format (basic validation)
bool isValidEmail(const string& email) {
    int atPos = -1;
    int dotPos = -1;
    
    // Find @ and . positions
    for (int i = 0; i < email.length(); i++) {
        if (email[i] == '@') {
            if (atPos != -1) return false; // Multiple @
            atPos = i;
        }
        if (email[i] == '.' && atPos != -1) {
            dotPos = i;
        }
    }
    
    // Check basic format: something@something.something
    if (atPos <= 0) return false; // No @ or @ at start
    if (dotPos <= atPos + 1) return false; // No domain
    if (dotPos >= email.length() - 1) return false; // No extension
    
    return true;
}

// Check if string contains only digits
bool isNumeric(const string& str) {
    if (str.empty()) return false;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}


// Validate phone number (10-11 digits)
bool isValidPhone(const string& phone)
{
    int length = phone.length();

    // Length must be either 11 (local) or 13 (international)
    if (!(length == 11 || length == 13))
    {
        cout << "\nInvalid Phone number length!";
        return false;
    }

    // -------------------------------
    // INTERNATIONAL FORMAT: +923XXXXXXXXX
    // -------------------------------
    if (length == 13)
    {
        if (phone[0] != '+')
        {
            cout << "\nInternational phone number must start with '+'!";
            return false;
        }
        if (phone[1] != '9' || phone[2] != '2')
        {
            cout << "\n+92 is the correct Pakistan country code!";
            return false;
        }
        if (phone[3] != '3')
        {
            cout << "\nPakistani mobile numbers start with 3!";
            return false;
        }

        // Remaining must be digits
        for (int i = 4; i < 13; i++)
        {
            if (phone[i] < '0' || phone[i] > '9')
            {
                cout << "\nPhone number should only contain digits after +923!";
                return false;
            }
        }

        return true;
    }

    // -------------------------------
    // LOCAL FORMAT: 03XXXXXXXXX
    // -------------------------------
    if (length == 11)
    {
        if (phone[0] != '0')
        {
            cout << "\nLocal phone number must start with 0!";
            return false;
        }
        if (phone[1] != '3')
        {
            cout << "\nPakistani mobile numbers have '3' after '0'!";
            return false;
        }

        for (int i = 2; i < 11; i++)
        {
            if (phone[i] < '0' || phone[i] > '9')
            {
                cout << "\nPhone number should only contain digits!";
                return false;
            }
        }

        return true;
    }

    return false; // fallback (never reached)
}


// Validate date format (DD-MM-YYYY)
bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    // Extract day, month, year
    string dayStr = date.substr(0, 2);
    string monthStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    // Check if all are numeric
    for (int i = 0; i < 2; i++) {
        if (dayStr[i] < '0' || dayStr[i] > '9') return false;
        if (monthStr[i] < '0' || monthStr[i] > '9') return false;
    }
    for (int i = 0; i < 4; i++) {
        if (yearStr[i] < '0' || yearStr[i] > '9') return false;
    }
    
    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);
    
    // Basic range checks
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 1900 || year > 2100) return false;
    
    // Month-specific day validation
    if (month == 2) {
        // Leap year check
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }
    
    return true;
}


// Check if string contains only letters
bool isAlpha(const string& str) {
    if (str.empty()) return false;
    
    for (int i = 0; i < str.length(); i++) {
        char c = tolower(str[i]);
        if (c != ' ' && (c < 'a' || c > 'z')) {
            return false;
        }
    }
    return true;
}

// Check if string contains only letters and numbers
bool isAlphaNumeric(const string& str) {
    if (str.empty()) return false;
    
    for (int i = 0; i < str.length(); i++) {
        char c = tolower(str[i]);
        if (c != ' ' && (c < 'a' || c > 'z') && (c < '0' || c > '9')) {
            return false;
        }
    }
    return true;
}

bool isImageFile(const string& filepath) {
    size_t dotPos = filepath.find_last_of('.');
    if (dotPos == string::npos)
    {
        cout << "\nNo extension found!";
        return false;
    }               // no extension found
    string extension = filepath.substr(dotPos);
    // Convert to lowercase for case-insensitive comparison
    string lowerExtension = extension;
    for (char& c : lowerExtension)
    {
        c = tolower(c);
    }

    for (const auto& ext : IMAGE_EXTENSIONS)
    {
        if (lowerExtension == ext) {
            return true;
        }
    }
    return false;
}

string removeSurroundingQuotes(string& inputPath)
{

    // Remove surrounding quotes
    while (inputPath.size() >= 2 &&
        inputPath.front() == '"')
    {
        inputPath = inputPath.erase(0, 1);  // str becomes "Hell";
    }

    while (inputPath.size() >= 2 && inputPath.back() == '"')
    {
        inputPath.erase(inputPath.length() - 1);  //str becomes "ello"

    }
    return inputPath;
}

bool checkUserFolderAccess(const string& ImageFilePath) {
    try {
        // Extract directory from the source file path
        size_t pos = ImageFilePath.find_last_of("\\/");
        string sourceDirectory = (pos == string::npos) ? "." : ImageFilePath.substr(0, pos);
        // If no directory in path (like just "image.jpg"), use current directory
        /// do we need this or not? i'm unsure

        if (sourceDirectory.empty()) {
            sourceDirectory = ".";
        }

        string testFile = sourceDirectory + "\\test_write_permission.tmp";
        ofstream file(testFile);
        if (file.is_open()) {
            file.close();
            remove(testFile.c_str());
            return true;
        }
        return false;
    }
    catch (...) {
        return false;
    }
}



bool createApplicantFolder(const string& appID)
{
    // Creates a folder in the folder containing the exe file.

    string Path = "Applications";

    Path = "mkdir " + Path + "\\\\" + appID + " 2>nul"; // (mkdir Applications\\<appID> 2>nul)
    // the 2>nul is added so because . if the folder Applications\\<appID> already existed,it was displaying message on console that it already exists automatically . adding this stops that console message!

    int result = system(Path.c_str()); // result will be 1 is successfully created

    // mkdir returns 0 on success, non-zero on failure
// But if folder already exists, it's also fine
// So we verify if folder exists after running
    ifstream test(Path); // just checking existence
    // We can use stat too
    struct stat st;
    if (stat(Path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR))
    {
        return true; // Folder exists
    }

    return false; // Something went wrong
}

bool createDataFolder(const string& appID)
{
    // Base folder
    string base = ".\\data";

    // Build command
    string command = "mkdir " + base + "\\\\" + appID + " 2>nul";

    // Run command
    int result = system(command.c_str());

    // mkdir returns 0 on success, non-zero on failure
    // But if folder already exists, it's also fine
    // So we verify if folder exists after running
    string folderPath = base + "\\\\" + appID;
    ifstream test(folderPath); // just checking existence
    // We can use stat too
    struct stat st;
    if (stat(folderPath.c_str(), &st) == 0 && (st.st_mode & S_IFDIR))
    {
        return true; // Folder exists
    }

    return false; // Something went wrong
}


string doubleBackslashes(const string& path)
{
    string result;

    for (char c : path)
    {
        result += c;
        if (c == '\\')
            result += '\\';
    }


    return result;
}

bool isValidPath(string& input, const string& applicantID)
{
    //this will validate path then store image in ./data/xxxx and return true
    // returns false if spaces are entered,input is empty,file is not an image,the folder of the image is inaccessible 

    // basically this is copied from readUserInput(); but that function was also converting to lowercase, which shouldn't be done while searching for an image by its name . so i removed that part and used the same code again.

    // TODO: Implement input validation
    if (check_spaces(input) || input == "") // only spaces or empty string
    {
        if (check_spaces(input))
        {
            cout << "\nYou only entered spaces!";
            return false;
        }
        else
        {
            cout << "\nInput is empty!";
            return false;
        }
    }

    // spaces before or after the text
    // .......hi....... will be fixed to hi   [..... represent spaces]
    size_t start = input.find_first_not_of(' '); // checks from left to right ,finds index of the first character that is not a space.
    size_t end = input.find_last_not_of(' '); //  checks from  right to left ,finds index of the first character that is not a space.
    input = input.substr(start, end - start + 1); // this basically makes a new string from the start index to the end-1 index [ which is our actual valid string ] 

    input = removeSurroundingQuotes(input);
    input = doubleBackslashes(input);

    if (!isImageFile(input))
    {
        cout << "\nThis is not an image.";
        return false;
    }

    if (!checkUserFolderAccess(input))
    {
        cout << "\nThe folder you entered is inaccessable!";
        return false;
    }

    // Step 1: Check if source file exists
    if (!ifstream(input))
    {
        cout << "\nError: File not found: " << input << endl;
        return false;
    }

    DWORD attrs = GetFileAttributesA(input.c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        cout << "Error: Path does not exist or is inaccessible: " << input << endl;
        return false;
    }
    if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        cout << "Error: Path is a directory, not a file: " << input << endl;
        return false;
    }



    // Step 3: Create destination directory ./data/xxxx

    string destinationDir = ".\\data\\" + applicantID;

    if (!createDataFolder(applicantID))
    {
        cout << "\nError: Failed to create destination folder!" << endl;
        return false;
    }


    // Step 4: Get filename and create destination path
    string filename;
    {
        size_t pos = input.find_last_of("/\\");
        if (pos == string::npos)
            filename = input;
        else
            filename = input.substr(pos + 1);
    }

    string destinationPath = destinationDir + "\\" + filename;
    // Step 5: Manual file copy
    ifstream src(input, ios::binary);
    ofstream dst(destinationPath, ios::binary);

    if (!src.is_open() || !dst.is_open())
    {
        cout << "\nError: Failed to copy file!" << endl;
        return false;
    }

    // Copy
    dst << src.rdbuf();

    // CLOSE BOTH STREAMS
    src.close();
    dst.close();

    // Verify file exists AND has size > 0
    struct stat st;
    if (stat(destinationPath.c_str(), &st) == 0 && st.st_size > 0)
    {
        return true;
    }
    else
    {
        cout << "\nError: File copy verification failed!" << endl;
        return false;
    }

}


bool isRefreeSame(const Application& app)
{
    // i have considered that cnic ,email and phone is unique for every individual in pakistan becuase same name ,date can be found 
    bool isNumberSame = false, isEmailSame = false, isCNICSame = false, toReturn = true;
    if (app.referenceCNIC[0] == app.referenceCNIC[1])
    {
        isCNICSame = true;
        toReturn = false;
    }

    if (app.referencePhone[0] == app.referencePhone[1])
    {
        isNumberSame = true;
        toReturn = false;
    }

    if (app.referenceEmail[0] == app.referenceEmail[1])
    {
        isCNICSame = true;
        toReturn = false;

    }

    if (isNumberSame)
    {
        cout << "\nNumber of both refrees are same.";
    }
    if (isEmailSame)
    {
        cout << "\nEmails of both refrees are same.";

    }
    if (isCNICSame)
    {
        cout << "\nCNIC of both refrees are same.";
    }

    return toReturn;

}




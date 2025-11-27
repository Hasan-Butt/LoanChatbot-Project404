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
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;


// =================== Basic Validation ========================

// Check if a string is numeric
bool isNumber(const string& str) {
    
}

// Check if input is non-empty
bool isNotEmpty(const string& str) {
   
}

// Convert string to integer safely
int stringToInt(const string& str) {
   
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
	while (input[i]!='\0')
	{
		if (input[i] != ' ')
			break;
		i++;
	}

	if (i == input.length()&&i!=0) // if i==0 then it means the user only entered enter key wo uper wala while loop chle ga hi nhi, aour aap ne spaces ke liye check hi nhi kiya . then how can you say ke there are all or no spaces jb check hi nhi kiya to? its an empty string. an empty string!="   " a string which has spaces. so i!=0 to handle that thing.
	{
		return true;
	}
	
	return false;
}
// =================== Range / Domain Checks ===================

// Check if loan amount is valid (>0)
bool isValidAmount(double amount) {
   
}

// Check if loan tenure is within 1–30 years
bool isValidTenure(int years) {
   
}

// Check if interest rate is within 1–100%
bool isValidRate(double rate) {
   
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
   
}

// ======================== Logging ==============================

// Log user-chatbot interactions to a file
void logInteraction(const string& userInput, const string& botResponse) {
    
}

// ======================= Colors Support =========================
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ======================== Input Validation ======================
// Validate CNIC (13 digits, format: XXXXX-XXXXXXX-X)
bool isValidCNIC(const string& cnic) {
    // Remove dashes for validation
    string digits = "";
    for (int i = 0; i < cnic.length(); i++) {
        if (cnic[i] >= '0' && cnic[i] <= '9') {
            digits += cnic[i];
        }
        else if (cnic[i] != '-') {
            return false; // Invalid character
        }
    }
    
    // Must have exactly 13 digits
    return digits.length() == 13;
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

// Validate phone number (10-11 digits)
bool isValidPhone(const string& phone) {
    string digits = "";
    
    for (int i = 0; i < phone.length(); i++) {
        if (phone[i] >= '0' && phone[i] <= '9') {
            digits += phone[i];
        }
        else if (phone[i] != '-' && phone[i] != ' ' && phone[i] != '+') {
            return false; // Invalid character
        }
    }
    
    // Pakistani numbers: 10-11 digits (with or without country code)
    return (digits.length() >= 10 && digits.length() <= 13);
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


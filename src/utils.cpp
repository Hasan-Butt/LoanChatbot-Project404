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

//This is what I added to check the spaces 
bool check_spaces(string& input)
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

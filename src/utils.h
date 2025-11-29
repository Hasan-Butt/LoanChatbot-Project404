/*
 * utils.h
 *
 * Description:
 * Header file declaring all helper functions for the LoanChatbot project.
 * Provides reusable utilities for input validation, range checks, loan calculations, and logging.
 *
 * Responsibilities:
 * - Validate user inputs (numeric, non-empty)
 * - Check ranges for loan amounts, tenure, and interest rates
 * - Perform basic loan-related calculations (e.g., simple interest)
 * - Log chatbot interactions for debugging or record-keeping
 */
#ifndef UTILS_H
#define UTILS_H
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

//Added colors support
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_CYAN 11
#define COLOR_RED 12
#define COLOR_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15
#define COLOR_GRAY 8
#define COLOR_DARK_CYAN 3

void setColor(int color);
// Basic validation
bool isNumber(const string& str);
bool isNotEmpty(const string& str);
int stringToInt(const string& str);
bool check_spaces(const string& input);
string trimString(string s);
string toLowerString(string s);
string removeCommas(string s);

// Range checks
bool isValidAmount(double amount);
bool isValidTenure(int years);
bool isValidRate(double rate);

// Loan calculations
double calculateSimpleInterest(double principal, double rate, double time);

// Logging
void logInteraction(const string& userInput, const string& botResponse, const string& appID);

// ===== Implementing Validation and utilities EPIC LP4-22 Assigned to Ayub =====
// ===== VALIDATION =====
bool isValidCNIC(const string& cnic);
bool isValidEmail(const string& email);
bool isValidPhone(const string& phone);
bool isValidDate(const string& date);
bool isNumeric(const string& str);
bool isAlpha(const string& str);
bool isAlphaNumeric(const string& str);


bool createApplicantFolder(const string& appID); // works fine
bool createDataFolder(const string& appID); //works fine now

bool isValidPath(string& input, const string& applicantID);// works fine
bool isImageFile(const string& filepath);// working fine
bool checkUserFolderAccess(const string& ImageFilePath);

string doubleBackslashes(const string& path);
string removeSurroundingQuotes(string& inputPath);
string generateApplicationID();
string getCurrentDate();


bool isRefreeSame(const Application& app);

#endif

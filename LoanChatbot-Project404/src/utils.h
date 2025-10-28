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

#include <string>
using namespace std;

// Basic validation
bool isNumber(const string& str);
bool isNotEmpty(const string& str);
int stringToInt(const string& str);

// Range checks
bool isValidAmount(double amount);
bool isValidTenure(int years);
bool isValidRate(double rate);

// Loan calculations
double calculateSimpleInterest(double principal, double rate, double time);

// Logging
void logInteraction(const string& userInput, const string& botResponse);

#endif

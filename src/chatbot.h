/*
 * chatbot.h
 * 
 * Description:
 * Header file declaring all classes for LoanChatbot modules:
 * - ChatbotInput: Handles user input reading and keyword extraction
 * - ChatbotProcessor: Processes input and generates chatbot responses
 * - ChatbotDisplay: Manages formatted output and messages
 * - ChatbotTester: Contains testing and debugging functionality
 * 
 * Notes:
 * - No STL containers are used; dynamic arrays are used instead
 * - Each class is modular for clear separation of concerns
 */
#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>
#include "application.h"
#include <vector>
using namespace std;

// Max number of keywords we can extract
const int MAX_KEYWORDS = 10;

// ----------------------------------Chatbot Input Reading Module--------------------------------
// LP4-7 Assigned to Ayub

class ChatbotInput {
public:
    // Read user input from console
    string readUserInput();
    
    // Validate and sanitize input
    string validateInput(string& input);
    
    // Process input for special commands or keywords
    // keywords: output array to store extracted keywords
    // return: number of keywords extracted

    // LATEST UPDATE WE DONT NEED IT ! 
   // int extractKeywords(const string& input, string keywords[], int maxKeywords = MAX_KEYWORDS);

    // ===== EPIC LP4-11 — INPUT COLLECTION Assigned to Hasan =====

    // Personal Info
    string getFullName();
    string getFatherName();
    string getPostalAddress();
    string getContactNumber();
    string getEmail();
    string getGender();
    string getMaritalStatus();
    int    getDependents();

    // CNIC & Employment
    string getCNIC();
    string getCNICExpiry();
    string getEmploymentStatus();

    // Financial Info
    long long getAnnualIncome();
    long long getAvgBill();
    long long getCurrentMonthBill();

    // Existing Loan (conditional)
    bool   askHasExistingLoan();
    long long getExistingLoanAmount();
    long long getAmountReturned();
    long long getAmountDue();
    string getExistingLoanBank();
    string getExistingLoanCategory();

    // References
    string getReferenceName(int refIndex);
    string getReferenceCNIC(int refIndex);
    string getReferenceDate(int refIndex);
    string getReferencePhone(int refIndex);
    string getReferenceEmail(int refIndex);

    // File uploads (paths) // AYUB BUTT 
    string getCNICFrontPath(const string& userID);
    string getCNICBackPath(const string& userID);
    string getElectricityBillPath(const string& userID);
    string getSalarySlipPath(const string& userID);
    

};

// ---------------------------------Chatbot Response Processing Module----------------------------
// LP4-8 Assigned to Kabeer
class ChatbotProcessor {
public:
    // Process user input and generate appropriate response
    string generateResponse(const string& input, string filename = "data/Utterances.txt");

    // ===== EPIC LP4-17 — INSTALLMENT PLAN GENERATION Assigned to Haider =====
    void generateInstallmentSchedule(
        int installments,
        long long price,
        long long downPayment,
        const string& startMonth
    );
    string getNextMonth(const string& current);
};

// --------------------------------------Display/Output Module--------------------------------------
// LP4-9 Assigned to Hasan
class ChatbotDisplay {
public:
    // Display chatbot response with formatting
    void displayResponse(const string& response);
    
    // Show welcome message and instructions
    void showWelcomeMessage();
    
    // Display error messages
    void showError(const string& errorMessage);
    
    // Format and style output text
    string formatOutput(const string& text);

    // ===== DISPLAY FOR EPIC LP4-20 Assigned to Kabeer =====
    void showApplicationSummary(Application &app);

};


// ===== File and Folder Utilities EPIC LP4-22 Assigned to Ayub =====
class ChatbotStorage {
public:
    // Saves the full application details into its folder
    bool saveApplicationToFile(Application app);
    int countApplicationsByCNIC(const string& cnic, const string& status = "");
    vector<Application> getApplicationsByCNIC(const string& cnic);
    Application getApplicationByID(const string& appID);
};

// --------------------------------------Testing and Debug Module-----------------------------------
//LP4-10 Assigned to Haider
class ChatbotTester {
public:
    // Test input processing functionality
    bool testInputProcessing();
    
    // Test response generation
    bool testResponseGeneration();
    
    //Testing on file for home loan
    bool testHomeLoanData();

    // Validate response accuracy
    bool validateResponse(const string& input, const string& expectedOutput);
    
    // Log debug information
    void logDebugInfo(const string& debugInfo);
};

#endif

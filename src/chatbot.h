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
    int extractKeywords(const string& input, string keywords[], int maxKeywords = MAX_KEYWORDS);

};

// ---------------------------------Chatbot Response Processing Module----------------------------
// LP4-8 Assigned to Kabeer
class ChatbotProcessor {
public:
    // Process user input and generate appropriate response
    string generateResponse(const string& input, string filename = "data/Utterances.txt");
    
    // Analyze input sentiment/intent
    string analyzeIntent(const string& input);
    
    // Handle loan-related queries
    string processLoanQuery(const string keywords[], int keywordCount);
    
    // Get contextual information for response
    string getContextInfo(const string& query);
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

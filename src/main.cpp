/*
 * main.cpp
 * 
 * Description:
 * This is the driver file for the LoanChatbot project.
 * It initializes the main chatbot components (input, processor, display, and tester),
 * shows the welcome message, and runs the main interaction loop.
 * 
 * Responsibilities:
 * - Initialize all chatbot modules
 * - Display the welcome message and instructions to the user
 * - Start the main chatbot loop for continuous user interaction
 * - Serve as the entry point of the program
 * 
 * Notes:
 * - The main logic of reading input, generating responses, and displaying output
 *   is handled in the respective modules (ChatbotInput, ChatbotProcessor, ChatbotDisplay)
 * - This file orchestrates the workflow but contains minimal business logic itself
 */

#include "chatbot.h"
#include <iostream>
#include "lender_dashboard.h"
#include <windows.h>
#include "utils.h"

void showWelcomeMessage(){
    ChatbotDisplay display;
    display.showWelcomeMessage();
}

// Run all test functions
void runAllTests()
{
    ChatbotTester tester;

    //Small delay with dots animation
    cout << "Starting Tests";
    for(int i=0; i<3; i++){
        cout<<".";
        Sleep(1000);
    }
    cout<<endl;

    tester.testInputProcessing();
    tester.testResponseGeneration();
    tester.testHomeLoanData();

    setColor(COLOR_BLUE);
    cout << "\nAll Tests Completed!" << endl<<endl;
     setColor(COLOR_WHITE);
}

//Main Chatbot Loop that Handles continuous flow 
void ChatbotEventsHandler(){
    ChatbotInput input;
    ChatbotProcessor processor;
    ChatbotDisplay display;
    ChatbotTester tester;
    
    setColor(COLOR_CYAN);      
    cout << "===========================================================\n";
    setColor(COLOR_YELLOW);
    cout << "\n";
    cout << "      _     ___    _    _   _ __  __    _  _____ _____ \n";
    cout << "     | |   / _ \\  / \\  | \\ | |  \\/  |  / \\|_   _| ____|\n";
    cout << "     | |  | | | |/ _ \\ |  \\| | |\\/| | / _ \\ | | |  _|  \n";
    cout << "     | |__| |_| / ___ \\| |\\  | |  | |/ ___ \\| | | |___ \n";
    cout << "     |_____\\___/_/   \\_\\_| \\_|_|  |_/_/   \\_\\_| |_____|\n";
    cout << "\n";

    setColor(COLOR_YELLOW);
    cout << "           Your Smart Partner for Smarter Loans\n";
    setColor(COLOR_CYAN);
    cout << "===========================================================\n";

    while (true) {

        setColor(COLOR_YELLOW);        // User’s label color
        cout << "You: ";
        setColor(COLOR_WHITE);
        string user = input.readUserInput();

        // exit command
        if (user == "exit" || user == "quit") {
            cout << "\nExiting LoanMate. Goodbye!\n";
            break;
        }

         // ask for tests
        if (user == "run tests") {
            runAllTests();
            continue;
        }

         // get response from processor (uses default filename from header)
        string response = processor.generateResponse(user);

        // if empty string returned, treat as generic fallback
        if (response.empty()) {
            response = "Sorry, I couldn't process that right now.";
        }

        display.displayResponse(response);
    }
}

int main() {

    showWelcomeMessage();
    ChatbotEventsHandler();
    // LenderDashboard dashboard;
    // dashboard.run();

    return 0;
}

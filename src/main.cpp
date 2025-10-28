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

//Main Chatbot Loop that Handles continuous flow 
void mainChatbotLoop(){
    
}

int main() {
    // Initialize chatbot components
    ChatbotInput input;
    ChatbotProcessor processor;
    ChatbotDisplay display;
    ChatbotTester tester;

    // Show welcome message
    display.showWelcomeMessage();

    

    return 0;
}

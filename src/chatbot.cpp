/*
 * chatbot.cpp
 *
 * Description:
 * Implements all functions declared in chatbot.h.
 * Contains module skeletons for input reading, response processing, display, and testing.
 *
 * Responsibilities:
 * - Implement ChatbotInput functions (reading, validation, keyword extraction)
 * - Implement ChatbotProcessor functions (response generation, loan query handling)
 * - Implement ChatbotDisplay functions (show messages, format output)
 * - Implement ChatbotTester functions (testing input and responses, logging debug info)
 *
 * Notes:
 * - Functions are currently skeletons for incremental implementation
 */
#include "chatbot.h"
#include "utils.h"
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <iostream>
using namespace std;

// ----------------------------------Chatbot Input Reading Module--------------------------------
// LP4-7 Assigned to Ayub

string ChatbotInput::readUserInput()
{
    string response;
    getline(cin, response);
    response = validateInput(response);
    return response;
}

string ChatbotInput::validateInput(string& input) {
    // TODO: Implement input validation
    while (check_spaces(input) || input == "") // only spaces or empty string
    {
        if (check_spaces(input))
        {
            system("cls");
            cout << "string contains only spaces! \n";
            getline(cin, input);
        }
        else
        {
            system("cls");
            cout << "empty string! \n";
            getline(cin, input);
        }
    }

    // spaces before or after the text
    // .......hi....... will be fixed to hi   [..... represent spaces]
    size_t start = input.find_first_not_of(' '); // checks from left to right ,finds index of the first character that is not a space.
    size_t end = input.find_last_not_of(' '); //  checks from  right to left ,finds index of the first character that is not a space.
    input = input.substr(start, end - start + 1); // this basically makes a new string from the start index to the end-1 index [ which is our actual valid string ] 

    // making it lower case for comparison
    int i = 0;
    while (i < input.length())
    {
        char c = input[i];
        c = tolower(c);
        input[i] = c;
        i++;
    }
    return input;
}

int ChatbotInput::extractKeywords(const string& input, string keywords[], int maxKeywords) {
    // TODO: Implement keyword extraction and return count
}


// ---------------------------------Chatbot Response Processing Module----------------------------
// LP4-8 Assigned to Kabeer

string ChatbotProcessor::generateResponse(const string& input, string filename) {
    // ---------------- Persistent State Variables ----------------
    static string selectedArea = ""; 
    static bool awaitingInstallmentInput = false;
    static bool inHomeLoanFlow = false; 
    static string lastAreaFile = "data/Home.txt";

    string target = toLowerString(trimString(input));

    // ---------------- Step 1: Home Loan Area Selection ----------------
    if (input == "1" || input == "2" || input == "3" || input == "4") {
        ifstream homeFile(lastAreaFile);
        if (!homeFile.is_open()) {
            return "Error: Cannot open Home.txt";
        }

        string line;
        getline(homeFile, line); // skip header
        selectedArea = "Area " + input;
        string result = "\nAvailable Home Loan Options for " + selectedArea + ":\n";

        bool found = false;
        while (getline(homeFile, line)) {
            int pos1=-1,pos2=-1,pos3=-1,pos4=-1,count=0;
            for (int i=0;i<line.length();i++){
                if (line[i]=='#'){
                    count++;
                    if(count==1) pos1=i;
                    else if(count==2) pos2=i;
                    else if(count==3) pos3=i;
                    else if(count==4) pos4=i;
                }
            }

            if(pos1!=-1 && pos2!=-1 && pos3!=-1 && pos4!=-1){
                string area="", size="", inst="", price="", down="";
                for(int i=0;i<pos1;i++) area+=line[i];
                for(int i=pos1+1;i<pos2;i++) size+=line[i];
                for(int i=pos2+1;i<pos3;i++) inst+=line[i];
                for(int i=pos3+1;i<pos4;i++) price+=line[i];
                for(int i=pos4+1;i<line.length();i++) down+=line[i];

                if(area==selectedArea){
                    found = true;
                    result += "- Size: " + size + 
                              " | Installments: " + inst + 
                              " | Price: " + price + 
                              " | Down Payment: " + down + "\n";
                }
            }
        }
        homeFile.close();

        if (!found) result += "No options available for " + selectedArea + ".";
        else result += "\nPlease enter number of installments (e.g. 36, 48, 60):";

        inHomeLoanFlow = true;
        awaitingInstallmentInput = true;
        return result;
    }

    // ---------------- Step 2: Installment Input ----------------
    if (awaitingInstallmentInput && inHomeLoanFlow) {
        if (input == "B" || input == "b") {
            awaitingInstallmentInput = false;
            inHomeLoanFlow = false;
            return "You are applying for a home loan. Please select area. Options are 1, 2, 3, 4";
        }

        ifstream homeFile(lastAreaFile);
        if (!homeFile.is_open()) {
            return "Error: Cannot open Home.txt";
        }

        string line;
        getline(homeFile, line); // skip header
        bool found = false;
        string response = "\nInstallment Plan for " + selectedArea + " (" + input + " months):\n";

        while (getline(homeFile, line)) {
            int pos1=-1,pos2=-1,pos3=-1,pos4=-1,count=0;
            for (int i=0;i<line.length();i++){
                if (line[i]=='#'){
                    count++;
                    if(count==1) pos1=i;
                    else if(count==2) pos2=i;
                    else if(count==3) pos3=i;
                    else if(count==4) pos4=i;
                }
            }

            if(pos1!=-1 && pos2!=-1 && pos3!=-1 && pos4!=-1){
                string area="", size="", inst="", price="", down="";
                for(int i=0;i<pos1;i++) area+=line[i];
                for(int i=pos1+1;i<pos2;i++) size+=line[i];
                for(int i=pos2+1;i<pos3;i++) inst+=line[i];
                for(int i=pos3+1;i<pos4;i++) price+=line[i];
                for(int i=pos4+1;i<line.length();i++) down+=line[i];

                if(area==selectedArea && inst==input){
                    long long priceVal = stoll(removeCommas(price));
                    long long downVal = stoll(removeCommas(down));
                    long long months = stoll(inst);
                    long long monthly = (priceVal - downVal) / months;

                    found = true;
                    response += "- Size: " + size + 
                                " | Price: " + price + 
                                " | Down Payment: " + down + 
                                " | Monthly Installment: " + to_string(monthly) + "\n";
                }
            }
        }
        homeFile.close();

        if (!found)
            response += "No plan found for that installment period.\n";
        else
            response += "\nWould you like to check another installment plan (enter number) or go back (B)?";

        awaitingInstallmentInput = true;
        inHomeLoanFlow = true;
        return response;
    }

    // ---------------- Step 3: Generic Response Handling ----------------
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return "";
    }

    string wildcardResponse = "";
    string line;
    while (getline(file, line)) {
        int pos = line.find('#');
        if (pos == -1) continue;

        string storedInput = line.substr(0, pos);
        string response = line.substr(pos + 1);
        string key = toLowerString(trimString(storedInput));

        if (key == target && key != "") {
            file.close();
            return trimString(response);
        }

        if (key == "*") {
            wildcardResponse = trimString(response);
        }
    }
    file.close();

    if (wildcardResponse != "")
        return wildcardResponse;

    return "I'm sorry, I didn't understand that. Please try again.";
}



string ChatbotProcessor::analyzeIntent(const string& input) {
    // TODO: Implement intent/sentiment analysis
}

string ChatbotProcessor::processLoanQuery(const string keywords[], int keywordCount) {
    // TODO: Implement loan query handling
}

string ChatbotProcessor::getContextInfo(const string& query) {
    // TODO: Implement context retrieval
}

// --------------------------------------Display/Output Module--------------------------------------
// LP4-9 Assigned to Hasan

void ChatbotDisplay::displayResponse(const string& response) {

    setColor(COLOR_CYAN);          
    cout << "LoanMate: ";
    setColor(COLOR_WHITE);

    for (int i = 0; response[i] != '\0'; i++) {
        cout << response[i];
        Sleep(10);
    }
    cout<<endl<<endl;
}

void ChatbotDisplay::showWelcomeMessage() {
    // TODO: Display welcome message and instructions
    system("cls");

    // Title
    setColor(COLOR_CYAN);
    cout << "\n";
    cout << "  ======================================================\n";
    setColor(COLOR_YELLOW);
    cout << "\n";
    cout << "      _     ___    _    _   _ __  __    _  _____ _____ \n";
    cout << "     | |   / _ \\  / \\  | \\ | |  \\/  |  / \\|_   _| ____|\n";
    cout << "     | |  | | | |/ _ \\ |  \\| | |\\/| | / _ \\ | | |  _|  \n";
    cout << "     | |__| |_| / ___ \\| |\\  | |  | |/ ___ \\| | | |___ \n";
    cout << "     |_____\\___/_/   \\_\\_| \\_|_|  |_/_/   \\_\\_| |_____|\n";
    cout << "\n";

    setColor(COLOR_YELLOW);
    cout << "        Version 1.0 | Developed by Team Project404\n";
    setColor(COLOR_CYAN);
    cout << "  ======================================================\n";

    setColor(COLOR_WHITE);
    cout << "            Initializing LoanMate AI Engine";

    // Animated dots
    for (int i = 0; i < 3; i++) {
        Sleep(300);
        cout << ".";
    }

    cout << "\n\n";

    // Progress bar animation
    setColor(COLOR_GREEN);
    cout << "          [";
    for (int i = 0; i < 30; i++) {
        cout << "=";
        Sleep(30);
    }
    cout << "] 100%\n\n";

    setColor(COLOR_CYAN);
    cout << "  ======================================================\n\n";

    setColor(COLOR_WHITE);
    cout << "          Features:\n";
    setColor(COLOR_GREEN);
    cout << "           > Conversational data entry\n";
    Sleep(500);
    cout << "           > Secure document upload\n";
    Sleep(500);
    cout << "           > Loan eligibility checking\n";
    Sleep(500);
    cout << "           > Installment & fee estimation\n";
    Sleep(500);
    cout << "           > Applicant & officer modes\n\n";

    setColor(COLOR_CYAN);
    cout << "  ======================================================\n\n";
    
    setColor(COLOR_YELLOW);
    cout << "          Press any key to start chatting...\n";
    setColor(COLOR_WHITE);

    _getch();
    system("cls");
}


void ChatbotDisplay::showError(const string& errorMessage) {
    // TODO: Display error messages
    setColor(COLOR_RED);
    cout << errorMessage << endl;
    setColor(COLOR_WHITE);
}

string ChatbotDisplay::formatOutput(const string& text) {
    // TODO: Implement text formatting/styling
    return text;
}

// --------------------------------------Testing and Debug Module-----------------------------------
//LP4-10 Assigned to Haider

// Test if all inputs from Utterances.txt are validated correctly
bool ChatbotTester::testInputProcessing()
{   
    setColor(COLOR_MAGENTA);
    cout << "\n=== Testing Input Processing ===" << endl<< endl;
    setColor(COLOR_WHITE);

    ifstream file("data/Utterances.txt");
    string line;

    // Check if file opened successfully
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open data/Utterances.txt" << endl;
        return false;
    }

    ChatbotInput inputProcessor;

    // Read each line from data/Utterances.txt file
    while (getline(file, line))
    {
        int found = 0;

        // Loop through each character to find '#' separator
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                found = 1;
                string input = "";

                // Extract input part before '#'
                for (int j = 0; j < i; j++) input += line[j];                

                // sanitize using validateInput
                string tmp = input;
                string sanitized = inputProcessor.validateInput(tmp);

                cout << "Original: \"" << input << "\" -> Sanitized: \"" << sanitized << "\"" << endl;
                break;
            }
        }
    }
    file.close();
    return true;
}

// Test if responses match expected outputs from Utterances.txt
bool ChatbotTester::testResponseGeneration()
{
    setColor(COLOR_MAGENTA);
    cout << "\n=== Testing Response Generation ===" << endl<< endl;
    setColor(COLOR_WHITE);
    // Open the utterances file (format: user_input#expected_response per line)
    ifstream file("data/Utterances.txt");
    string line;

    // Check if file opened successfully
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open data/Utterances.txt" << endl;
        return false;
    }

    ChatbotInput inputProcessor;

    // Read each line from data/Utterances.txt file
   while (getline(file, line))
    {   // Find separator index ('#') between input and expected response
        int pos = -1;
        for (int i = 0; i < (int)line.length(); i++)
        {
            if (line[i] == '#') { pos = i; break; }
        }

         // If a separator exists, extract input and expected response
        if (pos != -1)
        {
            string input = line.substr(0, pos);  // raw input from file
            string expected = line.substr(pos + 1);  // expected response from file

            //validateInput may prompt if input is empty/whitespace;
            // using it ensures tests use identical preprocessing rules.
            string tmp = input;
            string sanitized = inputProcessor.validateInput(tmp);

            // Generate the chatbot response for the sanitized input
            ChatbotProcessor processor;
            string response = processor.generateResponse(sanitized);

            // Compare actual response to expected and report result
            if (response == expected){
                setColor(COLOR_GREEN);
                cout << "PASS: " << input << " -> Correct" << endl;
                setColor(COLOR_WHITE);
            }
                
            else {
                setColor(COLOR_RED);
                cout << "FAIL: " << input << endl;
                cout << "Expected: " << expected << endl;
                cout << "Got: " << response << endl;
                setColor(COLOR_WHITE);
            }
        }
    }
    // Clean up and indicate success
    file.close();
    return true;
}

// Test one specific input and expected output
bool ChatbotTester::validateResponse(const string& input, const string& expectedOutput)
{
    ChatbotProcessor processor;
    string response = processor.generateResponse(input);

    if (response == expectedOutput)
    {
        setColor(COLOR_GREEN);
        cout << "PASS: " << input << " -> Correct" << endl;
        setColor(COLOR_WHITE);
        return true;
    }
    else
    {
        setColor(COLOR_RED);
        cout << "FAIL: " << input << endl;
        setColor(COLOR_YELLOW);
        cout << "Expected: " << expectedOutput << endl;
        cout << "Got: " << response << endl;
        setColor(COLOR_WHITE);
        return false;
    }
}

// Test if Home.txt data is read and parsed correctly
bool ChatbotTester::testHomeLoanData()
{
    setColor(COLOR_MAGENTA);
    cout << "\n=== Testing Home Loan Data ===" << endl<< endl;
    setColor(COLOR_WHITE);
    ifstream file("data/Home.txt");
    string line;

    // Check if file opened successfully
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open data/Home.txt" << endl;
        return false;
    }

    // Skip first line (header)
    getline(file, line);

    // Read each data line from data/Home.txt
    while (getline(file, line))
    {
        int pos1 = -1, pos2 = -1, pos3 = -1, pos4 = -1;
        int count = 0;

        // Find positions of all '#' separators
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                count++;
                if (count == 1)
                {
                    pos1 = i;
                }
                else if (count == 2)
                {
                    pos2 = i;
                }
                else if (count == 3)
                {
                    pos3 = i;
                }
                else if (count == 4)
                {
                    pos4 = i;
                }
            }
        }

        // If all separators found, extract data fields
        if (pos1 != -1 && pos2 != -1 && pos3 != -1 && pos4 != -1)
        {
            string area = "";
            string size = "";
            string installments = "";
            string price = "";
            string downPayment = "";

            // Extract area (before first '#')
            for (int i = 0; i < pos1; i++)
            {
                area += line[i];
            }

            // Extract size (between first and second '#')
            for (int i = pos1 + 1; i < pos2; i++)
            {
                size += line[i];
            }

            // Extract installments (between second and third '#')
            for (int i = pos2 + 1; i < pos3; i++)
            {
                installments += line[i];
            }

            // Extract price (between third and fourth '#')
            for (int i = pos3 + 1; i < pos4; i++)
            {
                price += line[i];
            }

            // Extract down payment (after fourth '#')
            for (int i = pos4 + 1; i < line.length(); i++)
            {
                downPayment += line[i];
            }

            cout << "Area: " << area << ", Size: " << size << ", Installments: " << installments;
            cout << ", Price: " << price << ", Down Payment: " << downPayment << endl;
        }
    }
    file.close();
    return true;
}

// Print debug messages during testing
void ChatbotTester::logDebugInfo(const string& debugInfo)
{
    setColor(COLOR_MAGENTA);
    cout << "[DEBUG] " << debugInfo << endl;
    setColor(COLOR_WHITE);
}


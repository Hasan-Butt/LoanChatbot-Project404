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
#include <iostream>
using namespace std;

// ----------------------------------Chatbot Input Reading Module--------------------------------
// LP4-7 Assigned to Ayub

string Chatbot::readUserInput() 
{
	string response;
	getline(cin, response); 
	response = validateInput(response);
	return response;
}

string ChatbotInput::validateInput(string& input) {
    // TODO: Implement input validation
    while (check_spaces(input)|| input == "") // only spaces or empty string
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
			c=tolower(c);
			input[i] = c;
			i++;
		}
		return input;
}

int ChatbotInput::extractKeywords(const string& input, string keywords[], int maxKeywords) {
    // TODO: Implement keyword extraction and return count
}

bool Chatbot::check_spaces(string& input)
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
// ---------------------------------Chatbot Response Processing Module----------------------------
// LP4-8 Assigned to Kabeer

string ChatbotProcessor::generateResponse(const string& input) {
    // TODO: Implement response generation
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
    // TODO: Implement formatted output display
}

void ChatbotDisplay::showWelcomeMessage() {
    // TODO: Display welcome message and instructions
}

void ChatbotDisplay::showError(const string& errorMessage) {
    // TODO: Display error messages
}

string ChatbotDisplay::formatOutput(const string& text) {
    // TODO: Implement text formatting/styling
}

// --------------------------------------Testing and Debug Module-----------------------------------
//LP4-10 Assigned to Haider

// Test if all inputs from Utterances.txt are validated correctly
bool ChatbotTester::testInputProcessing() 
{
    cout << "=== Testing Input Processing ===" << endl;
    
    ifstream file("data/Utterances.txt");
    string line;
    
    // Check if file opened successfully
    if (!file.is_open()) 
    {
        cout << "ERROR: Cannot open data/Utterances.txt" << endl;
        return false;
    }
    
    // Read each line from data/Utterances.txt file
    while (getline(file, line)) 
    {
        int found = 0;
        
        // Loop through each character to find '#' separator
        for(int i = 0; i < line.length(); i++) 
        {
            if(line[i] == '#') 
            {
                found = 1;
                string input = "";
                
                // Extract input part before '#'
                for(int j = 0; j < i; j++) 
                {
                    input += line[j];
                }
                
                // Skip '*' inputs (general responses)
                if(input != "*") 
                {
                    if(validateInput(input)) 
                    {
                        cout << "PASS: " << input << " is valid" << endl;
                    } 
                    else 
                    {
                        cout << "FAIL: " << input << " should be valid" << endl;
                    }
                }
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
    cout << "=== Testing Response Generation ===" << endl;
    
    ifstream file("data/Utterances.txt");
    string line;
    
    // Check if file opened successfully
    if (!file.is_open()) 
    {
        cout << "ERROR: Cannot open data/Utterances.txt" << endl;
        return false;
    }
    
    // Read each line from data/Utterances.txt file
    while (getline(file, line)) 
    {
        int found = 0;
        int pos = -1;
        
        // Find position of '#' separator
        for(int i = 0; i < line.length(); i++) 
        {
            if(line[i] == '#') 
            {
                found = 1;
                pos = i;
                break;
            }
        }
        
        // If separator found, process input and expected output
        if(found == 1) 
        {
            string input = "";
            string expected = "";
            
            // Extract input part before '#'
            for(int j = 0; j < pos; j++) 
            {
                input += line[j];
            }
            
            // Extract expected output after '#'
            for(int j = pos + 1; j < line.length(); j++) 
            {
                expected += line[j];
            }
            
            string response = generateResponse(input);
            
            // Compare actual response with expected response
            if(response == expected) 
            {
                cout << "PASS: " << input << " -> Correct" << endl;
            } 
            else 
            {
                cout << "FAIL: " << input << endl;
                cout << "Expected: " << expected << endl;
                cout << "Got: " << response << endl;
            }
        }
    }
    file.close();
    return true;
}

// Test one specific input and expected output
bool ChatbotTester::validateResponse(const string& input, const string& expectedOutput) 
{
    string response = generateResponse(input);
    
    if(response == expectedOutput) 
    {
        cout << "PASS: " << input << " -> Correct" << endl;
        return true;
    } 
    else 
    {
        cout << "FAIL: " << input << endl;
        cout << "Expected: " << expectedOutput << endl;
        cout << "Got: " << response << endl;
        return false;
    }
}

// Test if Home.txt data is read and parsed correctly
bool ChatbotTester::testHomeLoanData() 
{
    cout << "=== Testing Home Loan Data ===" << endl;
    
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
    while(getline(file, line)) 
    {
        int pos1 = -1, pos2 = -1, pos3 = -1, pos4 = -1;
        int count = 0;
        
        // Find positions of all '#' separators
        for(int i = 0; i < line.length(); i++) 
        {
            if(line[i] == '#') 
            {
                count++;
                if(count == 1) 
                {
                    pos1 = i;
                }
                else if(count == 2) 
                {
                    pos2 = i;
                }
                else if(count == 3) 
                {
                    pos3 = i;
                }
                else if(count == 4) 
                {
                    pos4 = i;
                }
            }
        }
        
        // If all separators found, extract data fields
        if(pos1 != -1 && pos2 != -1 && pos3 != -1 && pos4 != -1) 
        {
            string area = "";
            string size = "";
            string installments = "";
            string price = "";
            string downPayment = "";
            
            // Extract area (before first '#')
            for(int i = 0; i < pos1; i++) 
            {
                area += line[i];
            }
            
            // Extract size (between first and second '#')
            for(int i = pos1 + 1; i < pos2; i++) 
            {
                size += line[i];
            }
            
            // Extract installments (between second and third '#')
            for(int i = pos2 + 1; i < pos3; i++) 
            {
                installments += line[i];
            }
            
            // Extract price (between third and fourth '#')
            for(int i = pos3 + 1; i < pos4; i++) 
            {
                price += line[i];
            }
            
            // Extract down payment (after fourth '#')
            for(int i = pos4 + 1; i < line.length(); i++) 
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
    cout << "[DEBUG] " << debugInfo << endl;
}

// Run all test functions
void runAllTests() 
{
    ChatbotTester tester;
    
    cout << "Starting Tests..." << endl;
    
    tester.testInputProcessing();
    tester.testResponseGeneration();
    tester.testHomeLoanData();
    
    cout << "All Tests Completed!" << endl;
}
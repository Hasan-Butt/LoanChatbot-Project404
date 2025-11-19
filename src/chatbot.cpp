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

string ChatbotInput::readUserInput() {
    // TODO: Implement reading input from console
}

bool ChatbotInput::validateInput(const string& input) {
    // TODO: Implement input validation
}

int ChatbotInput::extractKeywords(const string& input, string keywords[], int maxKeywords) {
    // TODO: Implement keyword extraction and return count
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

string ChatbotProcessor::getNextMonth(const string& current) {
    const string months[12] = { "January","February","March","April","May","June",
                                "July","August","September","October","November","December" };
    int index = -1;
    for (int i = 0; i < 12; i++) {
        if (months[i] == current) { index = i; break; }
    }
    if (index == -1) return "January"; // default if not found
    return months[(index + 1) % 12];
}

void ChatbotProcessor::generateInstallmentSchedule(int installments, long long price, long long downPayment, const string& startMonth) {
    long long remaining = price - downPayment;
    long long monthlyPayment = remaining / installments;
    long long totalPaid = downPayment;

    string month = startMonth;

    cout << left << setw(12) << "Installment"
        << setw(12) << "Month"
        << setw(18) << "Monthly Payment"
        << setw(15) << "Total Paid"
        << setw(15) << "Remaining" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int i = 1; i <= installments; i++) {
        totalPaid += monthlyPayment;
        remaining -= monthlyPayment;

        cout << left << setw(12) << i
            << setw(12) << month
            << setw(18) << monthlyPayment
            << setw(15) << totalPaid
            << setw(15) << (remaining > 0 ? remaining : 0) << endl;

        month = getNextMonth(month);
    }
}

void ChatbotProcessor::handleMonthlySchedule()
{
    int installments;
    long long price;
    long long downPayment;
    string startMonth;

    cout << "Enter total price: ";
    cin >> price;

    cout << "Enter down payment: ";
    cin >> downPayment;

    cout << "Enter number of installments: ";
    cin >> installments;

    cout << "Enter starting month (e.g., January): ";
    cin >> startMonth;

    long long remaining = price - downPayment;
    long long monthlyPayment = remaining / installments;
    long long totalPaid = downPayment;

    string month = startMonth;

    cout << "\n================ Monthly Installment Schedule ================\n";
    cout << left << setw(12) << "Installment"
        << setw(12) << "Month"
        << setw(18) << "Monthly Payment"
        << setw(15) << "Total Paid"
        << setw(15) << "Remaining" << endl;
    cout << "---------------------------------------------------------------\n";

    for (int i = 1; i <= installments; i++)
    {
        totalPaid += monthlyPayment;
        remaining -= monthlyPayment;

        cout << left << setw(12) << i
            << setw(12) << month
            << setw(18) << monthlyPayment
            << setw(15) << totalPaid
            << setw(15) << (remaining > 0 ? remaining : 0) << endl;

        month = getNextMonth(month);  // Correct month progression
    }

    cout << "===============================================================\n";
}



void ChatbotProcessor::searchApplicationsByCNIC(const string& cnic)
{
    ifstream file("applications.txt");
    if (!file.is_open()) {
        cout << "ERROR: Could not open applications.txt" << endl;
        return;
    }

    string line;
    int submitted = 0;
    int approved = 0;
    int rejected = 0;
    int found = 0;

    while (getline(file, line))
    {
        string fileCNIC = "";
        string status = "";
        int cnicStart = -1, cnicEnd = -1;

        // Extract CNIC
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '#') {
                cnicStart = i + 1;
                break;
            }
        }
        if (cnicStart == -1) continue;

        for (int i = cnicStart; i < line.length(); i++) {
            if (line[i] == '#') {
                cnicEnd = i;
                break;
            }
            fileCNIC += line[i];
        }

        // If CNIC matches, check status
        if (fileCNIC == cnic)
        {
            found = 1;

            // Extract status (after last #)
            int lastHash = -1;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '#') lastHash = i;
            }

            for (int i = lastHash + 1; i < line.length(); i++) {
                status += line[i];
            }

            if (status == "Submitted") submitted++;
            else if (status == "Approved") approved++;
            else if (status == "Rejected") rejected++;
        }
    }

    file.close();

    ChatbotDisplay display;

    if (found == 0) {
        cout << "No applications found for CNIC: " << cnic << endl;
        return;
    }

    display.showCNICSearchSummary(submitted, approved, rejected);
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

void ChatbotDisplay::showInstallmentTable(int installmentNo, const string& month, long long monthlyPayment, long long totalPaid, long long remaining) {
    cout << left << setw(12) << installmentNo
        << setw(12) << month
        << setw(18) << monthlyPayment
        << setw(15) << totalPaid
        << setw(15) << remaining << endl;
}

void ChatbotDisplay::showCNICSearchSummary(int submitted, int approved, int rejected) {
    cout << "================= CNIC Search Summary =================" << endl;
    cout << "Total Submitted: " << submitted << endl;
    cout << "Approved      : " << approved << endl;
    cout << "Rejected      : " << rejected << endl;
    cout << "======================================================" << endl;
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
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                found = 1;
                string input = "";

                // Extract input part before '#'
                for (int j = 0; j < i; j++)
                {
                    input += line[j];
                }

                // Skip '*' inputs (general responses)
                if (input != "*")
                {
                    if (validateInput(input))
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
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                found = 1;
                pos = i;
                break;
            }
        }

        // If separator found, process input and expected output
        if (found == 1)
        {
            string input = "";
            string expected = "";

            // Extract input part before '#'
            for (int j = 0; j < pos; j++)
            {
                input += line[j];
            }

            // Extract expected output after '#'
            for (int j = pos + 1; j < line.length(); j++)
            {
                expected += line[j];
            }

            string response = generateResponse(input);

            // Compare actual response with expected response
            if (response == expected)
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

    if (response == expectedOutput)
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
    cout << "[DEBUG] " << debugInfo << endl;
}

void ChatbotTester::testInstallmentSchedule() {
    ChatbotProcessor processor;
    cout << "\n=== Testing Installment Schedule ===\n\n";

    int installments = 6;
    long long price = 120000;
    long long downPayment = 20000;
    string startMonth = "January";

    processor.generateInstallmentSchedule(installments, price, downPayment, startMonth);
}

void ChatbotTester::testCNICSearch() {
    ChatbotDisplay display;
    cout << "\n=== Testing CNIC Search Summary ===\n\n";

    int submitted = 5;
    int approved = 3;
    int rejected = 2;

    display.showCNICSearchSummary(submitted, approved, rejected);
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

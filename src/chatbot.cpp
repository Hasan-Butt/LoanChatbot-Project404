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
#include <iomanip>
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
    string ChatbotInput::readUserInput() {
        // TODO: Implement reading input from console
    }

    string ChatbotInput::validateInput(string & input) {
        bool ChatbotInput::validateInput(const string & input) {
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

        int ChatbotInput::extractKeywords(const string & input, string keywords[], int maxKeywords) {
            // TODO: Implement keyword extraction and return count
        }


        // ---------------------------------Chatbot Response Processing Module----------------------------
        // LP4-8 Assigned to Kabeer

        string ChatbotProcessor::generateResponse(const string & input, string filename) {
            // ---------------- Persistent State Variables ----------------
            static string selectedArea = "";
            static bool awaitingInstallmentInput = false;
            static bool inHomeLoanFlow = false;
            static string lastAreaFile = "data/Home.txt";

            string target = toLowerString(trimString(input));

            // ---------------- Check for non-Home loan options first ----------------
            // If user enters V, C, E, or B (but not in home loan flow)
            if (!inHomeLoanFlow && (target == "v" || target == "c" || target == "e" || target == "b")) {
                setColor(14); // Yellow
                cout << "\n================================================================\n";
                cout << "                     COMING SOON                                \n";
                cout << "================================================================\n";
                setColor(10); // Green
                cout << "This feature is under development and will be available soon!\n";
                setColor(8);
                cout << "================================================================\n";
                setColor(7);
                return "This feature is coming soon! Please try Home Loan (H) for now.";
                string ChatbotProcessor::generateResponse(const string & input) {
                    // TODO: Implement response generation
                }

                string ChatbotProcessor::analyzeIntent(const string & input) {
                    // TODO: Implement intent/sentiment analysis
                }

                string ChatbotProcessor::processLoanQuery(const string keywords[], int keywordCount) {
                    // TODO: Implement loan query handling
                }

                string ChatbotProcessor::getContextInfo(const string & query) {
                    // TODO: Implement context retrieval
                }

                string ChatbotProcessor::getNextMonth(const string & current) {
                    const string months[12] = { "January","February","March","April","May","June",
                                                "July","August","September","October","November","December" };
                    int index = -1;
                    for (int i = 0; i < 12; i++) {
                        if (months[i] == current) { index = i; break; }
                    }
                    if (index == -1) return "January"; // default if not found
                    return months[(index + 1) % 12];
                }

                // ---------------- Step 1: Home Loan Area Selection ----------------
                if (input == "1" || input == "2" || input == "3" || input == "4") {
                    ifstream homeFile(lastAreaFile);
                    if (!homeFile.is_open()) {
                        return "Error: Cannot open Home.txt";
                    }
                    void ChatbotProcessor::generateInstallmentSchedule(int installments, long long price, long long downPayment, const string & startMonth) {
                        long long remaining = price - downPayment;
                        long long monthlyPayment = remaining / installments;
                        long long totalPaid = downPayment;

                        string line;
                        getline(homeFile, line); // skip header
                        selectedArea = "Area " + input;
                        string result = "\nAvailable Home Loan Options for " + selectedArea + ":\n";

                        setColor(11); // Cyan
                        cout << "\n================================================================\n";
                        cout << "                  Home Loan Options for " << selectedArea << "\n";
                        cout << "================================================================\n";

                        setColor(14); // Yellow
                        cout << left
                            << setw(15) << "Size"
                            << setw(18) << "Installments"
                            << setw(22) << "Price"
                            << setw(18) << "Down Payment" << endl;

                        setColor(8); // Gray line
                        cout << "---------------------------------------------------------------\n";

                        bool found = false;
                        while (getline(homeFile, line)) {
                            int pos1 = -1, pos2 = -1, pos3 = -1, pos4 = -1, count = 0;
                            for (int i = 0; i < line.length(); i++) {
                                if (line[i] == '#') {
                                    count++;
                                    if (count == 1) pos1 = i;
                                    else if (count == 2) pos2 = i;
                                    else if (count == 3) pos3 = i;
                                    else if (count == 4) pos4 = i;
                                }
                            }
                            string month = startMonth;

                            if (pos1 != -1 && pos2 != -1 && pos3 != -1 && pos4 != -1) {
                                string area = "", size = "", inst = "", price = "", down = "";
                                for (int i = 0; i < pos1; i++) area += line[i];
                                for (int i = pos1 + 1; i < pos2; i++) size += line[i];
                                for (int i = pos2 + 1; i < pos3; i++) inst += line[i];
                                for (int i = pos3 + 1; i < pos4; i++) price += line[i];
                                for (int i = pos4 + 1; i < line.length(); i++) down += line[i];

                                if (area == selectedArea) {
                                    found = true;
                                    setColor(10); // Green rows
                                    cout << left
                                        << setw(15) << size
                                        << setw(18) << inst
                                        << setw(22) << price
                                        << setw(18) << down << endl;
                                }
                            }
                        }
                        homeFile.close();
                        cout << left << setw(12) << "Installment"
                            << setw(12) << "Month"
                            << setw(18) << "Monthly Payment"
                            << setw(15) << "Total Paid"
                            << setw(15) << "Remaining" << endl;
                        cout << "--------------------------------------------------------------" << endl;

                        setColor(8);
                        cout << "---------------------------------------------------------------\n";
                        for (int i = 1; i <= installments; i++) {
                            totalPaid += monthlyPayment;
                            remaining -= monthlyPayment;

                            setColor(7);
                            if (!found) result += "No options available for " + selectedArea + ".";
                            else result += "\nPlease enter number of installments (e.g. 36, 48, 60):";
                            cout << left << setw(12) << i
                                << setw(12) << month
                                << setw(18) << monthlyPayment
                                << setw(15) << totalPaid
                                << setw(15) << (remaining > 0 ? remaining : 0) << endl;

                            inHomeLoanFlow = true;
                            awaitingInstallmentInput = true;
                            return result;
                            month = getNextMonth(month);
                        }
                    }

                    // ---------------- Step 2: Installment Input ----------------
                    if (awaitingInstallmentInput && inHomeLoanFlow) {
                        if (input == "B" || input == "b") {
                            awaitingInstallmentInput = false;
                            inHomeLoanFlow = false;
                            return "You are applying for a home loan. Please select area. Options are 1, 2, 3, 4";
                        }
                        void ChatbotProcessor::handleMonthlySchedule()
                        {
                            int installments;
                            long long price;
                            long long downPayment;
                            string startMonth;

                            ifstream homeFile(lastAreaFile);
                            if (!homeFile.is_open()) {
                                return "Error: Cannot open Home.txt";
                            }
                            cout << "Enter total price: ";
                            cin >> price;

                            string line;
                            getline(homeFile, line); // skip header
                            bool found = false;
                            string response = "\nInstallment Plan for " + selectedArea + " (" + input + " months):\n";

                            setColor(11);
                            cout << "\n================================================================\n";
                            cout << "            Installment Plan for " << selectedArea
                                << " (" << input << " months)\n";
                            cout << "================================================================\n";

                            setColor(14);
                            cout << left
                                << setw(15) << "Size"
                                << setw(22) << "Price"
                                << setw(20) << "Down Payment"
                                << setw(20) << "Monthly Installment" << endl;

                            setColor(8);
                            cout << "--------------------------------------------------------------------\n";

                            while (getline(homeFile, line)) {
                                int pos1 = -1, pos2 = -1, pos3 = -1, pos4 = -1, count = 0;
                                for (int i = 0; i < line.length(); i++) {
                                    if (line[i] == '#') {
                                        count++;
                                        if (count == 1) pos1 = i;
                                        else if (count == 2) pos2 = i;
                                        else if (count == 3) pos3 = i;
                                        else if (count == 4) pos4 = i;
                                    }
                                }
                                cout << "Enter down payment: ";
                                cin >> downPayment;

                                if (pos1 != -1 && pos2 != -1 && pos3 != -1 && pos4 != -1) {
                                    string area = "", size = "", inst = "", price = "", down = "";
                                    for (int i = 0; i < pos1; i++) area += line[i];
                                    for (int i = pos1 + 1; i < pos2; i++) size += line[i];
                                    for (int i = pos2 + 1; i < pos3; i++) inst += line[i];
                                    for (int i = pos3 + 1; i < pos4; i++) price += line[i];
                                    for (int i = pos4 + 1; i < line.length(); i++) down += line[i];

                                    if (area == selectedArea && inst == input) {
                                        long long priceVal = stoll(removeCommas(price));
                                        long long downVal = stoll(removeCommas(down));
                                        long long months = stoll(inst);
                                        long long monthly = (priceVal - downVal) / months;

                                        found = true;
                                        setColor(10);
                                        cout << left
                                            << setw(15) << size
                                            << setw(22) << price
                                            << setw(20) << down
                                            << setw(20) << to_string(monthly) << endl;
                                    }
                                }
                            }
                            homeFile.close();
                            cout << "Enter number of installments: ";
                            cin >> installments;

                            cout << "Enter starting month (e.g., January): ";
                            cin >> startMonth;

                            long long remaining = price - downPayment;
                            long long monthlyPayment = remaining / installments;
                            long long totalPaid = downPayment;

                            string month = startMonth;

                            setColor(8);
                            cout << "--------------------------------------------------------------------\n";
                            cout << "\n================ Monthly Installment Schedule ================\n";
                            cout << left << setw(12) << "Installment"
                                << setw(12) << "Month"
                                << setw(18) << "Monthly Payment"
                                << setw(15) << "Total Paid"
                                << setw(15) << "Remaining" << endl;
                            cout << "---------------------------------------------------------------\n";

                            setColor(7);
                            if (!found)
                                response += "No plan found for that installment period.\n";
                            else
                                response += "\nWould you like to check another installment plan (enter number) or go back (B)?";
                            for (int i = 1; i <= installments; i++)
                            {
                                totalPaid += monthlyPayment;
                                remaining -= monthlyPayment;

                                cout << left << setw(12) << i
                                    << setw(12) << month
                                    << setw(18) << monthlyPayment
                                    << setw(15) << totalPaid
                                    << setw(15) << (remaining > 0 ? remaining : 0) << endl;

                                awaitingInstallmentInput = true;
                                inHomeLoanFlow = true;
                                return response;
                                month = getNextMonth(month);  // Correct month progression
                            }

                            // ---------------- Step 3: Generic Response Handling ----------------
                            ifstream file(filename);
                            cout << "===============================================================\n";
                        }



                        void ChatbotProcessor::searchApplicationsByCNIC(const string & cnic)
                        {
                            ifstream file("applications.txt");
                            if (!file.is_open()) {
                                cerr << "Error: Could not open file " << filename << endl;
                                return "";
                                cout << "ERROR: Could not open applications.txt" << endl;
                                return;
                            }

                            string wildcardResponse = "";
                            string line;
                            while (getline(file, line)) {
                                int pos = line.find('#');
                                if (pos == -1) continue;
                                int submitted = 0;
                                int approved = 0;
                                int rejected = 0;
                                int found = 0;

                                string storedInput = line.substr(0, pos);
                                string response = line.substr(pos + 1);
                                string key = toLowerString(trimString(storedInput));
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

                                    if (key == target && key != "") {
                                        file.close();
                                        return trimString(response);
                                        for (int i = cnicStart; i < line.length(); i++) {
                                            if (line[i] == '#') {
                                                cnicEnd = i;
                                                break;
                                            }
                                            fileCNIC += line[i];
                                        }

                                        if (key == "*") {
                                            wildcardResponse = trimString(response);
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

                                        if (wildcardResponse != "")
                                            return wildcardResponse;
                                        ChatbotDisplay display;

                                        if (found == 0) {
                                            cout << "No applications found for CNIC: " << cnic << endl;
                                            return;
                                        }

                                        return "I'm sorry, I didn't understand that. Please try again.";
                                        display.showCNICSearchSummary(submitted, approved, rejected);
                                    }



                                    string ChatbotProcessor::analyzeIntent(const string & input) {
                                        // TODO: Implement intent/sentiment analysis
                                    }

                                    string ChatbotProcessor::processLoanQuery(const string keywords[], int keywordCount) {
                                        // TODO: Implement loan query handling
                                    }

                                    string ChatbotProcessor::getContextInfo(const string & query) {
                                        // TODO: Implement context retrieval
                                    }



                                    // --------------------------------------Display/Output Module--------------------------------------
                                    // LP4-9 Assigned to Hasan

                                    void ChatbotDisplay::displayResponse(const string & response) {

                                        setColor(COLOR_CYAN);
                                        cout << "LoanMate: ";
                                        setColor(COLOR_WHITE);

                                        for (int i = 0; response[i] != '\0'; i++) {
                                            cout << response[i];
                                            Sleep(10);
                                        }
                                        cout << endl << endl;
                                        // TODO: Implement formatted output display
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


                                    void ChatbotDisplay::showError(const string & errorMessage) {
                                        // TODO: Display error messages
                                        setColor(COLOR_RED);
                                        cout << errorMessage << endl;
                                        setColor(COLOR_WHITE);
                                    }

                                    string ChatbotDisplay::formatOutput(const string & text) {
                                        // TODO: Implement text formatting/styling
                                        return text;
                                    }

                                    void ChatbotDisplay::showInstallmentTable(int installmentNo, const string & month, long long monthlyPayment, long long totalPaid, long long remaining) {
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
                                        setColor(COLOR_MAGENTA);
                                        cout << "\n=== Testing Input Processing ===" << endl << endl;
                                        setColor(COLOR_WHITE);
                                        {
                                            cout << "=== Testing Input Processing ===" << endl;

                                            ifstream file("data/Utterances.txt");
                                            string line;
                                            @@ - 427, 8 + 281, 6 @@ bool ChatbotTester::testInputProcessing()
                                                return false;
                                        }

                                        ChatbotInput inputProcessor;

                                        // Read each line from data/Utterances.txt file
                                        while (getline(file, line))
                                        {
                                            @@ - 443, 13 + 295, 23 @@ bool ChatbotTester::testInputProcessing()
                                                string input = "";

                                            // Extract input part before '#'
                                            for (int j = 0; j < i; j++) input += line[j];

                                            // sanitize using validateInput
                                            string tmp = input;
                                            string sanitized = inputProcessor.validateInput(tmp);
                                            for (int j = 0; j < i; j++)
                                            {
                                                input += line[j];
                                            }

                                            cout << "Original: \"" << input << "\" -> Sanitized: \"" << sanitized << "\"" << endl;
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
                                    @@ - 461, 10 + 323, 8 @@ bool ChatbotTester::testInputProcessing()
                                        // Test if responses match expected outputs from Utterances.txt
                                        bool ChatbotTester::testResponseGeneration()
                                    {
                                        setColor(COLOR_MAGENTA);
                                        cout << "\n=== Testing Response Generation ===" << endl << endl;
                                        setColor(COLOR_WHITE);
                                        // Open the utterances file (format: user_input#expected_response per line)
                                        cout << "=== Testing Response Generation ===" << endl;

                                        ifstream file("data/Utterances.txt");
                                        string line;

                                        @@ - 475, 84 + 335, 84 @@ bool ChatbotTester::testResponseGeneration()
                                            return false;
                                    }

                                    ChatbotInput inputProcessor;

                                    // Read each line from data/Utterances.txt file
                                    while (getline(file, line))
                                    {   // Find separator index ('#') between input and expected response
                                        while (getline(file, line))
                                        {
                                            int found = 0;
                                            int pos = -1;
                                            for (int i = 0; i < (int)line.length(); i++)

                                                // Find position of '#' separator
                                                for (int i = 0; i < line.length(); i++)
                                                {
                                                    if (line[i] == '#') { pos = i; break; }
                                                    if (line[i] == '#')
                                                    {
                                                        found = 1;
                                                        pos = i;
                                                        break;
                                                    }
                                                }

                                            // If a separator exists, extract input and expected response
                                            if (pos != -1)
                                                // If separator found, process input and expected output
                                                if (found == 1)
                                                {
                                                    string input = line.substr(0, pos);  // raw input from file
                                                    string expected = line.substr(pos + 1);  // expected response from file
                                                    string input = "";
                                                    string expected = "";

                                                    //validateInput may prompt if input is empty/whitespace;
                                                    // using it ensures tests use identical preprocessing rules.
                                                    string tmp = input;
                                                    string sanitized = inputProcessor.validateInput(tmp);
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

                                                    // Generate the chatbot response for the sanitized input
                                                    ChatbotProcessor processor;
                                                    string response = processor.generateResponse(sanitized);
                                                    string response = generateResponse(input);

                                                    // Compare actual response to expected and report result
                                                    if (response == expected) {
                                                        setColor(COLOR_GREEN);
                                                        // Compare actual response with expected response
                                                        if (response == expected)
                                                        {
                                                            cout << "PASS: " << input << " -> Correct" << endl;
                                                            setColor(COLOR_WHITE);
                                                        }

                                                        else {
                                                            setColor(COLOR_RED);
                                                    else
                                                    {
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
                                            bool ChatbotTester::validateResponse(const string & input, const string & expectedOutput)
                                            {
                                                ChatbotProcessor processor;
                                                string response = processor.generateResponse(input);
                                                string response = generateResponse(input);

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
                                                cout << "\n=== Testing Home Loan Data ===" << endl << endl;
                                                setColor(COLOR_WHITE);
                                                cout << "=== Testing Home Loan Data ===" << endl;

                                                ifstream file("data/Home.txt");
                                                string line;

                                                @@ - 647, 8 + 507, 46 @@ bool ChatbotTester::testHomeLoanData()
                                                    // Print debug messages during testing
                                                    void ChatbotTester::logDebugInfo(const string & debugInfo)
                                                {
                                                    setColor(COLOR_MAGENTA);
                                                    cout << "[DEBUG] " << debugInfo << endl;
                                                    setColor(COLOR_WHITE);
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
                                                Footer
                                                    © 202

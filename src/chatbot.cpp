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
#include "application.h"
#include <vector>
#include <iostream>
using namespace std;

vector<string> parseLine(const string& line, char delimiter) {
    vector<string> fields;
    string field = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == delimiter) {
            fields.push_back(field);
            field = "";
        }
        else {
            field += line[i];
        }
    }
    if (!field.empty()) {
        fields.push_back(field);
    }
    return fields;
}
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
            // system("cls");
            cout << "string contains only spaces! \n";
            getline(cin, input);
        }
        else
        {
            // system("cls");
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

//int ChatbotInput::extractKeywords(const string& input, string keywords[], int maxKeywords) {
//    // TODO: Implement keyword extraction and return count
//}

// -----------------------------------------------
// Personal Information
// -----------------------------------------------

string ChatbotInput::getFullName() {
    string name;
    while (true) {
        cout << "Enter Full Name: ";
        name = readUserInput();

        if (isAlpha(name) && name.length() >= 3) {
            return name;
        }

        setColor(COLOR_RED);
        cout << "Invalid name! Name should contain only letters and be at least 3 characters.\n";
        setColor(COLOR_WHITE);
    }
}


string ChatbotInput::getFatherName() {
    string name;
    while (true) {
        cout << "Enter Father's Name: ";
        name = readUserInput();

        if (isAlpha(name) && name.length() >= 3) {
            return name;
        }

        setColor(COLOR_RED);
        cout << "Invalid name! Name should contain only letters and be at least 3 characters.\n";
        setColor(COLOR_WHITE);
    }
}


string ChatbotInput::getPostalAddress() {
    cout << "Enter Postal Address: ";
    return readUserInput();
}

string ChatbotInput::getContactNumber() {
    string phone;
    while (true) {
        cout << "Enter Contact Number (10-11 digits): ";
        phone = readUserInput();

        if (isValidPhone(phone)) {
            return phone;
        }

        setColor(COLOR_RED);
        cout << "Invalid phone number! Please enter 10-11 digits.\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getEmail() {
    string email;
    while (true) {
        cout << "Enter Email Address: ";
        email = readUserInput();

        if (isValidEmail(email)) {
            return email;
        }

        setColor(COLOR_RED);
        cout << "Invalid email format! Please enter a valid email (e.g., user@example.com).\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getGender() {
    string gender;
    while (true) {
        cout << "Enter Gender (Male/Female/Other): ";
        gender = readUserInput();

        string lower = toLowerString(gender);
        if (lower == "male" || lower == "female" || lower == "other" || lower == "m" || lower == "f") {
            if (lower == "m") return "Male";
            if (lower == "f") return "Female";
            // Capitalize first letter
            gender[0] = toupper(gender[0]);
            return gender;
        }

        setColor(COLOR_RED);
        cout << "Invalid gender! Please enter Male, Female, or Other.\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getMaritalStatus() {
    string status;
    while (true) {
        cout << "Enter Marital Status (Single/Married/Divorced/Widowed): ";
        status = readUserInput();

        string lower = toLowerString(status);
        if (lower == "single" || lower == "married" || lower == "divorced" || lower == "widowed" ||
            lower == "s" || lower == "m" || lower == "d" || lower == "w") {
            if (lower == "s") return "Single";
            if (lower == "m") return "Married";
            if (lower == "d") return "Divorced";
            if (lower == "w") return "Widowed";
            // Capitalize first letter
            status[0] = toupper(status[0]);
            return status;
        }

        setColor(COLOR_RED);
        cout << "Invalid status! Please enter Single, Married, Divorced, or Widowed.\n";
        setColor(COLOR_WHITE);
    }
}

int ChatbotInput::getDependents() {
    while (true) {
        cout << "Enter Number of Dependents (0-20): ";
        int d;
        cin >> d;

        if (cin.fail() || d < 0 || d > 20) {
            cin.clear();
            cin.ignore(10000, '\n');
            setColor(COLOR_RED);
            cout << "Invalid input! Please enter a number between 0 and 20.\n";
            setColor(COLOR_WHITE);
        }
        else {
            cin.ignore();
            return d;
        }
    }
}

// -----------------------------------------------
// CNIC & Employment
// -----------------------------------------------

string ChatbotInput::getCNIC() {
    string cnic;
    while (true) {
        cout << "Enter CNIC (13 digits, format: XXXXX-XXXXXXX-X or XXXXXXXXXXXXX): ";
        cnic = readUserInput();

        if (isValidCNIC(cnic)) {
            // Format it properly if needed
            string digits = "";
            for (int i = 0; i < cnic.length(); i++) {
                if (cnic[i] >= '0' && cnic[i] <= '9') {
                    digits += cnic[i];
                }
            }
            // Return formatted: XXXXX-XXXXXXX-X
            if (digits.length() == 13) {
                return digits.substr(0, 5) + "-" + digits.substr(5, 7) + "-" + digits.substr(12, 1);
            }
        }

        setColor(COLOR_RED);
        cout << "Invalid CNIC! Please enter exactly 13 digits.\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getCNICExpiry() {
    string date;
    while (true) {
        cout << "Enter CNIC Expiry Date (DD-MM-YYYY): ";
        date = readUserInput();

        if (isValidDate(date)) {
            return date;
        }

        setColor(COLOR_RED);
        cout << "Invalid date format! Please use DD-MM-YYYY (e.g., 25-12-2030).\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getEmploymentStatus() {
    string status;
    while (true) {
        cout << "Select Employment Status:\n";
        cout << "1. Salaried\n2. Business\n3. Self-Employed\n4. Unemployed\n> ";
        status = readUserInput();

        if (status == "1") return "Salaried";
        if (status == "2") return "Business";
        if (status == "3") return "Self-Employed";
        if (status == "4") return "Unemployed";

        string lower = toLowerString(status);
        if (lower == "salaried") return "Salaried";
        if (lower == "business") return "Business";
        if (lower == "self-employed" || lower == "self employed") return "Self-Employed";
        if (lower == "unemployed") return "Unemployed";

        setColor(COLOR_RED);
        cout << "Invalid selection! Please enter 1, 2, 3, or 4.\n";
        setColor(COLOR_WHITE);
    }
}


// -----------------------------------------------
// Financial Information
// -----------------------------------------------

long long ChatbotInput::getAnnualIncome() {
    while (true) {
        cout << "Enter Annual Income (PKR): ";
        long long x;
        cin >> x;

        if (cin.fail() || x < 0 || x > 999999999999LL) {
            cin.clear();
            cin.ignore(10000, '\n');
            setColor(COLOR_RED);
            cout << "Invalid income! Please enter a valid positive amount.\n";
            setColor(COLOR_WHITE);
        }
        else {
            cin.ignore();
            return x;
        }
    }
}

long long ChatbotInput::getAvgBill() {
    while (true) {
        cout << "Enter Average Electricity Bill (Last 12 months, PKR): ";
        long long x;
        cin >> x;

        if (cin.fail() || x < 0 || x > 1000000) {
            cin.clear();
            cin.ignore(10000, '\n');
            setColor(COLOR_RED);
            cout << "Invalid amount! Please enter a reasonable bill amount.\n";
            setColor(COLOR_WHITE);
        }
        else {
            cin.ignore();
            return x;
        }
    }
}

long long ChatbotInput::getCurrentMonthBill() {
    while (true) {
        cout << "Enter Current Month's Electricity Bill (PKR): ";
        long long x;
        cin >> x;

        if (cin.fail() || x < 0 || x > 1000000) {
            cin.clear();
            cin.ignore(10000, '\n');
            setColor(COLOR_RED);
            cout << "Invalid amount! Please enter a reasonable bill amount.\n";
            setColor(COLOR_WHITE);
        }
        else {
            cin.ignore();
            return x;
        }
    }
}

// -----------------------------------------------
// Existing Loan Information
// -----------------------------------------------

bool ChatbotInput::askHasExistingLoan() {
    cout << "Do you have any existing loan? (yes/no): ";
    string response = readUserInput();
    response = toLowerString(response);
    return (response == "yes");
}

long long ChatbotInput::getExistingLoanAmount() {
    cout << "Enter Total Existing Loan Amount: ";
    long long x;
    cin >> x;
    cin.ignore();
    return x;
}

long long ChatbotInput::getAmountReturned() {
    cout << "Enter Amount Returned: ";
    long long x;
    cin >> x;
    cin.ignore();
    return x;
}

long long ChatbotInput::getAmountDue() {
    cout << "Enter Remaining Amount Due: ";
    long long x;
    cin >> x;
    cin.ignore();
    return x;
}

string ChatbotInput::getExistingLoanBank() {
    cout << "Enter Bank Name: ";
    return readUserInput();
}

string ChatbotInput::getExistingLoanCategory() {
    cout << "Enter Loan Category: ";
    return readUserInput();
}

// -----------------------------------------------
// References
// -----------------------------------------------

string ChatbotInput::getReferenceName(int refIndex) {
    cout << "Enter Reference " << refIndex << " Name: ";
    return readUserInput();
}

string ChatbotInput::getReferenceCNIC(int refIndex) {
    string cnic;
    while (true) {
        cout << "Enter Reference " << refIndex << " CNIC: ";
        cnic = readUserInput();

        if (isValidCNIC(cnic)) {
            // Format it properly
            string digits = "";
            for (int i = 0; i < cnic.length(); i++) {
                if (cnic[i] >= '0' && cnic[i] <= '9') {
                    digits += cnic[i];
                }
            }
            if (digits.length() == 13) {
                return digits.substr(0, 5) + "-" + digits.substr(5, 7) + "-" + digits.substr(12, 1);
            }
        }

        setColor(COLOR_RED);
        cout << "Invalid CNIC! Please enter exactly 13 digits.\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getReferenceDate(int refIndex) {
    string date;
    while (true) {
        cout << "Enter Reference " << refIndex << " Date (DD-MM-YYYY): ";
        date = readUserInput();

        if (isValidDate(date)) {
            return date;
        }

        setColor(COLOR_RED);
        cout << "Invalid date format! Please use DD-MM-YYYY.\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getReferencePhone(int refIndex) {
    string phone;
    while (true) {
        cout << "Enter Reference " << refIndex << " Phone: ";
        phone = readUserInput();

        if (isValidPhone(phone)) {
            return phone;
        }

        setColor(COLOR_RED);
        cout << "Invalid phone number! Please enter 10-11 digits.\n";
        setColor(COLOR_WHITE);
    }
}

string ChatbotInput::getReferenceEmail(int refIndex) {
    string email;
    while (true) {
        cout << "Enter Reference " << refIndex << " Email: ";
        email = readUserInput();

        if (isValidEmail(email)) {
            return email;
        }

        setColor(COLOR_RED);
        cout << "Invalid email format!\n";
        setColor(COLOR_WHITE);
    }
}

// -----------------------------------------------
// File Uploads (Paths Only)
// -----------------------------------------------


// AYUB BUTT'S CODE 


string ChatbotInput::getCNICFrontPath(const string& userID) {
    cout << "Enter CNIC Front Image Path: ";
    string input;
    getline(cin, input);
    while (!isValidPath(input, userID))
    {
        getline(cin, input);
    }
    return input;
}

string ChatbotInput::getCNICBackPath(const string& userID) {
    cout << "Enter CNIC Back Image Path: ";
    string input;
    getline(cin, input);
    while (!isValidPath(input, userID))
    {
        getline(cin, input);
    }
    return input;
}

string ChatbotInput::getElectricityBillPath(const string& userID) {
    cout << "Enter Electricity Bill Image Path: ";
    string input;
    getline(cin, input);
    while (!isValidPath(input, userID))
    {
        getline(cin, input);
    }
    return input;
}

string ChatbotInput::getSalarySlipPath(const string& userID) {
    cout << "Enter Salary Slip Image Path: ";
    string input;
    getline(cin, input);
    while (!isValidPath(input, userID))
    {
        getline(cin, input);
    }
    return input;
}

string startLoanApplication() {
    system("cls");
    setColor(COLOR_CYAN);
    cout << "\n====================================================\n";
    cout << "          LOAN APPLICATION FORM                     \n";
    cout << "====================================================\n\n";
    setColor(COLOR_WHITE);

    Application app;
    ChatbotInput input;
    ChatbotDisplay display;
    ChatbotStorage storage;

    // Application Base Info
    app.applicationID = generateApplicationID();
    app.status = "Pending";      // Your struct has only "status"

    cout << "Application ID: " << app.applicationID << "\n\n";

    // ===== SECTION 1: PERSONAL INFO =====
    setColor(COLOR_YELLOW);
    cout << "\n--- Personal Information ---\n";
    setColor(COLOR_WHITE);

    app.fullName = input.getFullName();
    app.fatherName = input.getFatherName();
    app.postalAddress = input.getPostalAddress();
    app.contactNumber = input.getContactNumber();
    app.email = input.getEmail();
    app.gender = input.getGender();
    app.maritalStatus = input.getMaritalStatus();
    app.dependents = input.getDependents();

    // ===== SECTION 2: CNIC & EMPLOYMENT =====
    setColor(COLOR_YELLOW);
    cout << "\n--- CNIC & Employment Information ---\n";
    setColor(COLOR_WHITE);

    app.CNIC = input.getCNIC();
    app.CNICExpiry = input.getCNICExpiry();
    app.employmentStatus = input.getEmploymentStatus();

    // ===== SECTION 3: FINANCIAL INFO =====
    setColor(COLOR_YELLOW);
    cout << "\n--- Financial Information ---\n";
    setColor(COLOR_WHITE);

    app.annualIncome = input.getAnnualIncome();
    app.avgBill = input.getAvgBill();
    app.currentMonthBill = input.getCurrentMonthBill();

    // ===== SECTION 4: EXISTING LOAN =====
    setColor(COLOR_YELLOW);
    cout << "\n--- Existing Loan Information ---\n";
    setColor(COLOR_WHITE);

    app.hasExistingLoan = input.askHasExistingLoan();

    if (app.hasExistingLoan) {
        app.existingLoanAmount = input.getExistingLoanAmount();
        app.amountReturned = input.getAmountReturned();
        app.amountDue = input.getAmountDue();
        app.existingLoanBank = input.getExistingLoanBank();
        app.existingLoanCategory = input.getExistingLoanCategory();
    }
    else {
        app.existingLoanAmount = 0;
        app.amountReturned = 0;
        app.amountDue = 0;
        app.existingLoanBank = "N/A";
        app.existingLoanCategory = "N/A";
    }

    // ===== SECTION 5: REFERENCES =====
    setColor(COLOR_YELLOW);
    cout << "\n--- Reference Information ---\n";
    setColor(COLOR_WHITE);

    app.referenceName[0] = input.getReferenceName(1);
    app.referenceCNIC[0] = input.getReferenceCNIC(1);
    app.referenceDate[0] = input.getReferenceDate(1);
    app.referencePhone[0] = input.getReferencePhone(1);
    app.referenceEmail[0] = input.getReferenceEmail(1);

    app.referenceName[1] = input.getReferenceName(2);
    app.referenceCNIC[1] = input.getReferenceCNIC(2);
    app.referenceDate[1] = input.getReferenceDate(2);
    app.referencePhone[1] = input.getReferencePhone(2);
    app.referenceEmail[1] = input.getReferenceEmail(2);

    // now where will you check that these people are same? the function is provided in UTILS.H

    // ===== SECTION 6: DOCUMENTS =====
    setColor(COLOR_YELLOW);
    cout << "\n--- Document Upload ---\n";
    setColor(COLOR_WHITE);

    app.CNICFrontPath = input.getCNICFrontPath(app.applicationID);
    app.CNICBackPath = input.getCNICBackPath(app.applicationID);
    app.electricityBillPath = input.getElectricityBillPath(app.applicationID);
    app.salarySlipPath = input.getSalarySlipPath(app.applicationID);

    // ===== CONFIRMATION =====
    system("cls");

    display.showApplicationSummary(app);

    cout << "\n\nDo you want to submit this application? (yes/no): ";
    string confirm = input.readUserInput();

    if (toLowerString(confirm) == "yes" || toLowerString(confirm) == "y") {
        if (storage.saveApplicationToFile(app)) {
            setColor(COLOR_GREEN);
            cout << "\n====================================================\n";
            cout << "  APPLICATION SUBMITTED SUCCESSFULLY!              \n";
            cout << "  Application ID: " << app.applicationID << "\n";
            cout << "  Status: Pending Review                           \n";
            cout << "====================================================\n";
            setColor(COLOR_WHITE);
            return "Your loan application has been submitted successfully! Application ID: " + app.applicationID;
        }
        else {
            setColor(COLOR_RED);
            cout << "\nERROR: Failed to save application!\n";
            setColor(COLOR_WHITE);
            return "Error: Failed to submit application. Please try again.";
        }
    }
    else {
        setColor(COLOR_YELLOW);
        cout << "\nApplication cancelled.\n";
        setColor(COLOR_WHITE);
        return "Application cancelled. You can start again anytime.";
    }
}
// Generate monthly payment plan
void generateMonthlyPlan(long long loanAmount, long long downPayment, int months, string startMonth, int startYear) {
    long long principal = loanAmount - downPayment;
    long long monthlyPayment = principal / months;
    long long remaining = principal;

    string monthNames[] = { "January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December" };

    int currentMonth = 0;
    // Convert startMonth to index
    for (int i = 0; i < 12; i++) {
        if (toLowerString(startMonth) == toLowerString(monthNames[i])) {
            currentMonth = i;
            break;
        }
    }

    int currentYear = startYear;

    setColor(COLOR_CYAN);
    cout << "\n============================================================\n";
    cout << "               MONTHLY PAYMENT PLAN                         \n";
    cout << "============================================================\n";
    setColor(COLOR_WHITE);

    cout << "Loan Amount:     " << loanAmount << "\n";
    cout << "Down Payment:    " << downPayment << "\n";
    cout << "Principal:       " << principal << "\n";
    cout << "Installments:    " << months << " months\n";
    cout << "Monthly Payment: " << monthlyPayment << "\n\n";

    setColor(COLOR_YELLOW);
    cout << left << setw(20) << "Month"
        << setw(20) << "Payment"
        << setw(20) << "Total Paid"
        << setw(20) << "Remaining" << "\n";
    setColor(COLOR_CYAN);
    cout << "------------------------------------------------------------\n";
    setColor(COLOR_WHITE);

    for (int i = 1; i <= months; i++) {
        long long paid = monthlyPayment * i;
        remaining = principal - paid;
        if (remaining < 0) remaining = 0;

        string monthYear = monthNames[currentMonth] + " " + to_string(currentYear);

        cout << left << setw(20) << monthYear
            << setw(20) << monthlyPayment
            << setw(20) << paid
            << setw(20) << remaining << "\n";

        currentMonth++;
        if (currentMonth >= 12) {
            currentMonth = 0;
            currentYear++;
        }
    }

    setColor(COLOR_CYAN);
    cout << "============================================================\n";
    setColor(COLOR_WHITE);
}

bool QueryApplication(string target) {
    if (target.find("my applications") != string::npos ||
        target.find("application status") != string::npos ||
        target.find("check application") != string::npos) {

        cout << "Enter your CNIC (13 digits): ";
        ChatbotInput input;
        string cnic = input.readUserInput();

        ChatbotStorage storage;
        int total = storage.countApplicationsByCNIC(cnic);
        int pending = storage.countApplicationsByCNIC(cnic, "Pending");
        int approved = storage.countApplicationsByCNIC(cnic, "Approved");
        int rejected = storage.countApplicationsByCNIC(cnic, "Rejected");

        setColor(COLOR_CYAN);
        cout << "\n========================================\n";
        cout << "   APPLICATION STATUS FOR CNIC: " << cnic << "\n";
        cout << "========================================\n";
        setColor(COLOR_WHITE);

        cout << "Total Applications:    " << total << "\n";
        setColor(COLOR_YELLOW);
        cout << "Pending Applications:  " << pending << "\n";
        setColor(COLOR_GREEN);
        cout << "Approved Applications: " << approved << "\n";
        setColor(COLOR_RED);
        cout << "Rejected Applications: " << rejected << "\n";
        setColor(COLOR_WHITE);

        cout << "\n========================================\n";
        return true;
    }
    return false;
}

string viewMonthlyPlan(string target) {
    if (target.find("monthly plan") != string::npos ||
        target.find("payment plan") != string::npos ||
        target.find("installment plan") != string::npos) {

        cout << "Enter your Application ID: ";
        ChatbotInput input;
        string appID = input.readUserInput();

        ChatbotStorage storage;
        Application app = storage.getApplicationByID(appID);

        if (app.applicationID.empty()) {
            return "Application not found. Please check the ID and try again.";
        }

        if (app.status != "Approved") {
            return "This application is not approved yet. Status: " + app.status;
        }

        // Ask for loan details
        cout << "Enter Loan Amount: ";
        long long loanAmount;
        cin >> loanAmount;
        cin.ignore();

        cout << "Enter Down Payment: ";
        long long downPayment;
        cin >> downPayment;
        cin.ignore();

        cout << "Enter Number of Installments: ";
        int months;
        cin >> months;
        cin.ignore();

        cout << "Enter Starting Month (e.g., January): ";
        string startMonth = input.readUserInput();

        cout << "Enter Starting Year (e.g., 2025): ";
        int startYear;
        cin >> startYear;
        cin.ignore();

        generateMonthlyPlan(loanAmount, downPayment, months, startMonth, startYear);
        return "Monthly payment plan generated successfully.";
    }
    return "";
}
// ---------------------------------Chatbot Response Processing Module----------------------------
// LP4-8 Assigned to Kabeer

string ChatbotProcessor::generateResponse(const string& input, string filename) {
    static string selectedLoanType = ""; // "home", "car", or "scooter"
    static string selectedOption = "";   // stores selected make/model/area
    static bool awaitingInstallmentInput = false;
    static bool awaitingSelection = false;
    static string currentDataFile = "";
    static bool askToApply = false;

    string target = toLowerString(trimString(input));

    // ----------------Handle loan application response ----------------
    if (askToApply) {
        string low = toLowerString(target);
        if (low == "yes" || low == "y") {
            askToApply = false;
            awaitingInstallmentInput = false;
            awaitingSelection = false;
            selectedLoanType = "";
            return startLoanApplication();
        }
        else if (low == "no" || low == "n") {
            askToApply = false;
            awaitingInstallmentInput = false;
            awaitingSelection = false;
            selectedLoanType = "";
            return "Okay! You can select a different loan type from the main menu.";
        }
        else {
            return "Please enter YES to apply, or NO to go back.";
        }
    }

    // ----------------Handle Installment Selection ----------------
    if (awaitingInstallmentInput && !selectedLoanType.empty()) {
        if (input == "B" || input == "b") {
            awaitingInstallmentInput = false;
            awaitingSelection = true;
            return "Going back. Please make your selection again.";
        }

        ifstream file(currentDataFile);
        if (!file.is_open()) {
            return "Error: Cannot open data file";
        }

        string line;
        getline(file, line); // skip header
        bool found = false;

        setColor(11);
        cout << "\n================================================================\n";
        cout << "            Installment Plan (" << input << " months)\n";
        cout << "================================================================\n";

        if (selectedLoanType == "home") {
            setColor(14);
            cout << left << setw(15) << "Size"
                << setw(22) << "Price"
                << setw(20) << "Down Payment"
                << setw(20) << "Monthly Installment" << endl;
            setColor(8);
            cout << "--------------------------------------------------------------------\n";

            while (getline(file, line)) {
                vector<string> fields = parseLine(line, '#');
                if (fields.size() >= 5) {
                    string area = fields[0];
                    string size = fields[1];
                    string inst = fields[2];
                    string price = fields[3];
                    string down = fields[4];

                    if (area == selectedOption && inst == input) {
                        long long priceVal = stoll(removeCommas(price));
                        long long downVal = stoll(removeCommas(down));
                        long long months = stoll(inst);
                        long long monthly = (priceVal - downVal) / months;

                        found = true;
                        setColor(10);
                        cout << left << setw(15) << size
                            << setw(22) << price
                            << setw(20) << down
                            << setw(20) << to_string(monthly) << endl;
                    }
                }
            }
        }
        else if (selectedLoanType == "car") {
            setColor(14);
            cout << left << setw(15) << "Model"
                << setw(12) << "Engine"
                << setw(8) << "Used"
                << setw(8) << "Year"
                << setw(20) << "Price"
                << setw(18) << "Down Payment"
                << setw(20) << "Monthly" << endl;
            setColor(8);
            cout << "--------------------------------------------------------------------\n";

            while (getline(file, line)) {
                vector<string> fields = parseLine(line, '#');
                if (fields.size() >= 8) {
                    string make = fields[0];
                    string model = fields[1];
                    string engine = fields[2];
                    string used = fields[3];
                    string year = fields[4];
                    string inst = fields[5];
                    string price = fields[6];
                    string down = fields[7];

                    if (make == selectedOption && inst == input) {
                        long long priceVal = stoll(removeCommas(price));
                        long long downVal = stoll(removeCommas(down));
                        long long months = stoll(inst);
                        long long monthly = (priceVal - downVal) / months;

                        found = true;
                        setColor(10);
                        cout << left << setw(15) << model
                            << setw(12) << engine
                            << setw(8) << used
                            << setw(8) << year
                            << setw(20) << price
                            << setw(18) << down
                            << setw(20) << to_string(monthly) << endl;
                    }
                }
            }
        }
        else if (selectedLoanType == "scooter") {
            setColor(14);
            cout << left << setw(15) << "Model"
                << setw(12) << "Range(KM)"
                << setw(15) << "Charge(Hrs)"
                << setw(15) << "Speed(KM/H)"
                << setw(20) << "Price"
                << setw(18) << "Down Payment"
                << setw(20) << "Monthly" << endl;
            setColor(8);
            cout << "--------------------------------------------------------------------\n";

            while (getline(file, line)) {
                vector<string> fields = parseLine(line, '#');
                if (fields.size() >= 8) {
                    string make = fields[0];
                    string model = fields[1];
                    string distance = fields[2];
                    string charging = fields[3];
                    string speed = fields[4];
                    string inst = fields[5];
                    string price = fields[6];
                    string down = fields[7];

                    if (make == selectedOption && inst == input) {
                        long long priceVal = stoll(removeCommas(price));
                        long long downVal = stoll(removeCommas(down));
                        long long months = stoll(inst);
                        long long monthly = (priceVal - downVal) / months;

                        found = true;
                        setColor(10);
                        cout << left << setw(15) << model
                            << setw(12) << distance
                            << setw(15) << charging
                            << setw(15) << speed
                            << setw(20) << price
                            << setw(18) << down
                            << setw(20) << to_string(monthly) << endl;
                    }
                }
            }
        }

        file.close();
        setColor(8);
        cout << "--------------------------------------------------------------------\n";
        setColor(7);

        if (!found) {
            return "No plan found for that installment period. Try again or 'B' to go back.";
        }
        else {
            awaitingInstallmentInput = false;
            awaitingSelection = false;
            askToApply = true;
            return "\nWould you like to apply for this loan? (yes/no)";
        }
    }

    // ----------------Handle Selection (Area/Make) ----------------
    if (awaitingSelection && !selectedLoanType.empty()) {
        if (input == "B" || input == "b") {
            awaitingSelection = false;
            selectedLoanType = "";
            return "Returning to main menu.";
        }

        ifstream file(currentDataFile);
        if (!file.is_open()) {
            return "Error: Cannot open data file";
        }

        string line;
        getline(file, line); // skip header

        // Convert input to proper format based on loan type
        if (selectedLoanType == "home") {
            selectedOption = "Area " + input;
        }
        else if (selectedLoanType == "car" || selectedLoanType == "scooter") {
            // Convert "1" -> "Make 1", "2" -> "Make 2"
            selectedOption = "Make " + input;
        }
        else {
            selectedOption = input;
        }

        setColor(11);
        cout << "\n================================================================\n";
        cout << "                  " << selectedLoanType << " Loan Options\n";
        cout << "================================================================\n";

        if (selectedLoanType == "home") {
            setColor(14);
            cout << left << setw(15) << "Size"
                << setw(18) << "Installments"
                << setw(22) << "Price"
                << setw(18) << "Down Payment" << endl;
            setColor(8);
            cout << "---------------------------------------------------------------\n";

            bool found = false;
            while (getline(file, line)) {
                vector<string> fields = parseLine(line, '#');
                if (fields.size() >= 5 && fields[0] == selectedOption) {
                    found = true;
                    setColor(10);
                    cout << left << setw(15) << fields[1]
                        << setw(18) << fields[2]
                        << setw(22) << fields[3]
                        << setw(18) << fields[4] << endl;
                }
            }

            file.close();
            setColor(8);
            cout << "---------------------------------------------------------------\n";
            setColor(7);

            if (!found) {
                awaitingSelection = false;
                return "No options available. Please try again.";
            }
            awaitingInstallmentInput = true;
            awaitingSelection = false;
            return "\nEnter number of installments (e.g. 36, 48, 60):";
        }
        else if (selectedLoanType == "car") {
            setColor(14);
            cout << left << setw(15) << "Model"
                << setw(12) << "Engine"
                << setw(8) << "Used"
                << setw(8) << "Year"
                << setw(18) << "Installments"
                << setw(20) << "Price"
                << setw(18) << "Down" << endl;
            setColor(8);
            cout << "---------------------------------------------------------------\n";

            bool found = false;
            while (getline(file, line)) {
                vector<string> fields = parseLine(line, '#');
                if (fields.size() >= 8 && fields[0] == selectedOption) {
                    found = true;
                    setColor(10);
                    cout << left << setw(15) << fields[1]
                        << setw(12) << fields[2]
                        << setw(8) << fields[3]
                        << setw(8) << fields[4]
                        << setw(18) << fields[5]
                        << setw(20) << fields[6]
                        << setw(18) << fields[7] << endl;
                }
            }

            file.close();
            setColor(8);
            cout << "---------------------------------------------------------------\n";
            setColor(7);

            if (!found) {
                awaitingSelection = false;
                return "No options available. Please try again.";
            }
            awaitingInstallmentInput = true;
            awaitingSelection = false;
            return "\nEnter number of installments (e.g. 48, 60):";
        }
        else if (selectedLoanType == "scooter") {
            setColor(14);
            cout << left << setw(15) << "Model"
                << setw(12) << "Range"
                << setw(15) << "Charge Time"
                << setw(15) << "Max Speed"
                << setw(18) << "Installments"
                << setw(20) << "Price"
                << setw(18) << "Down" << endl;
            setColor(8);
            cout << "---------------------------------------------------------------\n";

            bool found = false;
            while (getline(file, line)) {
                vector<string> fields = parseLine(line, '#');
                if (fields.size() >= 8 && fields[0] == selectedOption) {
                    found = true;
                    setColor(10);
                    cout << left << setw(15) << fields[1]
                        << setw(12) << fields[2]
                        << setw(15) << fields[3]
                        << setw(15) << fields[4]
                        << setw(18) << fields[5]
                        << setw(20) << fields[6]
                        << setw(18) << fields[7] << endl;
                }
            }

            file.close();
            setColor(8);
            cout << "---------------------------------------------------------------\n";
            setColor(7);

            if (!found) {
                awaitingSelection = false;
                return "No options available. Please try again.";
            }
            awaitingInstallmentInput = true;
            awaitingSelection = false;
            return "\nEnter number of installments (e.g. 48, 60):";
        }
    }

    // ----------------Initial Loan Type Selection ----------------
    if (target == "h") {
        selectedLoanType = "home";
        currentDataFile = "data/Home.txt";
        awaitingSelection = true;
        return "You are applying for a home loan. Please select area (1, 2, 3, or 4):";
    }
    else if (target == "c") {
        selectedLoanType = "car";
        currentDataFile = "data/Car.txt";
        awaitingSelection = true;
        return "You are applying for a car loan. Please select make (Make 1, Make 2):";
    }
    else if (target == "s") {
        selectedLoanType = "scooter";
        currentDataFile = "data/Scooter.txt";
        awaitingSelection = true;
        return "You are applying for a scooter loan. Please select make (Make 1):";
    }

    // ---------------- Query Applications by CNIC ----------------
    if (QueryApplication(target))
        return "Application status retrieved successfully.";

    // ---------------- View Monthly Plan for Approved Application ----------------
    string monthlyPlanResponse = viewMonthlyPlan(target);
    if (!monthlyPlanResponse.empty()) {
        return monthlyPlanResponse;
    }

    // ---------------- Generic Response Handling ----------------
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


//string ChatbotProcessor::analyzeIntent(const string& input) {
//    // TODO: Implement intent/sentiment analysis
//}
//
//string ChatbotProcessor::processLoanQuery(const string keywords[], int keywordCount) {
//    // TODO: Implement loan query handling
//}
//
//string ChatbotProcessor::getContextInfo(const string& query) {
//    // TODO: Implement context retrieval
//}

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
    cout << endl << endl;
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

// show a formatted application summary to the console
void ChatbotDisplay::showApplicationSummary(Application& app)
{
    setColor(COLOR_CYAN);
    cout << "\n=================== Application Summary ===================\n";
    setColor(COLOR_WHITE);

    cout << "Application ID: " << app.applicationID << "\n";
    cout << "Status:         " << app.status << "\n\n";

    cout << "---- Personal Info ----\n";
    cout << "Full Name:      " << app.fullName << "\n";
    cout << "Father Name:    " << app.fatherName << "\n";
    cout << "Postal Address: " << app.postalAddress << "\n";
    cout << "Contact No.:    " << app.contactNumber << "\n";
    cout << "Email:          " << app.email << "\n";
    cout << "Gender:         " << app.gender << "\n";
    cout << "Marital Status: " << app.maritalStatus << "\n";
    cout << "Dependents:     " << app.dependents << "\n\n";

    cout << "---- CNIC & Employment ----\n";
    cout << "CNIC:           " << app.CNIC << "\n";
    cout << "CNIC Expiry:    " << app.CNICExpiry << "\n";
    cout << "Employment:     " << app.employmentStatus << "\n\n";

    cout << "---- Financial Info ----\n";
    cout << "Annual Income:  " << app.annualIncome << "\n";
    cout << "Avg Bill:       " << app.avgBill << "\n";
    cout << "Current Bill:   " << app.currentMonthBill << "\n\n";

    cout << "---- Existing Loan ----\n";
    cout << "Has Loan:       " << (app.hasExistingLoan ? "Yes" : "No") << "\n";
    if (app.hasExistingLoan) {
        cout << "Loan Amount:    " << app.existingLoanAmount << "\n";
        cout << "Amount Returned:" << app.amountReturned << "\n";
        cout << "Amount Due:     " << app.amountDue << "\n";
        cout << "Bank:           " << app.existingLoanBank << "\n";
        cout << "Category:       " << app.existingLoanCategory << "\n\n";
    }
    else cout << "\n";

    cout << "---- References ----\n";
    for (int i = 0; i < 2; ++i) {
        cout << "Ref " << (i + 1) << " Name:  " << app.referenceName[i] << "\n";
        cout << "Ref " << (i + 1) << " CNIC:  " << app.referenceCNIC[i] << "\n";
        cout << "Ref " << (i + 1) << " Date:  " << app.referenceDate[i] << "\n";
        cout << "Ref " << (i + 1) << " Phone: " << app.referencePhone[i] << "\n";
        cout << "Ref " << (i + 1) << " Email: " << app.referenceEmail[i] << "\n";
    }
    cout << "\n---- Documents (paths) ----\n";
    cout << "CNIC Front:     " << app.CNICFrontPath << "\n";
    cout << "CNIC Back:      " << app.CNICBackPath << "\n";
    cout << "Electricity Bill:" << app.electricityBillPath << "\n";
    cout << "Salary Slip:    " << app.salarySlipPath << "\n";

    setColor(COLOR_CYAN);
    cout << "===========================================================\n\n";
    setColor(COLOR_WHITE);
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



// --------------------------------------Chatbot Storage-----------------------------------

// persist application to disk as a text file (returns true on success)
bool ChatbotStorage::saveApplicationToFile(Application app)
{
    // ensure directories exist (uses WinAPI)
    CreateDirectoryA("data", NULL);
    CreateDirectoryA("data\\applications", NULL);

    string path = string("data\\applications\\") + app.applicationID + ".txt";
    ofstream ofs(path.c_str());
    if (!ofs.is_open()) return false;

    ofs << "ApplicationID:" << app.applicationID << "\n";
    ofs << "Status:" << app.status << "\n\n";

    ofs << "FullName:" << app.fullName << "\n";
    ofs << "FatherName:" << app.fatherName << "\n";
    ofs << "PostalAddress:" << app.postalAddress << "\n";
    ofs << "ContactNumber:" << app.contactNumber << "\n";
    ofs << "Email:" << app.email << "\n";
    ofs << "Gender:" << app.gender << "\n";
    ofs << "MaritalStatus:" << app.maritalStatus << "\n";
    ofs << "Dependents:" << app.dependents << "\n\n";

    ofs << "CNIC:" << app.CNIC << "\n";
    ofs << "CNICExpiry:" << app.CNICExpiry << "\n";
    ofs << "EmploymentStatus:" << app.employmentStatus << "\n\n";

    ofs << "AnnualIncome:" << app.annualIncome << "\n";
    ofs << "AvgBill:" << app.avgBill << "\n";
    ofs << "CurrentMonthBill:" << app.currentMonthBill << "\n\n";

    ofs << "HasExistingLoan:" << (app.hasExistingLoan ? "1" : "0") << "\n";
    ofs << "ExistingLoanAmount:" << app.existingLoanAmount << "\n";
    ofs << "AmountReturned:" << app.amountReturned << "\n";
    ofs << "AmountDue:" << app.amountDue << "\n";
    ofs << "ExistingLoanBank:" << app.existingLoanBank << "\n";
    ofs << "ExistingLoanCategory:" << app.existingLoanCategory << "\n\n";

    for (int i = 0; i < 2; ++i) {
        ofs << "ReferenceName" << i << ":" << app.referenceName[i] << "\n";
        ofs << "ReferenceCNIC" << i << ":" << app.referenceCNIC[i] << "\n";
        ofs << "ReferenceDate" << i << ":" << app.referenceDate[i] << "\n";
        ofs << "ReferencePhone" << i << ":" << app.referencePhone[i] << "\n";
        ofs << "ReferenceEmail" << i << ":" << app.referenceEmail[i] << "\n";
    }
    ofs << "\nCNICFrontPath:" << app.CNICFrontPath << "\n";
    ofs << "CNICBackPath:" << app.CNICBackPath << "\n";
    ofs << "ElectricityBillPath:" << app.electricityBillPath << "\n";
    ofs << "SalarySlipPath:" << app.salarySlipPath << "\n";

    ofs.close();
    return true;
}

// Count applications by CNIC (optionally filter by status)
int ChatbotStorage::countApplicationsByCNIC(const string& cnic, const string& status) {
    int count = 0;

    // Open applications directory
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA("data\\applications\\*.txt", &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    }

    do {
        string filename = findData.cFileName;
        string filepath = "data\\applications\\" + filename;

        ifstream file(filepath);
        if (!file.is_open()) continue;

        string line;
        string fileCNIC = "";
        string fileStatus = "";

        // Read file to find CNIC and Status
        while (getline(file, line)) {
            if (line.find("CNIC:") == 0) {
                fileCNIC = line.substr(5);
            }
            if (line.find("Status:") == 0) {
                fileStatus = line.substr(7);
            }
        }
        file.close();

        // Check if CNIC matches
        if (fileCNIC == cnic) {
            // If status filter is empty, count all
            if (status.empty()) {
                count++;
            }
            // If status filter matches, count
            else if (fileStatus == status) {
                count++;
            }
        }

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return count;
}

// Get all applications for a CNIC
vector<Application> ChatbotStorage::getApplicationsByCNIC(const string& cnic) {
    vector<Application> apps;

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA("data\\applications\\*.txt", &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return apps;
    }

    do {
        string filename = findData.cFileName;
        string filepath = "data\\applications\\" + filename;

        ifstream file(filepath);
        if (!file.is_open()) continue;

        Application app;
        string line;

        // Parse the file
        while (getline(file, line)) {
            if (line.find("ApplicationID:") == 0) app.applicationID = line.substr(14);
            else if (line.find("Status:") == 0) app.status = line.substr(7);
            else if (line.find("FullName:") == 0) app.fullName = line.substr(9);
            else if (line.find("FatherName:") == 0) app.fatherName = line.substr(11);
            else if (line.find("CNIC:") == 0) app.CNIC = line.substr(5);
            else if (line.find("CNICExpiry:") == 0) app.CNICExpiry = line.substr(11);
            else if (line.find("Email:") == 0) app.email = line.substr(6);
            else if (line.find("ContactNumber:") == 0) app.contactNumber = line.substr(14);
            else if (line.find("AnnualIncome:") == 0) app.annualIncome = stoll(line.substr(13));
            // Add more fields as needed
        }
        file.close();

        // If CNIC matches, add to vector
        if (app.CNIC == cnic) {
            apps.push_back(app);
        }

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return apps;
}

// Get single application by ID
Application ChatbotStorage::getApplicationByID(const string& appID) {
    Application app;
    string filepath = "data\\applications\\" + appID + ".txt";

    ifstream file(filepath);
    if (!file.is_open()) {
        app.applicationID = ""; // Empty means not found
        return app;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("ApplicationID:") == 0) app.applicationID = line.substr(14);
        else if (line.find("Status:") == 0) app.status = line.substr(7);
        else if (line.find("FullName:") == 0) app.fullName = line.substr(9);
        else if (line.find("FatherName:") == 0) app.fatherName = line.substr(11);
        else if (line.find("PostalAddress:") == 0) app.postalAddress = line.substr(14);
        else if (line.find("ContactNumber:") == 0) app.contactNumber = line.substr(14);
        else if (line.find("Email:") == 0) app.email = line.substr(6);
        else if (line.find("Gender:") == 0) app.gender = line.substr(7);
        else if (line.find("MaritalStatus:") == 0) app.maritalStatus = line.substr(14);
        else if (line.find("Dependents:") == 0) app.dependents = stoi(line.substr(11));
        else if (line.find("CNIC:") == 0) app.CNIC = line.substr(5);
        else if (line.find("CNICExpiry:") == 0) app.CNICExpiry = line.substr(11);
        else if (line.find("EmploymentStatus:") == 0) app.employmentStatus = line.substr(17);
        else if (line.find("AnnualIncome:") == 0) app.annualIncome = stoll(line.substr(13));
        else if (line.find("AvgBill:") == 0) app.avgBill = stoll(line.substr(8));
        else if (line.find("CurrentMonthBill:") == 0) app.currentMonthBill = stoll(line.substr(17));
        else if (line.find("HasExistingLoan:") == 0) app.hasExistingLoan = (line.substr(16) == "1");
        else if (line.find("ExistingLoanAmount:") == 0) app.existingLoanAmount = stoll(line.substr(19));
        else if (line.find("AmountReturned:") == 0) app.amountReturned = stoll(line.substr(15));
        else if (line.find("AmountDue:") == 0) app.amountDue = stoll(line.substr(10));
        else if (line.find("ExistingLoanBank:") == 0) app.existingLoanBank = line.substr(17);
        else if (line.find("ExistingLoanCategory:") == 0) app.existingLoanCategory = line.substr(21);
        // Parse references
        else if (line.find("ReferenceName0:") == 0) app.referenceName[0] = line.substr(15);
        else if (line.find("ReferenceCNIC0:") == 0) app.referenceCNIC[0] = line.substr(15);
        else if (line.find("ReferenceDate0:") == 0) app.referenceDate[0] = line.substr(15);
        else if (line.find("ReferencePhone0:") == 0) app.referencePhone[0] = line.substr(16);
        else if (line.find("ReferenceEmail0:") == 0) app.referenceEmail[0] = line.substr(16);
        else if (line.find("ReferenceName1:") == 0) app.referenceName[1] = line.substr(15);
        else if (line.find("ReferenceCNIC1:") == 0) app.referenceCNIC[1] = line.substr(15);
        else if (line.find("ReferenceDate1:") == 0) app.referenceDate[1] = line.substr(15);
        else if (line.find("ReferencePhone1:") == 0) app.referencePhone[1] = line.substr(16);
        else if (line.find("ReferenceEmail1:") == 0) app.referenceEmail[1] = line.substr(16);
        // Parse document paths
        else if (line.find("CNICFrontPath:") == 0) app.CNICFrontPath = line.substr(14);
        else if (line.find("CNICBackPath:") == 0) app.CNICBackPath = line.substr(13);
        else if (line.find("ElectricityBillPath:") == 0) app.electricityBillPath = line.substr(20);
        else if (line.find("SalarySlipPath:") == 0) app.salarySlipPath = line.substr(15);
    }

    file.close();
    return app;
}
// --------------------------------------Testing and Debug Module-----------------------------------
//LP4-10 Assigned to Haider

// Test if all inputs from Utterances.txt are validated correctly
bool ChatbotTester::testInputProcessing()
{
    setColor(COLOR_MAGENTA);
    cout << "\n=== Testing Input Processing ===" << endl << endl;
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
    cout << "\n=== Testing Response Generation ===" << endl << endl;
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
            if (response == expected) {
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
    cout << "\n=== Testing Home Loan Data ===" << endl << endl;
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

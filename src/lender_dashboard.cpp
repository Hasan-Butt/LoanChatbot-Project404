#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <string>
#include "lender_dashboard.h"
#include <conio.h>
#include "utils.h"
#include "application.h"

using namespace std;
 // ===== Lender Dashboard EPIC LP4-20 Assigned to Kabeer =====
void LenderDashboard::run() {
    system("cls");
    displayHeader();
    
    int choice;
    do {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        system("cls");
        
        switch(choice) {
            case 1:
                viewAllApplications();
                break;
            case 2:
                viewPendingApplications();
                break;
            case 3:
                viewApplicationDetails();
                break;
            case 4:
                approveApplication();
                break;
            case 5:
                rejectApplication();
                break;
            case 6:
                cout << "Exiting Lender Dashboard...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
        
        if (choice != 6) {
            pauseAndClear();
        }
        
    } while (choice != 6);
}

void LenderDashboard::displayHeader() {
    setColor(COLOR_CYAN);
    cout << "\n==============================================\n";
    cout << "        LENDER DASHBOARD - LoanMate          \n";
    cout << "==============================================\n\n";
    setColor(COLOR_WHITE);
}

void LenderDashboard::showMenu() {
    setColor(COLOR_YELLOW);
    cout << "\n========== MENU ==========\n";
    setColor(COLOR_WHITE);
    cout << "1. View All Applications\n";
    cout << "2. View Pending Applications\n";
    cout << "3. View Application Details\n";
    cout << "4. Approve Application\n";
    cout << "5. Reject Application\n";
    cout << "6. Exit\n";
    cout << "==========================\n\n";
}

void LenderDashboard::pauseAndClear() {
    cout << "\nPress any key to continue...";
    _getch();
    system("cls");
}

void LenderDashboard::viewAllApplications() {
    setColor(COLOR_CYAN);
    cout << "========== ALL APPLICATIONS ==========\n\n";
    setColor(COLOR_WHITE);
    
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA("data\\applications\\*.txt", &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "No applications found.\n";
        return;
    }
    
    cout << left << setw(15) << "App ID" 
         << setw(25) << "Name" 
         << setw(20) << "CNIC" 
         << setw(15) << "Status" << "\n";
    cout << "--------------------------------------------------------------\n";
    
    do {
        string filename = findData.cFileName;
        string appID = filename.substr(0, filename.find(".txt"));
        
        Application app = loadApplication(appID);
        if (!app.applicationID.empty()) {
            cout << left << setw(15) << app.applicationID
                 << setw(25) << app.fullName
                 << setw(20) << app.CNIC
                 << setw(15) << app.status << "\n";
        }
        
    } while (FindNextFileA(hFind, &findData));
    
    FindClose(hFind);
}

void LenderDashboard::viewPendingApplications() {
    setColor(COLOR_YELLOW);
    cout << "========== PENDING APPLICATIONS ==========\n\n";
    setColor(COLOR_WHITE);
    
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA("data\\applications\\*.txt", &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "No applications found.\n";
        return;
    }
    
    cout << left << setw(15) << "App ID" 
         << setw(25) << "Name" 
         << setw(20) << "CNIC" << "\n";
    cout << "------------------------------------------------------\n";
    
    int count = 0;
    do {
        string filename = findData.cFileName;
        string appID = filename.substr(0, filename.find(".txt"));
        
        Application app = loadApplication(appID);
        if (!app.applicationID.empty() && app.status == "Pending") {
            cout << left << setw(15) << app.applicationID
                 << setw(25) << app.fullName
                 << setw(20) << app.CNIC << "\n";
            count++;
        }
        
    } while (FindNextFileA(hFind, &findData));
    
    FindClose(hFind);
    
    if (count == 0) {
        cout << "No pending applications.\n";
    }
}

void LenderDashboard::viewApplicationDetails() {
    cout << "Enter Application ID: ";
    string appID;
    getline(cin, appID);
    
    Application app = loadApplication(appID);
    
    if (app.applicationID.empty()) {
        setColor(COLOR_RED);
        cout << "Application not found!\n";
        setColor(COLOR_WHITE);
        return;
    }
    
    // Display full details
    setColor(COLOR_CYAN);
    cout << "\n========== APPLICATION DETAILS ==========\n";
    setColor(COLOR_WHITE);
    
    cout << "ID:             " << app.applicationID << "\n";
    cout << "Status:         " << app.status << "\n";
    cout << "Name:           " << app.fullName << "\n";
    cout << "Father's Name:  " << app.fatherName << "\n";
    cout << "CNIC:           " << app.CNIC << "\n";
    cout << "Contact:        " << app.contactNumber << "\n";
    cout << "Email:          " << app.email << "\n";
    cout << "Employment:     " << app.employmentStatus << "\n";
    cout << "Annual Income:  " << app.annualIncome << "\n";
    cout << "Existing Loan:  " << (app.hasExistingLoan ? "Yes" : "No") << "\n";
    if (app.hasExistingLoan) {
        cout << "  Amount Due:   " << app.amountDue << "\n";
    }
    cout << "\nReferences:\n";
    cout << "  1. " << app.referenceName[0] << " (" << app.referenceCNIC[0] << ")\n";
    cout << "  2. " << app.referenceName[1] << " (" << app.referenceCNIC[1] << ")\n";
}

void LenderDashboard::approveApplication() {
    cout << "Enter Application ID to approve: ";
    string appID;
    getline(cin, appID);
    
    if (updateApplicationStatus(appID, "Approved")) {
        setColor(COLOR_GREEN);
        cout << "Application " << appID << " has been APPROVED.\n";
        setColor(COLOR_WHITE);
    } else {
        setColor(COLOR_RED);
        cout << "Failed to approve application.\n";
        setColor(COLOR_WHITE);
    }
}

void LenderDashboard::rejectApplication() {
    cout << "Enter Application ID to reject: ";
    string appID;
    getline(cin, appID);
    
    if (updateApplicationStatus(appID, "Rejected")) {
        setColor(COLOR_RED);
        cout << "Application " << appID << " has been REJECTED.\n";
        setColor(COLOR_WHITE);
    } else {
        setColor(COLOR_RED);
        cout << "Failed to reject application.\n";
        setColor(COLOR_WHITE);
    }
}

Application LenderDashboard::loadApplication(const string& appID) {
    Application app;
    string filepath = "data\\applications\\" + appID + ".txt";
    
    ifstream file(filepath);
    if (!file.is_open()) {
        app.applicationID = "";
        return app;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.find("ApplicationID:") == 0) app.applicationID = line.substr(14);
        else if (line.find("Status:") == 0) app.status = line.substr(7);
        else if (line.find("FullName:") == 0) app.fullName = line.substr(9);
        else if (line.find("FatherName:") == 0) app.fatherName = line.substr(11);
        else if (line.find("CNIC:") == 0) app.CNIC = line.substr(5);
        else if (line.find("ContactNumber:") == 0) app.contactNumber = line.substr(14);
        else if (line.find("Email:") == 0) app.email = line.substr(6);
        else if (line.find("EmploymentStatus:") == 0) app.employmentStatus = line.substr(17);
        else if (line.find("AnnualIncome:") == 0) app.annualIncome = stoll(line.substr(13));
        else if (line.find("HasExistingLoan:") == 0) app.hasExistingLoan = (line.substr(16) == "1");
        else if (line.find("AmountDue:") == 0) app.amountDue = stoll(line.substr(10));
        else if (line.find("ReferenceName0:") == 0) app.referenceName[0] = line.substr(15);
        else if (line.find("ReferenceCNIC0:") == 0) app.referenceCNIC[0] = line.substr(15);
        else if (line.find("ReferenceName1:") == 0) app.referenceName[1] = line.substr(15);
        else if (line.find("ReferenceCNIC1:") == 0) app.referenceCNIC[1] = line.substr(15);
    }
    
    file.close();
    return app;
}

bool LenderDashboard::updateApplicationStatus(const string& appID, const string& newStatus) {
    string filepath = "data\\applications\\" + appID + ".txt";
    string tempPath = "data\\applications\\temp.txt";
    
    ifstream inFile(filepath);
    if (!inFile.is_open()) return false;
    
    ofstream outFile(tempPath);
    if (!outFile.is_open()) {
        inFile.close();
        return false;
    }
    
    string line;
    while (getline(inFile, line)) {
        if (line.find("Status:") == 0) {
            outFile << "Status:" << newStatus << "\n";
        } else {
            outFile << line << "\n";
        }
    }
    
    inFile.close();
    outFile.close();
    
    remove(filepath.c_str());
    rename(tempPath.c_str(), filepath.c_str());
    
    return true;
}
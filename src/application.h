#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
using namespace std;

struct Application {
    string applicationID;

    // Personal Info
    string fullName;
    string fatherName;
    string postalAddress;
    string contactNumber;
    string email;
    string gender;
    string maritalStatus;
    int dependents;

    // CNIC & Employment
    string CNIC;
    string CNICExpiry;
    string employmentStatus;

    // Financial Info
    long long annualIncome;
    long long avgBill;
    long long currentMonthBill;

    // Existing Loan
    bool hasExistingLoan;
    long long existingLoanAmount;
    long long amountReturned;
    long long amountDue;
    string existingLoanBank;
    string existingLoanCategory;

    // References (support 2 references as example)
    string referenceName[2];
    string referenceCNIC[2];
    string referenceDate[2];
    string referencePhone[2];
    string referenceEmail[2];

    // Document Paths
    string CNICFrontPath;
    string CNICBackPath;
    string electricityBillPath;
    string salarySlipPath;

    // Application Status
    string status; // Pending, Approved, Rejected
};

#endif

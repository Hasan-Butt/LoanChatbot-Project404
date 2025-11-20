#ifndef LENDER_DASHBOARD_H
#define LENDER_DASHBOARD_H

#include <string>
#include "application.h"

class LenderDashboard {
private:
    // Core functionality methods
    void showMenu();
    void viewAllApplications();
    void viewPendingApplications();
    void viewApplicationDetails();
    void approveApplication();
    void rejectApplication();
    
    // Utility methods
    Application loadApplication(const std::string& appID);
    bool updateApplicationStatus(const std::string& appID, const std::string& newStatus);
    void displayHeader();
    void pauseAndClear();

public:
    // Main entry point
    void run();

    // Constructor/Destructor
    LenderDashboard() = default;
    ~LenderDashboard() = default;
};

#endif
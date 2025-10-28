# LoanChatbot Project Report

## 1. Project Title
**LoanChatbot** – C++ Console-Based Chatbot for Loan Queries and Calculations

---

## 2. Project Description
LoanChatbot is designed to help users interactively understand loan eligibility, calculate simple interest, and receive guided assistance with loan-related queries. The chatbot reads user input, validates it, processes queries, and displays responses in a user-friendly format.

---

## 3. Project Objectives
- Develop a modular C++ chatbot using classes.
- Handle input validation, keyword extraction, and response generation.
- Avoid STL containers; use dynamic arrays for data handling.
- Implement reusable helper functions in `utils.cpp` (validation, calculations, logging).
- Maintain professional documentation and testing throughout development.

---

## 4. Project Architecture
**Modules Overview:**

| Module               | Responsibilities |
|---------------------|-----------------|
| ChatbotInput         | Read and validate user input, extract keywords |
| ChatbotProcessor     | Analyze input, generate responses, handle loan queries |
| ChatbotDisplay       | Display messages, format output, show errors |
| ChatbotTester        | Test input processing, response accuracy, log debug info |
| utils.cpp / utils.h  | Provide reusable helper functions for validation, calculations, and logging |

**Data Flow:**
1. User input is read via `ChatbotInput`.
2. Input is validated and keywords are extracted.
3. `ChatbotProcessor` processes keywords and generates responses.
4. `ChatbotDisplay` formats and shows responses.
5. Interactions are logged via `utils.cpp` functions.
6. `ChatbotTester` verifies correctness of modules.

---

## 5. Tools & Technology
- Programming Language: C++ (C++17 compatible)
- IDE: Dev C++
- Version Control: Git
- Project Management: Jira
- File Handling: Console I/O for interactions and logs

---

## 6. Development Approach
- **Incremental Development**: Implement and test each module step-by-step.
- **Dynamic Arrays**: Replace STL containers to handle keywords and data arrays.
- **Testing**: Validate each module independently using `ChatbotTester`.
- **Documentation**: Maintain README.md, ScrumPlan.md, and ProjectReport.md alongside coding.

---

## 7. Challenges and Risks
- Input validation edge cases (non-numeric or empty input)
- Keyword extraction without STL
- Ensuring modular integration works correctly
- File handling errors in logging

---

## 8. Expected Outcomes
- A working LoanChatbot prototype capable of:
  - Reading and validating user input
  - Generating appropriate responses to loan queries
  - Logging interactions for review
  - Displaying formatted messages in the console

---

## 9. Future Enhancements (Optional)
- Extend chatbot to calculate EMI or other loan metrics
- Add sentiment analysis for user intent
- Support more complex loan queries
- GUI-based interface using Qt (if console-only version is complete)

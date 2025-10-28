# LoanChatbot Scrum Plan

## 1. Project Overview
LoanChatbot is a C++ console-based application designed to guide users through loan-related queries, eligibility checks, and basic loan calculations. The chatbot validates user input, processes queries, and generates interactive responses. This project emphasizes modular programming, dynamic arrays, and clean separation of concerns.

---

## 2. Implementation Approach / Architecture
- **Modular Design**:
  - `ChatbotInput`: Handles reading and validating user input.
  - `ChatbotProcessor`: Processes input, analyzes intent, and generates responses.
  - `ChatbotDisplay`: Manages output formatting and displaying messages.
  - `ChatbotTester`: Contains testing routines for input processing and response accuracy.
  - `utils.cpp`: Contains helper functions for validation, calculations, and logging.
- **Data Handling**:
  - Dynamic arrays are used instead of STL containers.
  - Input validation and keyword extraction are centralized in helper functions.
- **Workflow**:
  - Initialize modules in `main.cpp`.
  - Show welcome message and instructions.
  - Start main chatbot loop for continuous interaction.

---

## 3. Tools & Technology
- Programming Language: C++ (C++17 compatible)
- IDE: Dev C++
- Version Control: Git
- Project Management: Jira (for tasks, sprint backlog, and progress tracking)

---

## 4. Risks / Challenges
- **Keyword Extraction**: Implementing dynamic array-based keyword extraction without STL may be error-prone.
- **Input Validation**: Edge cases (empty strings, non-numeric values) need careful handling.
- **Incremental Testing**: Each module must be tested independently to prevent cascading errors.
- **File Handling**: Logging interactions to files must handle file I/O errors gracefully.

---

## 5. Development Strategy
1. Implement **ChatbotInput** module first (reading, validating, and keyword extraction).
2. Implement **ChatbotProcessor** module for response generation and loan query handling.
3. Integrate **ChatbotDisplay** for formatted output and user guidance.
4. Implement **ChatbotTester** to verify correctness of each module.
5. Add logging and calculations in **utils.cpp** as needed.
6. Test the chatbot incrementally after completing each module.
7. Update documentation (`README.md`, `ProjectReport.md`) alongside development.

---

## 6. Learning Goals / Notes
- Gain experience in **modular programming** using classes in C++.
- Learn to **work without STL containers** by using dynamic arrays.
- Apply object-oriented programming concepts (classes, encapsulation, modularity).
- Practice **incremental development** and testing.
- Maintain professional documentation to complement Jira task tracking.

---

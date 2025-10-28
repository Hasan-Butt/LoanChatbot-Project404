# LoanChatbot-Project404
Console-based chatbot for loan processing (ISE Project using Scrum model)
# 💰 LoanChatbot 🤖

**LoanChatbot** is a C++ console-based chatbot designed to assist users with loan-related queries, eligibility checks, and basic calculations. It validates user input, processes queries, and provides interactive guidance step by step.  

---

## 🚀 Features (Planned / In Progress)
- ✅ Read and validate user input  
- ✅ Extract keywords from user queries  
- ✅ Generate responses for basic loan questions  
- ⚙️ Display formatted output in console  
- 📄 Read predefined responses from `Utterances.txt` and `Home.txt`  
- 🧪 Test and validate each module  
- 📝 Log user-chatbot interactions  

---

## 🏗️ Project Structure

```
LoanChatbot/
├── src/
│ ├── main.cpp
│ ├── chatbot.cpp
│ ├── chatbot.h
│ ├── utils.cpp
│ └── utils.h
├── data/
│ ├── Utterances.txt # Predefined chatbot responses
│ └── Home.txt # Welcome and home messages
├── docs/
│ ├── ScrumPlan.md
│ └── ProjectReport.md
└── README.md
```

- `src/` → Source code and helper files  
- `data/` → Text resources used by the chatbot  
- `docs/` → Project documentation  

---

## ⚡ How to Run
1. Open the project in **Dev C++** or any C++ IDE supporting C++17.  
2. Compile all `.cpp` files in the `src/` folder together (`main.cpp`, `chatbot.cpp`, `utils.cpp`).  
3. Ensure the `data/` folder is in the same directory as the executable.  
4. Run `main.exe` (or equivalent) to start the chatbot.  
5. The chatbot will read responses and prompts from `Utterances.txt` and `Home.txt`.  
6. Follow on-screen instructions to interact with LoanChatbot.  

---

## 🛠️ Tools & Technology
- C++ (C++17)  
- Dev C++ IDE  
- Git for version control  
- Jira for project and task management  
- Console-based file I/O for reading prompts and logging  

---

## 📌 Notes
- Currently, this is a **console-based prototype**; GUI may be added in the future.  
- All modules are **modular and incremental**, allowing for easy testing and expansion.  
- Dynamic arrays are used instead of STL containers to manage data like keywords and responses.  

---

## 👨‍💻 Team Members
- **Hasan** – Project Lead & Developer  
- **Kabeer** – Developer  
- **Haider** – Developer  
- **Ayub** – Developer

---

## 🌟 Future Enhancements
- EMI calculation and advanced loan metrics  
- Enhanced keyword extraction and intent analysis  
- GUI-based interface using Qt  
- Support for more complex and natural user queries  
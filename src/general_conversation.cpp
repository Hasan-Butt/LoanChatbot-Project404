#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>  
#include <ctime>    
#include "general_conversation.h"
using namespace std;

void initializeRandomSeed() {
    srand(time(0));  // Seed with current time
}

// Tokenize a string into individual words (lowercase, no punctuation)
vector<string> tokenize(const string& text) {
    vector<string> tokens;
    string word = "";
    
    for (int i = 0; i < text.length(); i++) {
        char c = tolower(text[i]);
        
        // Check if character is a letter or number
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            word += c;
        }
        else if (c == ' ' || c == '\t' || c == '\n') {
            // When we hit a space, save the word
            if (!word.empty()) {
                tokens.push_back(word);
                word = "";
            }
        }
        // Ignore punctuation as it just gets skipped
    }
    
    // Putting the last word
    if (!word.empty()) {
        tokens.push_back(word);
    }
    
    return tokens;
}


// Calculate Intersection over Union between two strings
double calculateIoU(const string& userInput, const string& corpusLine) {
    // Tokenize both strings
    vector<string> tokensUser = tokenize(userInput);
    vector<string> tokensCorpus = tokenize(corpusLine);
    
    // If either is empty, no match
    if (tokensUser.empty() || tokensCorpus.empty()) {
        return 0.0;
    }
    
    // Count intersection (common tokens)
    int intersection = 0;
    for (int i = 0; i < tokensUser.size(); i++) {
        for (int j = 0; j < tokensCorpus.size(); j++) {
            if (tokensUser[i] == tokensCorpus[j]) {
                intersection++;
                break; // Count each token only once
            }
        }
    }
    
    // Calculate union (all unique tokens)
    vector<string> unionTokens;
    
    // Add all user tokens to union
    for (int i = 0; i < tokensUser.size(); i++) {
        unionTokens.push_back(tokensUser[i]);
    }
    
    // Add corpus tokens that aren't already in union
    for (int i = 0; i < tokensCorpus.size(); i++) {
        bool alreadyExists = false;
        for (int j = 0; j < unionTokens.size(); j++) {
            if (tokensCorpus[i] == unionTokens[j]) {
                alreadyExists = true;
                break;
            }
        }
        if (!alreadyExists) {
            unionTokens.push_back(tokensCorpus[i]);
        }
    }
    
    int unionSize = unionTokens.size();
    
    if (unionSize == 0) {
        return 0.0;
    }
    
    // Calculate IoU = Intersection / Union
    return (double)intersection / (double)unionSize;
}

// Load all conversation pairs from file into memory (called once at startup)
vector<ConversationPair> loadConversationCorpus(const string& filename) {
    vector<ConversationPair> corpus;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        return corpus; // Return empty corpus
    }
    
    string line;
    string currentHuman1 = "";
    
    while (getline(file, line)) {
        // Check if this is a "Human 1:" line (question)
        if (line.find("Human 1:") == 0) {
            // Extract text after "Human 1: "
            currentHuman1 = line.substr(9); // 9 = length of "Human 1: "
        }
        // Check if this is a "Human 2:" line (response)
        else if (line.find("Human 2:") == 0 && !currentHuman1.empty()) {
            // We have a complete pair!
            ConversationPair pair;
            pair.question = currentHuman1;
            pair.response = line.substr(9); // 9 = length of "Human 2: "
            
            corpus.push_back(pair);
            
            // Reset for next pair
            currentHuman1 = "";
        }
    }
    
    file.close();
    
    cout << "[Loaded " << corpus.size() << " conversation pairs]\n";
    return corpus;
}

// Find best matching response using IoU algorithm
string findBestMatchFromCorpus(const string& userInput, 
                                       const vector<ConversationPair>& corpus) {
    if (corpus.empty()) {
        return "Conversation database not loaded.";
    }
    
    // Structure to hold matches with their IoU scores
    struct Match {
        string response;
        string question;
        double iou;
        int index;
    };
    
    vector<Match> allMatches;
    
    // Calculate IoU for all pairs and store results
    for (int i = 0; i < corpus.size(); i++) {
        double iou = calculateIoU(userInput, corpus[i].question);
        
        if (iou > 0.1) {  // Only consider reasonable matches
            Match m;
            m.response = corpus[i].response;
            m.question = corpus[i].question;
            m.iou = iou;
            m.index = i;
            allMatches.push_back(m);
        }
    }
    
    // No good matches found
    if (allMatches.empty()) {
        return "I'm not sure how to respond to that. Can you try rephrasing?";
    }
    
    // Find maximum IoU
    double maxIoU = 0.0;
    for (int i = 0; i < allMatches.size(); i++) {
        if (allMatches[i].iou > maxIoU) {
            maxIoU = allMatches[i].iou;
        }
    }
    
    // Collect all matches with max IoU
    vector<Match> bestMatches;
    for (int i = 0; i < allMatches.size(); i++) {
        if (allMatches[i].iou == maxIoU) {
            bestMatches.push_back(allMatches[i]);
        }
    }
    
    // Randomly select from best matches
    int randomIndex = rand() % bestMatches.size();
    
    return bestMatches[randomIndex].response;
}
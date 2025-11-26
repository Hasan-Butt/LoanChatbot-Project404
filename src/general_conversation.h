#include <vector>
#include <string>
using namespace std;

// Conversation structure to hold question-response pairs
struct ConversationPair {
    string question;  // Human 1 line
    string response;  // Human 2 line
};

// Tokenization and IoU functions
vector<string> tokenize(const string& text);
double calculateIoU(const string& userInput, const string& corpusLine);
vector<ConversationPair> loadConversationCorpus(const string& filename);
string findBestMatchFromCorpus(const string& userInput, 
                               const vector<ConversationPair>& corpus);
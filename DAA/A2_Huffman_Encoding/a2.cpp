#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Node structure for Huffman Tree
class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq){
        this->ch = ch;
        this->freq = freq;
        this->left = this->right = nullptr;
    }
};

// Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman Codes recursively
void generateCodes(Node* root, const string& code, unordered_map<char, string>& mp) {
    if (!root) return;

    // If leaf node → store that character's code
    if (!root->left && !root->right) {
        mp[root->ch] = (code == "" ? "0" : code);
        return;
    }

    generateCodes(root->left, code + "0", mp);
    generateCodes(root->right, code + "1", mp);
}

// Build Huffman Tree (returns root node)
Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto p : freq)
        pq.push(new Node(p.first, p.second));

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top(); // Root of Huffman Tree
}

int main() {
    string text;

    cout << "Enter a string: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Invalid input. Exiting.\n";
        return 0;
    }

    Node* root = buildHuffmanTree(text);

    unordered_map<char, string> mp;
    generateCodes(root, "", mp);

    cout << "\nHuffman Codes:\n";
    for (auto p : mp)
        cout << p.first << " = " << p.second << "\n";

    string encoded = "";
    for (char ch : text)
        encoded += mp[ch];

    cout << "\nEncoded String:\n" << encoded << endl;

    return 0;
}

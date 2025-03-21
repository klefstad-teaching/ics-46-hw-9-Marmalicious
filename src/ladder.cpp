#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error between " << word1 << " and " << word2 << " with msg:\n" << msg << endl;
    return;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > 1) return false;
    int i = 0, j = 0, edits = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            edits++;
            if (edits > d) return false;
            // account for double characters (ee)
            if (i + 1 < len1 && j + 1 < len2 && (str1[i] == str2[i + 1] || str1[j] == str2[j + 1])) {
                if (len2 > len1) ++j;
                else ++i;
            }
            // deletion
            else if (i + 1 < len1 && str1[i + 1] == str2[j]) ++i;
            // insertion
            else if (j + 1 < len2 && str1[i] == str2[j + 1]) ++j;
            // substitution
            else if (i + 1 < len1 && j + 1 < len2 && str1[i + 1] == str2[j + 1]) { ++i, ++j; }
        }
        ++i;
        ++j;
    }
    edits += abs(len1 - i - (len2 - j));
    return edits <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> q;
    vector<string> temp;
    vector<string> visited;
    temp.push_back(begin_word);
    visited.push_back(begin_word);
    q.push(temp);
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        string last = temp.back();
        for (string s : word_list)
            if (is_adjacent(last, s)) {
                bool found = 0;
                for (string v : visited)
                    if (s == v) { found = 1; break; }
                if (!found) {
                    visited.push_back(s);
                    temp.push_back(s);
                    if (s == end_word) return temp;
                    q.push(temp);
                    temp.pop_back();
                }
            }
    }
    temp.assign(0, "");
    return temp;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    string word;
    for (string word; in >> word;) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() < 2) {
        cout << "No word ladder found.";
    } else {
        cout << "Word ladder found: ";
    }
    for (string s : ladder) {
        cout << s << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    cout << endl;
}
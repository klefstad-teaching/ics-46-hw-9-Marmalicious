#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error between " << word1 << " and " << word2 << " with msg:\n" << msg << endl;
    return;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int s1 = str1.size() + 1;
    int s2 = str2.size() + 1;
    vector<vector<int>> matrix(s1, vector<int>(s2));
    for (int i = 1; i < s1; ++i)
        matrix[i][0] = i;
    for (int i = 1; i < s2; ++i)
        matrix[0][i] = i;
    for (int i = 1; i < s1; ++i) {
        for (int j = 1; j < s2; ++j) {
            int sub;
            if (str1[i - 1] == str2[j - 1])
                sub = 0;
            else
                sub = 1;
            int hold = min(matrix[i-1][j] + 1, matrix[i][j-1] + 1);
            matrix[i][j] = min(hold, matrix[i-1][j-1] + sub);
        }
    }
    return matrix[s1 - 1][s2 - 1] == d;
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
                    vector<string> copy = temp;
                    copy.push_back(s);
                    if (s == end_word) { temp = copy; break; };
                    q.push(copy);
                }
            }
    } 
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
    for (string s : ladder) {
        cout << s << " ";
    }
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
}
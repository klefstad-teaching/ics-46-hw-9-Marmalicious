#include "ladder.h"

int main() {
    set<string> list;
    load_words(list, "src/words.txt");
    //print_word_ladder(generate_word_ladder("dog", "cat", list));
    //verify_word_ladder();
    cout << generate_word_ladder("awake", "sleep", list).size();
}
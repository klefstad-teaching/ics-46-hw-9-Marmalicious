#include "ladder.h"

int main() {
    set<string> list;
    load_words(list, "src/words.txt");
    //print_word_ladder(generate_word_ladder("dog", "cat", list));
    verify_word_ladder();
    cout << (generate_word_ladder("awake", "sleep", list).size());
    //cout << edit_distance_within("wee", "see", 1) << endl
        //<< edit_distance_within("see", "seep", 1) << endl
        //<< edit_distance_within("seep", "sleep", 1) << endl;
}
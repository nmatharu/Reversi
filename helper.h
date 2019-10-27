
// Function that converts an x-axis int into its char label:
// ex. 0, 1, 2, 3 -> '1', '2', '3', '4'
char x_to_label(int x) {
    char label = '1';
    label += x;
    return label;
}
 
// Function that converts a y-axis int into its char label"
// ex. 0, 1, 2, 3 -> 'a', 'b', 'c', 'd'
char y_to_label(int y) {
    char label = 'a';
    label += y;
    return label;
}
 
// Function that converts an x-axis char label into its int
// ex. '1', '2', '3', '4' -> 0, 1, 2, 3
int label_to_x(char x) {
    int val = (int)x;
    val -= '1';
    return val;
}
 
// Function that converts a y-axis char label into its int
// ex. 'a', 'b', 'c', 'd' -> 0, 1, 2, 3
int label_to_y(char y) {
    int val = (int)y;
    val -= 'a';
    return val;
}

// Clean input when asking to play again
string clean_input(const string& s)
{
    string result;
 
    // Check if user entered a sentence or multiple words
    bool multiple_words = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            multiple_words = true;
        }
    }
 
    // If the user did input multiple words, just use the last word
    if (multiple_words) {
        int pos = s.find_last_of(' ');
        result = s.substr(pos + 1);
 
    } else {
 
        // Else, if only one word was entered, use it
        result = s;
    }
 
    for (int i = 0; i < result.length(); i++) {
 
        // Erase punctuation from the word
        if (ispunct(result[i])) result.erase(i--, 1);
 
        // Set the result to all lowercase
        result[i] = tolower(result[i]);
    }
 
    return result;
}
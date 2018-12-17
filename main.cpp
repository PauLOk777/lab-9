////////////////////////////////////////////////////////////////
30. Розбити слово на дві частини згідно з правилами перенесення 
слів кожне слово на парній позиції у введеному з клавіатури рядку. 
Визначити слова перенесення яких неможливе.
////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

using namespace std;

// Functions
bool isVowel(char);
bool canBeBrokenIntoSyllables(string);
int splitIntoArray(string*, string, char);
int countVowelsInWordForBreaking(string);
int countConsonantsInWordForBreaking(string);
string breakWordIntoSyllables(string);
string parseStringForBreaking(string);
string replaceChars(string, char, char);

// Array of vowel English characters
const char chars[] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
const int charsLength = 12;

// Main function
int main() {
  // Input initial string
  string str;
  cout << "Input your string: ";
  getline(cin, str);
  // Parse initial string (delete useless spaces, replace dots with spaces etc.)
  str = parseStringForBreaking(str);
  // Print initial string
  cout << str << endl;
  cout << "==================" << endl;
  
  // Create new array of strings for separate words
  string* strArr = new string[str.length()];
  // Find a number of words
  int size = splitIntoArray(strArr, str, ' ');
  // Break every word into syllables 
  for (int i = 0; i < size; i++) {
    if (!(i % 2)) {
      cout << strArr[i] << endl;
    } else {
      cout << breakWordIntoSyllables(strArr[i]) << endl;
    } 
  }
  return 0;
}

// Function that checks if the passed char is a vowel letter
bool isVowel(char item) {
	for (int i = 0; i < charsLength; i++) {
		if (chars[i] == item) {
			return true;
		}
	}
	return false;
}

// Function that checks if word can be broken into syllables
bool canBeBrokenIntoSyllables(string word) {
	int vowels = countVowelsInWordForBreaking(word);
	int consonants = countConsonantsInWordForBreaking(word);
	if (word.length() < 4) {
		return false;
	}
	else if (vowels > 1 && consonants > 1) {
		return true;
	}
	else {
		return false;
	}
}

// Function that splits string into an array of strings by the delimiter
int splitIntoArray(string* strArr, string str, char delimiter) {
	int ind = 0;
	for (int i = 0; i < str.length(); i++) {
		strArr[i] = "";
	}
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != delimiter) {
			strArr[ind] += str[i];
		}
		else {
			ind++;
		}
	}
	return ind + 1;
}

// Function that counts a number of vowel letters in word
int countVowelsInWordForBreaking(string word) {
	int k = 0;
	for (int i = 0; i < word.length(); i++) {
		if (i > 0) {
			if (isVowel(word[i]) && !isVowel(word[i - 1])) {
				k++;
			}
		}
		else {
			if (isVowel(word[i])) {
				k++;
			}
		}
	}
	return k;
}

// Function that counts a number of consonants letters in word
int countConsonantsInWordForBreaking(string word) {
	int k = 0;
	for (int i = 0; i < word.length(); i++) {
		if (!isVowel(word[i])) {
			k++;
		}
	}
	return k;
}

// Function that breaks word into syllables
string breakWordIntoSyllables(string word) {
	if (canBeBrokenIntoSyllables(word)) { // Word can be broken into syllables
		if (isVowel(word[0])) { // First letter is vowel
			for (int i = 1; i < word.length() - 1; i++) {
				if (!isVowel(word[i])) {
					word.insert(i + 1, "-");
					return word;
				}
			}
		}
		else { // First letter is consonant
			bool flag = false;
			for (int i = 1; i < word.length() - 1; i++) {
				if (isVowel(word[i])) {
					flag = true;
				}
				if (!isVowel(word[i]) && flag) {
					if (!isVowel(word[i + 1])) {
						word.insert(i + 1, "-");
						return word;
					}
					else {
						word.insert(i, "-");
						return word;
					}
				}
			}
		}
	}
	return word + " -> can't be broken";
}

// Function that parses string for the further breaking words inside it
string parseStringForBreaking(string str) {
	int index = 0;
	// Delete useless spaces from the beginning of the str
	while (str[0] == ' ') {
		str.replace(0, 1, "");
	}
	// Delete useless spaces from the ending of the str
	while (str[str.length() - 1] == ' ') {
		str.replace(str.length() - 1, 1, "");
	}
	// Delete useless spaces between words
	while (index < str.length() - 1) {
		if (str[index] == ' ' && str[index + 1] == ' ') {
			str.replace(index, 1, "");
		}
		else {
			index++;
		}
	}
	// Replace dots with spaces
	str = replaceChars(str, '.', ' ');
	return str;
}

// Function that replaces all the characters in the strings by another characters
string replaceChars(string str, char characher, char replacement) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == characher) {
			str[i] = replacement;
		}
	}
	return str;
}

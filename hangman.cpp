////////////////////////////////////
// Alex Mack
// C++ Program - Hangman Game
// 12/14/2017
///////////////////////////////////

#include <iostream>
#include <cstring>   // Needed for strlen and strcmp functions
#include <cctype>    // Needed for toupper function
#include <fstream>
using namespace std;

void displayWord(char []);
bool guessWord(char [], char []);
bool findLetters(char [], char [], char);

int main()
{
 
     ifstream inFile;         // File stream object
     const int LENGTH = 21;   // Length of string
     char word[LENGTH];       // Holds the secret word   
     char letters[LENGTH];    // Holds letters
     char incorrect[9];       // Holds incorrect letters
     char guess;              // Holds a guessed letter
     char choice = 'Y';       // Holds Y or N
     int index;               // Loop counter
     int misses;              // Number of misses

     // Open file for input
     inFile.open("wordlist.txt");

     cout << "\n\t\tHangman\n\n";

     while (toupper(choice) == 'Y' && !inFile.eof())
     {
         index = 0;
         misses = 0;

        // Read a word from the file and
        // store it in the word array
        inFile >> word;

       // Fill the letters array with dashes
       while (word[index] != '\0')
       {
            // Capatilize each letter in the word array
            char temp = toupper(word[index]);
            word[index] = temp;
            letters[index] = '-';
            index++;
       }
       
       letters[index] = '\0';   // Add null terminator
           
       // Guess the letters in the word
       while (!guessWord(letters, word) && misses < 8)
       {
           cout << endl;

           displayWord(letters);

           cout << "Guess a letter: ";
           cin >> guess;

           if (!findLetters(word, letters, guess))
           {
              // Capitalize letters stored in incorrect
              // array
              incorrect[misses] = toupper(guess);
              misses++;

              cout << endl;

              // Display incorrect letters
              for (index = 0; index < misses; index++)
              {
                  cout << static_cast<char>(toupper(incorrect[index]));
                  cout << " ";
              }

              cout << endl << endl;
            
           }

        }
       
        cout << endl;

       // Display outcome of the game
       if (guessWord(letters, word))
       {
          displayWord(letters);
          cout << "\nYou Won!\n";
       }
       else
       {
          displayWord(letters);
          cout << "\nYou Lost!\n";
       }

       cin.ignore();   // Skip the new line
       cout << "Start a new game (y/n)? ";
       cin.get(choice);
       
     }

     // Close the file
     inFile.close();

     cout << endl << endl;
     cout << static_cast<char>(169) << "Mack 2017\n";

     return 0;
} 

// Displays the word that the player
// needs to guess for the game
void displayWord(char l[])
{
    int index = 0;

    cout << "  ";

    while (l[index] != '\0')
    {
       cout << l[index] << " ";
       index++;

    }

    cout << endl << endl;

}

bool guessWord(char l[], char w[])
{
     if (strcmp(l, w) == 0)
         return true;
     else
        return false;
}

bool findLetters(char w[], char l[], char g)
{
     bool isFound = false;   // Holds true or false
     int index = 0;          // Loop counter

     while (w[index] != '\0')
     {
         if (w[index] == toupper(g))
         {
             l[index] = toupper(g);
             isFound = true;
         }  

         index++;              
     }
     
     return isFound;
}
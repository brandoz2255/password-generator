#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <openssl/sha.h>
#include <fstream>
#include <random>
#include <openssl/evp.h>
#include <unordered_set>
#include <bitset>
#include <tuple>



enum PasswordStrength {
    WEAK,
    MODERATE,
    STRONG
};


class Mainprogram {

private: 
    std::string customChars; // Declare customChars as a class member

    // Function to handle file operations
    void updatePasswordFile(const std::string& username, const std::string& password) {
        std::fstream file("password.pass", std::ios::in | std::ios::out);

        if (!file) {
            std::cerr << "Error opening file for update." << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        bool userFound = false;

        // Read the file line by line
        while (std::getline(file, line)) {
            size_t pos = line.find(username);

            // Check if the username is found in the line
            if (pos != std::string::npos) {
                // Update the line with the new password
                line = username + " " + password;
                userFound = true;
            }

            lines.push_back(line);
        }

        // If the user was not found, add a new entry
        if (!userFound) {
            lines.push_back(username + " " + password);
        }

        // Clear the content of the file
        file.close();
        std::ofstream outFile("password.pass", std::ios::trunc);

        // Write the modified lines back to the file
        for (const auto& updatedLine : lines) {
            outFile << updatedLine << std::endl;
        }

        std::cout << "Password file updated successfully." << std::endl;
    }



public:


    // Add a new function for editing an existing username
    void editExistingUsername() {
        std::string existingUsername;
        std::cout << "Enter the existing username you want to edit: ";
        std::cin >> existingUsername;


        std::ifstream file("password.pass"); // Open the file containing usernames and passwords
            std::string line;
            bool usernameFound = false;
            std::string lineToUpdate;

        std::ifstream file("password.pass"); // Replace with your actual file name
            std::string line;
            bool usernameFound = false;

            // Check if the username exists in the file
            while (std::getline(file, line)) {
                if (line == existingUsername) {
                    usernameFound = true;
                    break;
                }
            }

            file.close();





        // Check if the username exists in the file
        if (usernameExists(existingUsername)) {
            std::string newPassword = generate_password(12, true, true, true, true, "!@#");  // Generate a new password
            updatePasswordFile(existingUsername, newPassword);
            std::cout << "Password for username '" << existingUsername << "' has been updated.\n";
            std::cout << "Generated new password:\n" << newPassword << "\n";
        } else {
            std::cout << "Username not found. Please make sure the username exists.\n";
        }
    }

    // Function to check if a username exists in the file
    bool usernameExists(const std::string& username) {
        std::ifstream file("passwords.txt");
        std::string line;
        while (std::getline(file, line)) {
            if (line.find(username) != std::string::npos) {
                return true;
            }
        }
        return false;
    }




    void displayPasswordStrengthBar(const std::string& password) {
        int strength = evaluatePasswordStrength(password);

        std::cout << "\nPassword Strength Bar:\n";
        switch (strength) {
            case WEAK:
                std::cout << "\033[1;31m[==        ] Weak\033[0m\n";  // Red
                break;
            case MODERATE:
                std::cout << "\033[1;33m[====      ] Moderate\033[0m\n";  // Yellow
                break;
            case STRONG:
                std::cout << "\033[1;32m[=======   ] Strong\033[0m\n";  // Green
                break;
        }
    }







    // Add public access specifier before these methods

    void userGreeting() {
        std::cout << R"(__________                                               .___ 
    \______   \_____    ______ ________  _  _____________  __| _/ 
    |     ___/\__  \  /  ___//  ___/\ \/ \/ /  _ \_  __ \/ __ |  
    |    |     / __ \_\___ \ \___ \  \     (  <_> )  | \/ /_/ |  
    |____|    (____  /____  >____  >  \/\_/ \____/|__|  \____ |  
                    \/     \/     \/                          \/  
    ________                                  __                
    /  _____/  ____   ___________  _________ _/  |_  ___________ 
    /   \  ____/ __ \ /    \_  __ \/  _ \__  \\   __\/  _ \_  __ \
    \    \_\  \  ___/|   |  \  | \(  <_> ) __ \|  | (  <_> )  | \/
    \______  /\___  >___|  /__|   \____(____  /__|  \____/|__|   
            \/     \/     \/                 \/                   )" << std::endl;
    }

    std::tuple<std::string, std::string, int> userInput() {
        std::string keyword1, keyword2;
        int passwordLength;
        std::string customChars;  // Declare customCha

        std::cout << "\n----------------------------------------------------------\n" << std::endl;
        std::cout << "Please enter the first keyword: ";
        std::getline(std::cin >> std::ws, keyword1);  // Use std::ws to ignore leading whitespace

        std::cout << "Please enter the second keyword: ";
        std::getline(std::cin >> std::ws, keyword2);

        std::cout << "Choose the length of the password: ";
        while (true) {
            std::cin >> passwordLength;
            if (passwordLength > 0) {
                break;
            } else {
                std::cout << "Invalid length. Please enter a positive integer: ";
                std::cin.clear();  // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the buffer
            }
        }      
        
        std::cout << "Do you want to customize the characters in your password? (y/n): " << std::endl;
        char customizeChoice;
        std::cin >> customizeChoice;

        if (customizeChoice == 'y' || customizeChoice == 'Y') {
                std::cout << "Enter custom characters for password generation (or press Enter to skip): ";
                std::getline(std::cin >> std::ws, customChars);


                if (customChars.empty()) {
                    std::cout << "Alright, skipping customization. We'll surprise you with a spicy mix!" << std::endl;
                } else {
                    std::cout << "Custom characters set to: " << customChars << std::endl;
                }




        }


    std::cout << "\n----------------------------------------------------------\n" << std::endl;

    return std::make_tuple(keyword1, keyword2, passwordLength);
}



    std::string generate_username(const std::string& keyword1, const std::string& keyword2) {
         // Ensure keywords are not empty after trimming leading and trailing spaces
        std::string trimmedKeyword1 = keyword1;
        std::string trimmedKeyword2 = keyword2;

        // Trim leading spaces
        trimmedKeyword1.erase(0, trimmedKeyword1.find_first_not_of(' '));
        trimmedKeyword2.erase(0, trimmedKeyword2.find_first_not_of(' '));

        // Trim trailing spaces
        trimmedKeyword1.erase(trimmedKeyword1.find_last_not_of(' ') + 1);
        trimmedKeyword2.erase(trimmedKeyword2.find_last_not_of(' ') + 1);

        if (trimmedKeyword1.empty() || trimmedKeyword2.empty()) {
            std::cout << "Error: Keywords cannot be empty." << std::endl;
            return "";
    }


    // Extract the first two letters of each trimmed keyword
    std::string username = trimmedKeyword1.substr(0, 2) + trimmedKeyword2.substr(0, 2);

    // Add a random number for uniqueness
    srand(time(0)); // Initialize random seed
    int number = rand() % 900 + 100; // Generate random three-digit number
    username += std::to_string(number);

    return username;
}


   std::string generate_password(int length, bool includeUppercase, bool includeLowercase, bool includeDigits, bool includeSpecialChars, const std::string& customChars) {
        // Define character sets
        const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        const std::string digits = "0123456789";
        const std::string special_chars = "!@#$%^&*()-_=+[{]}|;:',.<>?/";

        // Combine character sets based on user preferences
        std::string validChars;
        if (includeUppercase) validChars += uppercase;
        if (includeLowercase) validChars += lowercase;
        if (includeDigits) validChars += digits;
        if (includeSpecialChars) validChars += special_chars;
        validChars += customChars;  // Add custom characters

        if (validChars.empty()) {
            std::cout << "Error: No character set selected." << std::endl;
            return "";
        }

        std::string password;
        password.reserve(length);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, validChars.size() - 1);

        for (int i = 0; i < length; ++i) {
            password += validChars[dis(gen)];
        }

        // Shuffle the characters in the password to ensure randomness
        std::shuffle(password.begin(), password.end(), gen);

        return password;
    }



    //Bool function that asks the user if they want to use the program again or not 
    bool askUserEmsg() {
        std::string decision;
        std::cout << "\nWould you like to generate another password and username? (yes/no)\n";
        std::cin >> decision;

        // Convert the string to lowercase for case-insensitive comparison
        std::transform(decision.begin(), decision.end(), decision.begin(), ::tolower);

        if (decision == "yes") {
            return true;
        } else if (decision == "no") {
            return false;
        } else {
            std::cout << "Syntax error! Please enter 'yes' or 'no'.\n";
            return askUserEmsg(); // Recursively call the function until valid input is received
        }
    }

    //Function for the exit message 
    void exitMessage() {
        std::cout << "\n----------------------------------------------------------\n" << std::endl;
        std::cout << "THANKS FOR USING THE C++ EDITION!!!" << std::endl;
        std::cout << "\n----------------------------------------------------------\n" << std::endl;
    }



    PasswordStrength evaluatePasswordStrength(const std::string& password) {
        bool hasLower = false, hasUpper = false;
        bool hasDigit = false, hasSpecialChar = false;
        int length = password.length();

        for (char c : password) {
            if (islower(c))
                hasLower = true;
            else if (isupper(c))
                hasUpper = true;
            else if (isdigit(c))
                hasDigit = true;
            else
                hasSpecialChar = true;
        }

        if (hasLower && hasUpper && hasDigit && hasSpecialChar && length >= 8)
            return STRONG;
        else if ((hasLower || hasUpper) && hasDigit && length >= 6)
            return MODERATE;
        else
            return WEAK;
        }



    };


int main() {
    Mainprogram mp;

    while (true) {
        mp.userGreeting();



        // Prompt the user for additional actions
        std::cout << "\nDo you want to edit an existing username? (yes/no): ";
        std::string editChoice;
        std::cin >> editChoice;


        if (editChoice == "yes") {
                    mp.editExistingUsername();
                } else if (editChoice == "no") {
                    break; // Exit the loop if the user decides to stop editing usernames
                } else {
                    std::cout << "Invalid choice. Please enter 'yes' or 'no'.\n";
                }


      

        if (editChoice == "yes") {
            mp.editExistingUsername();
        }





        std::cout << "\nWelcome to the Password Generator app C++ edition" << std::endl; 
        std::cout << "\nPlease input a key word to word to use to generate username" << std::endl;
        std::cout << "\nThe App also allows the user to choose how many characters to use in their password generation" << std::endl;
        std::cout << "\nHIGHLY RECOMMENDED THAT YOU MAKE THE PASSWORD LONGER THAN 10 CHARCTERS FOR SAFTEY!!" << std::endl; 

        std::string keyword1, keyword2;
        int passwordLength;

        std::tie(keyword1, keyword2, passwordLength) = mp.userInput();

        std::string password = mp.generate_password(passwordLength, true, true, true, true, "!@#");  // Including custom characters !@#
        std::string username = mp.generate_username(keyword1, keyword2);
        PasswordStrength strength = mp.evaluatePasswordStrength(password); // Removed the extra semicolon

        //switch statement to iterate the strenght of the password
        switch (strength) {
            case WEAK:
                std::cout << "\nPassword Strength: Weak\n";
                break;
            case MODERATE:
                std::cout << "\nPassword Strength: Moderate\n";
                break;
            case STRONG:
                std::cout << "\nPassword Strength: Strong\n";
                break;
        }

        mp.displayPasswordStrengthBar(password);

        std::cout << "\nGenerated Password:\n" << password << std::endl;
        std::cout << "\nGenerated Username:\n" << username << std::endl;

        std::ofstream f("password.pass", std::ios::out | std::ios::app);
        if (f.is_open()) {
            f << "Here is the Generated Password(s) and Username(s) --> \n";
            f << "Username: " << username << "\n";
            f << "Password: " << password << "\n\n";
            f.close();
        }

        if (!mp.askUserEmsg()) {
            break; // Exit the loop if the user decides to stop using the program
        }
    }

    mp.exitMessage();

    return 0;

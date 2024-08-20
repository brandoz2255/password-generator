# password-generator



## Overview

**Developed** a C++ application that generates secure, customizable passwords and usernames, integrating OpenSSL for cryptographic operations. **Engineered** this tool as a learning project to deepen my understanding of C++ programming, particularly in the areas of functions, classes, tuples, and the OpenSSL library.

**Important:** This tool was created purely for educational purposes. It should not be used in professional environments or for securing sensitive data.

## Features

- **Generate** strong, random passwords with customizable character sets, including uppercase letters, lowercase letters, digits, and special characters.
- **Create** unique usernames based on user-provided keywords, ensuring uniqueness with random numbers.
- **Evaluate** password strength and provide visual feedback through a strength bar.
- **Store** and **update** usernames and passwords securely in a file using file handling techniques.
- **Leverage** OpenSSL's cryptographic functions to ensure secure password generation and storage.

## What I Learned

Through this project, I **acquired** and **refined** several C++ programming skills, including:

- **Functions:** **Utilized** functions to modularize the code, improving readability and reusability.
- **Classes:** **Implemented** object-oriented principles, **designing** classes to encapsulate related functions and data.
- **Tuples:** **Applied** the `std::tuple` class to return multiple values from functions efficiently.
- **OpenSSL Library:** **Integrated** OpenSSL to handle cryptographic operations, **gaining** experience with secure programming practices


## Usage

To use this tool, clone the repository and compile the code using a C++ compiler. Note that this project is for educational purposes only and should not be used to secure real-world data.

``` bash
git clone https://github.com/yourusername/password-generator-cpp.git
cd password-generator-cpp
g++ -o password_generator main.cpp -lssl -lcrypto
./password_generator
```

## Disclaimer

This project was created as a learning exercise. It is not intended for professional use or to secure any sensitive information. **Explore** the code, **experiment** with it, and **learn** from it, but please do not rely on it for critical security needs.

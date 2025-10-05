Assignment No. 01

Section: BSDS-2
Semester: Fall 2025
Student Name: Ahmad Mahad Khan
CMS ID: 503103

Overview

This assignment showcases the implementation of Linked Lists, Stacks, and other essential data structures through three applied problem simulations:

Polynomial ADT – Algebraic manipulation using a linked list–based representation of terms.

Text Editor Simulation – Cursor-based text editing using two stacks.

UNO Card Game Simulation – Multi-player game logic built around dynamic state updates.

Each problem focuses on modularity, efficiency, and robust error handling to ensure clean and reusable implementations of data structure concepts.

Problem 1: Polynomial ADT
Approach

Utilized a singly linked list to represent polynomial terms, where each node holds a coefficient and exponent.

Implemented the following functions:

insertTerm(coef, exp) — Inserts a term in sorted order while merging like terms.

add(const Polynomial& other) — Returns a new polynomial that represents the sum.

multiply(const Polynomial& other) — Performs polynomial multiplication using nested iteration.

derivative() — Computes the derivative by applying the power rule to each term.

toString() — Formats the polynomial into a readable string such as 3x^4 + 2x^2 - x + 5.

Corner Cases Handled

Combining like terms.

Ignoring zero-coefficient terms.

Handling empty polynomial inputs.

Data Structure Used  : Linked List 

Problem 2: Text Editor Simulation
Approach

Implemented using two stacks to mimic text cursor movement efficiently:

left stack — stores characters to the left of the cursor.

right stack — stores characters to the right.

Supported operations include:

insertChar(char c) — Inserts a character at the cursor position.

deleteChar() — Deletes the character before the cursor.

moveLeft() / moveRight() — Moves the cursor left or right.

display() — Shows the current text along with a ‘|’ representing the cursor.

Example: "ab|c" → cursor is after 'b'.

Corner Cases Handled

Cursor cannot move beyond text boundaries.

Backspace at the start of the text has no effect.

Output remains consistent after every operation.

Data Structure Used

Two Stacks (std::stack<char>) for maintaining left and right portions of the text.

Problem 3: UNO Game Simulation
Approach

Designed a UNOGameImpl class based on a given interface to simulate a 2–4 player UNO game.

Managed deck, discard pile, and player hands using vectors.

The deck contains 76 cards (number + action cards) across four colors, shuffled with a fixed seed 1234 for reproducibility.

Gameplay Logic

Each player starts with 7 cards.

On a turn:

A player plays a matching card by color or value.

If none is playable, they draw one card.

A random 50% chance determines whether a player calls “UNO.”

Missing the UNO call triggers a 2-card penalty.

Properly implements Skip, Reverse, and Draw Two effects, as well as direction handling and player rotation.

The game ends when a player runs out of cards.

Corner Cases Handled

UNO detection (only one card left).

Handling empty deck situations.

Proper direction toggle and skip logic.

Challenges Faced

Merging polynomial terms correctly within a linked list.

Managing cursor movements efficiently without rebuilding entire strings.

Ensuring correct handling of action cards and turn order in the UNO simulation.

Keeping results reproducible by using a fixed random seed.

Repository Link

🔗 GitHub Repository (Public)

Compilation & Execution
# Compile Polynomial ADT
g++ AhmadMahadKhan_503103_polynomial.cpp -o polynomial
./polynomial

# Compile Text Editor
g++ AhmadMahadKhan_503103_texteditor.cpp -o texteditor
./texteditor

# Compile UNO Game
g++ AhmadMahadKhan_503103_uno.cpp -o uno
./uno



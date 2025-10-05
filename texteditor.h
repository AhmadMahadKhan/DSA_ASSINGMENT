
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>

class TextEditor {
public:
    virtual ~TextEditor() = default;  // Virtual destructor

    // Insert character at cursor
    virtual void insertChar(char c) = 0;

    // Delete character before cursor
    virtual void deleteChar() = 0;

    // Move cursor one position left
    virtual void moveLeft() = 0;

    // Move cursor one position right
    virtual void moveRight() = 0;

    // Return string with cursor position
    virtual std::string getTextWithCursor() const = 0;
};

#endif
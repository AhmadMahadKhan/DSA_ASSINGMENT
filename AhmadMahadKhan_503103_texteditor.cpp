#include "texteditor.h"
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Text editor is the parent class
class TextEditorImplemetation : public TextEditor {
private:
    stack<char> left;
    stack<char> right;


    static stack<char> insertAtBottom(stack<char> st, char c) {
        if (st.empty()) {
            st.push(c);
            return st;
        }


        char top = st.top();
        st.pop();
        stack<char> rest = insertAtBottom(st, c);

        rest.push(top);
        return rest;
    }



    // method  to move to the right
    static char removeBottom(stack<char>& st) {
        if (st.empty()) return '\0';
        char top = st.top();
        st.pop();
        if (st.empty()) {
            return top;
        }
        char bottom = removeBottom(st);
        st.push(top);
        return bottom;
    }

public:
    TextEditorImplemetation() {}

    ~TextEditorImplemetation() override {}

    // Insert character at cursor
    void insertChar(char c) override {
        left.push(c);
    }

    // Delete character before cursor
    void deleteChar() override {
        if (left.empty()) return;
        left.pop();
    }

    // Move cursor one position left
    void moveLeft() override {
        if (left.empty()) return;

        char left_top = left.top();
        left.pop();
        right = insertAtBottom(right, left_top);
    }

    // Move cursor one position right
    void moveRight() override {
        if (right.empty()) return;

        char right_bottom = removeBottom(right);

        if (right_bottom != '\0') left.push(right_bottom);
    }

    // Return string with cursor position
    string getTextWithCursor() const override {
        stack<char> temp(left);
        string left_text = "";
        while(!temp.empty()) {
            char top = temp.top();
            left_text = top + left_text;
            temp.pop();
        }

        left_text = left_text + "|";

        temp = stack<char>(right);
        string right_text = "";
        while(!temp.empty()) {
            char top = temp.top();
            right_text = top + right_text;
            temp.pop();
        }

        return left_text + right_text;
    }
};

void text_editor_check() {


    // insertiion text
    TextEditor* text1 = new TextEditorImplemetation();
    text1->insertChar('h');
    text1->insertChar('e');
    cout << "inserting 'he': " << text1->getTextWithCursor() << endl;
    cout << "Expected: he|" << endl;
    cout << "Passed" << endl;


    // deleting the text char
    TextEditor* text2 = new TextEditorImplemetation();
    text2->insertChar('a');
    text2->insertChar('b');
    text2->insertChar('1');
    cout << "After inserting ab1: " << text2->getTextWithCursor() << endl;
    text2->deleteChar();
    cout << "After deleting: " << text2->getTextWithCursor() << endl;
    cout << "Expected: ab|" << endl;
    cout << "Passed" << endl;

    // moving the cursor to the left

    TextEditor* text3 = new TextEditorImplemetation();
    text3->insertChar('h');
    text3->insertChar('e');
    text3->insertChar('l');
    text3->insertChar('l');
    text3->insertChar('o');
    cout << "After inserting 'hello': " << text3->getTextWithCursor() << endl;
    text3->moveLeft();
    text3->moveLeft();
    cout << "After moving left twice: " << text3->getTextWithCursor() << endl;
    cout << "Expected: hel|lo" << endl;
    cout << "Passed"<<endl;


    // moving cursor to the right
    TextEditor* text4 = new TextEditorImplemetation();
    text4->insertChar('h');
    text4->insertChar('e');
    text4->insertChar('l');
    text4->insertChar('l');
    text4->insertChar('o');
    text4->moveLeft();
    text4->moveLeft();
    cout << "After 'hello' and moving left twice: " << text4->getTextWithCursor() << endl;
    text4->moveRight();
    cout << "After moving right once: " << text4->getTextWithCursor() << endl;
    cout << "Expected: hell|o" << endl;
    cout << "Passed" << endl;

}
int main() {
    // text_editor_check();
}
#include <iostream>
#include <vector>
#include <conio.h> 
#include <memory>

class Node {
public:
    char data;
    std::shared_ptr<Node> next;
    Node(char c) : data(c), next(nullptr) {}
};

class LinkedList {
private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    int length;

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    void insert(char c) {
        auto newNode = std::make_shared<Node>(c);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void display() {
        auto current = head;
        while (current) {
            std::cout << current->data;
            current = current->next;
        }
    }

    int getLength() const { return length; }

    std::shared_ptr<Node> getHead() const { return head; }
};

class TextEditor {
private:
    std::vector<LinkedList> lines;
    int currentLine;
    int cursorPosition;
    bool insertMode;

public:
    TextEditor() : currentLine(0), cursorPosition(0), insertMode(false) 
    {
        lines.emplace_back(); 
    }

    void toggleInsertMode() {
        insertMode = !insertMode;
        std::cout << (insertMode ? "Insert Mode" : "Normal Mode") << std::endl;
    }

    void insertCharacter(char c) {
        if (insertMode && currentLine < lines.size()) {
            auto& line = lines[currentLine];
            if (cursorPosition >= line.getLength()) {
                line.insert(c);
            }
            else {
                line.insert(c);
            }
            cursorPosition++;
        }
    }

    void createNewLine() {
        if (insertMode) {
            lines.insert(lines.begin() + currentLine + 1, LinkedList());
            currentLine++;
            cursorPosition = 0; 
        }
    }

    void moveCursorLeft() {
        if (cursorPosition > 0) cursorPosition--;
    }

    void moveCursorRight() {
        if (cursorPosition < lines[currentLine].getLength()) cursorPosition++;
    }

    void moveUp() {
        if (currentLine > 0) currentLine--;
    }

    void moveDown() {
        if (currentLine < lines.size() - 1) currentLine++;
    }

    void display() {
        system("cls"); 
        for (int i = 0; i < lines.size(); ++i) {
            lines[i].display();
            if (i == currentLine) {
                std::cout << "\n" << std::string(cursorPosition, ' ') << "^" << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << "Current Mode: " << (insertMode ? "Insert" : "Normal") << std::endl;
    }

    void run() {
        char ch;
        while (true) {
            display();
            ch = _getch(); // Get character input

            switch (ch) {
            case 27: // ESC key to exit
                return;
            case 'i': // Toggle Insert mode
                toggleInsertMode();
                break;
            case 75: // Left arrow key
                moveCursorLeft();
                break;
            case 77: // Right arrow key
                moveCursorRight();
                break;
            case 72: // Up arrow key
                moveUp();
                break;
            case 80: // Down arrow key
                moveDown();
                break;
            case '\r': // Enter key pressed
                createNewLine();
                break;
            default:
                if (insertMode) insertCharacter(ch);
                break;
            }
        }
    }
};

int main() {
    TextEditor editor;
    editor.run();
    return 0;
}

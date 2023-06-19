#include <stdio.h>
#include <stdlib.h>

#define LINE_LIMIT 10

typedef struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    Node* cursor;
    int lineLength;
} TextEditor;

void initializeEditor(TextEditor* editor) {
    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;
    editor->lineLength = 0;
}

void insertCharacter(TextEditor* editor, char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = str[i];
            newNode->next = NULL;
            newNode->prev = NULL;

            if (editor->head == NULL) {
                editor->head = newNode;
                editor->tail = newNode;
                editor->cursor = newNode;
            } else {
                if (editor->cursor == NULL) {
                    editor->cursor = newNode;
                    editor->head = newNode;
                } else {
                    Node* nextNode = editor->cursor->next;
                    editor->cursor->next = newNode;
                    newNode->prev = editor->cursor;
                    newNode->next = nextNode;
                    if (nextNode != NULL) {
                        nextNode->prev = newNode;
                    } else {
                        editor->tail = newNode;
                    }
                    editor->cursor = newNode;
                }
            }

            editor->lineLength++;
        }

        if (editor->lineLength >= LINE_LIMIT && str[i] != '\n') {
            Node* newLineNode = (Node*)malloc(sizeof(Node));
            newLineNode->data = '\n';
            newLineNode->next = NULL;
            newLineNode->prev = editor->cursor;
            editor->cursor->next = newLineNode;
            editor->tail = newLineNode;
            editor->cursor = newLineNode;
            editor->lineLength = 0;
        }

        i++;
    }
}

void deleteCharacter(TextEditor* editor) {
    if (editor->cursor != NULL) {
        Node* prevNode = editor->cursor->prev;
        Node* nextNode = editor->cursor->next;

        if (prevNode != NULL) {
            prevNode->next = nextNode;
        } else {
            editor->head = nextNode;
        }

        if (nextNode != NULL) {
            nextNode->prev = prevNode;
            editor->cursor = nextNode;
        } else {
            editor->tail = prevNode;
            editor->cursor = prevNode;
        }

        free(editor->cursor);
        editor->lineLength--;
    }
}

void moveCursorLeft(TextEditor* editor) {
    if (editor->cursor != NULL && editor->cursor->prev != NULL) {
        editor->cursor = editor->cursor->prev;
    }
}

void moveCursorRight(TextEditor* editor) {
    if (editor->cursor != NULL && editor->cursor->next != NULL) {
        editor->cursor = editor->cursor->next;
    }
}

void displayText(TextEditor* editor) {
    Node* currentNode = editor->head;
    while (currentNode != NULL) {
        printf("%c", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main() {
    TextEditor editor;
    char choice;
    char str[100];

    initializeEditor(&editor);

    do {
        printf("\n------ Menu ------\n");
        printf("1. Insert characters\n");
        printf("2. Delete character\n");
        printf("3. Move cursor left\n");
        printf("4. Move cursor right\n");
        printf("5. Display text\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter characters to insert: ");
                scanf(" %[^\n]s", str);
                insertCharacter(&editor, str);
                break;
            case '2':
                deleteCharacter(&editor);
                break;
            case '3':
                moveCursorLeft(&editor);
                break;
            case '4':
                moveCursorRight(&editor);
                break;
            case '5':
                displayText(&editor);
                break;
            case '0':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != '0');

    return 0;
}


#include <curses.h>
#include "quizapp.h"

int main() {
    // PDCurses������
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // �N�C�Y�̎��s
    QuizApp quizApp;
    quizApp.runQuiz();

    // PDCurses�I������
    endwin();

    return 0;
}

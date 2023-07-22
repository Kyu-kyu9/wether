#include <curses.h>
#include "quizapp.h"

int main() {
    // PDCurses初期化
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // クイズの実行
    QuizApp quizApp;
    quizApp.runQuiz();

    // PDCurses終了処理
    endwin();

    return 0;
}

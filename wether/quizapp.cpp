#include "quizapp.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

QuizApp::QuizApp() {
    // クイズデータの読み込み
    const char* quizFilename = get_iniDirectory();
    if (!loadQuizData(quizFilename)) {
        // クイズデータの読み込みに失敗した場合のエラーハンドリング
        throw std::runtime_error("クイズデータの読み込みに失敗しました。");
    }
}

void QuizApp::runQuiz() {
    int score = 0;
    int numQuestions = quizData.numQuestions;

    // クイズのメインループ
    for (int i = 0; i < numQuestions; i++) {
        int userAnswer = displayQuestion(quizData.questions[i], i + 1);
        if (userAnswer == quizData.questions[i].correctAnswer) {
            score++;
            mvprintw(11, 1, "正解！ 現在のスコア: %d/%d", score, i + 1);
        }
        else {
            mvprintw(11, 1, "不正解... 現在のスコア: %d/%d", score, i + 1);
        }
        mvprintw(12, 1, "何かキーを押して次の問題へ");
        refresh();
        getch(); // ユーザーがEnterキーを押すまで次の問題へ
    }

    mvprintw(14, 1, "クイズ終了！ 最終スコア: %d/%d", score, numQuestions);
    mvprintw(15, 1, "何かキーを押して終了します...");
    refresh();
    getch();

    // スコアをファイルに出力
    saveScore("score.txt", score, numQuestions);
}

bool QuizApp::loadQuizData(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::vector<Question> questions;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string questionText;
        std::string choice1, choice2, choice3, choice4;
        int correctAnswer;

        // CSV形式で問題と選択肢を読み込む
        if (std::getline(iss, questionText, ',') &&
            std::getline(iss, choice1, ',') &&
            std::getline(iss, choice2, ',') &&
            std::getline(iss, choice3, ',') &&
            std::getline(iss, choice4, ',') &&
            iss >> correctAnswer) {

            Question question;
            question.questionText = questionText;
            question.choices[0] = choice1;
            question.choices[1] = choice2;
            question.choices[2] = choice3;
            question.choices[3] = choice4;
            question.correctAnswer = correctAnswer;

            questions.push_back(question);
        }
    }

    file.close();

    quizData.numQuestions = questions.size();
    if (quizData.numQuestions > 0) {
        for (int i = 0; i < quizData.numQuestions; i++) {
            quizData.questions[i] = questions[i];
        }
    }
    else {
        return false;
    }

    return true;
}

int QuizApp::displayQuestion(const Question& question, int questionNumber) {
    clear();
    mvprintw(2, 1, "問題 %d: %s", questionNumber, question.questionText.c_str());
    mvprintw(4, 1, "1. %s", question.choices[0].c_str());
    mvprintw(5, 1, "2. %s", question.choices[1].c_str());
    mvprintw(6, 1, "3. %s", question.choices[2].c_str());
    mvprintw(7, 1, "4. %s", question.choices[3].c_str());
    mvprintw(9, 1, "回答を選択してください (1-4): ");
    refresh();

    int userAnswer = 0;
    while (true) {
        char inputChar = getch();
        if (inputChar >= '1' && inputChar <= '4') {
            userAnswer = inputChar - '0';
            break;
        }
    }
    return userAnswer;
}

bool QuizApp::saveScore(const char* filename, int score, int totalQuestions) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << "最終スコア: " << score << "/" << totalQuestions << std::endl;
    file.close();
    return true;
}

const char* QuizApp::get_iniDirectory() {
    static char ini_filename[MAX_PATH];

    char section[MAX_PATH];
    char keyword[MAX_PATH];
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);

    sprintf_s(section, "section1");
    sprintf_s(keyword, "filename");

    char settingFile[MAX_PATH];
    sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);

    // 設定ファイル(setting.ini)からクイズデータファイル名を読み込む
    if (GetPrivateProfileString(section, keyword, "none", ini_filename, MAX_PATH, settingFile) != 0) {
        return ini_filename;
    }
    else {
        fprintf_s(stdout, "%s dosen't contain [%s] %s\n", settingFile, section, keyword);
    }

    return "";
}

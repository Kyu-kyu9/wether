#pragma once
#ifndef QUIZAPP_H
#define QUIZAPP_H

#include <string>

// クイズの問題と選択肢を格納する構造体
struct Question {
    std::string questionText;
    std::string choices[4];
    int correctAnswer;
};

// クイズデータを格納する構造体
struct QuizData {
    int numQuestions;
    Question questions[100]; // 最大100問まで対応
};

// クイズアプリのクラス
class QuizApp {
public:
    QuizApp();
    void runQuiz();

private:
    bool loadQuizData(const char* filename);
    int displayQuestion(const Question& question, int questionNumber);
    bool saveScore(const char* filename, int score, int totalQuestions);
    const char* get_iniDirectory();

    QuizData quizData;
};

#endif // QUIZAPP_H

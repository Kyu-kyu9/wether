#pragma once
#ifndef QUIZAPP_H
#define QUIZAPP_H

#include <string>

// �N�C�Y�̖��ƑI�������i�[����\����
struct Question {
    std::string questionText;
    std::string choices[4];
    int correctAnswer;
};

// �N�C�Y�f�[�^���i�[����\����
struct QuizData {
    int numQuestions;
    Question questions[100]; // �ő�100��܂őΉ�
};

// �N�C�Y�A�v���̃N���X
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

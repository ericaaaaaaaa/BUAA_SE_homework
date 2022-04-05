#include <QtWidgets/QApplication>
#include <QCommandLineParser>
#include <QPushButton>
#include <QDebug>
#include <QObject>
#include <iostream>
#include <windows.h>
#include <assert.h>
#include <fstream>
#include <streambuf>
#include <string>
#include "windows.h"
#include "form.h"
#include "tchar.h"
//#include "pair.h"

#pragma execution_character_set("utf-8")

using namespace std;
//extern "C"

typedef int(*functionN)(char* words[], int len, char* result[]);
typedef int(*functionM)(char* words[], int len, char* result[]);
typedef int(*functionW)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
typedef int(*functionC)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

typedef int (*chain_word)(char* [], int, char* [], char, char, bool);
typedef int (*chain_all)(char* [], int, char* []);
typedef int (*chain_word_unique)(char* [], int, char* []);
typedef int (*chain_char)(char* [], int, char* [], char, char, bool);

inline bool isLegalFilename(const string& name) {
    size_t len = name.length(); // .txt
    if (len > 3 && name[len - 1] == 't' && name[len - 2] == 'x'
        && name[len - 3] == 't' && name[len - 4] == '.') return true;
    return false;
}

int main(int argc, char* argv[]) {
    
    HMODULE hModule;
    hModule = LoadLibrary(TEXT("../bin/core.dll"));
    if (hModule == nullptr) {
        //cout<<GetLastError()<<endl;
        cout << "dll doesn't exist" << endl;
        return 0;
    }

    chain_word W = (chain_word)GetProcAddress(hModule, "gen_chain_word");
    chain_all N = (chain_all)GetProcAddress(hModule, "gen_chains_all");
    chain_word_unique M = (chain_word_unique)GetProcAddress(hModule, "gen_chain_word_unique");
    chain_char C = (chain_char)GetProcAddress(hModule, "gen_chain_char");
    //string str = "./Core_pair.dll";
    //LPCSTR path = str.c_str();
    /*
    functionC C = (functionC)GetProcAddress(hModule, "gen_chain_char");
    functionW W = (functionW)GetProcAddress(hModule, "gen_chain_word");
    functionN N = (functionN)GetProcAddress(hModule, "gen_chains_all");
    functionM M = (functionM)GetProcAddress(hModule, "gen_chain_word_unique");
    */
    if (C == NULL) {
        cout << "cannot find function -c";
        return 0;
    }
    if (N == NULL) {
        cout << "cannot find function -n";
        return 0;
    }
    if (W == NULL) {
        cout << "cannot find function -w";
        return 0;
    }
    if (M == NULL) {
        cout << "cannot find function -m";
        return 0;
    }
    //cout << "finish load function" << endl;
    // start GUI
    QApplication a(argc, argv);
    auto *hw = new QWidget();    //main GUI window
    Ui::Form createUi;      //createUi is not a real window
    createUi.setupUi(hw);   //createUi is a tool for creating the GUI
    // 清空文本
    QWidget::connect(createUi.pushButton_clear, &QPushButton::clicked, [&]{
        createUi.textEdit_input->clear();
    });
    // 运行程序
    QWidget::connect(createUi.pushButton, &QPushButton::clicked, [&]{
        //qDebug() << "-n: " << createUi.checkBoxN->isChecked();
        //createUi.textBrowser->setText("haha\nhehe");
        // 防止在处理时 checkBox 被更改
        //cout << "CheckBox -n " << createUi.checkBoxN->isChecked();
        createUi.textEdit_input->setReadOnly(true); // 先将输入框设为只读
        createUi.lineEdit_H->setReadOnly(true);
        createUi.lineEdit_T->setReadOnly(true);
        //cout << "CheckBox -n " << createUi.checkBoxN->isChecked();
        // 读入 -h 和 -t，并判断是否合法
        char head = 0, tail = 0;
        if (createUi.checkBox_H->isChecked()) {
            string headStr = createUi.lineEdit_H->text().toStdString();
            if (headStr.length() != 1) { // head 长度不为 1
                createUi.textBrowser->setText("ERROR: head parameter illegal.(length != 1)");
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            else {
                head = headStr[0];
                /*
                if (isalpha(headStr[0])) {
                    head = tolower(headStr[0]);
                    cout << "set head as: " << head << endl;
                }
                else { // head 不为英文字符
                    createUi.textBrowser->setText("ERROR: head parameter illegal.(!isalpha())");
                    createUi.textEdit_input->setReadOnly(false);
                    createUi.lineEdit_H->setReadOnly(false);
                    createUi.lineEdit_T->setReadOnly(false);
                    return;
                }
                */
            }
        }
        if (createUi.checkBox_T->isChecked()) {
            string tailStr = createUi.lineEdit_T->text().toStdString();
            if (tailStr.length() != 1) { // head 长度不为 1
                createUi.textBrowser->setText("ERROR: tail parameter illegal.(length != 1)");
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            else {
                tail = tailStr[0];
                /*
                if (isalpha(tailStr[0])) {
                    tail = tolower(tailStr[0]);
                    cout << "set tail as: " << head << endl;
                }
                else { // head 不为英文字符
                    createUi.textBrowser->setText("ERROR: tail parameter illegal.(!isalpha())");
                    createUi.textEdit_input->setReadOnly(false);
                    createUi.lineEdit_H->setReadOnly(false);
                    createUi.lineEdit_T->setReadOnly(false);
                    return;
                }
                */
            }
        }
        //cout << "CheckBox -n " << createUi.checkBoxN->isChecked();
        // 读入文本框中的单词
        char** words = (char**)malloc(20000 * sizeof(char*));
        //char* words[20000];
        string inputString = createUi.textEdit_input->toPlainText().toStdString();
        //string inputString = std::string((const char*)createUi.textEdit_input->toPlainText().toLocal8Bit().constData());
        size_t strLen = inputString.length();
        string currentWord;
        int wordCount = 0;
        //cout << "Reading words from input text..." << endl;
        //cout << "Print inputString: " << inputString << endl;
        for (size_t i = 0; i < strLen; ++i) {
            char curChar = inputString[i];
            if (isalpha(curChar)) {
                currentWord += (islower(curChar)) ? (curChar) : ('a' + (curChar - 'A'));
            }
            else {
                if (currentWord.length() > 1) {
                    //cout << "ready to copy word: " << currentWord << endl;
                    words[wordCount] = (char*)malloc((currentWord.length() + 1) * sizeof(char));
                    //strcpy_s(words[wordCount++], currentWord.length() + 1, currentWord.data());
                    strcpy(words[wordCount++], currentWord.c_str());
                    //words[wordCount] = (char*)currentWord.c_str();
                    //words[wordCount] = currentWord.c_str;
                    //cout << "copy finished" << endl;
                }
                currentWord.clear();
            }
            if (wordCount > 10000 || (createUi.checkBox_R->isChecked() && wordCount > 100)) {
                createUi.textBrowser->setText("ERROR: input text is too long");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
        }
        if (currentWord.length() > 1) { 
            words[wordCount] = (char*)malloc((currentWord.length() + 1) * sizeof(char));
            strcpy(words[wordCount++], currentWord.c_str());
        }
        //cout << "Reading words finished. Total: " << wordCount << endl;
        // 查看是否有各种参数 & 选择函数进行处理 & 判断参数组合合法性
        if (createUi.checkBoxN->isChecked()) { 
            //cout << "In function -n" << endl;
            // 检查合法性
            if (createUi.checkBox_W->isChecked() || createUi.checkBox_C->isChecked() ||
                createUi.checkBox_H->isChecked() || createUi.checkBox_T->isChecked() ||
                createUi.checkBox_M->isChecked()) {
                createUi.textBrowser->setText("ERROR: parameter illegal: -n cannot appear with other parameters");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            //cout << "function -n is legal. Start running..." << endl;
            // int gen_chains_all(char* words[], int len, char* result[])
            // 返回所有符合定义的单词链，函数返回值为单词链的总数
            char* result[20000] = { 0 };
            int returnValue = N(words, wordCount, result);
            //int returnValue = gen_chains_all(words, wordCount, result);
            //cout << "Proccess finished. Return value " << returnValue << endl;
            if (returnValue > 20000) { // 返回单词链数过长
                createUi.textBrowser->setText("ERROR: output text is too long");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            if (returnValue == -1) { // 包含环路
                createUi.textBrowser->setText("ERROR: contains loop");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            // 打印结果
            string ret = to_string(returnValue) + "\n";
            //cout << ret << endl;
            for (int i = 0; i < returnValue; ++i) {
                ret += string(result[i]) + "\n";
            }
            createUi.textBrowser->setText(QString::fromStdString(ret));
        }
        else if (createUi.checkBox_W->isChecked()) {
            // int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
            /* 计算最多单词数量的最长单词链，其中前三个参数已经在上文进行了说明，head和tail分别为单词链首字母与尾字母约束
            （如果传入0，表示没有约束），当enable_loop为true时表示允许输入单词文本中隐含“单词环” */
            if (createUi.checkBox_C->isChecked() || createUi.checkBox_M->isChecked()) {
                createUi.textBrowser->setText("ERROR: parameter illegal: -w cannot appear with -m or -c");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            char* result[20000] = { 0 };
            //cout << "WWW: head: " << head << endl;
            int returnValue = W(words, wordCount, result, head, tail, createUi.checkBox_R->isChecked());
            //cout << "Proccess finished. Return value " << returnValue << endl;
            if (returnValue > 20000) { // 返回单词链数过长
                createUi.textBrowser->setText("ERROR: output text is too long");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            if (returnValue == -1) { // 包含环路
                createUi.textBrowser->setText("ERROR: contains loop");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            if (returnValue == -2) { // 参数异常
                createUi.textBrowser->setText(QString::fromStdString(result[0]));
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            string ret = to_string(returnValue) + "\n";
            for (int i = 0; i < returnValue; ++i) {
                ret += string(result[i]) + "\n";
            }
            createUi.textBrowser->setText(QString::fromStdString(ret));
        }
        else if (createUi.checkBox_C->isChecked()) {
            if (createUi.checkBox_M->isChecked()) {
                createUi.textBrowser->setText("ERROR: parameter illegal: -c cannot appear with -m");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            char* result[20000] = { 0 };
            int returnValue = C(words, wordCount, result, head, tail, createUi.checkBox_R->isChecked());
            //cout << "Proccess finished. Return value " << returnValue << endl;
            if (returnValue > 20000) { // 返回单词链数过长
                createUi.textBrowser->setText("ERROR: output text is too long");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            if (returnValue == -1) { // 包含环路
                createUi.textBrowser->setText("ERROR: contains loop");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            if (returnValue == -2) { // 参数异常
                createUi.textBrowser->setText(QString::fromStdString(result[0]));
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            string ret = to_string(returnValue) + "\n";
            for (int i = 0; i < returnValue; ++i) {
                ret += string(result[i]) + "\n";
            }
            createUi.textBrowser->setText(QString::fromStdString(ret));
        }
        else if (createUi.checkBox_M->isChecked()) {
            char* result[20000] = { 0 };
            int returnValue = M(words, wordCount, result);
            //cout << "Proccess finished. Return value " << returnValue << endl;
            if (returnValue > 20000) { // 返回单词链数过长
                createUi.textBrowser->setText("ERROR: output text is too long");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            if (returnValue == -1) { // 包含环路
                createUi.textBrowser->setText("ERROR: contains loop");
                free(words);
                createUi.textEdit_input->setReadOnly(false);
                createUi.lineEdit_H->setReadOnly(false);
                createUi.lineEdit_T->setReadOnly(false);
                return;
            }
            // 打印结果
            string ret = to_string(returnValue) + "\n";
            for (int i = 0; i < returnValue; ++i) {
                ret += string(result[i]) + "\n";
            }
            createUi.textBrowser->setText(QString::fromStdString(ret));
        }
        else { // 没有功能参数
            createUi.textBrowser->setText("ERROR: no functional parameter.(-n or -w or -c or -m needed)");
            free(words);
            createUi.textEdit_input->setReadOnly(false);
            createUi.lineEdit_H->setReadOnly(false);
            createUi.lineEdit_T->setReadOnly(false);
            return;
        }
        // 释放空间
        //cout << "About to free" << endl;
        free(words);
        //cout << "free finished" << endl;
        // 恢复可以编辑的状态
        createUi.textEdit_input->setReadOnly(false); // 先将输入框设为只读
        createUi.lineEdit_H->setReadOnly(false);
        createUi.lineEdit_T->setReadOnly(false);
    });
    // 导入文本
    QWidget::connect(createUi.pushButton_import, &QPushButton::clicked, [&]{
        QString strSrcName = QFileDialog::getOpenFileName(
                hw,
                QObject::tr("打开输入文件"),
                QObject::tr("."),
                QObject::tr("Text files(*.txt);;")
        );
        if (isLegalFilename(strSrcName.toStdString())) {
            //ifstream t(strSrcName.toStdString());
            //string str((std::istreambuf_iterator<char>(t)),
                //std::istreambuf_iterator<char>());
            //createUi.textEdit_input->setText(QString::fromStdString(str));
            QFile file(strSrcName);
            file.open(QIODevice::ReadOnly);
            QByteArray array = file.readAll();
            createUi.textEdit_input->setText(array);
            file.close();
        }
        else {
            createUi.textBrowser->setText("ERROR: filename illegal");
        }
    });
    // 导出文本
    QWidget::connect(createUi.pushButton_export, &QPushButton::clicked, [&]{
        /*
        QString output = createUi.textBrowser->toPlainText();
        QFile outputFile;
        outputFile.setFileName("./solution.txt");
        if(outputFile.open(QIODevice::WriteOnly |QIODevice::Text)){
            QTextStream stream(&outputFile);
            stream << output  << endl;
            outputFile.close();
        }
        */
        QString curPath = QCoreApplication::applicationDirPath();//返回应用程序可执行文件所在的目录
        QString dlgTitle = "保存文件";
        QString filter = "txt文件(*.txt)";
        QString aFileName = QFileDialog::getSaveFileName(hw, dlgTitle, curPath, filter);
        QFile outputFile;
        outputFile.setFileName(aFileName);
        QString output = createUi.textBrowser->toPlainText();
        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&outputFile);
            stream << output << endl;
            outputFile.close();
        }
    });
    hw->show();             //hw is the real window
    return QApplication::exec();
}

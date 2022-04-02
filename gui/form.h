/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FORM_H
#define FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QFileDialog>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QCheckBox *checkBox_M;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QCheckBox *checkBox_T;
    QCheckBox *checkBox_W;
    QCheckBox *checkBox_C;
    QCheckBox *checkBoxN;
    QPushButton *pushButton_export;
    QLabel *label;
    QPushButton *pushButton_import;
    QCheckBox *checkBox_R;
    QTextEdit *textEdit_input;
    QPushButton *pushButton_clear;
    QCheckBox *checkBox_H;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit_H;
    QLineEdit *lineEdit_T;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(796, 559);
        checkBox_M = new QCheckBox(Form);
        checkBox_M->setObjectName(QStringLiteral("checkBox_M"));
        checkBox_M->setGeometry(QRect(500, 110, 91, 19));
        scrollArea = new QScrollArea(Form);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(40, 336, 701, 191));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 699, 189));
        scrollArea->setWidget(scrollAreaWidgetContents);
        checkBox_T = new QCheckBox(Form);
        checkBox_T->setObjectName(QStringLiteral("checkBox_T"));
        checkBox_T->setGeometry(QRect(500, 200, 91, 19));
        checkBox_W = new QCheckBox(Form);
        checkBox_W->setObjectName(QStringLiteral("checkBox_W"));
        checkBox_W->setGeometry(QRect(500, 80, 91, 19));
        checkBox_C = new QCheckBox(Form);
        checkBox_C->setObjectName(QStringLiteral("checkBox_C"));
        checkBox_C->setGeometry(QRect(500, 140, 91, 19));
        checkBoxN = new QCheckBox(Form);
        checkBoxN->setObjectName(QStringLiteral("checkBoxN"));
        checkBoxN->setGeometry(QRect(500, 50, 91, 19));
        pushButton_export = new QPushButton(Form);
        pushButton_export->setObjectName(QStringLiteral("pushButton_export"));
        pushButton_export->setGeometry(QRect(330, 280, 93, 28));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(500, 20, 72, 15));
        pushButton_import = new QPushButton(Form);
        pushButton_import->setObjectName(QStringLiteral("pushButton_import"));
        pushButton_import->setGeometry(QRect(50, 280, 93, 28));
        checkBox_R = new QCheckBox(Form);
        checkBox_R->setObjectName(QStringLiteral("checkBox_R"));
        checkBox_R->setGeometry(QRect(500, 230, 91, 19));
        textEdit_input = new QTextEdit(Form);
        textEdit_input->setObjectName(QStringLiteral("textEdit_input"));
        textEdit_input->setGeometry(QRect(30, 20, 411, 241));
        pushButton_clear = new QPushButton(Form);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(190, 280, 93, 28));
        checkBox_H = new QCheckBox(Form);
        checkBox_H->setObjectName(QStringLiteral("checkBox_H"));
        checkBox_H->setGeometry(QRect(500, 170, 91, 19));
        textBrowser = new QTextBrowser(Form);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(30, 330, 721, 201));
        lineEdit_H = new QLineEdit(Form);
        lineEdit_H->setObjectName(QStringLiteral("lineEdit_H"));
        lineEdit_H->setGeometry(QRect(550, 170, 113, 21));
        lineEdit_T = new QLineEdit(Form);
        lineEdit_T->setObjectName(QStringLiteral("lineEdit_T"));
        lineEdit_T->setGeometry(QRect(550, 200, 113, 21));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(470, 280, 93, 28));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("最长单词链", "最长单词链", Q_NULLPTR));
        checkBox_M->setText(QApplication::translate("Form", "-m", Q_NULLPTR));
        checkBox_T->setText(QApplication::translate("Form", "-t", Q_NULLPTR));
        checkBox_W->setText(QApplication::translate("Form", "-w", Q_NULLPTR));
        checkBox_C->setText(QApplication::translate("Form", "-c", Q_NULLPTR));
        checkBoxN->setText(QApplication::translate("Form", "-n", Q_NULLPTR));
        pushButton_export->setText(QApplication::translate("Form", "\345\257\274\345\207\272\346\226\207\346\234\254", Q_NULLPTR));
        label->setText(QApplication::translate("Form", "\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_import->setText(QApplication::translate("Form", "\345\257\274\345\205\245\346\226\207\346\234\254", Q_NULLPTR));
        checkBox_R->setText(QApplication::translate("Form", "-r", Q_NULLPTR));
        textEdit_input->setHtml(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\234\250\346\255\244\350\276\223\345\205\245\346\226\207\346\234\254</p></body></html>", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("Form", "\346\270\205\347\251\272", Q_NULLPTR));
        checkBox_H->setText(QApplication::translate("Form", "-h", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Form", "\350\277\220\350\241\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

class Widget : public QWidget {
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_import_clicked();

    void on_pushButton_export_clicked();

    void on_pushButton_run_clicked();
};

void Widget::on_pushButton_import_clicked()
{
    //获取将要打开的文件名
    QString strSrcName = QFileDialog::getOpenFileName(
            this,
            tr("打开配置文件"),
            tr("."),
            tr("Text files(*.txt);;All files(*)")
    );
    if( strSrcName.isEmpty() )
    {
        //空字符串不处理，返回
        return;
    }
    else
    {
        //设置源文件名
        throw strSrcName;
    }
}

QT_END_NAMESPACE

#endif // FORM_H

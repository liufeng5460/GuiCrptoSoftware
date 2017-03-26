#ifndef DECRYPTIONUI_H
#define DECRYPTIONUI_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QTextEdit>
#include <QComboBox>

class DecryptionUI : public QWidget
{
    Q_OBJECT
public:
    explicit DecryptionUI(QWidget *parent = 0);

private:
    QGridLayout *Layout01;
    QLabel *fileInputLabel;
    QLabel *showChoseFile;
    QLabel *showOutputFile;
    QPushButton *choseOutputRoot;
    QPushButton *choseFileBtn;
    QPushButton *decrptionFileBtn;


    QGridLayout *Layout02;
    QLabel *typingInputLabel;
    QTextEdit *inputStrArea;
    QPushButton *decrptionStrBtn;

    QGridLayout *Layout03;
    QLabel *outputLabel;
    QTextEdit *outputArea;
    QPushButton *saveToLocal;

    QLabel *choseKeyLabel;
    QComboBox *chooseKey;


signals:

protected slots:
 //   void choseFile();
   // void changeRoot();
  //  void doDecryptionFile();
  // void doDecryptionString();

//    void saveToLocalFun();
};

#endif // DECRYPTIONUI_H

#ifndef ENCRYPTIONUI_H
#define ENCRYPTIONUI_H


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


class EncryptionUI : public QWidget
{
    Q_OBJECT
public:
    explicit EncryptionUI(QWidget *parent = 0);

private:
    QGridLayout *Layout01;
    QLabel *fileInputLabel;
    QLabel *showChoseFile;
    QLabel *showOutputFile;
    QPushButton *choseOutputRoot;
    QPushButton *choseFileBtn;
    QPushButton *encrptionFileBtn;

    QGridLayout *Layout02;
    QLabel *typingInputLabel;
    QTextEdit *inputStrArea;
    QPushButton *encrptionStrBtn;

    QGridLayout *Layout03;
    QLabel *outputLabel;
    QTextEdit *outputArea;
    QPushButton *saveToLocal;

    QLabel *choseKeyLabel;
    QComboBox *chooseKey;


signals:

protected slots:
 //   void choseFile();
  //  void changeRoot();

  //  void doEncryptionFile();
  //  void doEncryptionString();


};




#endif // ENCRYPTIONUI_H

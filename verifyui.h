#ifndef VERIFYUI_H
#define VERIFYUI_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include "qstring.h"
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRadioButton>
#include <QStringList>
#include <QLabel>
#include <QComboBox>
class VerifyUI : public QWidget
{
    Q_OBJECT
public:
    explicit VerifyUI(QWidget *parent = 0);

private:
    QGridLayout *Layout01;

    QLabel *fileInputLabel;
    QLabel *showSignFile;
    QLabel *showOriFile;
    QLabel *choseModeLabel;
    QLabel *choseKeyLabel;
    QRadioButton *MD2,*MD5;
    QPushButton *choseSignFileBtn;
    QPushButton *choseOriFileBtn;
    QPushButton *verifyFileBtn;

    QComboBox *chooseKey;


signals:


protected slots:
  //  void choseSignFile();
 //   void choseOriFile();
  //  void doVerify();
};

#endif // VERIFYUI_H

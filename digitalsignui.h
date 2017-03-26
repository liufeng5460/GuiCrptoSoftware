#ifndef DIGITALSIGNUI_H
#define DIGITALSIGNUI_H


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


class DigitalSignUI : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalSignUI(QWidget *parent = 0);


private:
    QGridLayout *Layout01;

    QLabel *fileInputLabel;
    QLabel *showChoseFile;
    QLabel *showOutputFile;
    QLabel *choseModeLabel;
    QLabel *choseKeyLabel;
    QRadioButton *MD2,*MD5;
    QPushButton *choseRootBtn;
    QPushButton *choseFileBtn;
    QPushButton *signFileBtn;

    QComboBox *chooseKey;


signals:


protected slots:
  //  void choseFile();
    //void changeRoot();
  //  void doSign();
//    void itemClicked(QModelIndex index);
};

#endif // DIGITALSIGNUI_H

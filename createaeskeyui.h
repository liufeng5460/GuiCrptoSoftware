#ifndef CREATEAESKEYUI_H
#define CREATEAESKEYUI_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>


#include <QFileDialog>
#include <QGridLayout>
#include <QTextEdit>
#include <QRadioButton>

class CreateAESKeyUI : public QWidget
{
    Q_OBJECT
public:
    explicit CreateAESKeyUI(QWidget *parent = 0);

private:
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *KeyLengthLabel;
    QRadioButton *Lenth16;
    QRadioButton *Lenth32;
    QPushButton *submitBtn;

private slots:
    void genAesKey();
};

#endif // CREATEAESKEYUI_H

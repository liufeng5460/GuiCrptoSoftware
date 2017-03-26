#ifndef CREATECERTIFICATION
#define CREATECERTIFICATION

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStack>
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QTextEdit>



class CreateCertificationUI : public QWidget
{
    Q_OBJECT
public:
    explicit CreateCertificationUI(QWidget *parent = 0);

private:
    QLabel *nameLabel;
    QLabel *mailLabel;
    QLabel *validFromLabel;
    QLabel *validUtilLabel;
    QLineEdit *nameEdit;
    QLineEdit *mailEdit;
    QLineEdit *validFromEdit;
    QLineEdit *validUtilEdit;
    QString pubFileName;
    QString privFileName;
    QPushButton *submitBtn;

signals:
    void toShowWidget(QStack<QString>);

private slots:
    void pushShowWidget(QString );
    void genKey();

};



#endif //CREATECERTIFICATION


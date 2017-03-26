#include "verifyui.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
VerifyUI::VerifyUI(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("文件验证"));
    this->setWindowIcon(QIcon(":/image/encrypt"));

    /**** Layout01 ****/
    fileInputLabel=new QLabel(tr("请选择待验证的文件：（txt格式）"));
    showSignFile=new QLabel(tr("签名后的文件："));
    showOriFile=new QLabel(tr("签名前的文件："));
    choseModeLabel=new QLabel(tr("请选择使用MD2或MD5："));
//    MD2=new QRadioButton(tr("MD2"),this);
//    MD5=new QRadioButton(tr("MD5"),this);
    choseOriFileBtn=new QPushButton(tr("浏览"));
    choseSignFileBtn=new QPushButton(tr("浏览"));
    verifyFileBtn=new QPushButton(tr("验证文件"));

    Layout01=new QGridLayout();
    Layout01->addWidget(fileInputLabel,0,0);
    Layout01->addWidget(showOriFile,1,0);
    Layout01->addWidget(choseOriFileBtn,1,1);
    Layout01->addWidget(showSignFile,2,0);
    Layout01->addWidget(choseSignFileBtn,2,1);
    Layout01->addWidget(choseModeLabel,3,0);
//    Layout01->addWidget(MD2,4,0);
//    Layout01->addWidget(MD5,5,0);


     /**** Layout02 ****/
    chooseKey = new QComboBox();
    choseKeyLabel=new QLabel(tr("请选择一个证书"));

    /*********read file content*********/
    QFile *file=new QFile(QCoreApplication::applicationDirPath()+"/Key/pubkey");
    QTextCodec *code = QTextCodec::codecForName("utf8");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(file);
    stream.setCodec(code);

    QString line;
    do{
       line =QString(stream.readLine());
        QStringList temp  = line.split(";") ;
        chooseKey->addItem(temp[0]);
    } while (!line.isNull());
    file->close();

    Layout01->addWidget(choseKeyLabel,6,0);
    Layout01->addWidget(chooseKey,7,0);
    Layout01->addWidget(verifyFileBtn,8,1);

    /**** Layout02 ****/


    /*************************************/
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(Layout01);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //connect(choseSignFileBtn,SIGNAL(clicked()),this,SLOT(choseSignFile()));
  // connect(choseOriFileBtn,SIGNAL(clicked()),this,SLOT(choseOriFile()));
 //   connect(verifyFileBtn,SIGNAL(clicked()),this,SLOT(doVerify()));
}


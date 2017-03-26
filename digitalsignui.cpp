#include "digitalsignui.h"
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>
#include <QTextCodec>
#include <QStringList>
#include <QCoreApplication>
#include <string>

#include "myrsa.h"
DigitalSignUI::DigitalSignUI(QWidget *parent):
    QWidget(parent)
{

    this->setWindowTitle(tr("文件签名"));
    this->setWindowIcon(QIcon(":/img/encrypt.jpg"));

    /**** Layout01 ****/
    fileInputLabel=new QLabel(tr("请选择待签名的文件：（txt格式）"));
    showChoseFile=new QLabel;
    showOutputFile=new QLabel;
    choseModeLabel=new QLabel(tr("请选择使用MD2或MD5："));
//    MD2=new QRadioButton(tr("MD2"),this);
//    MD5=new QRadioButton(tr("MD5"),this);
    choseFileBtn=new QPushButton(tr("浏览"));
    choseRootBtn=new QPushButton(tr("更改路径"));
    signFileBtn=new QPushButton(tr("数字签名"));

    Layout01=new QGridLayout();
    Layout01->addWidget(fileInputLabel,0,0);
    Layout01->addWidget(showChoseFile,1,0);
    Layout01->addWidget(choseFileBtn,1,1);
    Layout01->addWidget(showOutputFile,2,0);
    Layout01->addWidget(choseRootBtn,2,1);
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
    Layout01->addWidget(signFileBtn,8,1);

    /**** Layout02 ****/


    /*************************************/
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(Layout01);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //connect(choseFileBtn,SIGNAL(clicked()),this,SLOT(choseFile()));
  //  connect(choseRootBtn,SIGNAL(clicked()),this,SLOT(changeRoot()));
   // connect(signFileBtn,SIGNAL(clicked()),this,SLOT(doSign()));

}


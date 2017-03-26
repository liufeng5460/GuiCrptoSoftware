#include "createcertificationui.h"
#include "fileoperation.h"
#include<QTextCodec>
#include<QStringList>
#include<QTextStream>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>

#include "myrsa.h"


CreateCertificationUI::CreateCertificationUI(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle(tr("新建证书"));

    nameLabel=new QLabel(tr("姓名:\t"));
    mailLabel=new QLabel(tr("邮箱:\t"));
    validFromLabel=new QLabel(tr("生效期:\t"));
    validUtilLabel=new QLabel(tr("失效期:\t"));

    nameEdit=new QLineEdit;
    mailEdit=new QLineEdit;
    validFromEdit=new QLineEdit;
    validUtilEdit=new QLineEdit;

    submitBtn=new QPushButton(tr("提交"));

    QGridLayout *mainLayout =new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(15);

    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameEdit,0,1);
    mainLayout->addWidget(mailLabel,1,0);
    mainLayout->addWidget(mailEdit,1,1);
    mainLayout->addWidget(validFromLabel,2,0);
    mainLayout->addWidget(validFromEdit,2,1);
    mainLayout->addWidget(validUtilLabel,3,0);
    mainLayout->addWidget(validUtilEdit,3,1);
    mainLayout->addWidget(submitBtn,4,1);


    connect(submitBtn,SIGNAL(clicked()),this,SLOT(genKey()));
//    connect(submitBtn,SIGNAL(clicked()),this,SLOT(pushShowWidget()));
}


void CreateCertificationUI::genKey(){

    QString keyname=nameEdit->text();
     string name=keyname.toStdString();

     FileOperation testKeyName;
     if(testKeyName.isContain(keyname,"mykey")){
             QMessageBox::critical(this,tr("警告"),tr("该RSA密钥已存在，请换一个名称！"));
             return;
     }

     string privFile="Key/RSA/PrivKey_"+name;
     string pubFile="Key/RSA/PubKey_"+name;

    const char *privFilename=privFile.c_str();
    const char *pubFilename=pubFile.c_str();

    pubFileName = QString::fromStdString(pubFile);
    privFileName = QString::fromStdString(privFile);

    MyRSA rsa;
    rsa.GenerateRSAKey(2048, privFilename, pubFilename);

    QString MyKeyinfo=nameEdit->text().toUtf8()+";" +mailEdit->text().toUtf8()+";" +validFromEdit->text().toUtf8()+";" +validUtilEdit->text().toUtf8() +";"
            +pubFilename+";"+privFilename;

    pushShowWidget(MyKeyinfo);

}




void CreateCertificationUI::pushShowWidget(QString MyKeyinfo)
{
    QStack<QString> inform;
    inform.push(privFileName);
    inform.push(pubFileName);
    inform.push(validUtilEdit->text());
    inform.push(validFromEdit->text());
    inform.push(mailEdit->text());
    inform.push(nameEdit->text());
    emit toShowWidget(inform);

    QFile file01(QCoreApplication::applicationDirPath()+"/Key/mykey");
    if( file01.open(QIODevice::ReadWrite|QIODevice::Append | QIODevice::Text) ){
       QTextStream in01(&file01);
       in01<<  MyKeyinfo << "\n";
    } else {
        qDebug() <<  file01.error();
        qDebug() <<  file01.errorString();
    }
    file01.close();

    this->close();
}

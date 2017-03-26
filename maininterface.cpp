#include "maininterface.h"
#include <QMenu>
#include <QMenuBar>

MainInterface::MainInterface(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("集成加密软件"));
    this->setWindowIcon(QIcon(":/img/Icon"));
    this->setMinimumSize(850,350);

    showWidget = new ShowWidgetUI(this);
    setCentralWidget(showWidget);


     createCertification=new CreateCertificationUI;

   createAESKEY=new CreateAESKeyUI;
     encryptionWindow =new EncryptionUI;
      decryptionWindow =new DecryptionUI;
     digitalWindow=new DigitalSignUI;
     verifyWindow=new VerifyUI;
  //   client=new Client;

    createActions();
    createMenus();
    createToolBars();


}

MainInterface::~MainInterface()
{

}

void MainInterface::createActions()
{
    //"引入新证书"动作
    importCertificationAction =new QAction(QIcon(":/img/import.jpg"),tr("引入证书"),this);
    importCertificationAction->setShortcut(tr("Ctrl+O"));
    importCertificationAction->setStatusTip(tr("添加一个证书"));
    connect(importCertificationAction,SIGNAL(triggered()),this,SLOT(showSelectCertification()));

    //"新建新证书"动作
    newCertificationAction =new QAction(QIcon(":/img/newFile.jpg"),tr("新建证书"),this);
    newCertificationAction->setShortcut(tr("Ctrl+N"));
    newCertificationAction->setStatusTip(tr("新建一个证书"));
    connect(newCertificationAction,SIGNAL(triggered()),this,SLOT(createNewCertification()));

    //"新建Aes Key"动作
    newAesKeyAction =new QAction(QIcon(":/img/newFile.jpg"),tr("新建Aes密钥"),this);
    newAesKeyAction->setStatusTip(tr("新建Aes密钥"));
    connect(newAesKeyAction,SIGNAL(triggered()),this,SLOT(createNewAESKey()));

    //更改接收文件端口号
    changePortAction=new QAction(tr("更改本机端口号"),this);
    changePortAction->setStatusTip(tr("更改本机接收文件端口号"));
 //   connect(changePortAction,SIGNAL(triggered()),this,SLOT(changePortWidget()));

    //"加密"动作
    EncryptionAction =new QAction(QIcon(":/img/encrypt.jpg"),tr("加密文件"),this);
    EncryptionAction->setStatusTip(tr("打开加密窗口"));
    connect(EncryptionAction,SIGNAL(triggered()),this,SLOT(openEncryptWindow()));

    //"解密"动作
    DecryptionAction =new QAction(QIcon(":/img/decrypt.jpg"),tr("解密文件"),this);
    DecryptionAction->setStatusTip(tr("打开解密窗口"));
    connect(DecryptionAction,SIGNAL(triggered()),this,SLOT(openDecryptWindow()));


    //"数字签名"动作
    digitalSignature =new QAction(QIcon(":/img/digtialsignature.jpg"),tr("数字签名"),this);
    digitalSignature->setStatusTip(tr("数字签名"));
      connect(digitalSignature,SIGNAL(triggered()),this,SLOT(openDigtialSignatureWindow()));


    //"身份认证"动作
    authentication =new QAction(QIcon(":/img/identity.jpg"),tr("身份认证"),this);
    authentication->setStatusTip(tr("身份认证"));
   connect(authentication,SIGNAL(triggered()),this,SLOT(openAuthenticationWindow()));

    //"文件传输"动作
    FileTransitionAction=new QAction(QIcon(":/img/filetransition.jpg"),tr("文件传输"),this);
    FileTransitionAction->setStatusTip(tr("文件传输"));
  //  connect(FileTransition,SIGNAL(triggered()),this,SLOT(openServer()));


    //"退出"动作
    exitAction =new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
}

void MainInterface::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("file"));
    fileMenu->addAction(importCertificationAction);
    fileMenu->addAction(newCertificationAction);
    fileMenu->addAction(newAesKeyAction);
    fileMenu->addSeparator();
     fileMenu->addAction(exitAction);

    fileMenu = menuBar()->addMenu(tr("manipulation"));
    fileMenu->addAction(EncryptionAction);
    fileMenu->addAction(DecryptionAction);
    fileMenu->addSeparator();
    fileMenu->addAction(FileTransitionAction);

}

void MainInterface::createToolBars()
{
    //zone01
    zone01 =addToolBar("File");
    zone01->addAction(newCertificationAction);

    //zone02
    zone02 =addToolBar("Tool");
    zone02->addAction(EncryptionAction);
    zone02->addAction(DecryptionAction);
    zone02->addAction(digitalSignature);
    zone02->addAction(authentication);
    zone02->addAction(FileTransitionAction);

   zone01->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    zone02->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

}


void MainInterface::showSelectCertification(){
    showWidget->AddCertification();

}

void MainInterface::createNewCertification(){
    createCertification->show();
}

void MainInterface::openEncryptWindow(){
    encryptionWindow->show();
}

void MainInterface::createNewAESKey(){
    createAESKEY->show();
}


void MainInterface::openDecryptWindow(){
    decryptionWindow->show();
}


void MainInterface::openDigtialSignatureWindow(){
    digitalWindow->show();
}

void MainInterface::openAuthenticationWindow(){
    verifyWindow->show();
}

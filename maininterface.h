#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>

#include "showwidgetui.h"
#include "createcertificationui.h"
#include "encryptionui.h"
#include "createaeskeyui.h"
#include "decryptionui.h"
#include "digitalsignui.h"
#include "verifyui.h"
class MainInterface : public QMainWindow
{
    Q_OBJECT

public:
    MainInterface(QWidget *parent = 0);
    ~MainInterface();

    void createActions();                        	//创建动作
    void createMenus();                           	//创建菜单
    void createToolBars();                      	//创建工具栏


private:

    ShowWidgetUI *showWidget;

    CreateCertificationUI *createCertification;
     EncryptionUI *encryptionWindow;
     DecryptionUI *decryptionWindow;
     CreateAESKeyUI * createAESKEY;
     DigitalSignUI *digitalWindow;
    VerifyUI *verifyWindow;

    QMenu *fileMenu;

    QAction *importCertificationAction;
    QAction *newCertificationAction;
    QAction *newAesKeyAction;
    QAction *digitalSignature;
    QAction *authentication;
    QAction *changePortAction;
    QAction *FileTransitionAction;
    QAction *EncryptionAction;
    QAction *DecryptionAction;
    QAction *exitAction;

    QToolBar *zone01;                          	//工具栏
    QToolBar *zone02;

protected slots:

    void showSelectCertification();
    void createNewCertification();
    void createNewAESKey();
    void openEncryptWindow();
     void openDecryptWindow();
    void openDigtialSignatureWindow();
    void openAuthenticationWindow();

   // void openServer();
//    void openClient();

  // void changePortWidget();
   // void changeUdpPort();
};

#endif // MAININTERFACE_H

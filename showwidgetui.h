#ifndef SHOWWIDGETUI_H
#define SHOWWIDGETUI_H

#include <QString>
#include <QStandardItemModel>
#include <QTableView>
#include <QMenu>
#include <QAction>

class ShowWidgetUI : public QFrame
{
    Q_OBJECT
public:
    explicit ShowWidgetUI(QWidget *parent = 0);

    //此处用于接收Certification内容
    QString *name;
    QString *mail;
    QString *validFrom;
    QString *validUtil;
    QString *detail;
    QString *keyId;

    QStandardItemModel *model01;
    QStandardItemModel *model02;
    QTableView *tableView01;
    QTableView *tableView02;

    QMenu *menu01;
    QMenu *menu02;
    QAction *deletePubKey;
    QAction *deletePubAndPrivKey;
    QAction *showPubKeyMess;
    QAction *showPubAndPrivKeyMess;

public slots:
    void AddCertification();
    void createMenu();

    void showMenu01(QPoint);
    void showMenu02(QPoint);


    void deletePubKeyFun();
    void deletePubAndPrivKeyFun();
     void showPubKeyMessFun();
     void showPubKeyMessFun(const QModelIndex &);
     void showPubAndPrivKeyMessFun();
     void showPubAndPrivKeyMessFun(const QModelIndex &);

     QString readTableData(QTableView * ,int , int );
};

#endif // SHOWWIDGETUI_H

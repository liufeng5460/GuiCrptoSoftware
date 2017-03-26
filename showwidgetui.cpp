#include "showwidgetui.h"
#include "fileoperation.h"
#include "myrsa.h"
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QStack>
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include <QTextStream>
#include <string>
ShowWidgetUI::ShowWidgetUI(QWidget *parent)
{
    model01 = new QStandardItemModel();
    model01->setColumnCount(6);
    model01->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("姓名"));
    model01->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("邮箱"));
    model01->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("生效期"));
    model01->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("失效期"));
    model01->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("公钥"));
    model01->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("私钥"));

    tableView01=new QTableView;
    tableView01->setModel(model01);
    tableView01->setColumnWidth(0,115);
    tableView01->setColumnWidth(1,130);
    tableView01->setColumnWidth(2,85);
    tableView01->setColumnWidth(3,85);
    tableView01->setColumnWidth(4,195);
    tableView01->setColumnWidth(5,195);
    tableView01->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView01->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView01->setMouseTracking(true);

    model02 = new QStandardItemModel();
    model02->setColumnCount(5);
    model02->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("姓名"));
    model02->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("邮箱"));
    model02->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("生效期"));
    model02->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("失效期"));
    model02->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("公钥"));

    tableView02=new QTableView;
    tableView02->setModel(model02);
    tableView02->setColumnWidth(0,150);
    tableView02->setColumnWidth(1,180);
    tableView02->setColumnWidth(2,120);
    tableView02->setColumnWidth(3,120);
    tableView02->setColumnWidth(4,230);
    tableView02->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView02->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView02->setMouseTracking(true);

    /*********read file content*********/
    QFile *file01=new QFile(QCoreApplication::applicationDirPath()+"/Key/mykey");
    QTextCodec *code = QTextCodec::codecForName("utf8");
    file01->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream01(file01);
    stream01.setCodec(code);

    QString line;
    int linenum=0;
    do{
        line =QString(stream01.readLine());
        if(line.isEmpty() || line.isNull()) break;
        QStringList temp  = line.split(";") ;
        QList<QString>::Iterator it = temp.begin(),itend = temp.end();
          int iter = 0;
          for (;it != itend && iter<=5; it++,iter++){
              model01->setItem(linenum, iter, new QStandardItem(temp[iter]));
           }
          linenum++;
    } while (!line.isNull() && !line.isEmpty());
     file01->close();

     /*********read file content*********/
     QFile *file02=new QFile(QCoreApplication::applicationDirPath()+"/Key/pubkey");
     file02->open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream stream02(file02);
     stream02.setCodec(code);
     linenum=0;
     do{
         line =QString(stream02.readLine());
         if(line.isEmpty() || line.isNull()) break;
         QStringList temp  = line.split(";") ;
         QList<QString>::Iterator it = temp.begin(),itend = temp.end();
           int iter = 0;
           for (;it != itend && iter<=4; it++,iter++){
             model02->setItem(linenum, iter, new QStandardItem(temp[iter]));
            }
           linenum++;
     } while (!line.isNull() && !line.isEmpty());
      file02->close();


      QVBoxLayout *mainLayout =new QVBoxLayout(this);
      mainLayout->setMargin(5);
      mainLayout->setSpacing(5);
      mainLayout->addWidget(new QLabel(tr("我的证书：")));
      mainLayout->addWidget(tableView01);
      mainLayout->addWidget(new QLabel(tr("拥有他人证书：")));
      mainLayout->addWidget(tableView02);

      createMenu();

      connect(tableView01, SIGNAL(customContextMenuRequested(QPoint)),
              this, SLOT(showMenu01(QPoint)));
      connect(tableView02, SIGNAL(customContextMenuRequested(QPoint)),
              this, SLOT(showMenu02(QPoint)));

      connect(tableView02, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(showPubKeyMessFun(const QModelIndex &)));
      connect(tableView01, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(showPubAndPrivKeyMessFun(const QModelIndex &)));



}


void ShowWidgetUI::createMenu()
{
    menu01=new QMenu(tableView01);
    menu02=new QMenu(tableView02);

    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView02->setContextMenuPolicy(Qt::CustomContextMenu);

    deletePubKey=new QAction(this);
    deletePubKey->setText(QString(tr("删除该证书")));
    deletePubAndPrivKey=new QAction(this);
    deletePubAndPrivKey->setText(QString(tr("删除该证书")));
    showPubKeyMess=new QAction(this);
    showPubKeyMess->setText(QString(tr("查看证书信息")));
    showPubAndPrivKeyMess=new QAction(this);
    showPubAndPrivKeyMess->setText(QString(tr("查看证书信息")));

  connect(deletePubKey, SIGNAL(triggered(bool)), this, SLOT(deletePubKeyFun()));
  connect(deletePubAndPrivKey, SIGNAL(triggered(bool)), this, SLOT(deletePubAndPrivKeyFun()));
    connect(showPubKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubKeyMessFun()));
    connect(showPubAndPrivKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubAndPrivKeyMessFun()));

}


void ShowWidgetUI::showMenu01(QPoint pos)
{
        menu01->clear(); //清除原有菜单
        menu01->addAction(deletePubAndPrivKey);
        menu01->addAction(showPubAndPrivKeyMess);
        //菜单出现的位置为当前鼠标的位置
        menu01->exec(QCursor::pos());
}

void ShowWidgetUI::showMenu02(QPoint pos)
{
    menu02->clear(); //清除原有菜单
    menu02->addAction(deletePubKey);
    menu02->addAction(showPubKeyMess);
    //菜单出现的位置为当前鼠标的位置
    menu02->exec(QCursor::pos());
}


void ShowWidgetUI::showPubKeyMessFun(){
    int currentRow = tableView02->currentIndex().row();
    QString keyroot=readTableData(tableView02,currentRow,4);
    MyRSA rsa;
    string content;
    try{
    content= rsa.getKey(keyroot.toStdString().c_str());
    }catch(FileStore::OpenErr e){
        QMessageBox::warning(this,tr("Detail"),tr("file open error!"));
        return;
    }
    QString detail=tr("公钥路径：\n");
    detail += keyroot + "\n";
    detail += tr("公钥内容：\n");
    detail += QString::fromStdString(content);
    QMessageBox::information(this,tr("Detail"),detail);
}

void ShowWidgetUI::showPubKeyMessFun(const QModelIndex &index){
    int currentRow=index.row();
    QString keyroot=readTableData(tableView02,currentRow,4);
    MyRSA rsa;
  //  string content = rsa.getKey(keyroot.toStdString().c_str());
    string content;
    try{
    content= rsa.getKey(keyroot.toStdString().c_str());
    }catch(FileStore::OpenErr e){
        QMessageBox::warning(this,tr("Detail"),tr("file open error!"));
        return;
    }
    QString detail=tr("公钥路径：\n");
    detail += keyroot + "\n";
    detail += tr("公钥内容：\n");
    detail += QString::fromStdString(content);
    QMessageBox::information(this,tr("Detail"),detail);
}

QString ShowWidgetUI::readTableData(QTableView *tableView, int row, int col){
    QAbstractItemModel *tmpModel = tableView->model();
    QModelIndex index = tmpModel->index(row,col);
    return tmpModel->data(index).toString();
}

void ShowWidgetUI::showPubAndPrivKeyMessFun(const QModelIndex &index){
    int currentRow=index.row();
    QAbstractItemModel *tmpModel = tableView01->model();
    QModelIndex index01 = tmpModel->index(currentRow,4);
    QModelIndex index02 = tmpModel->index(currentRow,5);
    QString pubkeyroot=tmpModel->data(index01).toString();
    QString privkeyroot=tmpModel->data(index02).toString();
    MyRSA rsa;
    string pubkey;
    string privkey;
    try{
     pubkey = rsa.getKey(pubkeyroot.toStdString().c_str());
     privkey = rsa.getKey(privkeyroot.toStdString().c_str());
    }catch(FileStore::OpenErr e){
        QMessageBox::warning(this,tr("Detail"),tr("file open error!"));
        return;
    }

    QString detail=tr("公钥路径： \t");
    detail += pubkeyroot + "\n";
    detail += tr("公钥内容：\n");
    detail += QString::fromStdString(pubkey) + "\n \n";
    detail += tr("私钥路径： \t");
    detail += privkeyroot + "\n";
    detail += tr("私钥内容：\n");
    detail += QString::fromStdString(privkey);
    QMessageBox::information(this,tr("Detail"),detail);
}

void ShowWidgetUI::showPubAndPrivKeyMessFun(){
    int currentRow = tableView01->currentIndex().row();
    QString pubkeyroot=readTableData(tableView01,currentRow,4);
    QString privkeyroot=readTableData(tableView01,currentRow,5);
    MyRSA rsa;
    string pubkey;
    string privkey;
    try{
     pubkey = rsa.getKey(pubkeyroot.toStdString().c_str());
     privkey = rsa.getKey(privkeyroot.toStdString().c_str());
    }catch(FileStore::OpenErr e){
        QMessageBox::warning(this,tr("Detail"),tr("file open error!"));
        return;
    }

    QString detail=tr("公钥路径： \t");
    detail += pubkeyroot + "\n";
    detail += tr("公钥内容：\n");
    detail += QString::fromStdString(pubkey) + "\n \n";
    detail += tr("私钥路径： \t");
    detail += privkeyroot + "\n";
    detail += tr("私钥内容：\n");
    detail += QString::fromStdString(privkey);
    QMessageBox::information(this,tr("Detail"),detail);
}

void ShowWidgetUI::deletePubKeyFun(){

    QMessageBox message(QMessageBox::Warning,tr("警告"),tr("删除证书的动作不可撤销，是否要删除该证书？"),QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::No){
        return;
    }

    int currentRow = tableView02->currentIndex().row();
    QString pubkeyroot = QCoreApplication::applicationDirPath() + "/" + readTableData(tableView02,currentRow,4);
    FileOperation fileOperation;
    try {
        QFile::remove(pubkeyroot);
        tableView02->model()->removeRow(currentRow);
        fileOperation.deleteOnelineInFile(currentRow,QString(QCoreApplication::applicationDirPath()+"/Key/pubkey"));
    } catch (Exception e) {
        cout << e.GetErrorType() << endl;
        cout << e.GetWhat() << endl;
        QMessageBox::warning(this,tr("delete public key"),tr("encounter an error!"));
        return;

    }
    QMessageBox::information(this,tr("delete public key"),tr("delete successfully!"));
}


void ShowWidgetUI::deletePubAndPrivKeyFun(){

    QMessageBox message(QMessageBox::Warning,tr("警告"),tr("删除证书的动作不可撤销，是否要删除该证书？"),QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::No){
        return;
    }

    int currentRow = tableView01->currentIndex().row();
    QString pubkeyroot= QCoreApplication::applicationDirPath() + "/" + readTableData(tableView01,currentRow,4);
    QString privkeyroot= QCoreApplication::applicationDirPath() + "/" + readTableData(tableView01,currentRow,5);
    FileOperation fileOperation;
    try {
        QFile::remove(pubkeyroot);
        QFile::remove(privkeyroot);
        tableView01->model()->removeRow(currentRow);
        fileOperation.deleteOnelineInFile(currentRow,QString(QCoreApplication::applicationDirPath()+"/Key/mykey"));
    } catch (Exception e) {
        cout << e.GetErrorType() << endl;
        cout << e.GetWhat() << endl;
        QMessageBox::warning(this,tr("delete public and private key"),tr("encounter an error!"));
        return;
    }
     QMessageBox::information(this,tr("delete public key"),tr("delete successfully!"));
}

void ShowWidgetUI::AddCertification()
{
    QString filePlace = QFileDialog::getOpenFileName(this,tr("打开文件"),"/","All files(*)");
    QFile *file=new QFile(filePlace);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(file);
    QTextCodec *code = QTextCodec::codecForName("ANSI");
    stream.setCodec(code);
    QString data;
    QString info="";
    int i=0;
    int currentIndex=tableView02->model()->rowCount();
    qDebug() << currentIndex;

    while (!stream.atEnd() && i<=5)
    {
        data=QString(stream.readLine());
        info=info+data+";";
        model02->setItem(currentIndex, i, new QStandardItem(data));
        i=i+1;
    }
    file->close();

    qDebug() << info;

    QFile filein(QCoreApplication::applicationDirPath()+"/Key/pubkey");
    if( filein.open(QIODevice::ReadWrite|QIODevice::Append | QIODevice::Text) ){
       QTextStream in(&filein);
       in<<  info << "\n";
    } else {
        qDebug() <<  filein.error();
        qDebug() <<  filein.errorString();
    }
    filein.close();
}

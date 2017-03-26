#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

class FileOperation
{
public:
    FileOperation();

    bool isContain(QString newKeyName, QString KeyInfoFileName);

    //删除文件的某一行
    void deleteOnelineInFile(int nNumLine, QString filename);
    void DeleteOneline(int nNum, QString &strall);
};

#endif // FILEOPERATION_H

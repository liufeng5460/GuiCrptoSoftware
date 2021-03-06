#include "fileoperation.h"
#include <QCoreApplication>
FileOperation::FileOperation()
{

}


bool FileOperation::isContain(QString newKeyName, QString KeyInfoFileName){
    QFile *keyInfo=new QFile(QCoreApplication::applicationDirPath()+"/Key/"+KeyInfoFileName);
    keyInfo->open(QIODevice::ReadOnly | QIODevice::Text);
    QString keyInfoStr=keyInfo->readAll();
    keyInfo->close();

    if(keyInfoStr.lastIndexOf(newKeyName)>=0){
        return true;
    }
    return false;
}



//如果是5行，RowNum最大为4
void FileOperation::DeleteOneline(int RowNum, QString &fileContent)//
{
    int nLine=0;
    int Index=0;
    //算出行数nLine
    while(Index!=-1)
    {
        Index=fileContent.indexOf('\n',Index+1);
        nLine++;
    }

    //如果是直接从位置0开始删除\n算一个字符"abc\nme\ndo" \n的index是3要删除3+1个字符，即index+1个
    if(RowNum==0)
    {
        int nIndex=fileContent.indexOf('\n');
        fileContent.remove(0,nIndex+1);
    }
    else
    {
        int nTemp=RowNum;
        int nIndex=0,nIndex2=0;
        while(nTemp--)
        {
            //
            nIndex=fileContent.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1)//说明是有效的
            {
                nIndex2=fileContent.indexOf('\n',nIndex+1);
            }
        }
        //删除的行不是最后一行（从nIndex+1这个位置起nIndex2-nIndex个字符全部抹去）
        if(RowNum<nLine-1)
        {
            fileContent.remove(nIndex+1, nIndex2-nIndex);//不用减一
        }
        //删除的是最后一行（从nIndex起始len-nIndex个字符全抹去）
        //不能从nIndex+1处开始，
        else if(RowNum==nLine-1)
        {
            int len=fileContent.length();
            fileContent.remove(nIndex,len-nIndex);
        }
        else
        {

        }

    }
}
void FileOperation::deleteOnelineInFile(int RowNum, QString filename)
{
    QString fileContent;
    QFile readfile(filename);
    if(readfile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&readfile);
        fileContent=stream.readAll();
    }
    readfile.close();
    DeleteOneline(RowNum, fileContent);

    QFile writefile(filename);
    if(writefile.open(QIODevice::WriteOnly))
    {
        QTextStream wrtstream(&writefile);
        wrtstream<<fileContent;
    }
    writefile.close();
}

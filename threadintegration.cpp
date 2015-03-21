#include "threadintegration.h"
#include <QDir>
#include <QFile>

ThreadIntegration::ThreadIntegration()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

ThreadIntegration::~ThreadIntegration()
{

}
void ThreadIntegration::setDate(int pStartYear, int pEndYear)
{
    startYear=pStartYear;
    endYear=pEndYear;
}

void ThreadIntegration::setChoice(int pChoice)
{
    choice = pChoice;
}
void ThreadIntegration::init()
{
    QFile f("20150101.csv");
    if(f.open (QIODevice::ReadOnly))
    {
        QTextStream ts (&f);
        QStringList line = ts.readLine().split(';');
        QString request = "CREATE TABLE firsttest(";
        int nbMusique = 0;
        for (int i = 0 ; i < line.length() ; i ++)
        {
            if (line[i].toUpper() == "MUSIQUE")
            {
                QString temp;
                switch(nbMusique)
                {
                case 0 :
                    temp = "Poney";
                    break;
                case 1 :
                    temp = "Jockey";
                    break;
                case 2 :
                    temp = "Trainer";
                    break;
                default:
                    break;
                }
                line[i] = line[i] + temp;
                nbMusique++;
            }
            line[i].replace(" ","");
            line[i].replace("/","");
            request+= line[i];
            request+= " char(255)";
            request+= ",";
        }
        request.remove(request.lastIndexOf(","),1);
        request+= ");";
        f.close ();
        QSqlQuery createDB;
        if(createDB.exec(request))
        {
            qDebug() << "BDD crée";
        }
        else
        {
            qDebug() << "Erreur lors de la création";
        }
    }

    else {
        qDebug() << "can't init BDD : not open";
    }
}

void ThreadIntegration::remove()
{
    if(db.isOpen())
    {
        QSqlQuery deleteBDD;
        if(deleteBDD.exec("DROP TABLE firsttest"))
        {
            qDebug() << "BDD supprimé";
            //retour = true;
        }
        else
        {
            qDebug() << "Erreur lors de la suppression";
        }
    }
    else
    {
        qDebug() << "can't delete BDD : not open";
    }
}

void ThreadIntegration::run()
{

    db.setDatabaseName("test.dev.db");
    if(db.open())
        qDebug() << "ok";
    if(db.isValid())
        qDebug() << "valid";
    bool retour = true;
    switch(choice)
    {
    case 0:
        update();
        break;
    case 1:
        remove();
        break;
    case 2:
        init();
    default: break;
    }
    db.close();
}

void ThreadIntegration::update()
{
    bool retour = true;
    for (int year = startYear; year < endYear; year++)
    {
        QString sDataDir("../../../data/"+QString::number(year));
        QDir dataDir(sDataDir);
        QStringList listfiles = dataDir.entryList();
        int nbOfFiles = listfiles.length() - 2;
        for (int file = 2 ; file < listfiles.length();file++)
        {
            QFile f(sDataDir+"/"+listfiles[file]);
            qDebug() << listfiles[file];
            if(f.open (QIODevice::ReadOnly))
            {
                QTextStream ts (&f);
                while(!ts.atEnd()){
                    QStringList line = ts.readLine().split(';');
                    QString request = "INSERT INTO firsttest VALUES(";
                    for (int i = 0 ; i < line.length() ; i ++)
                    {
                        request += "'";
                        line[i].replace("'","");
                        request += line[i];
                        request += "'";
                        request += ",";
                    }
                    request.remove(request.lastIndexOf(",")-3,4);
                    request+= ");";
                    QSqlQuery createDB;
                    if(!createDB.exec(request))
                    {
                        retour = false;
                    }
                }
                f.close ();
            }
        }
    }
}


#include "db.h"

DB::DB()
{

}

DB::~DB()
{

}
bool DB::connectBDD()
{
    bool retour = false;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.dev.db");
    if (db.isValid())
    {
        db.open();
        if (db.isOpen())
        {
            qDebug() << "DB is open";
            retour = true;
        } else {
            qDebug() << "DB is not open";
        }
    }
    else
    {
        qDebug() << "DB is not valid";
    }
    return retour;
}
bool DB::initBDD()
{
    bool retour = false;
    if(db.isOpen())
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
                retour = true;
            }
            else
            {
                qDebug() << "Erreur lors de la création";
            }
        }
    }
    else {
        qDebug() << "can't init BDD : not open";
    }
    return retour;
}

bool DB::deleteBDD()
{
    bool retour = false;
    if(db.isOpen())
    {
        QSqlQuery deleteBDD;
        if(deleteBDD.exec("DROP TABLE firsttest"))
        {
            qDebug() << "BDD supprimé";
            retour = true;
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
    return retour;
}

bool DB::updateData()
{
    bool retour = true;
    for (int year =2009; year < 2010 ; year++)
    {
        //changeStatusMessage("Year : " + QString::number(year));
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
                        //qDebug() << createDB.lastError().text();
                        //qDebug() << createDB.lastQuery();
                        retour = false;
                    }
                }
                f.close ();
            }
        }
    }
    return retour;
}


#include "threadintegration.h"


ThreadIntegration::ThreadIntegration()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    finDemandee = false;
}

ThreadIntegration::~ThreadIntegration()
{

}
void ThreadIntegration::setDate(int pStartYear, int pEndYear)
{
    startYear=pStartYear;
    endYear=pEndYear;
}

void ThreadIntegration::setFinDemandee(bool pFinDemande)
{
    finDemandee=pFinDemande;
}

void ThreadIntegration::setChoice(int pChoice)
{
    choice = pChoice;
}

bool ThreadIntegration::checkTable()
{
    QString request = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='PoneyDB'";
    QSqlQuery createDB;
    if(createDB.exec(request))
    {
        while(createDB.next())
        {
            if(createDB.value(0).toString() == "1")
            {
                return true;
            }
            else {
                return false;
            }
        }
    }
    else
    {
        emit haveSomethingToSay("Can't check if the table already exist");
    }
}
void ThreadIntegration::init()
{
    if(checkTable())
    {
        checkTableFinished("1");
    }
    else
    {
        checkTableFinished("0");
    }
}

void ThreadIntegration::create()
{
    if(!checkTable())
    {
        QFile f("structure.csv");
        if(f.open (QIODevice::ReadOnly))
        {
            QTextStream ts (&f);
            QStringList line = ts.readLine().split(';');
            QString request = "CREATE TABLE PoneyDB(";
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
                emit haveSomethingToSay("DB Poney created");
            }
            else
            {
                emit haveSomethingToSay("initialization : Can't create DB");
            }
        }
    }
    else
    {
        emit haveSomethingToSay("initalization : PONEYDB already exist");
    }
}

void ThreadIntegration::remove()
{
    if(checkTable())
    {
        QSqlQuery deleteBDD;
        if(deleteBDD.exec("DROP TABLE PoneyDB"))
        {
            emit haveSomethingToSay("DB deleted");
        }
        else
        {
            emit haveSomethingToSay("remove : Can't remove DB");
        }
    }
    else
    {
        emit haveSomethingToSay("remove : PONEYDB doesn't exist ,can't remove");
    }
}

void ThreadIntegration::run()
{
    db.setDatabaseName("test.dev.db");
    if(!db.open() || !db.isValid())
    {
        emit haveSomethingToSay("run : can't open DB");
    }
    else
    {
        switch(choice)
        {
        case 0:
            init();
            break;
        case 1:
            update();
            break;
        case 2:
            remove();
            break;
        case 3:
            create();
        default: break;
        }
        db.close();
    }
}

void ThreadIntegration::update()
{
    if(checkTable())
    {
        for (int year = startYear; year < endYear+1; year++)
        {
            QString sDataDir("../../../data/"+QString::number(year));
            QDir dataDir(sDataDir);
            QStringList listfiles = dataDir.entryList();
            int nbOfFiles = listfiles.length() - 2;
            emit yearStarted(QString::number(year) +"+"+QString::number(nbOfFiles)) ;
            for (int file = 2 ; file < listfiles.length();file++)
            {
                if(!finDemandee)
                {

                    QFile f(sDataDir+"/"+listfiles[file]);
                    qDebug() << listfiles[file];
                    if(f.open (QIODevice::ReadOnly))
                    {
                        QTextStream ts (&f);
                        while(!ts.atEnd()){
                            QStringList line = ts.readLine().split(';');
                            QString request = "INSERT INTO PoneyDB VALUES(";
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
                               // emit haveSomethingToSay("update :  can't insert this line");
                            }
                        }
                        f.close ();
                    }
                    emit lineInserted(file-2);
                }
                else {
                    emit threadStoped();
                    finDemandee = false;
                    break;
                }
            }
        }
    }
    else {
        emit haveSomethingToSay("update : can't update data -> click on create");
    }
}


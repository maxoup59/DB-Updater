#include "db.h"

DB::DB()
{
    queryExecutor = new ThreadIntegration();
}

DB::~DB()
{

}
bool DB::connectBDD()
{
    bool retour = false;
    return retour;
}
bool DB::initBDD()
{
    bool retour = true;
    queryExecutor->setChoice(2);
    queryExecutor->start();
    return retour;
}

bool DB::deleteBDD()
{
    bool retour = false;
    queryExecutor->setChoice(1);
    queryExecutor->start();
    return retour;
}

bool DB::updateData()
{
    bool retour = true;
    queryExecutor->setChoice(0);
    queryExecutor->start();
    return retour;
}

void DB::setYear(int start, int end)
{
    startYear = start;
    endYear = end;
}


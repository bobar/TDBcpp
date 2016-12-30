#include "TDBExceptions.h"

TDBException::TDBException()
{}


TDBTrigrammeException::TDBTrigrammeException(QString tri) :
        trig(tri)
{}
TDBTrigrammeInconnuException::TDBTrigrammeInconnuException(QString tri) :
        TDBTrigrammeException(tri)
{}
TDBTrigrammeExistantException::TDBTrigrammeExistantException(QString tri) :
        TDBTrigrammeException(tri)
{}

TDBTrigrammeInvalideException::TDBTrigrammeInvalideException(QString tri) :
        TDBTrigrammeException(tri)
{}

TDBTrigrammeMailException::TDBTrigrammeMailException(QString tri) :
        TDBTrigrammeException(tri)
{}

QString TDBTrigrammeException::what()
{
    return QString("Erreur de trigramme générique : ").append(trig);
}

QString TDBTrigrammeExistantException::what()
{
    return QString("Trigramme déjà existant : ").append(trig);
}

QString TDBTrigrammeInconnuException::what()
{
    return QString("Trigramme inconnu : ").append(trig);
}

QString TDBTrigrammeInvalideException::what()
{
    return QString("Trigramme invalide : ").append(trig);
}

QString TDBTrigrammeMailException::what()
{
    return QString("Trigramme sans mail : ").append(trig);
}

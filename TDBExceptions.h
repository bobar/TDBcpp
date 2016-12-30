#ifndef TDBEXCEPTIONS_H
#define TDBEXCEPTIONS_H

#include <QString>

// included by TDBApplication.h

enum trigramme_errors
{
    no_error,
    trigramme_existant,
    trigramme_inconnu
};

class TDBException
{
    public:
        virtual QString what() {return QString("Exception inconnue");}
        TDBException();
    protected:
};

class TDBTrigrammeException : public TDBException
{
    protected:
        QString trig;
    public:
        TDBTrigrammeException(QString tri);
        virtual QString what();
        QString trigramme() {return trig;}

};
class TDBTrigrammeExistantException : public TDBTrigrammeException
{
    public:
        TDBTrigrammeExistantException(QString tri);
        virtual QString what();
};

class TDBTrigrammeInconnuException : public TDBTrigrammeException
{
    public:
        TDBTrigrammeInconnuException(QString tri);
        virtual QString what();
};

class TDBTrigrammeInvalideException : public TDBTrigrammeException
{
    public:
        TDBTrigrammeInvalideException(QString tri);
        virtual QString what();
};

class TDBAuthException {
};


class TDBTrigrammeMailException : public TDBTrigrammeException
{
    public:
        TDBTrigrammeMailException(QString tri);
        virtual QString what();
};

#endif

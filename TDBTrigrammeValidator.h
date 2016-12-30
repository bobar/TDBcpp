#ifndef TDBTRIGRAMMEVALIDATOR_H
#define TDBTRIGRAMMEVALIDATOR_H

#include <QValidator>

#include "TDBApplication.h"

class TDBTrigrammeValidator : public QValidator
{
    public:
        TDBTrigrammeValidator(QObject* parent);
        State validate(QString & input, int & pos) const;
};

#endif
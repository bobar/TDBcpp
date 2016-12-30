#include "TDBTrigrammeValidator.h"

TDBTrigrammeValidator::TDBTrigrammeValidator(QObject* parent) : QValidator(parent)
{
}

QValidator::State TDBTrigrammeValidator::validate(QString & input, int & pos) const
{
    input = input.toUpper();

	// quelques (rares) trucs interdits 
	// - commencer par un nombre
	// - les trucs de merde genre tabluation. On garde juste espace.
	if(input.length() > 0 && input.at(0).isDigit())
		return Invalid;
		
	for(int i = 0; i < input.length() ; i ++)
		if(!input.at(i).isPrint())
			return Invalid;
	
    switch (input.length())
    {
    case 0:case 1:case 2:
        return Intermediate;
        break;
    case 3:
        return Acceptable;
        break;
    default:
        return Invalid;
        break;
    }
}

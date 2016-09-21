
#ifndef IDNCONVERTER_H
#define IDNCONVERTER_H

#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QString>
#include <unicode/idna.h>

class IdnConverter : public QObject
{
	Q_OBJECT

public:
	IdnConverter();
	~IdnConverter();
	QString convertToAce(const QString &);
	QString convertToIdn(const QString &);
	
private: 
	icu::IDNA *idnaConv;
	QString buildResult(const icu::UnicodeString &, const icu::IDNAInfo &, const UErrorCode &);
	
};

#endif


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
	
	/**
	 * Converts the given domain name to ACE format.
	 */
	QString convertToAce(const QString &);
	
	/**
	 * Converts the given domain name to IDN format.
	 */
	QString convertToIdn(const QString &);
	
private: 
	
	/**
	 * The IDNA instance for conversion
	 */
	icu::IDNA *idnaConv;
	
	/**
	 * Builds a result string taking care of conversion errors check.
	 * 
	 * @param text conversion result to use
	 * @param info container of IDNA processing details
     * @param errCode ICU error code
	 */
	QString buildResult(const icu::UnicodeString &text, const icu::IDNAInfo &info, const UErrorCode &errCode);
	
};

#endif


#ifndef IDNCONVERTER_H
#define IDNCONVERTER_H

#include <QString>
#include <memory>
#include <unicode/idna.h>

class IdnConverter
{

public:
	IdnConverter();

	/**
	 * Converts the given domain name to ACE format.
	 * Returns an empty string if the conversion fails.
	 */
	QString convertToAce(const QString &) const;

	/**
	 * Converts the given domain name to IDN format.
	 * Returns an empty string if the conversion fails.
	 */
	QString convertToIdn(const QString &) const;

private:

	/**
	 * The IDNA instance for conversion
	 */
	std::unique_ptr<icu::IDNA> idnaConv;

	/**
	 * Builds a result string taking care of conversion errors check.
	 *
	 * @param text conversion result to use
	 * @param info container of IDNA processing details
	 * @param errCode ICU error code
	 */
	static QString buildResult(const icu::UnicodeString &text, const icu::IDNAInfo &info, const UErrorCode &errCode);

};

#endif

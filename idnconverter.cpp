
#include "idnconverter.h"

#include <qt5/QtCore/QChar>
#include <qt5/QtCore/QString>
#include <unicode/idna.h>

IdnConverter::IdnConverter() 
{
	const int32_t idnaOpts = UIDNA_NONTRANSITIONAL_TO_ASCII | UIDNA_NONTRANSITIONAL_TO_UNICODE;
	UErrorCode errorCode = U_ZERO_ERROR;
	idnaConv = icu::IDNA::createUTS46Instance(idnaOpts, errorCode); 
}

IdnConverter::~IdnConverter()
{
	delete idnaConv;
}

QString IdnConverter::convertToAce(const QString &domainName)
{
	UErrorCode errCode = U_ZERO_ERROR;
	icu::IDNAInfo info;
	icu::UnicodeString source(domainName.toUtf8().constData());
	icu::UnicodeString target;
	
	idnaConv->nameToASCII(source, target, info, errCode);
	
	return buildResult(target, info, errCode);
}

QString IdnConverter::convertToIdn(const QString &domainName)
{
	UErrorCode errCode = U_ZERO_ERROR;
	icu::IDNAInfo info;
	icu::UnicodeString source(domainName.toUtf8().constData());
	icu::UnicodeString target;
	
	idnaConv->nameToUnicode(source, target, info, errCode);
	
	return buildResult(target, info, errCode);
}

QString IdnConverter::buildResult(const icu::UnicodeString &text, const icu::IDNAInfo &info, const UErrorCode &errCode)
{
	if (U_FAILURE(errCode) || info.hasErrors()) {
		return QString("");
	}
	return QString((QChar*) text.getBuffer(), text.length());
}

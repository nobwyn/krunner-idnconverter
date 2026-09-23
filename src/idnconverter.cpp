
#include "idnconverter.h"

IdnConverter::IdnConverter()
{
	const uint32_t idnaOpts = UIDNA_NONTRANSITIONAL_TO_ASCII | UIDNA_NONTRANSITIONAL_TO_UNICODE;
	UErrorCode errorCode = U_ZERO_ERROR;
	idnaConv.reset(icu::IDNA::createUTS46Instance(idnaOpts, errorCode));
}

QString IdnConverter::convertToAce(const QString &domainName) const
{
	if (!idnaConv) {
		return QString();
	}

	UErrorCode errCode = U_ZERO_ERROR;
	icu::IDNAInfo info;
	const icu::UnicodeString source(reinterpret_cast<const UChar *>(domainName.utf16()), domainName.length());
	icu::UnicodeString target;

	idnaConv->nameToASCII(source, target, info, errCode);

	return buildResult(target, info, errCode);
}

QString IdnConverter::convertToIdn(const QString &domainName) const
{
	if (!idnaConv) {
		return QString();
	}

	UErrorCode errCode = U_ZERO_ERROR;
	icu::IDNAInfo info;
	const icu::UnicodeString source(reinterpret_cast<const UChar *>(domainName.utf16()), domainName.length());
	icu::UnicodeString target;

	idnaConv->nameToUnicode(source, target, info, errCode);

	return buildResult(target, info, errCode);
}

QString IdnConverter::buildResult(const icu::UnicodeString &text, const icu::IDNAInfo &info, const UErrorCode &errCode)
{
	if (U_FAILURE(errCode) || info.hasErrors()) {
		return QString();
	}
	return QString::fromUtf16(reinterpret_cast<const char16_t *>(text.getBuffer()), text.length());
}

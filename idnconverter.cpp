
#include "idnconverter.h"

#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <stdio.h>
#include <stdlib.h>
#include <unicode/idna.h>
#include <unicode/unistr.h>
#include <QDebug>

IdnConverter::IdnConverter(QObject *parent, const QVariantList &args)
	: Plasma::AbstractRunner(parent, args)
{
	Q_UNUSED(args);
	
	// General runner configuration
	setObjectName(QLatin1String("IDN Converter"));
	setHasRunOptions(true);
	setIgnoredTypes(Plasma::RunnerContext::Directory |
					Plasma::RunnerContext::File |
					Plasma::RunnerContext::NetworkLocation);
	setSpeed(AbstractRunner::NormalSpeed);
	setPriority(HighestPriority);
	setDefaultSyntax(
		Plasma::RunnerSyntax(
			QString::fromLatin1("idn :q:"),
			i18n("Converts the :q: to IDN/ACE formats. Pressing ENTER copies selected entry to the clipboard.")
		)
	);
	
	const int32_t idnaOpts = UIDNA_NONTRANSITIONAL_TO_ASCII | UIDNA_NONTRANSITIONAL_TO_UNICODE;
	UErrorCode errorCode = U_ZERO_ERROR;
	idna = icu::IDNA::createUTS46Instance(idnaOpts, errorCode); 
}

IdnConverter::~IdnConverter()
{
}

/**
 */
void IdnConverter::match(Plasma::RunnerContext &context)
{
	if (!context.isValid()) {
		return;
	}

	const QString enteredKey = context.query();
	qDebug() << "Got query: [" << enteredKey << "]";
	
	QString domainName;
	if (enteredKey.startsWith("idn")) {
		domainName = enteredKey.mid(4);
	} else if (enteredKey.startsWith("xn--")) {
		domainName = enteredKey;
	} else {
		return;
	}
	
	qDebug() << "Got domain: [" << domainName << "]";
	
	UErrorCode error = U_ZERO_ERROR;
	icu::IDNAInfo info;
	icu::UnicodeString source(domainName.toUtf8().constData());
	icu::UnicodeString target;
	
	if (domainName.startsWith("xn--")) {
		idna->nameToUnicode(source, target, info, error);
	} else {
		idna->nameToASCII(source, target, info, error);
	}
	
	if (U_FAILURE(error) || info.hasErrors()) {
		qDebug() << "GOT ERROR!";
		return;
	}
	
	QString domainNameAce, domainNameIdn;
	if (domainName.startsWith("xn--")) {
		domainNameAce = domainName;
		domainNameIdn = QString((QChar*) target.getBuffer(), target.length());
	} else {
		domainNameAce = QString((QChar*) target.getBuffer(), target.length());
		domainNameIdn = domainName;
	}
	
	qDebug() << "Converted -> ACE[" << domainNameAce << "], IDN[" << domainNameIdn << "]";
	
	QList<Plasma::QueryMatch> matches;
	
	Plasma::QueryMatch match1(this);
	match1.setIcon(QIcon::fromTheme("klipper"));
	match1.setType(Plasma::QueryMatch::ExactMatch);
	match1.setText("ACE: " + domainNameAce);
	match1.setSubtext(domainNameAce);
	matches.append(match1);

	Plasma::QueryMatch match2(this);
	match2.setIcon(QIcon::fromTheme("klipper"));
	match2.setType(Plasma::QueryMatch::ExactMatch);
	match2.setText("IDN: " + domainNameIdn);
	match2.setSubtext(domainNameIdn);
	matches.append(match2);
	
	// Pass the framework the results
	context.addMatches(matches);
}

/**
 */
void IdnConverter::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
	Q_UNUSED(context);

	// copy the selection to clipboard
	QApplication::clipboard()->setText(match.subtext());
}

K_EXPORT_PLASMA_RUNNER(idnconverter, IdnConverter)

#include "idnconverter.moc"

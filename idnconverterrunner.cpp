
#include "idnconverterrunner.h"
#include "idnconverter.h"

#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <stdio.h>
#include <stdlib.h>
#include <unicode/idna.h>
#include <unicode/unistr.h>
#include <QDebug>

IdnConverterRunner::IdnConverterRunner(QObject *parent, const QVariantList &args)
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
	
	idnConv = new IdnConverter();
}

IdnConverterRunner::~IdnConverterRunner()
{
	delete idnConv;
}

/**
 */
void IdnConverterRunner::match(Plasma::RunnerContext &context)
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
	
	QList<Plasma::QueryMatch> matches;
	if (domainName.startsWith("xn--")) {
		matches.append(buildMatch("IDN", idnConv->convertToIdn(domainName)));
		matches.append(buildMatch("ACE", domainName));
	} else {
		matches.append(buildMatch("ACE", idnConv->convertToAce(domainName)));
		matches.append(buildMatch("IDN", domainName));
	}
	
	// Pass the framework the results
	context.addMatches(matches);
}

/**
 */
void IdnConverterRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
	Q_UNUSED(context);

	// copy the selection to clipboard
	QApplication::clipboard()->setText(match.subtext());
}

/**
 */
Plasma::QueryMatch IdnConverterRunner::buildMatch(const QString &prefix, const QString &domainName)
{
	Plasma::QueryMatch match(this);
	match.setIcon(QIcon::fromTheme("klipper"));
	match.setType(Plasma::QueryMatch::ExactMatch);
	match.setText(prefix + ": " + domainName);
	match.setSubtext(domainName);
	
	return match;
}

K_EXPORT_PLASMA_RUNNER(idnconverter, IdnConverterRunner)

#include "idnconverterrunner.moc"

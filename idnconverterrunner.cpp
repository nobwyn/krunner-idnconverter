
#include "idnconverterrunner.h"
#include "idnconverter.h"

#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
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
	
	// regexp for domain name detection
	domainNamePattern = QRegExp("\\w([\\w-]*\\w)?\\.\\w([\\w-]*\\w)?");
	
	// converter for 
	idnConv = new IdnConverter();
}

IdnConverterRunner::~IdnConverterRunner()
{
	delete idnConv;
}

void IdnConverterRunner::match(Plasma::RunnerContext &context)
{
	if (!context.isValid()) {
		return;
	}

	const QString keyword = context.query();
	qDebug() << "Got query: [" << keyword << "]";
	
	QList<Plasma::QueryMatch> matches;
	if (isAceDomain(keyword)) {
		qDebug() << "Matched ACE!";

		matches.append(buildMatch("IDN", idnConv->convertToIdn(keyword), 1.0));
		matches.append(buildMatch("ACE", keyword, 0.5));
		
	} else if (isIdnDomain(keyword)) {
		qDebug() << "Matched IDN!";

		matches.append(buildMatch("ACE", idnConv->convertToAce(keyword), 1.0));
		matches.append(buildMatch("IDN", keyword, 0.5));
		
	} else {
		return;
	}
	
	// Pass the framework the results
	context.addMatches(matches);
}

void IdnConverterRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
	Q_UNUSED(context);
	QApplication::clipboard()->setText(match.subtext());
}

bool IdnConverterRunner::isAceDomain(const QString &keyword)
{
	return keyword.startsWith("xn--", Qt::CaseSensitivity::CaseInsensitive);
}

bool IdnConverterRunner::isIdnDomain(const QString &keyword)
{
	return keyword.indexOf(domainNamePattern) != -1;
}

Plasma::QueryMatch IdnConverterRunner::buildMatch(const QString &prefix, const QString &domainName, const qreal relevance)
{
	Plasma::QueryMatch match(this);
	match.setIcon(QIcon::fromTheme("klipper"));
	match.setType(Plasma::QueryMatch::ExactMatch);
	match.setText(prefix + ": " + domainName);
	match.setSubtext(domainName);
	match.setRelevance(relevance);
	
	return match;
}

K_EXPORT_PLASMA_RUNNER(idnconverter, IdnConverterRunner)

#include "idnconverterrunner.moc"

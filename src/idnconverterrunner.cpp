
#include "idnconverterrunner.h"

#include <KLocalizedString>
#include <QClipboard>
#include <QGuiApplication>

K_PLUGIN_CLASS_WITH_JSON(IdnConverterRunner, "idnconverterrunner.json")

IdnConverterRunner::IdnConverterRunner(QObject *parent, const KPluginMetaData &metaData)
	: KRunner::AbstractRunner(parent, metaData)
	// regexp for domain name detection
	, domainNamePattern(QStringLiteral("\\w([\\w-]*\\w)?\\.\\w([\\w-]*\\w)?"), QRegularExpression::UseUnicodePropertiesOption)
{
	addSyntax(
		QStringLiteral("idn :q:"),
		i18n("Converts the :q: to IDN/ACE formats. Pressing ENTER copies selected entry to the clipboard.")
	);
	setMinLetterCount(3);
}

void IdnConverterRunner::match(KRunner::RunnerContext &context)
{
	const QString keyword = context.query();

	QList<KRunner::QueryMatch> matches;
	if (isAceDomain(keyword)) {
		const QString idn = idnConv.convertToIdn(keyword);
		if (idn.isEmpty()) {
			return;
		}
		matches.append(buildMatch(QStringLiteral("IDN"), idn, 1.0));
		matches.append(buildMatch(QStringLiteral("ACE"), keyword, 0.5));

	} else if (isIdnDomain(keyword)) {
		const QString ace = idnConv.convertToAce(keyword);
		if (ace.isEmpty()) {
			return;
		}
		matches.append(buildMatch(QStringLiteral("ACE"), ace, 1.0));
		matches.append(buildMatch(QStringLiteral("IDN"), keyword, 0.5));

	} else {
		return;
	}

	// Pass the framework the results
	context.addMatches(matches);
}

void IdnConverterRunner::run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &match)
{
	Q_UNUSED(context);
	QGuiApplication::clipboard()->setText(match.subtext());
}

bool IdnConverterRunner::isAceDomain(const QString &keyword) const
{
	return keyword.startsWith(QLatin1String("xn--"), Qt::CaseInsensitive);
}

bool IdnConverterRunner::isIdnDomain(const QString &keyword) const
{
	return domainNamePattern.match(keyword).hasMatch();
}

KRunner::QueryMatch IdnConverterRunner::buildMatch(const QString &prefix, const QString &domainName, const qreal relevance)
{
	KRunner::QueryMatch match(this);
	match.setIconName(QStringLiteral("klipper"));
	match.setCategoryRelevance(KRunner::QueryMatch::CategoryRelevance::Highest);
	match.setText(prefix + QLatin1String(": ") + domainName);
	match.setSubtext(domainName);
	match.setRelevance(relevance);

	return match;
}

#include "idnconverterrunner.moc"

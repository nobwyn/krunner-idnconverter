
#ifndef RUNNER_IDNCONVERTER_H
#define RUNNER_IDNCONVERTER_H

#include "idnconverter.h"
#include <KRunner/AbstractRunner>
#include <unicode/idna.h>

class IdnConverterRunner : public Plasma::AbstractRunner
{
	Q_OBJECT

public:
	IdnConverterRunner(QObject *parent, const QVariantList &args);
	~IdnConverterRunner();

	/**
	 * Checks whether given query looks like a domain name and builds
	 * matches with IDN/ACE domain names if it is so.
	 */
	void match(Plasma::RunnerContext &);
	
	/**
	 * Copies the domain name from selected match to the clipboard.
	 */
	void run(const Plasma::RunnerContext &, const Plasma::QueryMatch &);

private:
	
	/**
	 * Builds a match object with given prefix and domain name
	 * 
	 * @param prefix The prefix for displaying
	 * @param domainName The domain name to use for the match
	 * @param relevance The relevance for the created result
	 */
	Plasma::QueryMatch buildMatch(const QString &prefix, const QString &domainName, const qreal relevance);
	
	/**
	 * Returns whether given keyword looks like a domain name in IDN format.
	 */
	bool isIdnDomain(const QString &);
	
	/**
	 * Returns whether given keyword looks like a domain name in ACE format.
	 */
	bool isAceDomain(const QString &);
	
	/**
	 * The instance for conversions between IDN/ACE formats
	 */
	IdnConverter *idnConv;
	
	/**
	 * Pattern for IDN detection.
	 */
	QRegExp domainNamePattern;
	
};

#endif

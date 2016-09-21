
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

	void match(Plasma::RunnerContext &);
	void run(const Plasma::RunnerContext &, const Plasma::QueryMatch &);

private:
	IdnConverter *idnConv;
	Plasma::QueryMatch buildMatch(const QString &, const QString &);
	
};

#endif

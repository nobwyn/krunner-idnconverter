
#ifndef RUNNER_IDNCONV_H
#define RUNNER_IDNCONV_H

#include <KRunner/AbstractRunner>
#include <unicode/idna.h>

class IdnConverter : public Plasma::AbstractRunner
{
	Q_OBJECT

public:
	IdnConverter(QObject *parent, const QVariantList &args);
	~IdnConverter();

	void match(Plasma::RunnerContext &);
	void run(const Plasma::RunnerContext &, const Plasma::QueryMatch &);
   
private:
	icu::IDNA *idna;
	
};

#endif

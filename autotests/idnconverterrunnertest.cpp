
#include <KRunner/AbstractRunnerTest>

using namespace KRunner;

class IdnConverterRunnerTest : public AbstractRunnerTest
{
	Q_OBJECT

private Q_SLOTS:
	void initTestCase()
	{
		initProperties();
	}

	void testConversion_data()
	{
		QTest::addColumn<QString>("query");
		QTest::addColumn<QString>("expectedFirst");
		QTest::addColumn<QString>("expectedSecond");

		QTest::newRow("idn to ace") << QStringLiteral("šešiai.lt") << QStringLiteral("xn--eiai-f6ab.lt") << QStringLiteral("šešiai.lt");
		QTest::newRow("ace to idn") << QStringLiteral("xn--eiai-f6ab.lt") << QStringLiteral("šešiai.lt") << QStringLiteral("xn--eiai-f6ab.lt");
		QTest::newRow("ascii domain") << QStringLiteral("example.com") << QStringLiteral("example.com") << QStringLiteral("example.com");

		// German domains
		QTest::newRow("umlaut idn to ace") << QStringLiteral("münchen.de") << QStringLiteral("xn--mnchen-3ya.de") << QStringLiteral("münchen.de");
		QTest::newRow("umlaut ace to idn") << QStringLiteral("xn--kln-sna.de") << QStringLiteral("köln.de") << QStringLiteral("xn--kln-sna.de");
		// nontransitional processing keeps "ß" instead of mapping it to "ss"
		QTest::newRow("sharp s idn to ace") << QStringLiteral("straße.de") << QStringLiteral("xn--strae-oqa.de") << QStringLiteral("straße.de");
		QTest::newRow("sharp s ace to idn") << QStringLiteral("xn--strae-oqa.de") << QStringLiteral("straße.de") << QStringLiteral("xn--strae-oqa.de");
		QTest::newRow("umlaut and sharp s") << QStringLiteral("grüße.de") << QStringLiteral("xn--gre-6ka8l.de") << QStringLiteral("grüße.de");
		QTest::newRow("multiple idn labels") << QStringLiteral("bücher.fußball.de") << QStringLiteral("xn--bcher-kva.xn--fuball-cta.de") << QStringLiteral("bücher.fußball.de");
		QTest::newRow("uppercase umlaut") << QStringLiteral("MÜNCHEN.DE") << QStringLiteral("xn--mnchen-3ya.de") << QStringLiteral("MÜNCHEN.DE");
		QTest::newRow("capital sharp s") << QStringLiteral("STRAẞE.de") << QStringLiteral("xn--strae-oqa.de") << QStringLiteral("STRAẞE.de");
	}

	void testConversion()
	{
		QFETCH(QString, query);
		QFETCH(QString, expectedFirst);
		QFETCH(QString, expectedSecond);

		const QList<QueryMatch> matches = launchQuery(query);
		QCOMPARE(matches.count(), 2);
		QCOMPARE(matches.at(0).subtext(), expectedFirst);
		QCOMPARE(matches.at(1).subtext(), expectedSecond);
	}

	void testNoMatch_data()
	{
		QTest::addColumn<QString>("query");

		QTest::newRow("plain word") << QStringLiteral("hello");
		QTest::newRow("invalid ace") << QStringLiteral("xn--.lt");
	}

	void testNoMatch()
	{
		QFETCH(QString, query);

		QVERIFY(launchQuery(query).isEmpty());
	}
};

QTEST_MAIN(IdnConverterRunnerTest)

#include "idnconverterrunnertest.moc"

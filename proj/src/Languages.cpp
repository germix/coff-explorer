#include "Languages.h"
#include <QLocale>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QApplication>

#include <QDebug>

Languages::Languages()
{
}
Languages::~Languages()
{
}
void Languages::load(QString language)
{
	if(currentLanguage != language)
	{
		currentLanguage = language;

		QLocale locale = QLocale(language);
		QLocale::setDefault(locale);

		loadTranslator(&qtTranslator, QString("qt_%1.qm").arg(language));
		loadTranslator(&appTranslator, QString(baseName + "_%1.qm").arg(language));

	}
}
void Languages::init(QMenu* menu, QString basePath, QString baseName, QString initialLocale)
{
	this->baseName = baseName;
	// ...
	QActionGroup* langGroup = new QActionGroup(this);
	langGroup->setExclusive(true);

	connect(langGroup, SIGNAL(triggered(QAction*)), this, SLOT(actionTriggered(QAction*)));

	//
	// If there is no initial language, use the system language
	//
	if(initialLocale.isEmpty())
	{
		QString defaultLocale = QLocale::system().name();
		defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

		initialLocale = defaultLocale;
	}

	//
	// Get the folder where the languages ​​are
	//
	languagesPath = QApplication::applicationDirPath();
	if(!basePath.isEmpty() && (basePath.at(0) != '/' && basePath.at(0) != '\\'))
	{
		languagesPath += '/';
	}
	languagesPath.append(basePath);

	//
	// Get the list of language files
	//
	QDir dir(languagesPath);
	QStringList fileNames = dir.entryList(QStringList(baseName + "_*.qm"));

	//
	// List each one and create an action to add it to the menu
	//
	for(int i = 0; i < fileNames.size(); i++)
	{
		QString locale;

		locale = fileNames[i];
		locale.truncate(locale.lastIndexOf('.'));
		locale.remove(0, locale.indexOf('_') + 1);

		QString lang = QLocale::languageToString(QLocale(locale).language());
		QIcon ico(QString("%1/%2.png").arg(languagesPath).arg(locale));

		QAction* action = new QAction(ico, lang, this);
		action->setCheckable(true);
		action->setData(locale);

		menu->addAction(action);
		langGroup->addAction(action);

		if(initialLocale == locale)
		{
			action->setChecked(true);
		}
	}
	//
	// Load initial language
	//
	load(initialLocale);
}
void Languages::loadTranslator(QTranslator* t, const QString& fname)
{
	// Remove the old translator
	qApp->removeTranslator(t);

	// Load the new translator
	if(t->load(languagesPath + "/" + fname))
	{
		qApp->installTranslator(t);
	}
	else
	{
		qDebug() << QString("Can't load \"%1\" translator.").arg(fname);
	}

}
void Languages::actionTriggered(QAction* action)
{
	if(action != NULL)
	{
		load(action->data().toString());
	}
}


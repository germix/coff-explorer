#include "RecentFilesMenu.h"
#include <QFileInfo>

#define MAGIC (('R' << 24) | ('M' << 16) | ('N' << 8) | 'U')

RecentFilesMenu::RecentFilesMenu(const QString& _title, const QIcon& _clearIcon) : QMenu(_title)
{
	connect(this, SIGNAL(triggered(QAction*)), this, SLOT(slotActionTriggered(QAction*)));

	format = "%d: %s";
	maxFiles = 5;
	maxVisibles = 2;
	clearIcon = _clearIcon;
	rebuild();
}
RecentFilesMenu::RecentFilesMenu(int _maxFiles, int _maxVisibles, const QString& _title, const QIcon& _clearIcon) : QMenu(_title)
{
	connect(this, SIGNAL(triggered(QAction*)), this, SLOT(slotActionTriggered(QAction*)));

	format = "%d: %s";
	maxFiles = _maxFiles;
	maxVisibles = qMin(_maxFiles, _maxVisibles);
	clearIcon = _clearIcon;
	rebuild();
}
RecentFilesMenu::~RecentFilesMenu()
{
}
void RecentFilesMenu::addFile(const QString& fileName)
{
	files.removeAll(fileName);
	files.prepend(fileName);

	while(files.size() > maxFiles)
		files.removeLast();

	rebuild();
}
void RecentFilesMenu::removeFile(const QString& fileName)
{
	files.removeAll(fileName);
	rebuild();
}
QByteArray RecentFilesMenu::saveState() const
{
	uint32_t magic = MAGIC;
	uint32_t version = 0;
	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);

	stream << magic;
	stream << version;
	stream << files;

	return data;
}
bool RecentFilesMenu::restoreState(const QByteArray& state)
{
	uint32_t magic;
	uint32_t version;
	QDataStream stream(state);

	stream >> magic;
	stream >> version;
	if(magic != MAGIC && version != 1)
	{
		return false;
	}
	stream >> files;

	rebuild();

	return true;
}
void RecentFilesMenu::rebuild()
{
	int num = qMin(files.size(), maxVisibles);

	clear();

	setEnabled(num > 0);
	if(num > 0)
	{
		//
		// Agregar acciones para los archivos
		//
		for(int i = 0; i < num; i++)
		{
			QString strippedName = QFileInfo(files[i]).fileName();

			QString text = format;
			text.replace(QLatin1String("%d"), QString::number(i+1));
			text.replace(QLatin1String("%s"), strippedName);

			QAction* action = addAction(text);
			action->setData(files[i]);
		}
		//
		// Agregar acción para borrar menu
		//
		addSeparator();
		addAction(clearIcon, tr("Clear menu"), this, SLOT(slotClearMenu()));
	}
}
void RecentFilesMenu::rebuild(const QString& title)
{
	setTitle(title);
	rebuild();
}
void RecentFilesMenu::slotClearMenu()
{
	files.clear();
	rebuild();
}
void RecentFilesMenu::slotActionTriggered(QAction* action)
{
	if(action->data().isValid())
	{
#if 0
		QString fileName = action->data().toString();

		files.removeAll(fileName);
		emit onFileTriggered(fileName);
		delete action;
		rebuild();
#else
		emit onFileTriggered(action->data().toString());
#endif
	}
}


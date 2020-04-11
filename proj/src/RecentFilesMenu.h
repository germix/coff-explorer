#ifndef RECENTFILESMENU_H
#define RECENTFILESMENU_H
#include <QMenu>
#include <QStringList>

class RecentFilesMenu :public  QMenu
{
	Q_OBJECT
	QStringList files;
	QString format;
	int maxFiles;
	int maxVisibles;
	QIcon clearIcon;
public:
	RecentFilesMenu(const QString& title, const QIcon& clearIcon = QIcon());
	RecentFilesMenu(int maxFiles, int maxVisibles, const QString& title, const QIcon& clearIcon = QIcon());
	~RecentFilesMenu();
public:
	void addFile(const QString& fileName);
	void removeFile(const QString& fileName);
	QByteArray saveState() const;
	bool restoreState(const QByteArray& state);
	void rebuild();
	void rebuild(const QString& title);
signals:
	void onFileTriggered(const QString& fileName);
private slots:
	void slotClearMenu();
	void slotActionTriggered(QAction* action);
};

#endif // RECENTFILESMENU_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Languages.h"

namespace Ui {
class MainWindow;
}


class QSplitter;
class QTreeView;
class QTextEdit;

class TreeModel;
class SymbolTableModel;
class StringTableModel;
class RelocationsModel;

class RecentFilesMenu;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	Ui::MainWindow*		ui;
	TreeModel*			model;
	QTreeView*			treeView;
	QTextEdit*			textView;
	QWidget*			emptyWidget;

	QSplitter*			splitter;
	QString				lastDirectory;
	QString				currentFileName;

	QTreeView*			symbolTableView;
	SymbolTableModel*	symbolTableModel;

	QTreeView*			stringTableView;
	StringTableModel*	stringTableModel;

	//
	// Section widget
	//
	QTabWidget*			sectionWidget;
	QTextEdit*			sectionHeaderView;
	QTreeView*			sectionRelocationsView;
	RelocationsModel*	sectionRelocationsModel;

	Languages			languages;

	RecentFilesMenu*	recentFiles;
public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();
private:
	void openFile(QString fileName);
	void setCurrentWidget(QWidget* widget);
	void initRecentFilesMenu(const QByteArray& state);
private:
	void changeEvent(QEvent* e);
	void dropEvent(QDropEvent* e);
	void dragEnterEvent(QDragEnterEvent* e);
private slots:
	void slotAction();
	void slotTreeView_doubleClicked(const QModelIndex& index);
	void slotRecentFiles_fileTriggered(const QString& fileName);
};

#endif // MAINWINDOW_H

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QSplitter>
#include <QTreeView>
#include <QTextEdit>
#include <QListWidget>
#include <QSettings>

#include "AboutDialog.h"
#include "TreeItem.h"
#include "TreeModel.h"
#include "TreeItemFileHeader.h"
#include "TreeItemFolder.h"
#include "TreeItemRoot.h"
#include "TreeItemSection.h"
#include "TreeItemStringTable.h"
#include "TreeItemSymbolTable.h"
#include "StringTableModel.h"
#include "SymbolTableModel.h"
#include "RecentFilesMenu.h"

#define SETTINGS_APPLICATION "CoffExplorer"
#define SETTINGS_ORGANIZATION "Germix"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->menu_View->addAction(ui->mainToolBar->toggleViewAction());

	model = new TreeModel();
	treeView = new QTreeView();
	treeView->setModel(model);
	treeView->setHeaderHidden(true);
	connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotTreeView_doubleClicked(QModelIndex)));

	textView = new QTextEdit();
	textView->setReadOnly(true);
	textView->setFont(QFont("Courier New", 14));

	stringTableView = new QTreeView();
	stringTableView->setRootIsDecorated(false);
	stringTableView->setModel(stringTableModel = new StringTableModel());

	symbolTableView = new QTreeView();
	symbolTableView->setRootIsDecorated(false);
	symbolTableView->setModel(symbolTableModel = new SymbolTableModel());

	emptyWidget = new QWidget();

	splitter = new QSplitter();
	splitter->addWidget(treeView);
	splitter->addWidget(emptyWidget);
	setCentralWidget(splitter);

	//
	// Load settings
	//
	QString fileToOpen;
	{
		QSettings s(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

		lastDirectory = s.value("LastDirectory", "").toString();
		restoreGeometry(s.value("MainGeometry").toByteArray());
		restoreState(s.value("MainState").toByteArray());
		splitter->restoreGeometry(s.value("SplitterGeometry").toByteArray());
		splitter->restoreState(s.value("SplitterState").toByteArray());

		fileToOpen = s.value("FileToOpenAtStartup").toString();
		ui->actionOptionsOpenLastestFileAtStartup->setChecked(s.value("OpenLastestFileAtStartup", false).toBool());

		symbolTableView->header()->restoreState(s.value("TreeViewSymbolTable").toByteArray());
		stringTableView->header()->restoreState(s.value("TreeViewStringTable").toByteArray());

		languages.init(ui->menu_Languages, "translations", "coffexplorer", s.value("Language").toString());

		initRecentFilesMenu(s.value("RecentFiles").toByteArray());
	}

	//
	// Open lastest file
	//
	if(!fileToOpen.isEmpty() && ui->actionOptionsOpenLastestFileAtStartup->isChecked())
	{
		openFile(fileToOpen);
	}
}

MainWindow::~MainWindow()
{
	//
	// Save settings
	//
	{
		QSettings s(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

		s.setValue("Language", languages.language());
		s.setValue("LastDirectory", lastDirectory);
		s.setValue("MainGeometry", saveGeometry());
		s.setValue("MainState", saveState());
		s.setValue("SplitterGeometry", splitter->saveGeometry());
		s.setValue("SplitterState", splitter->saveState());
		s.setValue("FileToOpenAtStartup", currentFileName);
		s.setValue("OpenLastestFileAtStartup", ui->actionOptionsOpenLastestFileAtStartup->isChecked());

		s.setValue("TreeViewSymbolTable", symbolTableView->header()->saveState());
		s.setValue("TreeViewStringTable", stringTableView->header()->saveState());
	}

	delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
	if(e != NULL)
	{
		switch(e->type())
		{
#if 1
			case QEvent::LocaleChange:
				{
					QString locale = QLocale::system().name();
					locale.truncate(locale.lastIndexOf('_'));
					languages.load(locale);
				}
				break;
#endif
			case QEvent::LanguageChange:
				ui->retranslateUi(this);
				recentFiles->rebuild(tr("Recent files"));
				break;
			default:
				break;
		}
	}
	QMainWindow::changeEvent(e);
}

void MainWindow::dropEvent(QDropEvent* e)
{
	QString s;
	const QList<QUrl> urls = e->mimeData()->urls();

	for(int i = 0; i < urls.size(); i++)
	{
		s = urls.at(i).toLocalFile();
		if(!s.isEmpty())
		{
			openFile(s);
		}
	}
	// ...
	e->acceptProposedAction();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
	if(e->mimeData()->hasFormat("text/uri-list"))
	{
		e->acceptProposedAction();
	}
}

void MainWindow::openFile(QString fileName)
{
	if(!currentFileName.isEmpty())
	{
		recentFiles->addFile(currentFileName);
	}
	currentFileName = QString();
	stringTableModel->setStringTable(nullptr);
	symbolTableModel->setSymbolTable(nullptr);
	ui->actionFileReload->setEnabled(false);

	if(model->loadFile(fileName))
	{
		currentFileName = fileName;
		recentFiles->removeFile(currentFileName);
		lastDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
		ui->actionFileReload->setEnabled(true);

		for(int i = 0; i < model->root->children[0]->children.size(); i++)
		{
			if(dynamic_cast<TreeItemStringTable*>(model->root->children[0]->children[i]))
			{
				stringTableModel->setStringTable((TreeItemStringTable*)model->root->children[0]->children[i]);
			}
			else if(dynamic_cast<TreeItemSymbolTable*>(model->root->children[0]->children[i]))
			{
				symbolTableModel->setSymbolTable((TreeItemSymbolTable*)model->root->children[0]->children[i]);
			}
		}
	}
}

void MainWindow::setCurrentWidget(QWidget* widget)
{
	if(splitter->widget(1) != widget)
	{
		splitter->replaceWidget(1, widget);
	}
}

void MainWindow::initRecentFilesMenu(const QByteArray& state)
{
	recentFiles = new RecentFilesMenu(20, 10, tr("Recent files"), QIcon(":/images/action-clear.png"));

	ui->menu_File->insertMenu(ui->actionFileExit, recentFiles);
	ui->menu_File->insertSeparator(ui->actionFileExit);

	connect(recentFiles, SIGNAL(onFileTriggered(QString)), this, SLOT(slotRecentFiles_fileTriggered(QString)));

	recentFiles->restoreState(state);
}

void MainWindow::slotAction()
{
	QAction* action = qobject_cast<QAction*>(sender());

	if(action == ui->actionFileOpen)
	{
		QString filters = tr("Object files (*.obj;*o)");
		QString fileName = QFileDialog::getOpenFileName(
						this,
						tr("Load object file"),
						lastDirectory,
						filters + ";;");
		if(!fileName.isNull())
		{
			openFile(fileName);
		}
	}
	else if(action == ui->actionFileReload)
	{
		openFile(currentFileName);
	}
	else if(action == ui->actionFileExit)
	{
		close();
	}
	else if(action == ui->actionHelpAbout)
	{
		AboutDialog().exec();
	}
	else if(action == ui->actionOptionsOpenLastestFileAtStartup)
	{
	}
}

void MainWindow::slotTreeView_doubleClicked(const QModelIndex& index)
{
	TreeItem* item = model->toItem(index);
	if(!item)
		return;
	TreeItemFileHeader* fileHeaderItem = dynamic_cast<TreeItemFileHeader*>(item);
	TreeItemSection* sectionItem = dynamic_cast<TreeItemSection*>(item);
	TreeItemSymbolTable* symbolTableItem = dynamic_cast<TreeItemSymbolTable*>(item);
	TreeItemStringTable* stringTableItem = dynamic_cast<TreeItemStringTable*>(item);

	if(fileHeaderItem != nullptr)
	{
		QString s;

		s += QString().sprintf("Machine: 0x%04X\n", fileHeaderItem->header.Machine);
		s += QString().sprintf("NumberOfSections: %d\n", fileHeaderItem->header.NumberOfSections);
		s += QString().sprintf("TimeDateStamp: %d\n", fileHeaderItem->header.TimeDateStamp);
		s += QString().sprintf("PointerToSymbolTable: %d\n", fileHeaderItem->header.PointerToSymbolTable);
		s += QString().sprintf("NumberOfSymbols: %d\n", fileHeaderItem->header.NumberOfSymbols);
		s += QString().sprintf("SizeOfOptionalHeader: %d\n", fileHeaderItem->header.SizeOfOptionalHeader);
		s += QString().sprintf("Characteristics: 0x%04X\n", fileHeaderItem->header.Characteristics);

		textView->setText(s);
		setCurrentWidget(textView);
	}
	else if(sectionItem != nullptr)
	{
		QString s;

		s += QString().sprintf("Name: %ls\n", (const wchar_t*)sectionItem->name.constData());
		s += QString().sprintf("VirtualSize: 0x%08X\n", sectionItem->header.VirtualSize);
		s += QString().sprintf("VirtualAddress: 0x%08X\n", sectionItem->header.VirtualAddress);
		s += QString().sprintf("SizeOfRawData: %d\n", sectionItem->header.SizeOfRawData);
		s += QString().sprintf("PointerToRawData: %d\n", sectionItem->header.PointerToRawData);
		s += QString().sprintf("PointerToRelocations: %d\n", sectionItem->header.PointerToRelocations);
		s += QString().sprintf("PointerToLinenumbers: %d\n", sectionItem->header.PointerToLinenumbers);
		s += QString().sprintf("NumberOfRelocations: %d\n", sectionItem->header.NumberOfRelocations);
		s += QString().sprintf("NumberOfLinenumbers: %d\n", sectionItem->header.NumberOfLinenumbers);
		s += QString().sprintf("Characteristics: 0x%08X\n", sectionItem->header.Characteristics);

		textView->setText(s);
		setCurrentWidget(textView);
	}
	else if(symbolTableItem != nullptr)
	{
		setCurrentWidget(symbolTableView);
	}
	else if(stringTableItem != nullptr)
	{
		setCurrentWidget(stringTableView);
	}
}

void MainWindow::slotRecentFiles_fileTriggered(const QString& fileName)
{
	openFile(fileName);
}

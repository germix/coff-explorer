#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QFile>

class TreeItem;
class TreeItemFolder;
class QFile;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	TreeItem* root;
	QFile file;
	TreeItemFolder* sectionFolder;
public:
	explicit TreeModel(QObject* parent = nullptr);
	~TreeModel();
public:
	QModelIndex index(int row, int column,
					  const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& child) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public:
	void clear();
	bool loadFile(const QString& fileName);
public:
	TreeItem* toItem(const QModelIndex& index) const;
	QModelIndex toIndex(TreeItem* item, int column = 0) const;
};

#endif // TREEMODEL_H

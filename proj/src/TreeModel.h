#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>

class TreeItem;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	TreeItem* root;
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

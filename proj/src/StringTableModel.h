#ifndef STRINGTABLEMODEL_H
#define STRINGTABLEMODEL_H
#include <QAbstractItemModel>

class TreeItemStringTable;

class StringTableModel : public QAbstractItemModel
{
	Q_OBJECT
	TreeItemStringTable* root;
public:
	explicit StringTableModel(QObject* parent = nullptr);
	~StringTableModel();
public:
	void setStringTable(TreeItemStringTable* st);

public:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	QModelIndex index(int row, int column,
					  const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& child) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
};

#endif // STRINGTABLEMODEL_H

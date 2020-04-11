#ifndef SYMBOLTABLEMODEL_H
#define SYMBOLTABLEMODEL_H
#include <QAbstractItemModel>

class TreeItemSymbolTable;

class SymbolTableModel : public QAbstractItemModel
{
	Q_OBJECT
	TreeItemSymbolTable* root;
public:
	explicit SymbolTableModel(QObject* parent = nullptr);
	~SymbolTableModel();
public:
	void setSymbolTable(TreeItemSymbolTable* st);

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

#endif // SYMBOLTABLEMODEL_H

#ifndef RELOCATIONSMODEL_H
#define RELOCATIONSMODEL_H
#include <QAbstractItemModel>
#include "coff.h"

class RelocationsModel : public QAbstractItemModel
{
	Q_OBJECT
	QVector<IMAGE_RELOCATION>		relocations;
	const struct REL_TABLE_LOOKUP*	relocationTypesLookup;
public:
	explicit RelocationsModel(QObject* parent = nullptr);
	~RelocationsModel();
public:
	void clear();
	void setRelocation(const QVector<IMAGE_RELOCATION>& rel, uint16_t machine);

private:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	QModelIndex index(int row, int column,
					  const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& child) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
};

#endif // RELOCATIONSMODEL_H

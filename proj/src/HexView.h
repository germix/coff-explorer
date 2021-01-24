#ifndef HEXVIEW_H
#define HEXVIEW_H
#include <QAbstractScrollArea>

class HexView : public QAbstractScrollArea
{
	QIODevice* io;
	QFont font;
	qint64 dataOffset;
	qint64 dataSize;
	qint64 linesCount;
public:
	HexView();
	~HexView();
public:
	void setData(QIODevice* io, qint64 dataOffset, qint64 dataSize);
private:
	void setup(bool reset = false);
public:
	void paintEvent(QPaintEvent* e);
	void resizeEvent(QResizeEvent* e);
};

#endif // HEXVIEW_H

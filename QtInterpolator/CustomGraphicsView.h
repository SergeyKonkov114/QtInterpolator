#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include <vector>

class CustomGraphicsView : public QGraphicsView {
	Q_OBJECT;
public:
	explicit CustomGraphicsView(QWidget* parent = 0);
	void setData(const std::vector<double>& d);
	void startPainting();

public slots:
	void clearScene();
private slots:
	void redrawView();

private:
	void resizeEvent(QResizeEvent* event);
	void deleteItemsFromGroup(QGraphicsItemGroup* group);

private:
	QGraphicsScene* scene;
	QGraphicsItemGroup* group;
	QTimer* timer;
	std::vector<double> data;
};
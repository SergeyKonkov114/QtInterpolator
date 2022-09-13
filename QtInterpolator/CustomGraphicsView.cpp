#include "CustomGraphicsView.h"
#include <QGraphicsItemGroup>

#include <algorithm>

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
	: QGraphicsView(parent)
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene();
	this->setScene(scene);

	group = new QGraphicsItemGroup();
	scene->addItem(group);

	timer = new QTimer();
	timer->setSingleShot(true);

	connect(timer, &QTimer::timeout, this, &CustomGraphicsView::redrawView);
	timer->start(50);
}

void CustomGraphicsView::redrawView() {
	if (data.empty()) { return; }

	this->deleteItemsFromGroup(group);
	int width = this->width();
	int height = this->height();

	scene->setSceneRect(0, 0, width, height);

	QPen penRed(Qt::red);
	auto max_it = std::max_element(data.begin(), data.end());
	int x_cur = 0, step_x = 1;
	for (int i = 0; i < static_cast<int>(data.size()) - 1; ++i) {
		group->addToGroup(scene->addLine(x_cur, *max_it - data[i], x_cur + step_x, *max_it - data[i + 1], penRed));
		x_cur += step_x;
	}
}

void CustomGraphicsView::resizeEvent(QResizeEvent* event) {
	timer->start(50);
	QGraphicsView::resizeEvent(event);
}

void CustomGraphicsView::deleteItemsFromGroup(QGraphicsItemGroup* group) {
	for each (QGraphicsItem* item in scene->items(group->boundingRect()))
	{
		if (item->group() == group) {
			delete item;
		}
	}
}

void CustomGraphicsView::setData(const std::vector<double>& d) {
	data = d;
}

void CustomGraphicsView::startPainting() {
	timer->start();
}

void CustomGraphicsView::clearScene() {
	deleteItemsFromGroup(group);
}
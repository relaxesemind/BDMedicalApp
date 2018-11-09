#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QGraphicsView>
#include <memory>

class ImageEditor : public QGraphicsView
{
    using PXitem = QGraphicsPixmapItem;
    using pItem = std::unique_ptr<PXitem>;
public:
    ImageEditor();

//protected:
//  void mouseMoveEvent(QMouseEvent *event)override;
//  void mousePressEvent(QMouseEvent *event)override;
//  void mouseReleaseEvent(QMouseEvent *event)override;
//  void drawBackground(QPainter *painter, const QRectF &rect)override;
//  void keyPressEvent(QKeyEvent *event)override;
//  void wheelEvent(QWheelEvent *event)override;

};

#endif // IMAGEEDITOR_H

#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Common/consts.h"
#include "Common/magic.h"
#include "Common/Models/models.h"

#include <QGraphicsView>
#include <memory>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include <QPointF>
#include <QLineF>
#include <QColor>
#include <QWheelEvent>
#include <QStylePainter>
#include <QStack>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPen>
#include <QMouseEvent>


enum DrawTool : int {
    Pencil = 0, Rect = 1, Line = 2
};


class ImageEditor : public QGraphicsView
{
    Q_OBJECT

    using PXitem = QGraphicsPixmapItem;
    using pItem = std::unique_ptr<PXitem>;
public:
    explicit ImageEditor(QWidget* widget = nullptr);
    ~ImageEditor()override;

public:
    QString colorName;
    QColor color;
    qreal thickness;
    int currentImageID;
    QStack<QLineF> lines_stack;
    QStack<RectModel> rect_stack;
    QStack<LineModel> modelsLine_stack;
    bool isActive();
    bool getActivity();
    void setTool(const DrawTool &value);

public slots:
    void setImage(const QPixmap& pixmap);
    void setActivity(bool value);
    void clearEditor();

signals:
    void imageDidZoomed(qreal);

protected:
    void wheelEvent(QWheelEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
//  void drawBackground(QPainter *painter, const QRectF &rect)override;
//  void keyPressEvent(QKeyEvent *event)override;
private:
    QPoint transformCoordinates(QPoint)const;

private:
    QGraphicsScene scene;
    pItem currentImageItem;
    QPixmap drawPix;
    qreal currentZoom;
    bool drawFlag;
    DrawTool tool;
    bool activity;
    QPoint previousPoint;
    QStack<QGraphicsLineItem *> linesItems_stack_by_pencil;
    QStack<QGraphicsLineItem *> linesItems_stack_by_line;
    QGraphicsLineItem *tempLineForVisual;
    QGraphicsRectItem *tempRectForVisual;
};

#endif // IMAGEEDITOR_H

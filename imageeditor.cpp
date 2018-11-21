#include "imageeditor.h"

ImageEditor::ImageEditor(QWidget* widget) : QGraphicsView (widget)
{
    setScene(&scene);
    tool = DrawTool::Pencil;
    drawFlag = false;
    drawPix.load(":/res/draw_cur.png");
    activity = true;
    tempLineForVisual = nullptr;
    tempRectForVisual = nullptr;
    setCursor(QCursor(drawPix,0,drawPix.height()));
}

ImageEditor::~ImageEditor()
{

}

bool ImageEditor::isActive()
{
    return scene.items().count() > 0;
}

void ImageEditor::setImage(const QPixmap &pixmap)
{
    currentImageItem = std::make_unique<ImageEditor::PXitem>(pixmap);
    scene.addItem(currentImageItem.get());
    ImageEditor::centerOn(currentImageItem.get());
    ImageEditor::fitInView(currentImageItem.get(),Qt::KeepAspectRatio);
    currentZoom = 1.0;
    update();
}

void ImageEditor::wheelEvent(QWheelEvent *event)
{
    if (scene.items().isEmpty()){
        return;
    }
    QPoint degrees = event->angleDelta() / 8;
    if (degrees.y() > 0)
    {
        scale(EditorConsts::zoomMultiplier,EditorConsts::zoomMultiplier);
        currentZoom *= EditorConsts::zoomMultiplier;
    }
    else
    {
        scale(1/EditorConsts::zoomMultiplier,1/EditorConsts::zoomMultiplier);
        currentZoom /= EditorConsts::zoomMultiplier;
    }
    emit imageDidZoomed(currentZoom * 100);
}

void ImageEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (drawFlag == false || scene.items().isEmpty())
    {
        return;
    }

    QPoint point = transformCoordinates(event->pos());

    switch (tool) {
    case DrawTool::Pencil:
    {
        QLineF line(previousPoint.x(),previousPoint.y(),point.x(),point.y());
        QGraphicsLineItem *lineItem = scene.addLine(line,QPen(QBrush(color),thickness,Qt::SolidLine,Qt::RoundCap));
        linesItems_stack_by_pencil.push(lineItem);
        lines_stack.push(line);
        previousPoint = point;
        break;
    }
    case DrawTool::Line:
    {
        if (tempLineForVisual)
        {
            scene.removeItem(tempLineForVisual);
        }
        QLineF line(previousPoint.x(),previousPoint.y(),point.x(),point.y());
        tempLineForVisual = scene.addLine(line,QPen(QBrush(color),thickness,Qt::SolidLine,Qt::RoundCap));
        break;
    }
    case DrawTool::Rect:
    {
        if (tempRectForVisual)
        {
            scene.removeItem(tempRectForVisual);
        }
        QRectF rectf;
        rectf.setBottomLeft(QPointF(previousPoint.x(),previousPoint.y()));
        rectf.setTopRight(QPointF(point.x(),point.y()));
        tempRectForVisual = scene.addRect(rectf,QPen(QBrush(color),thickness,Qt::SolidLine,Qt::RoundCap));
//        RectModel rectModel;
//        rectModel.imageID = currentImageID;
//        rectModel.color = colorName;
//        rectModel.thickness = cast(int,thickness);
//        rectModel.point_x1 = cast(int,rectf.bottomLeft().x());
//        rectModel.point_y1 = cast(int,rectf.bottomLeft().y());
//        rectModel.point_x2 = cast(int,rectf.topRight().x());
//        rectModel.point_y2 = cast(int, rectf.topRight().y());
//        rect_stack.push(rectModel);

        break;
    }
  }
}

void ImageEditor::mousePressEvent(QMouseEvent *event)
{
    if (!getActivity())
    {
        return;
    }
    drawFlag = true;
    previousPoint = transformCoordinates(event->pos());
    lines_stack.clear();
}

void ImageEditor::mouseReleaseEvent(QMouseEvent *event)
{
    drawFlag = false;
}

QPoint ImageEditor::transformCoordinates(QPoint pos) const
{
    QPointF l = mapToScene(pos.x(),pos.y());
    return QPoint(cast(qint32,l.x()),cast(qint32,l.y()));
}

void ImageEditor::setTool(const DrawTool &value)
{
    tool = value;
}

bool ImageEditor::getActivity()
{
    return activity && isActive();
}

void ImageEditor::setActivity(bool value)
{
    activity = value;
}

void ImageEditor::clearEditor()
{
    currentImageItem = nullptr;
    scene.clear();
}











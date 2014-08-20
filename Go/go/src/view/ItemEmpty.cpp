#include "ItemEmpty.h"
#include "DefinationEditorSelectionType.h"

ItemEmpty::ItemEmpty(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_EMPTY);
}

bool ItemEmpty::isSelectable(float x, float y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return false;
}

bool ItemEmpty::isSelectable(float x, float y, float width, float height)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(width);
    Q_UNUSED(height);
    return false;
}

QRectF ItemEmpty::boundingRect() const
{
    return QRectF(0.0f, 0.0f, 1.0f, 1.0f);
}

void ItemEmpty::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->drawPoint(0, 0);
}

void ItemEmpty::save(QDomDocument &document, QDomElement &root)
{
    Q_UNUSED(document);
    Q_UNUSED(root);
}

bool ItemEmpty::tryOpen(QDomElement &root)
{
    Q_UNUSED(root);
    return true;
}

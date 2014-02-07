#include "ItemDrawable.h"
#include "DefinationEditorSelectionType.h"

ItemDrawable::ItemDrawable(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_NULL);
    this->_color = QColor(Qt::black);
}

ItemDrawable::~ItemDrawable()
{
}

bool ItemDrawable::isSelectable(float x, float y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return true;
}

bool ItemDrawable::isSelectable(float x, float y, float width, float height)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(width);
    Q_UNUSED(height);
    return true;
}

bool ItemDrawable::moveable() const
{
    return false;
}

void ItemDrawable::setColor(QColor color)
{
    this->_color = color;
    this->update();
}

void ItemDrawable::save(QDomDocument &document, QDomElement &root)
{
    Q_UNUSED(document);
    Q_UNUSED(root);
}

bool ItemDrawable::tryOpen(QDomElement &root)
{
    Q_UNUSED(root);
    return true;
}

#include "itemdrawable.h"
#include "definationeditorselectiontype.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemDrawable::ItemDrawable(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_NULL);
    this->_color = QColor(Qt::black);
}

/**
 * Destructor.
 */
ItemDrawable::~ItemDrawable()
{
}

/**
 * Whether the item is selected with the given position.
 * @param x X position.
 * @param y Y position.
 * @return Returns true if the item is selected, otherwise false.
 */
bool ItemDrawable::isSelectable(float x, float y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return true;
}

/**
 * Whether the item is selected with the given area.
 * @param x X position.
 * @param y Y position.
 * @param width Width.
 * @param height Height.
 * @return Returns true if the item is selected, otherwise false.
 */
bool ItemDrawable::isSelectable(float x, float y, float width, float height)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(width);
    Q_UNUSED(height);
    return true;
}

/**
 * Whether the item is movable.
 * @return Returns true is the item is moveable, otherwise false.
 */
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

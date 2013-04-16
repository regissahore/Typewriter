#include <QFontMetricsF>
#include "itemgotext.h"
#include "definationeditorselectiontype.h"

ItemGOText::ItemGOText(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT);
}

QString ItemGOText::text() const
{
    return this->_text;
}

void ItemGOText::setText(const QString text)
{
    this->_text = text;
    this->prepareGeometryChange();
}

bool ItemGOText::isSelected(float x, float y)
{
    QFont font;
    QFontMetricsF metrics(font);
    qreal width = metrics.width(this->text());
    qreal height = metrics.height();
    return x >= this->pos().x() &&
            x <= this->pos().x() + width &&
            y >= this->pos().y() &&
            y <= this->pos().y() + height;
}

bool ItemGOText::isSelected(float x, float y, float w, float h)
{
    float left, right, top, bottom;
    if (w >= 0)
    {
        left = x;
        right = x + w;
    }
    else
    {
        left = x + w;
        right = x;
    }
    if (h >= 0)
    {
        top = y;
        bottom = y + h;
    }
    else
    {
        top = y + h;
        bottom = y;
    }
    QFont font;
    QFontMetricsF metrics(font);
    qreal width = metrics.width(this->text());
    qreal height = metrics.height();
    return left <= this->pos().x() &&
            right >= this->pos().x() + width &&
            top <= this->pos().y() &&
            bottom >= this->pos().y() + height;
}

QRectF ItemGOText::boundingRect() const
{
    QFont font;
    font.setPixelSize(26);
    QFontMetricsF metrics(font);
    qreal width = metrics.width(this->text());
    qreal height = metrics.height();
    return QRectF(0, 0, width, height);
}

void ItemGOText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::black);
    painter->setPen(Qt::SolidLine);
    painter->setBrush(Qt::black);
    QFont font;
    font.setPixelSize(26);
    painter->setFont(font);
    painter->drawText(0, 0, 1000, 1000, Qt::AlignLeft | Qt::AlignTop, this->text());
}

void ItemGOText::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("text");
    element.setAttribute("x", this->pos().x());
    element.setAttribute("y", this->pos().y());
    element.setAttribute("value", this->text());
    root.appendChild(element);
}

bool ItemGOText::tryOpen(QDomElement &root)
{
    if (root.tagName() != "text")
    {
        return false;
    }
    this->setX(root.attribute("x").toFloat());
    this->setY(root.attribute("y").toFloat());
    this->setText(root.attribute("value", QObject::tr("Text")));
    return true;
}

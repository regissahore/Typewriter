#include <QFontMetricsF>
#include "ItemGoText.h"
#include "DefinationEditorSelectionType.h"

ItemGoText::ItemGoText(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_Go_TEXT);
}

QString ItemGoText::text() const
{
    return this->_text;
}

void ItemGoText::setText(const QString text)
{
    this->_text = text;
    this->prepareGeometryChange();
}

bool ItemGoText::isSelectable(float x, float y)
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

bool ItemGoText::isSelectable(float x, float y, float w, float h)
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

QRectF ItemGoText::boundingRect() const
{
    QFont font;
    font.setPixelSize(26);
    QFontMetricsF metrics(font);
    qreal width = metrics.width(this->text());
    qreal height = metrics.height();
    return QRectF(0, 0, width, height);
}

void ItemGoText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::black);
    painter->setPen(Qt::SolidLine);
    painter->setBrush(Qt::black);
    QFont font;
    font.setPixelSize(26);
    painter->setFont(font);
    painter->drawText(0, 0, 1000, 1000, Qt::AlignLeft | Qt::AlignTop, this->text());
}

ItemGoText* ItemGoText::copy() const
{
    ItemGoText *text = new ItemGoText();
    text->_text = this->_text;
    text->setX(this->x() + 100);
    text->setY(this->y() + 100);
    return text;
}

void ItemGoText::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("text");
    element.setAttribute("x", this->pos().x());
    element.setAttribute("y", this->pos().y());
    element.setAttribute("value", this->text());
    root.appendChild(element);
}

bool ItemGoText::tryOpen(QDomElement &root)
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

#include "tablewidgetgoitem.h"

TableWidgetGOItem::TableWidgetGOItem(const QString &text) : QTableWidgetItem(text)
{
}

TableWidgetGOItem::GOParameterType TableWidgetGOItem::parameterType() const
{
    return this->_parameterType;
}

void TableWidgetGOItem::setParameterType(GOParameterType type)
{
    this->_parameterType = type;
}

#include "messageeditorselection.h"
#include "gooperator.h"

/**
 * Constructor.
 */
MessageEditorSelection::MessageEditorSelection() : Message(), TypedItem()
{
    this->setName("Editor_Selection");
}

/**
 * Output the selection to string.
 * @return The selected string.
 */
QString MessageEditorSelection::toString()
{
    QString str = QObject::tr("Type: ");
    switch (this->type())
    {
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
        str += QObject::tr("GO operator. ");
        if (this->message())
        {
            str += QString(QObject::tr("Operator Type: %1 ID: %2")).
                    arg(((ItemGOOperator*)this->message())->model()->type()).
                    arg(((ItemGOOperator*)this->message())->model()->id());
        }
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
        str += QObject::tr("GO signal. ");
        break;
    default:
        return QObject::tr("Undefined selection. ");
    }
    return str;
}

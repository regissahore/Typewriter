#include "EditorGoMarkov.h"
#include "ViewGoMarkov.h"
#include "MessageFactory.h"
#include "DefinationToolType.h"

EditorGoMarkov::EditorGoMarkov(QWidget *parent) : EditorGo(parent)
{
    delete this->_view;
    this->_view = new ViewGoMarkov(this);
    this->layout()->addWidget(this->_view);
    this->_filter = tr("Go Markov Files(*.gom)");
    this->_suffix = "gom";
}

void EditorGoMarkov::activate()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_Go_MARKOV_POINTER_EXTEND;
    this->sendMessage(message);
}

#include "editorgomarkov.h"
#include "viewgomarkov.h"
#include "messagefactory.h"
#include "definationtooltype.h"

EditorGOMarkov::EditorGOMarkov(QWidget *parent) : EditorGO(parent)
{
    delete this->_view;
    this->_view = new ViewGOMarkov(this);
    this->layout()->addWidget(this->_view);
    this->_filter = tr("GO Markov Files(*.gom)");
    this->_suffix = "gom";
}

void EditorGOMarkov::activate()
{
    Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
    this->sendMessage(message);
}

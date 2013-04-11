#include "gomarkovequivalentparallel.h"
#include "gomarkovstatus.h"
#include "gomarkovoperator.h"

GOMarkovEquivalentParallel::GOMarkovEquivalentParallel() : GOMarkovEquivalent()
{
}

GOMarkovStatus GOMarkovEquivalentParallel::getEquivalentStatus()
{
    GOMarkovStatus status;
    return status;
}

void GOMarkovEquivalentParallel::save(QDomDocument &document, QDomElement &root)
{
    QDomElement equivalentRoot = document.createElement("parallel");
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->id());
        equivalentRoot.appendChild(element);
    }
    root.appendChild(equivalentRoot);
}

bool GOMarkovEquivalentParallel::tryOpen(QDomElement &root)
{
    if (root.tagName() != "parallel")
    {
        return false;
    }
    this->_idList->clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_idList->push_back(element.attribute("id").toInt());
    }
    return true;
}

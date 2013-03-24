#ifndef DOMITEM_H
#define DOMITEM_H
/**
 * The item which can read and generate DOM elements.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QDomDocument>
#include <QDomElement>

class DomItem
{
public:
    virtual void save(QDomDocument &document, QDomElement &root) = 0;
    virtual bool tryOpen(QDomElement &root) = 0;
};

#endif // DOMITEM_H

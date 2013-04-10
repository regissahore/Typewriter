#ifndef VIEWGOMARKOV_H
#define VIEWGOMARKOV_H
/**
 * The graphics view for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "viewgo.h"

class ViewGOMarkov : public ViewGO
{
    Q_OBJECT
public:
    explicit ViewGOMarkov(QWidget *parent = 0);
};

#endif // VIEWGOMARKOV_H

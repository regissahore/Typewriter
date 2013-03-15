#ifndef SCENEGO_H
#define SCENEGO_H

#include <QGraphicsScene>
#include "view/itemgooperator.h"
#include "view/itemgosource.h"

class SceneGO : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGO(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SCENEGO_H

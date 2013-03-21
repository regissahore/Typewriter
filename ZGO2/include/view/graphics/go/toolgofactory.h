#ifndef TOOLGOFACTORY_H
#define TOOLGOFACTORY_H
/**
 * The factory of GO tools.
 * The produce method is static, thus the class should not instantiated.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "definationtooltype.h"
#include "toolgoabstract.h"
#include "toolgopointer.h"
#include "toolgomove.h"
#include "toolgozoom.h"
#include "toolgoselect.h"
#include "toolgooperatortype1.h"
#include "toolgooperatortype2.h"
#include "toolgooperatortype3.h"
#include "toolgooperatortype4.h"
#include "toolgooperatortype5.h"
#include "toolgooperatortype6.h"
#include "toolgooperatortype7.h"
#include "toolgooperatortype8.h"
#include "toolgooperatortype9.h"
#include "toolgooperatortype10.h"
#include "toolgooperatortype11.h"
#include "toolgooperatortype12.h"
#include "toolgooperatortype13.h"
#include "toolgooperatortype14.h"
#include "toolgooperatortype15.h"
#include "toolgooperatortype16.h"
#include "toolgooperatortype17.h"

class ToolGOFactory
{
public:
    static ToolGOAbstract* produce(SceneGO *sceneGO, int type);
    static void release(ToolGOAbstract* tool);
};

#endif // TOOLGOFACTORY_H

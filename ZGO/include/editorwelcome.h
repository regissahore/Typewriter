#ifndef EDITORWELCOME_H
#define EDITORWELCOME_H
#include "editorabstract.h"

class EditorWelcome : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorWelcome(QWidget *parent = 0);
    bool trySave();
    bool trySaveAs();
    bool tryClose();
};

#endif // EDITORWELCOME_H

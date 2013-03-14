#ifndef EDITORWELCOME_H
#define EDITORWELCOME_H
/**
 * 欢迎界面。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "view/editorabstract.h"

class EditorWelcome : public EditorAbstract
{
public:
    explicit EditorWelcome(QWidget *parent = 0);
};

#endif // EDITORWELCOME_H

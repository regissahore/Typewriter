#ifndef MAINMENUANALYSIS_H
#define MAINMENUANALYSIS_H
/**
 * The main menu of analysis.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "mainmenuabstract.h"

class MainMenuAnalysis : public MainMenuAbstract
{
    Q_OBJECT
public:
    MainMenuAnalysis();

private:
    QAction *_actionProbability;
    QAction *_actionPath;
    QAction *_actionCut;

private slots:
    void slotActionProbability();
    void slotActionPath();
    void slotActionCut();
};

#endif // MAINMENUANALYSIS_H

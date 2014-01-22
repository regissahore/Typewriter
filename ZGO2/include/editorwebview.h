#ifndef EDITORWEBVIEW_H
#define EDITORWEBVIEW_H
#include "editorabstract.h"

class QWebView;

class EditorWebView : public EditorAbstract
{
    Q_OBJECT
public:
    EditorWebView(QWidget *parent = 0);
    void setPath(QString path);
    bool trySaveAs();

protected:
    QWebView *_webView;
};

#endif // EDITORWEBVIEW_H

#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QWebView>
#include <QWebFrame>
#include <QVBoxLayout>
#include "editorwebview.h"

EditorWebView::EditorWebView(QWidget *parent) : EditorAbstract(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_webView = new QWebView(this);
    layout->addWidget(this->_webView);
    this->setModified(false);
    this->_filter = tr("HTML Files(*.html)");
    this->_suffix = "html";
}

void EditorWebView::setPath(QString path)
{
    this->EditorAbstract::setPath(path);
    this->_webView->load(QUrl::fromLocalFile(path));
    this->_webView->show();
}

bool EditorWebView::trySaveAs()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File As"), ".", this->_filter);
    if (path != "")
    {
        if (QFileInfo(path).suffix() != this->_suffix)
        {
            path.append("." + this->_suffix);
        }
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Cannot write the file. "));
            return false;
        }
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << this->_webView->page()->mainFrame()->toHtml();
        file.flush();
        file.close();
        return true;
    }
    return false;
}

#ifndef DELEGATELINEEDIT_H
#define DELEGATELINEEDIT_H
/**
 * Delegate for line edit.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QItemDelegate>

class DelegateLineEdit : public QItemDelegate
{
    Q_OBJECT
public:
    DelegateLineEdit(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATELINEEDIT_H

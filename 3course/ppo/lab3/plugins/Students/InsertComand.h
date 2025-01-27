#ifndef INSERTCOMAND_H
#define INSERTCOMAND_H


#include "TreeModel.h"

#include "Comands.h"
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStringList>
#include <QTreeView>
#include <QUndoCommand>
#include <QVector>
#include <QJsonObject>
#include <iostream>
#include <memory>

class InsertCommand : public BaseCommand
{

public:
    InsertCommand(QModelIndex parent, QVector<QVariant> insertData, TreeModel *_treeModel);
    ~InsertCommand();

    virtual void undo();

    virtual void redo();
private:
    TreeModel *treeModel;
    QModelIndex m_parent;
    QVector<QVariant> m_insertData;
};
#endif // INSERTCOMAND_H

// Copyright (C) 2016 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0

#ifndef NODEWRAPPER_H
#define NODEWRAPPER_H

#include <QFileInfo>
#include <QList>
#include <QMap>
#include <QStack>



class NodeWrapper {
public:
    NodeWrapper(const QString value, const QString valueType, const QString nodeType,
                quint32 row, quint32 col, const QStringRef source, const QMap<QString, QString> tokenMap,
                const QFileInfo fileName):
        value(value), valueType(valueType), nodeType(nodeType), row(row), col(col),
        source(source.toString()), tokenMap(tokenMap), fileName(fileName) {}

    NodeWrapper(const NodeWrapper *other);

    ~NodeWrapper();

    inline bool operator==(NodeWrapper &other);
    inline bool operator!=(NodeWrapper &other);

    void addChild(NodeWrapper *node);
    const QString getValue();
    const QString getValueType();
    const QString getNodeType();
    const QString getSource();
    const quint32 getRow();
    const quint32 getCol();
    const QFileInfo getFileName();
    const QList<NodeWrapper *>& getChildren();
    const QMap<QString, QString>& getTokenMap();
    bool hasToken(const QString &key);
    QString getToken(const QString &key);
    void print();

    const QList<NodeWrapper*> getNodes(QString nodeType);
    const QList<NodeWrapper*> getNodes(QStack<QString> nodeType);
    const QString getId();
    bool  dropNode(NodeWrapper* id);

    QString getOutput();

    void merge(const NodeWrapper &other);

private:
    QList<NodeWrapper *> children;
    const QMap<QString, QString> tokenMap;
    const QString value;
    const QString valueType;
    const QString nodeType;
    const quint32 row;
    const quint32 col;
    const QString source;
    const QFileInfo fileName;

    void innerPrint(const int);
    void innerGetNodes(QStack<QString> searchList, const QStack<QString>& originalList, QList<NodeWrapper*>& nodes);
};

#endif // NODEWRAPPER_H

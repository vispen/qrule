// Copyright (C) 2017 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0

#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QXmlStreamReader>
#include <QProcess>
#include <QtMath>

class TestSuite {
public:
    TestSuite() {}
    ~TestSuite() {}

    void runTestSuite();

private:
    QString findXmlAttribute(QXmlStreamReader &xml, QString name);
    bool compareXMLFiles(QFile &file1, QFile &file2);
    void runQRuleEngine(QString ruleFile, QString qmlFile);

};

#endif // TESTSUITE_H


// Copyright (C) 2016 - 2017 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0
#include "qruleengine.h"

#include <stdio.h>
#include "gen/Parser.H"
#include "gen/Printer.H"
#include "gen/Absyn.H"
#include "qrulevisitor.h"

#include <QDebug>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <output/xmloutputformatter.h>
#include <QTextStream>

void printOutput(const QList<QRuleOutput*> &ruleViolations, QString fileName) {
    OutputFormatter* xof = new XMLOutputFormatter(ruleViolations);
    qDebug() << xof->format().toStdString().c_str();

    QDir d;
    d.mkdir(QString("output"));
    QFile fl(d.absolutePath() + "/output/" + fileName);
    fl.open(QIODevice::WriteOnly);
    fl.write(xof->format().toStdString().c_str());
    fl.close();
    delete xof;
}

void messageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg) {
}

int main(int argv, char *argc[]) {

    // Setup commandline parser
    QCoreApplication app(argv, argc);
    QCoreApplication::setApplicationName("QRuleEngine");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser commandLine;
    commandLine.setApplicationDescription(QLatin1String("Semantic rule engine for verifying QML code."));
    commandLine.addHelpOption();
    commandLine.addVersionOption();

    QCommandLineOption setDebug(QStringList() << "debug", QLatin1String("Enable debugging messages"));
    commandLine.addOption(setDebug);

    QCommandLineOption setDot(QStringList() << "d" << "dotty", QLatin1String("Create dot file for each QML file"));
    commandLine.addOption(setDot);

    QCommandLineOption setOutput(QStringList() << "o" << "outPutFile", QLatin1String("Change name of the output file"), "nameFile", "output.xml");
    commandLine.addOption(setOutput);

    QCommandLineOption setPath(QStringList() << "I" << "ImportPath", QLatin1String("Change project path"), "path", "");
    commandLine.addOption(setPath);

    commandLine.addPositionalArgument(QLatin1String("qrule"), QLatin1String("QRule rules file"));
    commandLine.addPositionalArgument(QLatin1String("files"), QLatin1String("list of qml or js files to verify"));

    commandLine.process(app);

    if (!commandLine.isSet(setDebug)) {
        qInstallMessageHandler(messageHandler);
    }

    // Display help instead of running the QRule Engine if too few arguments were given
    if (commandLine.positionalArguments().length() < 2) {
        commandLine.showHelp(-1);
    }

    // Parse arguments
    bool s_setDot = commandLine.isSet(setDot);
    QString name = commandLine.value(setOutput);
    QString path = commandLine.value(setPath);
    QStringList arguments = commandLine.positionalArguments();
    QString qruleFilename = arguments.takeFirst();

    // Start QRuleEngine
    QRuleEngine qruleEngine = QRuleEngine(qruleFilename, path);

    QList<QRuleOutput*> violations = qruleEngine.verifyQMLFiles(arguments, s_setDot);

    qDebug() << "############################################";
    qDebug() << "                XML OUTPUtT";
    qDebug() << "############################################";
    printOutput(violations, name);

    return violations.isEmpty() ? 0 : 1;
}

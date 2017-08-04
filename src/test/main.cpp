// Copyright (C) 2016 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0

#include <QDebug>
#include <QProcess>

int main(int argv, char *argc[]) {

	qDebug() << "############################################";
        qDebug() << "                Running TESTs";
        qDebug() << "############################################";

        /* QRuleEngine [options] qrule files

          1. Run QRuleEngine with rule against file to be tested, name the output file.

          1.1 Map the rule against the file and check if they are ok.

          2. if the rule passed then do nothing. if the rule did not pass save the out put and display it.

        */

        QProcess process;
        process.start("./QRuleEngine",
                      QStringList() << "resources/rule.kr" << "resources/fil.qml",
                      QIODevice::ReadWrite);
        if(!process.waitForFinished()) // beware the timeout default parameter
            qDebug() << "executing program failed with exit code" << process.exitCode();
        else
            qDebug() << QString(process.readAllStandardOutput()).split('\n');


}

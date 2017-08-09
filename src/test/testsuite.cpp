// Copyright (C) 2017 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0

#include "testsuite.h"

void TestSuite::runTestSuite()
{
    qDebug() << "############################################";
    qDebug() << "                TEST suite started";
    qDebug() << "############################################";

    float nrules = 0, errors = 0, good = 0, bad = 0;
    QDir d;
    QString fileName("/resources/testSuite.txt");
    QFile fileTestSuite(d.absolutePath() + fileName);
    if (!fileTestSuite.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening testSuite.txt, " << fileTestSuite.fileName()
                 << ", " << fileTestSuite.errorString();
        return;
    }
    QTextStream in(&fileTestSuite);
    // count number of rules

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        // If the line start with # it is a comment and should be ignored.
        if(!QString::compare(QString(line[0]), QString("#"), Qt::CaseInsensitive) == 0)
        {
            nrules++;
        }
    }
    in.seek(0);
    int row = 1;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        // If the line start with # it is a comment and should be ignored.
        if(QString::compare(QString(line[0]), QString("#"), Qt::CaseInsensitive) == 0)
        {
            row++;
            continue;
        }else
        {
            QStringList list = line.split(";", QString::KeepEmptyParts);
            if(list.length() != 4)
            {
                errors++;
                qDebug() <<"[" << qFloor(errors+good+bad)/nrules * 100 << "%]" << "wrong number of arguments on line" << row << "in " << fileName;
            }
            else
            {
                // run QRuleEngine
                runQRuleEngine(list.at(1).trimmed(), list.at(2).trimmed());
                // validate result from QRuleEngine

                QFile file(d.absolutePath() + "/output/output.xml");
                QFile file_valid(d.absolutePath() + "/resources/validXmlOutput/" + list.at(3).trimmed());
                if (compareXMLFiles(file, file_valid))
                {
                    good++;
                    qDebug() <<"[" << qFloor(errors+good+bad)/nrules * 100 << "%]" << list.at(0).trimmed() << " - ok";
                }
                else
                {
                    bad++;
                    qDebug() <<"[" << qFloor(errors+good+bad)/nrules * 100 << "%]" << list.at(0).trimmed() << " - failed";
                }
            }
        }
        row++;
     }

    qDebug() << "############################################";
    qDebug() << "                TEST suite completed";
    qDebug() << "";
    qDebug() << "Total:" << good+bad+errors << "good:" << good << "bad:" << bad << "errors:" << errors;
    qDebug() << "############################################";
}

/* Run QruleEngine with ruleFile and qmlFile
 *
 */
void TestSuite::runQRuleEngine(QString ruleFile, QString qmlFile)
{
    QProcess process;
    process.start("./QRuleEngine",
                  QStringList() << "resources/qmlTestFiles/" + ruleFile << "resources/qmlTestFiles/" + qmlFile,
                  QIODevice::ReadWrite);
    if(!process.waitForFinished()) // beware the timeout default parameter
        qDebug() << "executing program failed with exit code" << process.exitCode();
}

/* Return attribnute with name from xml Element
 *
 */
QString TestSuite::findXmlAttribute(QXmlStreamReader &xml, QString name)
{
    foreach(const QXmlStreamAttribute &attr, xml.attributes()) {
        if (QString::compare(attr.name().toString(), QString(name), Qt::CaseSensitive) == 0) {
            QString attributeValue = attr.value().toString();
            return attributeValue;
        }
    }
    return QString();
}

/* Basic comparison of xmlFiles
 *
 */
bool TestSuite::compareXMLFiles(QFile &file1, QFile &file2) {

    QFile *filePointer1 = std::addressof(file1);
    QFile *filePointer2 = std::addressof(file2);

    if (!filePointer1->open(QIODevice::ReadOnly) || !filePointer2->open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open xml file:" << filePointer1->fileName() << ", " << filePointer2->fileName();
        return false;
    }

    QXmlStreamReader xmlReader1(filePointer1), xmlReader2(filePointer2);

    /* We'll parse the XML until we reach end of it.*/
    while (!xmlReader1.atEnd() && !xmlReader1.hasError() && !xmlReader2.atEnd() && !xmlReader2.hasError())
    {
         /* Read next element.*/
        QXmlStreamReader::TokenType token1 = xmlReader1.readNext();
        QXmlStreamReader::TokenType token2 = xmlReader2.readNext();
        if (token1 == QXmlStreamReader::StartDocument || token2 == QXmlStreamReader::StartDocument){
            continue;
        }

        /* Find start of element */
        if (token1 == QXmlStreamReader::StartElement)
        {
            if (!QString::compare(xmlReader1.name().toString(), xmlReader2.name().toString(), Qt::CaseSensitive) == 0)
            {
                qDebug() << "xml element missmatch in files: " << filePointer1->fileName() << ", "
                         << filePointer2->fileName() << " element in file 1: "
                         << xmlReader1.name() << " in file 2: " << xmlReader2.name();
                return false;
            }

            /* Qrule tag contain attributes */
            if (xmlReader1.name() == "qrule")
            {
                if (!QString::compare(findXmlAttribute(xmlReader1, "tag"), findXmlAttribute(xmlReader2, "tag")) == 0)
                {
                    qDebug() << "xml tag missmatch in files: " << filePointer1->fileName()
                             << ", " << filePointer2->fileName() << " tag in file 1: "
                             << xmlReader1.name() << " in file 2: " << xmlReader2.name();
                    return false;
                }
            }

            if (xmlReader1.name() == "occurrance")
            {
                if (!QString::compare(findXmlAttribute(xmlReader1, "row"), findXmlAttribute(xmlReader2, "row")) == 0 ||
                    !QString::compare(findXmlAttribute(xmlReader1, "col"), findXmlAttribute(xmlReader2, "col")) == 0)
                {
                    qDebug() << "xml row, col missmatch in files: " << filePointer1->fileName() << ", "
                             << filePointer2->fileName() << "in file1 row:" << findXmlAttribute(xmlReader1, "row")
                             << ", col:" << findXmlAttribute(xmlReader1, "col") << ", in file2 row:"
                             << findXmlAttribute(xmlReader2, "row") << ", col:" << findXmlAttribute(xmlReader2, "col");
                    return false;
                }
            }
        }
        if (xmlReader1.hasError() || xmlReader2.hasError())
        {
            qDebug() << "Error parsing xml:" << (xmlReader1.hasError() ? xmlReader1.errorString(): xmlReader2.errorString());
        }
    }
}

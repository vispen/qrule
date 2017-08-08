// Copyright (C) 2017 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0

#include <QDebug>
#include <QProcess>
#include <QDateTime>
#include <QFile>
#include <QXmlStreamReader>
#include <QDir>

QString findXmlAttribute(QXmlStreamReader &xml, QString name);

/* Basic comparison of xmlFiles
 *
 */
bool compareXMLFiles(QFile &file1, QFile &file2) {

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
                qDebug() << "xml element missmatch in files: " << filePointer1->fileName() << ", " << filePointer2->fileName()
                    << " element in file 1: " << xmlReader1.name() << " in file 2: " << xmlReader2.name();
                return false;
            }

            /* Qrule tag contain attributes */
            if (xmlReader1.name() == "qrule")
            {
                if (!QString::compare(findXmlAttribute(xmlReader1, "tag"), findXmlAttribute(xmlReader2, "tag")) == 0)
                {
                    qDebug() << "xml tag missmatch in files: " << filePointer1->fileName() << ", " << filePointer2->fileName()
                        << " tag in file 1: " << xmlReader1.name() << " in file 2: " << xmlReader2.name();
                    return false;
                }
            }

            if (xmlReader1.name() == "occurrance")
            {
                if (!QString::compare(findXmlAttribute(xmlReader1, "row"), findXmlAttribute(xmlReader2, "row")) == 0 ||
                    !QString::compare(findXmlAttribute(xmlReader1, "col"), findXmlAttribute(xmlReader2, "col")) == 0)
                {
                    qDebug() << "xml row, col missmatch in files: " << filePointer1->fileName() << ", " << filePointer2->fileName()
                        << "in file1 row:" << findXmlAttribute(xmlReader1, "row") << ", col:" << findXmlAttribute(xmlReader1, "col")
                        << ", in file2 row:" << findXmlAttribute(xmlReader2, "row") << ", col:" << findXmlAttribute(xmlReader2, "col");
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

/* Return attribnute with name from xml Element
 *
 */
QString findXmlAttribute(QXmlStreamReader &xml, QString name)
{
    foreach(const QXmlStreamAttribute &attr, xml.attributes()) {
        if (QString::compare(attr.name().toString(), QString(name), Qt::CaseSensitive) == 0) {
            QString attributeValue = attr.value().toString();
            return attributeValue;
        }
    }
    return QString();
}

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
            qDebug() << QString("### Start validating xml files ####");


        QDir d;
        QFile file(d.absolutePath() + "/output/output.xml");
        QFile file_valid(d.absolutePath() + "/resources/validXmlOutput/basic_2.xml");
        if (compareXMLFiles(file, file_valid))
            qDebug() << "Wohooo it was a success !!   :o)";
        else
            qDebug() << "sadly the xml did not match up :o( ";

        qDebug() << "############################################";
        qDebug() << "                TEST session completed";
        qDebug() << "############################################";

}



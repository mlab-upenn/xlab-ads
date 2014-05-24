#include "xmldataparser.h"

XMLDataParser::XMLDataParser(QObject *parent) :
    QObject(parent)
{
}

void XMLDataParser::loadXML(QString filename)
{
    xmlFile = new QFile(filename);
    qDebug()<<filename;
    // If we can't open it, let's show an error message.
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot Open XML file";
    }
    xmlReader.setDevice(xmlFile);
}

void XMLDataParser::parseXML()
{
    while(!xmlReader.atEnd() &&
            !xmlReader.hasError())
    {

        QXmlStreamReader::TokenType token = xmlReader.readNext();

        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument)
            continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xmlReader.name() == "frame")
            {

                Frame* curFrame;
                QXmlStreamAttributes attributes = xmlReader.attributes();
                curFrame = this->parseFrame(xmlReader);
                qDebug() << attributes.count();
                dataMap[attributes.value("num").toInt()] = curFrame;

            }

        }
    }
    qDebug()<<"Parse done!";

}
Frame* XMLDataParser::parseFrame(QXmlStreamReader &xmlReader)
{
    Frame * outputFrame = new Frame();
    while(!((xmlReader.tokenType() == QXmlStreamReader::EndElement) && (xmlReader.name().toString() == "frame" )))
    {
        //skip the empty <frame> contents
        xmlReader.readNext();
        QMap<QString, QString> item;
        item = parseItem(xmlReader);
        if(item.size() > 0)
            outputFrame->InsertItem(item);
    }

    return outputFrame;


}
QMap<QString, QString> XMLDataParser::parseItem(QXmlStreamReader &xmlReader)
{

    QMap<QString, QString> item;
    xmlReader.readNext();
    if(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().toString() == "frame")
        return item;
    if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name().toString() == "item")
    {

        while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().toString() == "item"))
        {

            if(xmlReader.tokenType() == QXmlStreamReader::StartElement && xmlReader.name().toString() != "item")
            {
                QString name = xmlReader.name().toString();
                xmlReader.readNext();
                item[name] = xmlReader.text().toString();
            }
            xmlReader.readNext();
        }
    }
    return item;

}

void XMLDataParser::loadnewxml(QMediaContent video)
{
    qDebug() << video.canonicalUrl().fileName().section(".",0,0);
    this->loadXML(video.canonicalUrl().fileName().section(".",0,0) + QString(".xml"));
    this->parseXML();
}

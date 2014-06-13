#include "settings.h"
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QStringList>

Settings::Settings(QString filename, QObject *parent) :
    QSettings(filename, QSettings::IniFormat, parent) {
}

QMap<QString, QString> Settings::readGrp(QString grp) {
    QMap<QString, QString> retmap;
    retmap.clear();
    if(grp.length() > 0) {
        QFile file;
        file.setFileName(this->fileName());
        qDebug() << Q_FUNC_INFO <<this->fileName();
        if(!file.exists()) {
            return retmap;
        }
        if(file.open(QIODevice::ReadOnly)) {
            setIniCodec(QTextCodec::codecForName("UTF-8"));
            beginGroup(grp);
            QString item;
            QStringList items = childKeys();
            foreach (item, items) {
                retmap.insert(item, value(item, "").toString().trimmed());
            }
            endGroup();
        }
        file.close();
    }
    return retmap;
}
#pragma once

#include<QSqlDatabase>
#include<QString>
#include<QMap>


namespace sql {

class SQLDriver
{
public:
    SQLDriver();
    ~SQLDriver();

    QString execQuery(QString conname, QString query);
    void initConnection(QString host, QString dbname);

private:
    QMap<QString, QSqlDatabase> mConnectionMap;
    QSqlDatabase connect(QString conname, QString host, QString dbname, QString user, QString passwd);
};

}

#include<QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include "sql_driver.hpp"
#include "QString"
sql::SQLDriver::SQLDriver()
{

}

sql::SQLDriver::~SQLDriver()
{
    for(auto db : mConnectionMap.keys())
        mConnectionMap[db].close();
}

void sql::SQLDriver::initConnection(QString host, QString dbname)
{

    mConnectionMap["Regular"] = connect("Regular", host,dbname, "user", "user");
    mConnectionMap["Admin"] = connect("Admin",host, dbname, "newuser", "password");


    for(auto db : mConnectionMap.keys())
        if(!mConnectionMap[db].open())
            qDebug() << "Could not access the database: " << mConnectionMap[db].lastError().text();
        else
            qDebug() << "=====================\n"
                     << "State of database: " << mConnectionMap[db].databaseName() << endl
                     << "Opened: "  << mConnectionMap[db].open() << endl
                     << "On host: " << mConnectionMap[db].hostName() << endl
                     << "Options: " << mConnectionMap[db].connectOptions() << endl
                     << "Type: " << mConnectionMap[db].connectionName() << endl
                     << "=====================\n";
}

QSqlDatabase sql::SQLDriver::connect(QString conname, QString host, QString dbname, QString user, QString passwd)
{
    auto db = QSqlDatabase::addDatabase("QMYSQL", conname);
    db.setHostName(host);
    db.setPort(3306);
    db.setDatabaseName(dbname);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setConnectOptions();
    return db;
}

QString sql::SQLDriver::execQuery(QString conname, QString querystr)
{
    if(mConnectionMap.find(conname) == mConnectionMap.end()) {
        qDebug() << "Error in executing query: Invalid connection name.\n";
        return "{ }";
    }
    QSqlQuery query = QSqlQuery(mConnectionMap[conname]);
    query.setForwardOnly(true);
    query.exec(querystr);
    if(!query.isActive()) {
        qDebug() << "Error in executing query: " << query.lastError().text() << "\n";
        return "{ }";
    }

    QJsonDocument  json;
    QJsonArray     recordsArray;
    while(query.next()) {
        QJsonObject recordObject;
        for(int i=0; i < query.record().count(); i++)
            recordObject.insert( query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)) );
        recordsArray.push_back(recordObject);
    }
    json.setArray(recordsArray);

    return QString(json.toJson());

}


#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

#include <QtSql/QSqlQuery>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QCoreApplication>
#include <QPluginLoader>

#include <QDebug>
#include <QObject>

#define CURR_DB_VER "1.1"

class IO_MySQLInterface: public QObject
{
    Q_OBJECT
public:
    explicit IO_MySQLInterface(QObject *parent = 0);

public:
    static bool isDBConnected();
    static void setDBConnectionStat(bool connected);

    static int getLogInState() ;
    static int getLogInUID() ;
    static int getLogInGID() ;
    static QString getLogInUname() ;
    static QString getLogInGname() ;
    static QString getLogInGtype() ;
    static QString getLogInUstatus() ;


    static QSqlDatabase& getDatabase(){return m_db;}

    static void InitDBParameters();
    static bool ConnectDb();
    static void SetHost(const char *hostName);
    static void SetDbName(const char *DbName);
    static void SetPortNumber(int portNum);
    static void SetUserName(const char *userName);
    static void SetPassword(const char *password);
    static QSqlQuery ExcSQLCMD(QString command);
    static int userLogIn(QString uname, QString upassword);

private:
    static QSqlDatabase m_db;
    static bool m_isDBConnected;
    static int m_logInState;
    static int m_logInUID;
    static int m_logInGID;
    static QString m_logInUstatus;
    static QString m_logInUname;
    static QString m_logInGtype;
    static QString m_logInGname;
    static QString m_logInRealName;
public:
    static QString selectDBvalue(QString db, QString key,
                          QString conditionKey, QString conditionValue);
	static QStringList selectDBvalue(QString db, QStringList keys, QString conditionKey);
	static QStringList selectDBvalueList(QString db, QString key, QString conditionKey = "");
    static bool updateDBvalue(QString db, QStringList keys, QStringList values, QString conditionKey);
    static bool insertDBvalue(QString db, QStringList keys, QStringList values);
	static QString selectDBvalue(QString db, QString key, QString conditionKeyAndValue);
    static int selectDBCountvalue(QString db, QString conditionKey = "", QString conditionValue = "");
    static int updateDBvalue(QString db, QString key, QString value,
                          QString conditionKey, QString conditionValue);
    static bool checkUnique(QString db, QString key, QString value);
	static bool query(QString cmd);
};

#endif // MYSQLINTERFACE_H

#include "io_mysqlinterface.h"
#include <QtWidgets/QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

// static variables
QSqlDatabase IO_MySQLInterface::m_db;
bool IO_MySQLInterface::m_isDBConnected = false;
int IO_MySQLInterface::m_logInState = 0;
int IO_MySQLInterface::m_logInUID;
int IO_MySQLInterface::m_logInGID;
QString IO_MySQLInterface::m_logInUstatus;
QString IO_MySQLInterface::m_logInUname;
QString IO_MySQLInterface::m_logInGtype;
QString IO_MySQLInterface::m_logInGname;
QString IO_MySQLInterface::m_logInRealName;

IO_MySQLInterface::IO_MySQLInterface(QObject *parent): QObject(parent)
{
}

bool IO_MySQLInterface::isDBConnected()
{
    return m_isDBConnected;
}

void IO_MySQLInterface::setDBConnectionStat(bool connected)
{
    m_isDBConnected = connected;
}

int IO_MySQLInterface::getLogInState()
{
    return m_logInState;
}
int IO_MySQLInterface::getLogInUID()
{
    return m_logInUID;
}
int IO_MySQLInterface::getLogInGID()
{
    return m_logInGID;
}
QString IO_MySQLInterface::getLogInUname()
{
    return m_logInUname;
}
QString IO_MySQLInterface::getLogInGname()
{
    return m_logInGname;
}
QString IO_MySQLInterface::getLogInGtype()
{
    return m_logInGtype;
}

QString IO_MySQLInterface::getLogInUstatus()
{
    return m_logInUstatus;
}

void IO_MySQLInterface::InitDBParameters()
{
    QCoreApplication::addLibraryPath("d:\program_files\Qt\Qt5.9.1\Tools\QtCreator\bin\plugins");
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
	m_db.setDatabaseName("mysql");
    m_db.setPort(3306);
	m_db.setUserName(QString("ro") +"ot");
	m_db.setPassword("321");

	/*
	m_db.setDatabaseName("turbidimeter_db");
	m_db.setPort(3306);
	m_db.setUserName(QString("TMDBmana") +"ge");
	m_db.setPassword(QString("TMDBmana")+ "ge@" + "XQ" +"WF2" + "018" + "0511");
	*/

	/*
    m_db.setDatabaseName("haloes_caliper_db");
    m_db.setPort(3306);
    m_db.setUserName("HCDBmanage");
    m_db.setPassword("HCDBmanage@XQWF");
	*/

    //g_pRstDB = &m_db;
}

bool IO_MySQLInterface::ConnectDb()
{
	{
        if(m_db.open()){
			qDebug() << "[INF] MySQL connected!"<<endl;
            m_isDBConnected = true;
        } else {
			qDebug() << "[ERR] MySQL connection failed!"<<endl;
            m_isDBConnected = false;
        }
    }
    return m_isDBConnected;
}

void IO_MySQLInterface::SetHost(const char *hostName)
{
    m_db.setHostName(hostName);
}
void IO_MySQLInterface::SetDbName(const char *DbName)
{
    m_db.setDatabaseName(DbName);
}
void IO_MySQLInterface::SetPortNumber(int portNum)
{
    m_db.setPort(portNum);
}
void IO_MySQLInterface::SetUserName(const char *userName)
{
    m_db.setUserName(userName);
}
void IO_MySQLInterface::SetPassword(const char *password)
{
    m_db.setPassword(password);
}

QSqlQuery IO_MySQLInterface::ExcSQLCMD(QString command)
{
    return m_db.exec(command);
}

int IO_MySQLInterface::userLogIn(QString uname, QString upassword)
{
    if (!m_isDBConnected) {
        return -1;
    }

    m_logInState = 0;
    QString sql = "SELECT * FROM account_tbl WHERE "
                  "uname = '"  + uname + "'"
                  " and AES_DECRYPT(upassword, 'key') = '" + upassword + "' LIMIT 1";
    QSqlQuery query = m_db.exec(sql);
    if (query.next() == false) {
        return -1;
    } else {
        m_logInUID = query.value("uid").toInt();
        m_logInUname = query.value("uname").toString();
        m_logInGID = query.value("ugroupid").toInt();
        m_logInRealName = query.value("urealname").toString();
        m_logInUstatus = query.value("ustatus").toString();
        sql = QString("SELECT * FROM `group_tbl` WHERE "
              "`gid` = %1").arg(m_logInGID);
        //qDebug() << sql;
        query = m_db.exec(sql);
        query.next();
        m_logInGtype = query.value("gtype").toString();
        m_logInGname = query.value("gname").toString();

        qDebug() << m_logInUname << " as a " << m_logInGtype << "logged in";
        m_logInState = 1;
        return 0;
        //ui->labelErrInfo->setVisible(true);
    }
    qDebug() << "Password error2";
    return -1;
}

QString IO_MySQLInterface::selectDBvalue(QString db, QString key, QString conditionKey, QString conditionValue)
{
    QSqlQuery query;
    QString queryText = "SELECT " + key + " FROM " + db + " WHERE " + conditionKey
            + " = '" + conditionValue + "';";
    query.exec(queryText);
    if (query.next()) {
        return query.value(0).toString();
    } else {
        return QString("");
    }
}

QStringList IO_MySQLInterface::selectDBvalue(QString db, QStringList keys, QString conditionKey)
{
    QSqlQuery query;
    QStringList retList;
    QString queryText = "SELECT " + keys.join(',') + " FROM " + db + " WHERE " + conditionKey + ";";
    query.exec(queryText);
    int num = keys.size();
    if (!query.next()) {
        QSqlError err = query.lastError();
		qDebug() << "SelectDBValue Error(QStringList):" << err.databaseText() << db << keys << conditionKey;
        return QStringList();
    } else {
        for (int i = 0; i < num; i++) {
            retList << query.value(i).toString();
        }
        return retList;
    }
}

QStringList IO_MySQLInterface::selectDBvalueList(QString db, QString key, QString conditionKey)
{
    QSqlQuery query;
    QStringList retList;
	QString queryText;
	if (conditionKey.isEmpty()) {
		queryText = "SELECT " + key + " FROM " + db + ";";
	} else {
		queryText = "SELECT " + key + " FROM " + db + " WHERE " + conditionKey + ";";
	}
	//qDebug() << queryText;
    query.exec(queryText);
    while(query.next()) {
        retList << query.value(0).toString();
    }
    return retList;
}

bool IO_MySQLInterface::updateDBvalue(QString db, QStringList keys, QStringList values, QString conditionKey)
{
    QString key;
    QString value;
    QStringList settingText;
    int i = 0;
    foreach (key, keys) {
        settingText << key + " = " + values[i++];
    }
    QString updateQueryStr = "UPDATE "+ db + " SET " + settingText.join(',') + " WHERE " + conditionKey;
    QSqlQuery query;
    return query.exec(updateQueryStr);
}

bool IO_MySQLInterface::insertDBvalue(QString db, QStringList keys, QStringList values)
{
    QString insertQueryStr = "INSERT INTO "+ db + " ( " + keys.join(',') + " ) "
                     "VALUES (" + values.join(',') + ")";
	//qDebug() << insertQueryStr;
    QSqlQuery query;
    return query.exec(insertQueryStr);
}

QString IO_MySQLInterface::selectDBvalue(QString db, QString key, QString conditionKeyAndValue)
{
    QSqlQuery query;
    QString queryText = "SELECT " + key + " FROM " + db + " WHERE " + conditionKeyAndValue + ";";
    query.exec(queryText);
    if (query.next()) {
        return query.value(0).toString();
    } else {
        return QString("");
    }
}

int IO_MySQLInterface::selectDBCountvalue(QString db, QString conditionKey, QString conditionValue)
{
    QSqlQuery query;
	QString queryText = "SELECT count(*) FROM " + db + " ";
    if (!conditionKey.isEmpty()) {
        queryText += " WHERE `" + conditionKey
            + "` = '" + conditionValue + "';";
    }
    query.exec(queryText);
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}

/*
int IO_MySQLInterface::selectDBCountvalue(QString db, QString conditionKeyAndValue)
{
    QSqlQuery query;
    QString queryText = "SELECT count(*) FROM " + db + " ";
    if (!conditionKeyAndValue.isEmpty()) {
        queryText += " WHERE " + conditionKeyAndValue + ";";
    }
    query.exec(queryText);
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
*/

int IO_MySQLInterface::updateDBvalue(QString db, QString key, QString value, QString conditionKey, QString conditionValue)
{
    QSqlQuery query;
    QString queryText = "UPDATE " + db + " SET " + key  + " = " + value + " WHERE " + conditionKey
            + " = " + conditionValue + ";";
    if (!query.exec(queryText)) {
        QSqlError err = query.lastError();
        qDebug() << "Update Password Error:" << err.databaseText();
        return -1;
    }
    return 0;
}

bool IO_MySQLInterface::checkUnique(QString db, QString key, QString value)
{
    QSqlQuery query;
    QString queryText = "SELECT * FROM " + db + " WHERE " + key + " = " + value + " ;";
	//qDebug() << queryText;
    query.exec(queryText);
    if (query.next()) {
        qDebug() << query.value(0).toString();
        return false;
    } else {
        return true;
	}
}

bool IO_MySQLInterface::query(QString cmd)
{
	QSqlQuery query;
	bool ret = query.exec(cmd);
	if (!ret) {
		qDebug() << query.lastError().text();
	}
	return ret;
}

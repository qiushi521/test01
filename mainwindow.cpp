#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qdir>
#include <QProcess>
#include <QDebug>
#include "copypythonlib.h"
#include <QString>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        m_removePreviewsTables(false),
        m_setupDBTimerID(0),
        m_updateDBTimerID(0),
        m_progressBarTimerID(0)
{
	ui->setupUi(this);

	m_cmdText[IT_VS2012] 	= "vc2012_redist_x64.exe /silent";
	m_cmdText[IT_WAMP] 		= "wampserver2.5-64b.exe /silent";
	m_cmdText[IT_START_WAMP]= "start /b C:\\wamp\\wampmanager.exe";
	m_cmdText[IT_V370_DRIVER]= ".\\V370_Driver\\Setup.exe";
	m_cmdText[IT_MYSQL] 	= "#MySQL";
	m_cmdText[IT_START_MYSQL] 	= "#startMySQL";
	m_cmdText[IT_BOOT_OPTION]= "bcdedit /set {current} bootstatuspolicy ignoreallfailures";
	m_cmdText[IT_SETUP_DB] 	= "#setupDB";
	m_cmdText[IT_MKDIRS] 	= "#mkdirs";

	m_promotingText[IT_VS2012] 		=  "安装vc2012发布包";
	m_promotingText[IT_WAMP] 		= "安装Wamp服务(完成后需点击“允许访问”)";
	m_promotingText[IT_START_WAMP] 	= "启动Wamp服务";
	m_promotingText[IT_MYSQL] 		= "安装MySQL服务";
	m_promotingText[IT_START_MYSQL] 	= "启动MySQL";
	m_promotingText[IT_V370_DRIVER]	= "安装V370驱动程序(安装过程中请点击相应勾选和下一步按钮)";
	m_promotingText[IT_BOOT_OPTION] = "设置系统启动选项";
	m_promotingText[IT_SETUP_DB] 	= "配置数据库";
	m_promotingText[IT_MKDIRS] 	 	= "创建程序文件夹";

	m_operations << /*IT_VS2012 << IT_WAMP << IT_START_WAMP <<
	                IT_BOOT_OPTION <<*/IT_MYSQL << IT_START_MYSQL << IT_MKDIRS <<IT_SETUP_DB;
	m_cmdProcess = new QProcess(this);

	setWindowTitle(QString("比浊仪控制软件自动安装及配置程序　Ver") + VER);

	ui->textEdit->setReadOnly(true);

    ui->btnUpdateDB->setVisible(false);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_btnStartInstall_clicked()
{
	//m_cmdProcIess->waitForStarted();
	ui->btnUpdateDB->setEnabled(false);
	ui->btnCopyFiles->setEnabled(false);
	ui->btnStartInstall->setEnabled(false);
	m_currCmdIndex = -1;
	excuteSetupOperation();
    m_progressBarTimerID = startTimer(3*1000);
}

void MainWindow::excuteSetupOperation()
{
	QString command;
	m_currCmdIndex++;
	if (m_currCmdIndex >= m_operations.length()) {
		ui->btnStartInstall->setEnabled(true);
		ui->textEdit->append(" ===== 软件安装配置完成. =====\n");
		ui->progressBar->setValue(100);
        if (m_progressBarTimerID != 0) {
            killTimer(m_progressBarTimerID);
            m_progressBarTimerID = 0;
        }
		return;
	}
	ui->textEdit->append(QString("===== Step %1 / %2 =====").arg(m_currCmdIndex+1).arg(m_operations.length()));
	ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + "...");
	ui->progressBar->setValue(100.0 * (m_currCmdIndex) / m_operations.length());
	command = m_cmdText[m_operations[m_currCmdIndex]];
	qDebug() << "IT option: Step " << m_currCmdIndex + 1 << command;
	if (command.startsWith("#")) {
		if (m_operations[m_currCmdIndex] == IT_SETUP_DB) {
			m_setupDBTimerID = startTimer(5000);    //wait for wampserver to start
		} else if (m_operations[m_currCmdIndex] == IT_MKDIRS) {
			checkOrCreateFolder();
		} else if (m_operations[m_currCmdIndex] == IT_MYSQL) {
			extractMySQL();
		} else if (m_operations[m_currCmdIndex] == IT_START_MYSQL) {
            startMySQL();
		}
	} else {
		connect(m_cmdProcess, SIGNAL(finished(int)), this, SLOT(onLastOpComplete(int)));
		m_cmdProcess->start("cmd", QStringList()<<"/c"<<command);
	}
}

void MainWindow::onLastOpComplete(int errCode)
{
	if (m_currCmdIndex < m_operations.length()) {
		if (errCode == 0) {
			ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 已完成.\n\n");
		} else {
			ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 失败.\n\n");
		}
	} else {
		ui->textEdit->append(QString::number(errCode));
	}
	disconnect(m_cmdProcess, 0, 0, 0);
	excuteSetupOperation();
}

//拷贝文件夹：
bool MainWindow::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
		if(!targetDir.mkdir(targetDir.absolutePath()))
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList){
		if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
			if(!copyDirectoryFiles(fileInfo.filePath(),
			                       targetDir.filePath(fileInfo.fileName()),
			                       coverFileIfExist))
				return false;
		}
		else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
			if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
				targetDir.remove(fileInfo.fileName());
			}

			/// 进行文件copy
			if(!QFile::copy(fileInfo.filePath(),
			                targetDir.filePath(fileInfo.fileName()))){
				return false;
			}
		}
	}
	return true;
}

void MainWindow::on_btnCopyFiles_clicked()
{
	ui->btnUpdateDB->setEnabled(false);
	ui->btnCopyFiles->setEnabled(false);
	ui->textEdit->append("启动Wamp服务...\n");
	disconnect(m_cmdProcess, 0, 0, 0);
	m_cmdProcess->start("cmd", QStringList()  << "/c"<< "start /b C:\\wamp\\wampmanager.exe");
	m_setupDBTimerID = startTimer(5000);
}

void MainWindow::onCopyLibsFinished()
{
	/*
	ui->textEdit->append("全部安装完成");
	setupDB();
	exit(0);
	*/
}

/**
 * @brief MainWindow::setupDB
 */
void MainWindow::setupDB()
{
    QString sqlFileName = ":/res_file/turbidimeter_db.sql";
	ui->textEdit->append("创建数据库...");

	int num1 = 1984;
	int num2 = 2018;
	QStringList sign = QStringList() << "@" << "-" << "^";
	QString pd = "xQ" + sign[0] + QString::number(num1) + sign[1] + "Wf" + sign[2] + "Bj" + QString::number(num2);
	IO_MySQLInterface::InitDBParameters();
	IO_MySQLInterface::SetPassword("");
	if (IO_MySQLInterface::ConnectDb()) {   // default blank password
		qDebug() << "[INF] Set password";
		IO_MySQLInterface::updateDBvalue("`user`", QStringList() << "`Password`", QStringList() << "PASSWORD('" + pd +"')" ,
		                                 "`user`='root'");
		IO_MySQLInterface::query("FLUSH PRIVILEGES;");
	} else {
		IO_MySQLInterface::SetPassword(pd.toLocal8Bit());
		if (IO_MySQLInterface::ConnectDb()) {   // default blank password
			qDebug() << "[INF] Log in OK.";
			//qDebug() << "[INF] Drop previous user" << IO_MySQLInterface::query("DROP user TMDBmanage@localhost;");
			//qDebug() << "[INF] Drop previous user" << IO_MySQLInterface::query("DROP user TMDBmanage@localhost;");
		} else {
			qDebug() << "[ERR] Can't login to DB root.";
			QMessageBox::warning(this, "错误", "数据库服务不存在.", QMessageBox::Yes);
			return;
		}
	}
	QString keys="ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890abcdemng";
	//            012345678901234567890123456789012345678901234
	//            0         1         2         3         4
	pd = QString("TM%1%2m%3%4a%5%6").arg(keys[3]).arg(keys[1]).arg(keys[37]).arg(keys[43]).arg(keys[44]).arg(keys[41]);
	pd += sign[0];
	pd += "XQWF";
	pd += QString::number(num2);
	pd += QString("0%1").arg(511);
	//qDebug() << pd;
	bool isDBExist = IO_MySQLInterface::query("use `turbidimeter_db`");
	qDebug() << "[INF] Create User:\t" << IO_MySQLInterface::query("create USER `TMDBmanage`@`localhost` IDENTIFIED BY '" + pd + "';");
	ui->textEdit->append(" -创建用户");
	qDebug() << "[INF] Create DB: \t" << IO_MySQLInterface::query("create DATABASE `turbidimeter_db`;");
	ui->textEdit->append(" -创建数据库");
	qDebug() << "[INF] Grant privileges:\t" << IO_MySQLInterface::query("GRANT ALL privileges on `turbidimeter_db`.* to `TMDBmanage`@`localhost`;");
	qDebug() << "[INF] Grand User:\t" << IO_MySQLInterface::query("UPDATE `mysql`.`user` SET `Select_priv`='Y', `File_priv`='Y' WHERE `User` = 'TMDBmanage';");
	qDebug() << "[INF] Use DB:\t" << IO_MySQLInterface::query("use `turbidimeter_db`");
	IO_MySQLInterface::query("FLUSH PRIVILEGES;");
	ui->textEdit->append(" -设置权限");

	QFile sqlFile(sqlFileName);
	if (!sqlFile.open(QIODevice::ReadOnly)) {
		qDebug() << "[ERR] Can't open file.";
		ui->btnUpdateDB->setEnabled(true);
		ui->btnCopyFiles->setEnabled(true);
		ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 失败.\n\n");
		excuteSetupOperation();
		return;
	}

	bool needDropTable = true;
	if (isDBExist) {
		if (QMessageBox::No == QMessageBox::warning(this, "确认", "数据库已存在，是否全部删除后重新创建？", QMessageBox::Yes, QMessageBox::No)) {
			needDropTable = false;
		}
	}

	QString sqlStat;
	QString line;
	int i = 0;
	while (!sqlFile.atEnd()) {
		line = sqlFile.readLine();
		line = line.simplified();
		if (line.endsWith('\n') || line.endsWith('\r')) {
			line = line.left(line.length() - 1);    //remove '\n'
		}
		if (line.startsWith('-') || line.startsWith('/') || line.length() == 0) continue;
		sqlStat += line;
		if (sqlStat.endsWith(';')) {
			if (line.contains("DROP") && (needDropTable == false)) {
				sqlStat.clear();
				continue;
			}
			qDebug() << sqlStat.left(20) + "...:" << IO_MySQLInterface::query(sqlStat);
			sqlStat.clear();
		}
	}
	ui->textEdit->append(" -创建数据库表结构.");
	pd = "key";
	if (needDropTable) {
		IO_MySQLInterface::query("UPDATE `account_tbl` SET `upassword` = AES_ENCRYPT('1', '" + pd + "') WHERE `uid`='1'");
	}
	ui->textEdit->append("创建数据库已完成.\n\n");
	ui->btnUpdateDB->setEnabled(true);
	ui->btnCopyFiles->setEnabled(true);
	ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 已完成.\n\n");
	excuteSetupOperation();
}

void MainWindow::updateDB()
{
	ui->textEdit->append("升级数据库...\n");
	int num1 = 1984;
	int num2 = 2018;
	QStringList sign = QStringList() << "@" << "-" << "^";
	QString pd = "xQ" + sign[0] + QString::number(num1) + sign[1] + "Wf" + sign[2] + "Bj" + QString::number(num2);
	//qDebug() << pd;
	IO_MySQLInterface::InitDBParameters();
	IO_MySQLInterface::SetPassword("");
	if (IO_MySQLInterface::ConnectDb()) {   // default blank password
		qDebug() << "[INF] Set password";
		IO_MySQLInterface::updateDBvalue("`user`", QStringList() << "`Password`", QStringList() << "PASSWORD('" + pd +"')" ,
		                                 "`user`='root'");
		IO_MySQLInterface::query("FLUSH PRIVILEGES;");
	} else {
		IO_MySQLInterface::SetPassword(pd.toLocal8Bit());
		if (IO_MySQLInterface::ConnectDb()) {   // default blank password
			qDebug() << "[INF] Log in OK.";
			//qDebug() << "[INF] Drop previous user" << IO_MySQLInterface::query("DROP user TMDBmanage@localhost;");
			//qDebug() << "[INF] Drop previous user" << IO_MySQLInterface::query("DROP user TMDBmanage@localhost;");
		} else {
			qDebug() << "[ERR] Can't login to DB root.";
		}
	}
	pd = "TMD";
	pd += "B";
	pd += "manage";
	pd += sign[0];
	pd += "XQWF";
	pd += QString::number(num2);
	pd += "0511";

	bool isDBExist = IO_MySQLInterface::query("use `turbidimeter_db`");
	if (!isDBExist) {
		QMessageBox::warning(this, "错误", "数据库不存在! ", QMessageBox::Yes);
		return;
	}
	qDebug() << "[INF] Grant privileges:\t" << IO_MySQLInterface::query("GRANT ALL privileges on `turbidimeter_db`.* to `TMDBmanage`@`localhost`;");
	qDebug() << "[INF] Grand User:\t" << IO_MySQLInterface::query("UPDATE `mysql`.`user` SET `Select_priv`='Y', `File_priv`='Y' WHERE `User` = 'TMDBmanage';");
	IO_MySQLInterface::query("FLUSH PRIVILEGES;");
	ui->textEdit->append(" -更新用户权限\n");

	//QFile sqlFile(":/rec_file/turbidimeter_db.sql");
	QFile sqlFile("turbidimeter_db.sql");
	if (!sqlFile.open(QIODevice::ReadOnly)) {
		qDebug() << "[ERR] Can't open file.";
		return;
	}
	ui->textEdit->append("升级数据库已完成.\n");
	ui->btnUpdateDB->setEnabled(true);
	ui->btnCopyFiles->setEnabled(true);
}

void MainWindow::on_btnUpdateDB_clicked()
{
	ui->btnUpdateDB->setEnabled(false);
	ui->btnCopyFiles->setEnabled(false);
	ui->textEdit->append("启动Wamp服务...\n");
	disconnect(m_cmdProcess, 0, 0, 0);
	m_cmdProcess->start("cmd", QStringList()  << "/c"<< "start /b C:\\wamp\\wampmanager.exe");
	m_updateDBTimerID = startTimer(5000);
}

/**
 * @brief MainWindow::checkOrCreateFolder
 */
void MainWindow::checkOrCreateFolder()
{
	QStringList programFolders;
	QString  folder;
	programFolders << "C:\\XQWF_HC\\images" << "C:\\XQWF_HC\\report" << "C:\\XQWF_HC\\config";
	foreach (folder, programFolders) {
		QDir dir(folder);
		if (!dir.exists()) {
			dir.mkpath(folder);
		}
	}
	ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 已完成.\n\n");
    excuteSetupOperation();
}
QString mysqlDir = "c:\\dbsv\\";
/**
 * @brief MainWindow::extractMySQL
 */
void MainWindow::extractMySQL()
{
    QProcess p(0);
    QStringList args;
    QString command = ".\\7-zip\\7z.exe";
    QString targetFile = "mysql.7z";

    QDir dir(mysqlDir);
    if(!dir.exists()) {
	    dir.mkpath(mysqlDir);
    }

    args << "x";
    args << targetFile;
    args << "-o" + mysqlDir;
    args << "-aoa";

    qDebug() << command << args;
    p.start(command, args);
    p.waitForFinished();//等待完成
	ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 已完成.\n\n");
    excuteSetupOperation();
}

/**
 * @brief MainWindow::startMySQL
 */
void MainWindow::startMySQL()
{
    QProcess p(0);
    QString command = mysqlDir + "mysql\\bin\\mysqld.exe";

    qDebug() << command << p.startDetached(command);
	ui->textEdit->append(m_promotingText[m_operations[m_currCmdIndex]] + " 已完成.\n\n");
    excuteSetupOperation();
}
void MainWindow::timerEvent(QTimerEvent *e)
{
	if (e->timerId() == m_setupDBTimerID) {
		setupDB();
		killTimer(m_setupDBTimerID);
		m_setupDBTimerID = 0;
	} else if (e->timerId() == m_updateDBTimerID) {
		updateDB();
		killTimer(m_updateDBTimerID);
		m_updateDBTimerID = 0;
	} else if (e->timerId() == m_progressBarTimerID) {
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }
}

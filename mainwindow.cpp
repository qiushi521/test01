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
	m_removePreviewsTables(false)
{
	ui->setupUi(this);
	m_operations << "vc2012_redist_x64.exe /silent" << "wampserver2.5-64b.exe /silent"
				 << "start /b C:\\wamp\\wampmanager.exe"
				 << "python-3.6.5-amd64.exe /quiet InstallAllUsers=1";
	m_operationNames << "安装vc2012发布包" << "安装Wamp服务" << "启动Wamp服务"
					 << "安装Python3.6";
	m_currCmdIndex = 0;
	m_cmdProcess = new QProcess(this);
	connect(m_cmdProcess, SIGNAL(finished(int)), this, SLOT(onLastOpComplete(int)));

	//ui->textEdit->setVisible(false);
	ui->btnCopyFiles->setVisible(false);
	//ui->btnStartInstall->setVisible(false);
	//on_btnStartInstall_clicked();

	//setupDB();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_btnStartInstall_clicked()
{
	//m_cmdProcIess->waitForStarted();
	m_currCmdIndex = 0;
	excuteSetupOperation();
}

void MainWindow::excuteSetupOperation()
{
	QString command;
	if (m_currCmdIndex >= m_operations.length()) {
		return;
	}
	ui->textEdit->insertPlainText(m_operationNames[m_currCmdIndex] + "...\n");
	command = m_operations[m_currCmdIndex];
	m_cmdProcess->start("cmd", QStringList()<<"/c"<<command);
}

void MainWindow::onLastOpComplete(int errCode)
{
	if (m_currCmdIndex < m_operations.length()) {
		if (errCode == 0) {
			ui->textEdit->insertPlainText(m_operationNames[m_currCmdIndex] + "已完成.\n\n");
		} else {
			ui->textEdit->insertPlainText(m_operationNames[m_currCmdIndex] + "失败.\n\n");
		}
	} else {
		ui->textEdit->insertPlainText(QString::number(errCode));
	}
	m_currCmdIndex++;
	if (m_currCmdIndex < m_operations.length()) {
		excuteSetupOperation();
	} else {
		ui->textEdit->insertPlainText("复制Python库...\n\n");
		CopyPythonLib *copyPythonLib = new CopyPythonLib(this);
		copyPythonLib->start();
		connect(copyPythonLib, &CopyPythonLib::finished, copyPythonLib, &QObject::deleteLater);
		connect(copyPythonLib, SIGNAL(copyFinished()), this, SLOT(onCopyLibsFinished()));
	}
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
	QString command;
	ui->textEdit->insertPlainText("复制库文件...\n");
	m_currCmdIndex = 100;
	copyDirectoryFiles("python_lib", "C:\\Program Files\\Python36\\Lib\\site-packages", 1);
	//command = "xcopy python_lib\* \"C:\\Program Files\\Python36\\Lib\\site-packages\\\" /s";
	//m_cmdProcess->start("cmd", QStringList()<<"/c"<<command);
}

void MainWindow::onCopyLibsFinished()
{
	ui->textEdit->insertPlainText("全部安装完成");
	setupDB();
	exit(0);
}

void MainWindow::setupDB()
{
	int num1 = 1984;
	int num2 = 2018;
	QStringList sign = QStringList() << "@" << "-" << "^";
	QString pd = "xQ" + sign[0] + QString::number(num1) + sign[1] + "Wf" + sign[2] + "Bj" + QString::number(num2);
	//qDebug() << pd;
	IO_MySQLInterface::InitDBParameters();
	IO_MySQLInterface::SetPassword("");
	if (IO_MySQLInterface::ConnectDb()) {   // default blank password
		qDebug() << "[INF] Set password";
		ui->textEdit->insertPlainText("set password");
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
	qDebug() << "create User:\t" << IO_MySQLInterface::query("create USER `TMDBmanage`@`localhost` IDENTIFIED BY '" + pd + "';");
	bool createDBOK = IO_MySQLInterface::query("create DATABASE `turbidimeter_db`;");
	qDebug() << "grant privileges:\t" << IO_MySQLInterface::query("GRANT ALL privileges on `turbidimeter_db`.* to `TMDBmanage`@`localhost`;");
	qDebug() << "grand User:\t" << IO_MySQLInterface::query("UPDATE `mysql`.`user` SET `Select_priv`='Y', `File_priv`='Y' WHERE `User` = 'TMDBmanage';");
	qDebug() << "use DB:\t" << IO_MySQLInterface::query("use `turbidimeter_db`");
	IO_MySQLInterface::query("FLUSH PRIVILEGES;");

	//QFile sqlFile(":/rec_file/turbidimeter_db.sql");
	QFile sqlFile("turbidimeter_db.sql");
	if (!sqlFile.open(QIODevice::ReadOnly)) {
		qDebug() << "[ERR] Can't open file.";
		return;
	}

	bool needDropTable = true;
	if (createDBOK == false) {
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
			qDebug() << sqlStat << IO_MySQLInterface::query(sqlStat);
			sqlStat.clear();
		}
	}
	pd = "key";
	if (needDropTable) {
		IO_MySQLInterface::query("UPDATE `account_tbl` SET `upassword` = AES_ENCRYPT('1', '" + pd + "') WHERE `uid`='1'");
	}
}

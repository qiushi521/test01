#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "IO_mysqlinterface.h"
#if _MSC_VER >= 1600
	#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);

private slots:
	void on_btnStartInstall_clicked();
	void onLastOpComplete(int errCode);

	void on_btnCopyFiles_clicked();
	void onCopyLibsFinished();

	void setupDB();
	void excuteSetupOperation();

private:
	Ui::MainWindow *ui;
private:
	QString m_currCmd;
	int m_currCmdIndex;
	QStringList m_operations;
	QStringList m_operationNames;
	QProcess* m_cmdProcess;
	int m_timeOverTimerID;
	bool m_removePreviewsTables;
};

#endif // MAINWINDOW_H

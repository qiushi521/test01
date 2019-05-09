#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "IO_mysqlinterface.h"
#if _MSC_VER >= 1600
	#pragma execution_character_set("utf-8")
#endif

#define VER "1.3"

/**
 *
 */
typedef enum install_task_enum {
    IT_VS2012 = 0,
    IT_WAMP,
    IT_START_WAMP,
    IT_V370_DRIVER,
    IT_SETUP_DB,
    IT_BOOT_OPTION,
    IT_MKDIRS,
    IT_NUM
} install_task_e;

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
	void updateDB();
	void excuteSetupOperation();

	void on_btnUpdateDB_clicked();
private:
    void checkOrCreateFolder();

private:
	Ui::MainWindow *ui;
	int m_setupDBTimerID;
    int m_progressBarTimerID;
	int m_updateDBTimerID;
    QString m_promotingText[IT_NUM];
    QString m_cmdText[IT_NUM];
private:
	QString m_currCmd;
	int m_currCmdIndex;
	QList<install_task_e> m_operations;
	QStringList m_operationNames;
	QProcess* m_cmdProcess;
	int m_timeOverTimerID;
	bool m_removePreviewsTables;
	void timerEvent(QTimerEvent *e);
};

#endif // MAINWINDOW_H

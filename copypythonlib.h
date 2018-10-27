#ifndef COPYPYTHONLIB_H
#define COPYPYTHONLIB_H

#include <QObject>
#include <QThread>

class CopyPythonLib : public QThread
{
	Q_OBJECT
public:
	explicit CopyPythonLib(QObject *parent = nullptr);
	void run();
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);

signals:
	void copyFinished();

public slots:
};

#endif // COPYPYTHONLIB_H

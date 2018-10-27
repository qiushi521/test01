#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <QFile>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
void customMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str);
#else
void customMessageHandler(QtMsgType type, const char *msg);
#endif
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	//qInstallMessageHandler(customMessageHandler);
#else
	qInstallMsgHandler(customMessageHandler);
#endif

	MainWindow w;
	w.show();

	return a.exec();
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
void customMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str)
{
	QString txt=str;
#else
void customMessageHandler(QtMsgType type, const char *msg)
{
	QString txt(msg);
#endif
	QFile outFile("debug.log");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outFile);
	ts << txt << endl;
	fprintf(stderr, "%s\n", txt.toLocal8Bit().data());
	fflush(stderr);
}

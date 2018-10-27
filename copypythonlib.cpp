#include "copypythonlib.h"
#include <QDir>

CopyPythonLib::CopyPythonLib(QObject *parent) : QThread(parent)
{

}

void CopyPythonLib::run()
{
	copyDirectoryFiles("python_lib", "C:\\Program Files\\Python36\\Lib\\site-packages", 1);
	emit copyFinished();
}

bool CopyPythonLib::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
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

#include "StringUtils.h"

std::string FuckExivPath(QString fuck_path) {

#ifdef _WIN32
    QTextCodec* gbk = QTextCodec::codecForName("gbk");
    QString strUnicode=gbk->toUnicode(fuck_path.toLocal8Bit().data());
    QByteArray result_bytes=gbk->fromUnicode(strUnicode);
    return std::string(result_bytes);
#else
    return std::string(fuck_path.toStdString().c_str());
#endif
}

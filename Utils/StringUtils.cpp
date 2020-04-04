#include "StringUtils.h"

std::string UTF8toGBK(QString fuck_path)
{
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    QTextCodec *gbk = QTextCodec::codecForName("gbk");

    QString strUnicode = utf8->toUnicode(fuck_path.toLocal8Bit().data());
    QByteArray result_bytes = gbk->fromUnicode(strUnicode);

    return std::string(result_bytes);
}

std::string GBKtoUTF8(QString fuck_path) {
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    QTextCodec *gbk = QTextCodec::codecForName("gbk");

    QString strUnicode = gbk->toUnicode(fuck_path.toLocal8Bit().data());
    QByteArray result_bytes = utf8->fromUnicode(strUnicode);

    return std::string(result_bytes);
}



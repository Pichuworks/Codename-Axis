#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QTextCodec>
#include <QString>

std::string UTF8toGBK(QString fuck_path);

std::string GBKtoUTF8(QString fuck_path);

#endif // STRINGUTILS_H

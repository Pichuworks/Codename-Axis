#ifndef AXISINIT_H
#define AXISINIT_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QObject>
#include <QMutex>

class AxisInit : public QObject
{
    Q_OBJECT
public:
    explicit AxisInit(QObject *parent = 0);
    static AxisInit *Instance() {
        static QMutex mutex;
        if (!self) {
            QMutexLocker locker(&mutex);
            if (!self) {
                self = new AxisInit;
            }
        }
        return self;
    }

    void start();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static AxisInit *self;

signals:

public slots:
};

#endif // AXISINIT_H

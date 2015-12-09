#if defined(SNAPSHOT_LIBRARY)
#define SNAPSHOT_EXPORT Q_DECL_EXPORT
#else
#define SNAPSHOT_EXPORT Q_DECL_IMPORT
#endif

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QtCore/qglobal.h>
#include <QObject>

class SNAPSHOT_EXPORT snapshot :public QObject
{
    Q_OBJECT
public:
    snapshot * genp(){return new snapshot;}
    snapshot(){}
};

#endif // SNAPSHOT_H

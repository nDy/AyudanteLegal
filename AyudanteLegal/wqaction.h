#ifndef WQACTION_H
#define WQACTION_H
#include <QAction>

class WQAction: public QAction
{
private:
    QString* route;
public:
    WQAction(QObject* parent, QString text,QString* file):QAction(parent){
        this->setText(text);
        route = file;
    }
};

#endif // WQACTION_H

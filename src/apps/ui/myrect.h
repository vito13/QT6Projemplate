#include <QObject>

class myrect : public QObject
{
    Q_OBJECT
public:
    explicit myrect(QObject* parent = nullptr);

public slots:
    void doSomething();
};
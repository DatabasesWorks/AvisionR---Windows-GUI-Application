#ifndef SOURCE_H
#define SOURCE_H

#include <QMainWindow>

namespace Ui {
class source;
}

class source : public QMainWindow
{
    Q_OBJECT

public:
    explicit source(QWidget *parent = 0);
    ~source();

private:
    Ui::source *ui;
};

#endif // SOURCE_H

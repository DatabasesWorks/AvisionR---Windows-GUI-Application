#include "source.h"
#include "ui_source.h"

source::source(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::source)
{
    ui->setupUi(this);
}

source::~source()
{
    delete ui;
}

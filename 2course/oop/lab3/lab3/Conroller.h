#ifndef CONROLLER_H
#define CONROLLER_H
#include <QMainWindow>
#include <structures.h>
namespace Ui {
class MainWindow;
}
class Controller
{
public:
    new_params getParams(pick a);
    void setUi(Ui::MainWindow *&temp);


private:
    Ui::MainWindow *ui;
};

#endif // CONROLLER_H

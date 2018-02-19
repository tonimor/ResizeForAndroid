#include "QResizeDialog.h"
#include "QResizeApp.h"

int main(int argc, char *argv[])
{
    QResizeApp app(argc, argv);
    QResizeDialog w;
    w.show();
    return app.exec();
}

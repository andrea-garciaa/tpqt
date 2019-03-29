#include <QApplication>
#include "mafenetre.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MaFenetre mafenetre(nullptr);
    mafenetre.show();

    return app.exec();
}

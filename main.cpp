#include "TDBApplication.h"
#include "TDBMainWindow.h"

int main (int argc, char** argv)
{
    TDBApplication app(argc, argv);

    int i = app.parse();

    if( i != 0 )
        exit(i<0?0:i);
    else
    {
        TDBMainWindow mythe;
        mythe.show();

        return app.exec();
    }
}

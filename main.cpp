#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("房贷计算");

    QFont font1;
    font1.setFamily(QString::fromUtf8("Tahoma"));
    font1.setPointSize(13);
    w.setFont(font1);       //设置窗口显示字体
    w.show();

    return a.exec();
}

#include <QCoreApplication>
#include <QDebug>

#include <QFrame>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>


namespace AboutBox
{
    class Window : public QMainWindow
    {
    Q_OBJECT
    public:
        Window()
        {
            buttonShowAbout.setText("About...");
            buttonShowAbout.move(10, 10);
            connect(&buttonShowAbout, &QPushButton::clicked, [&] {
                QMessageBox::about(this, "About dialog", "About dialog\n\nversion 1.0.0 (1.0)\n\nAbout dialog description.\n\nCopyright © 2020 Gammasoft.\nAll rights reserved.");
            });

            buttonShowAboutQt.setText("AboutQt...");
            buttonShowAboutQt.move(100, 10);
            connect(&buttonShowAboutQt, &QPushButton::clicked, [&] {
                QMessageBox::aboutQt(this, "About dialog");
            });

            setCentralWidget(&frame);
            setWindowTitle("About box example");
            resize(300, 300);
        }

    private:
        QFrame frame;
        QPushButton buttonShowAbout {&frame};
        QPushButton buttonShowAboutQt {&frame};
    };

    int test(int argc, char *argv[])
    {
        QApplication application(argc, argv);
        Window window;
        window.show();
        return QApplication::exec();
    }
}


int main(int argc, char *argv[])
{
    AboutBox::test(argc, argv);
    return EXIT_SUCCESS;
}

#include "main.moc"

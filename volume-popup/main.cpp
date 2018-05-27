/*
    Volume-popup - simple popup\cloud for Box-like WM's.
    Copyright (C) 2018 Volk_Milit (aka Ja'Virr-Dar)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QTimer>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPixmap>
#include <QtSvg/QSvgRenderer>
#include <QImage>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QDebug>
#include <QDesktopWidget>
#include <QImage>
#include <QColor>

class MyWindowWidget : public QWidget
{
public:
    MyWindowWidget(QWidget *parent)
        : QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Popup)
    {
        this->setWindowTitle("volume-popup");

        int x = QApplication::desktop()->availableGeometry().width() / 2 - this->width();
        int y = QApplication::desktop()->availableGeometry().height() - this->height() * 10;
        this->move(x, y);

        QString icons;
        QString theme;
        QFile file(QDir::homePath() + "/.gtkrc-2.0");
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QString line = in.readLine();
                if (line.contains("gtk-icon-theme-name"))
                    icons = line.split("=").at(1);
                if (line.contains("gtk-theme-name"))
                    theme = line.split("=").at(1);
            }
        }
        file.close();

        icons.remove("\"");
        theme.remove("\"");

        QString volumeicon;
        QDirIterator it(QDir::homePath() + "/.icons/" + icons,\
                        QDir::AllEntries | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            if (it.next().contains("audio-volume-high"))
            {
                volumeicon = it.filePath();
                break;
            }
        }

        QString tooltipBgColor;
        QString tooltipFgColor;
        theme = QDir::homePath() + "/.themes/" + theme + "/gtk-2.0/gtkrc";
        QFile gtkrc(theme);
        if (gtkrc.open(QIODevice::ReadOnly))
        {
            QTextStream ingtk(&gtkrc);
            while(!ingtk.atEnd())
            {
                QString line = ingtk.readLine();
                if (line.contains("tooltip_bg_color:"))
                    tooltipBgColor = line.split(":").at(1);
                if (line.contains("tooltip_fg_color:"))
                    tooltipFgColor = line.split(":").at(1);
            }
        }

        tooltipBgColor.remove("\"");
        tooltipFgColor.remove("\"");
        tooltipFgColor.remove(" #");

        QString sr = tooltipFgColor.mid(1, 2);
        QString sg = tooltipFgColor.mid(2, 2);
        QString sb = tooltipFgColor.mid(4, 5);
        const unsigned int r = sr.toUInt(nullptr, 16);
        const unsigned int g = sg.toUInt(nullptr, 16);
        const unsigned int b = sb.toUInt(nullptr, 16);

        QVariant p;
        if (QApplication::arguments().size() > 1)
            p = QApplication::arguments().at(1);
        else
            p = 0;

        QVBoxLayout *layout = new QVBoxLayout;

        QProgressBar *progressbar = new QProgressBar;
        progressbar->setValue(p.toInt());

        QColor color;
        color.setRgb(r, g, b);

        QPixmap pix;
        pix.load(volumeicon);
        pix = pix.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QImage tmp = pix.toImage();
        for (auto x = 0; x < tmp.width(); x++)
        {
            for (auto y = 0; y < tmp.height(); y++)
            {
                color.setAlpha(tmp.pixelColor(x, y).alpha());
                tmp.setPixelColor(x, y, color);
            }
        }
        pix = QPixmap::fromImage(tmp);

        QLabel *label = new QLabel;
        label->setPixmap(pix);
        label->setAlignment(Qt::AlignCenter);

        layout->addWidget(label);
        layout->addWidget(progressbar);

        this->setLayout(layout);

        this->setStyleSheet(".QWidget{background-color: " + tooltipBgColor + ";\
                                    border: 0px solid black; border-radius: 3px;}");

        this->setWindowOpacity(0.8);

        layout->deleteLater();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;

    MyWindowWidget widget(&window);
    widget.show();

    QTimer::singleShot(1000, &app, SLOT(quit()));

    return app.exec();
}

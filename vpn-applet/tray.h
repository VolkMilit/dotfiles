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

#ifndef TRAY_H
#define TRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QCoreApplication>
#include <QProcess>
#include <QDirIterator>
#include <QDir>
#include <QFile>
#include <QTextStream>

class tray : public QWidget
{
    Q_OBJECT

    public:
        explicit tray(QWidget *parent = 0, const QString &ovpnfile = "");
        virtual ~tray();
        void create();

    private slots:
        void vpn();
        void tor();
        void updateMenu(QSystemTrayIcon::ActivationReason reason);

    private:
        bool checkProcess(const QString &name);

        QAction *a_quit;
        QAction *a_vpn;
        QAction *a_tor;

        QMenu *tmenu;

        QString m_ovpnfile;
};

#endif // TRAY_H

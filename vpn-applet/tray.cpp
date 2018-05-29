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

#include "tray.h"
#include <QDebug>

tray::tray(QWidget *parent, const QString &ovpnfile) : QWidget(parent)
{
    a_quit = new QAction("Quit", this);
    connect(a_quit, &QAction::triggered, qApp, &QCoreApplication::quit);

    a_vpn = new QAction("VPN", this);
    a_vpn->setCheckable(true);
    connect(a_vpn, &QAction::triggered, this, &tray::vpn);

    a_tor = new QAction("Tor", this);
    a_tor->setCheckable(true);
    connect(a_tor, &QAction::triggered, this, &tray::tor);

    tmenu = new QMenu(this);
    tmenu->addAction(a_vpn);
    tmenu->addAction(a_tor);
    tmenu->addSeparator();
    tmenu->addAction(a_quit);

    QFile ovpn(ovpnfile);
    if (!ovpnfile.isEmpty() && ovpn.exists())
        m_ovpnfile = ovpnfile;
    else
        a_vpn->setEnabled(false);
}

tray::~tray()
{
    delete a_quit;
    delete a_vpn;
    delete a_tor;
    delete tmenu;
}

bool tray::checkProcess(const QString &name)
{
    bool found = false;
    QDirIterator it("/proc");

    QString line;

    while (it.hasNext())
    {
        QFile file(it.next() + "/cmdline");

        if (!file.exists())
            continue;

        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        line = in.readLine();

        if (line.contains(name))
        {
            file.close();
            found = true;
            break;
        }

        file.close();
    }

    return found;
}

void tray::updateMenu(QSystemTrayIcon::ActivationReason reason)
{
    if (checkProcess("/usr/bin/tor"))
        a_tor->setChecked(true);
    else
        a_tor->setChecked(false);

    if (checkProcess("openvpn"))
        a_vpn->setChecked(true);
    else
        a_vpn->setChecked(false);

    if (reason != 1)
    {
        tmenu->popup(QCursor::pos());
        tmenu->show();
    }
}

void tray::vpn()
{
    if (checkProcess("openvpn"))
        return;

    QProcess *proc = new QProcess;
    proc->start("x-terminal-emulator -e sudo openvpn " + m_ovpnfile);
}

void tray::tor()
{
    QString startstop = "start";
    if (checkProcess("/usr/bin/tor"))
        startstop = "stop";

    QProcess *proc = new QProcess;
    proc->start("x-terminal-emulator -e sudo service tor " + startstop);
}

void tray::create()
{
    QSystemTrayIcon *ticon = new QSystemTrayIcon(this);
    ticon->setIcon(QIcon::fromTheme("internet-services"));
    ticon->setContextMenu(tmenu);

    connect(ticon, &QSystemTrayIcon::activated, this, &tray::updateMenu);

    ticon->show();
}

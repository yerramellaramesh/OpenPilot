/**
 ******************************************************************************
 *
 * @file       TCPtelemetryconfiguration.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   map
 * @{
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "tcptelemetryconfiguration.h"
#include <QtCore/QDataStream>
#include <coreplugin/icore.h>

TCPtelemetryConfiguration::TCPtelemetryConfiguration(QString classId, const QByteArray &state, QObject *parent) :
    IUAVGadgetConfiguration(classId, parent),
    m_HostName("127.0.0.1"),
    m_Port(1000),
    m_UseTCP(1)
{
    settings = Core::ICore::instance()->settings();
}
TCPtelemetryConfiguration::~TCPtelemetryConfiguration()
{
}
IUAVGadgetConfiguration *TCPtelemetryConfiguration::clone()
{
    TCPtelemetryConfiguration *m = new TCPtelemetryConfiguration(this->classId());
    m->m_Port = m_Port;
    m->m_HostName = m_HostName;
    m->m_UseTCP = m_UseTCP;
    return m;
}

QByteArray TCPtelemetryConfiguration::saveState() const
{
   QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << m_Port;
    stream << m_HostName;
    stream << m_UseTCP;
    return bytes;

}


void TCPtelemetryConfiguration::savesettings() const
{
    settings->beginGroup(QLatin1String("TCPtelemetryconnection"));

        settings->beginWriteArray("Current");
        settings->setArrayIndex(0);
        settings->setValue(QLatin1String("HostName"), m_HostName);
        settings->setValue(QLatin1String("Port"), m_Port);
        settings->setValue(QLatin1String("UseTCP"), m_UseTCP);
        settings->endArray();
        settings->endGroup();
}


void TCPtelemetryConfiguration::restoresettings()
{
    settings->beginGroup(QLatin1String("TCPtelemetryconnection"));

        settings->beginReadArray("Current");
        settings->setArrayIndex(0);
        m_HostName = (settings->value(QLatin1String("HostName"), tr("")).toString());
        m_Port = (settings->value(QLatin1String("Port"), tr("")).toInt());
        m_UseTCP = (settings->value(QLatin1String("UseTCP"), tr("")).toInt());
        settings->endArray();
        settings->endGroup();


}

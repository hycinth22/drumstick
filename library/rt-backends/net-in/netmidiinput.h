/*
    Drumstick RT (realtime MIDI In/Out)
    Copyright (C) 2009-2020 Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NETMIDIINPUT_H
#define NETMIDIINPUT_H

#include <QObject>
#include <QHostAddress>
#include <QtPlugin>
#include <drumstick/rtmidiinput.h>

namespace drumstick {
namespace rt {

    const QString STR_ADDRESS_IPV4(QLatin1Literal("225.0.0.37"));
    const QString STR_ADDRESS_IPV6(QLatin1Literal("ff12::37"));
    const int MULTICAST_PORT(21928);
    const int LAST_PORT(21948);

    class NetMIDIInputPrivate;

    class NetMIDIInput : public MIDIInput
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "net.sourceforge.drumstick.rt.MIDIInput/2.0")
        Q_INTERFACES(drumstick::rt::MIDIInput)
    public:
        explicit NetMIDIInput(QObject *parent = nullptr);

        // MIDIInput interface
    public:
        virtual void initialize(QSettings* settings) override;
        virtual QString backendName() override;
        virtual QString publicName() override;
        virtual void setPublicName(QString name) override;
        virtual QList<MIDIConnection> connections(bool advanced) override;
        virtual void setExcludedConnections(QStringList conns) override;
        virtual void open(const MIDIConnection& name) override;
        virtual void close() override;
        virtual MIDIConnection currentConnection() override;
        virtual void setMIDIThruDevice(MIDIOutput *device) override;
        virtual void enableMIDIThru(bool enable) override;
        virtual bool isEnabledMIDIThru() override;

    private:
        NetMIDIInputPrivate * const d;
    };

}}

#endif // NETMIDIINPUT_H

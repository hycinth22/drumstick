/*
    Drumstick Backend using the ALSA Sequencer
    Copyright (C) 2009-2010 Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef ALSAMIDIInput_H
#define ALSAMIDIInput_H

#include <QObject>
#include <QtPlugin>
#include "rtmidiinput.h"

namespace drumstick {
namespace rt {

    class ALSAMIDIInput: public MIDIInput
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "net.sourceforge.drumstick.rt.MIDIInput")
        Q_INTERFACES(drumstick::rt::MIDIInput)

    public:
        ALSAMIDIInput(QObject *parent = 0);
        virtual ~ALSAMIDIInput();

        // MIDIInput interface
        virtual QString backendName();
        virtual QString publicName();
        virtual void setPublicName(QString name);
        virtual QStringList connections(bool advanced);
        virtual void setExcludedConnections(QStringList conns);
        virtual void open(QString name);
        virtual void close();
        virtual QString currentConnection();

        virtual void setMIDIThruDevice(MIDIOutput *device);
        virtual void enableMIDIThru(bool enable);
        virtual bool isEnabledMIDIThru();

    private:
        class ALSAMIDIInputPrivate;
        ALSAMIDIInputPrivate * const d;
    };

}}

#endif /* ALSAMIDIInput_H */

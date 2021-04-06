/*
    Drumstick RT (realtime MIDI In/Out)
    Copyright (C) 2009-2021 Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "synthoutput.h"

namespace drumstick { namespace rt {

SynthOutput::SynthOutput(QObject *parent) : MIDIOutput(parent)
{
    m_synth = new SynthEngine;
    m_synth->moveToThread(&m_synthThread);
    connect(&m_synthThread, &QThread::started,  m_synth, &SynthEngine::initialize);
    connect(&m_synthThread, &QThread::finished, m_synth, &QObject::deleteLater);
}

SynthOutput::~SynthOutput()
{
    if (m_synthThread.isRunning()) {
        m_synthThread.quit();
        m_synthThread.wait();
    }
}

QStringList SynthOutput::getAudioDrivers()
{
    return m_synth->getVariantData("audiodrivers").toStringList();
}

void SynthOutput::initialize(QSettings *settings)
{
    m_synth->readSettings(settings);
    m_synthThread.start(QThread::HighPriority);
}

QString SynthOutput::backendName()
{
    return SynthEngine::QSTR_FLUIDSYNTH;
}

QString SynthOutput::publicName()
{
    return SynthEngine::QSTR_FLUIDSYNTH;
}

void SynthOutput::setPublicName(QString name)
{
    Q_UNUSED(name)
}

QList<MIDIConnection> SynthOutput::connections(bool advanced)
{
    Q_UNUSED(advanced)
    return QList<MIDIConnection>{MIDIConnection(SynthEngine::QSTR_FLUIDSYNTH, SynthEngine::QSTR_FLUIDSYNTH)};
}

void SynthOutput::setExcludedConnections(QStringList conns)
{
    Q_UNUSED(conns)
}

void SynthOutput::open(const MIDIConnection& name)
{
    Q_UNUSED(name)
    m_synth->open();
}

void SynthOutput::close()
{
    m_synth->close();
}

MIDIConnection SynthOutput::currentConnection()
{
    return m_synth->currentConnection();
}

void SynthOutput::sendNoteOff(int chan, int note, int vel)
{
    m_synth->noteOff(chan, note, vel);
}

void SynthOutput::sendNoteOn(int chan, int note, int vel)
{
    m_synth->noteOn(chan, note, vel);
}

void SynthOutput::sendKeyPressure(int chan, int note, int value)
{
    Q_UNUSED(chan)
    Q_UNUSED(note)
    Q_UNUSED(value)
}

void SynthOutput::sendController(int chan, int control, int value)
{
    m_synth->controlChange(chan, control, value);
}

void SynthOutput::sendProgram(int chan, int program)
{
    m_synth->setInstrument(chan, program);
}

void SynthOutput::sendChannelPressure(int chan, int value)
{
    Q_UNUSED(chan)
    Q_UNUSED(value)
}

void SynthOutput::sendPitchBend(int chan, int value)
{
    m_synth->bender(chan, value);
}

void SynthOutput::sendSysex(const QByteArray &data)
{
    Q_UNUSED(data)
}

void SynthOutput::sendSystemMsg(const int status)
{
    Q_UNUSED(status)
}

} // namespace rt
} // namespace drumstick

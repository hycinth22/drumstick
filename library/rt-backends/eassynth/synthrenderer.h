/*
    Sonivox EAS Synthesizer for Qt applications
    Copyright (C) 2016-2023, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SYNTHRENDERER_H_
#define SYNTHRENDERER_H_

#include <QObject>
#include <QReadWriteLock>
#include <QWaitCondition>
#include <QSettings>
#include <pulse/simple.h>
#include <drumstick/rtmidioutput.h>
#include "eas.h"

namespace drumstick { namespace rt {

    class SynthRenderer : public QObject
    {
        Q_OBJECT

    public:
        explicit SynthRenderer(QObject *parent = nullptr);
        virtual ~SynthRenderer();

        void stop();
        bool stopped();
        void initReverb(int reverb_type);
        void initChorus(int chorus_type);
        void setReverbWet(int amount);
        void setChorusLevel(int amount);
        void sendMessage(int m0);
        void sendMessage(int m0, int m1);
        void sendMessage(int m0, int m1, int m2);
        MIDIConnection connection();
        void setBufferTime(int milliseconds);
        void initialize(QSettings* settings);
        bool getStatus() const;
        QStringList getDiagnostics() const;
        void setCondition(QWaitCondition *cond);
        QString getLibVersion();
        QString getSoundFont();

        static const QString QSTR_PREFERENCES;
        static const QString QSTR_BUFFERTIME;
        static const QString QSTR_REVERBTYPE;
        static const QString QSTR_REVERBAMT;
        static const QString QSTR_CHORUSTYPE;
        static const QString QSTR_CHORUSAMT;
        static const QString QSTR_SONIVOXEAS;
        static const QString QSTR_SOUNDFONT;

    private:
        void initEAS();
        void initPulse();
        void uninitEAS();
        void uninitPulse();
        void writeMIDIData(const QByteArray& message);
        void initSoundfont();

    public slots:
        void run();

    signals:
        void finished();

    private:
        bool m_Stopped;
        QReadWriteLock m_mutex;
        QWaitCondition *m_rendering;
        /* SONiVOX EAS */
        int m_sampleRate, m_bufferSize, m_channels;
        EAS_DATA_HANDLE m_easData;
        EAS_HANDLE m_streamHandle;
        QString m_soundfont;
        /* pulseaudio */
        int m_bufferTime;
        pa_simple *m_pulseHandle;
        /* object properties */
        bool m_status;
        QStringList m_diagnostics;
        EAS_U32 m_libVersion;
    };

}} /* drumstick::rt */
#endif /*SYNTHRENDERER_H_*/

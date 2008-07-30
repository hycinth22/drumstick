/*
    MIDI Sequencer C++ library 
    Copyright (C) 2006-2008, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along 
    with this program; if not, write to the Free Software Foundation, Inc., 
    51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.    
*/
 
#ifndef INCLUDED_PLAYTHREAD_H
#define INCLUDED_PLAYTHREAD_H

#include "commons.h"
#include "event.h"
#include <QThread>
#include <QMutex>

namespace ALSA 
{
namespace Sequencer 
{

class MidiClient; 
class MidiQueue;

class SequencerOutputThread: public QThread
{
    Q_OBJECT

public:
    SequencerOutputThread(MidiClient *seq, int portId);
    virtual ~SequencerOutputThread(); 

    virtual void run();
    bool stopped();
    void stop();
    virtual unsigned int getInitialPosition() { return 0; }
    virtual unsigned int getEchoResolution() { return 0; }

    /* Virtual methods to be reimplemented */
    virtual bool hasNext() = 0;
    virtual SequencerEvent* nextEvent() = 0;

signals:
    void finished();
    
protected:    
    void shutupSound();
    void sendEchoEvent(int tick);
    void sendSongEvent(SequencerEvent* ev);
    void drainOutput();
    void syncOutput();

private:
    MidiClient *m_MidiClient;
    int m_PortId;
    bool m_Stopped;
    MidiQueue *m_Queue;
    int m_QueueId;
    int m_npfds;
    pollfd* m_pfds;
    QMutex m_mutex;
};

}
}

#endif /*INCLUDED_PLAYTHREAD_H*/

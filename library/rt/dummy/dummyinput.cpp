#include "dummyinput.h"

namespace drumstick {
namespace rt {

QString DummyInput::backendName()
{
    return "DUMMY";
}

QString DummyInput::publicName()
{
    return QString();
}

void DummyInput::setPublicName(QString name)
{
}

QStringList DummyInput::connections(bool advanced)
{
    return QStringList();
}

void DummyInput::setExcludedConnections(QStringList conns)
{
}

QString DummyInput::currentConnection()
{
    return QString();
}

void DummyInput::open(QString name)
{
}

void DummyInput::close()
{
}

void DummyInput::setMIDIThruDevice(MIDIOutput *device)
{
}

void DummyInput::enableMIDIThru(bool enable)
{
}

bool DummyInput::isEnabledMIDIThru()
{
    return false;
}

}}




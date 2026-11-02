#include "../include/SpaceEvent.h"

SpaceEvent::SpaceEvent(const std::string& name, int severity)
    : eventName(name), severity(severity) {
    if (this->severity < 1) this->severity = 1;
}

std::string SpaceEvent::getEventName() const { return eventName; }
int SpaceEvent::getSeverity() const { return severity; }

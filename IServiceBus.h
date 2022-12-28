#ifndef AUTOBRAKE_ISERVICEBUS_H
#define AUTOBRAKE_ISERVICEBUS_H

#include <functional>
#include "Events.h"


using SpeedUpdateCallback = std::function<void(const Events::SpeedUpdate &)>;
using CarDetectedCallback = std::function<void(const Events::CarDetected &)>;

struct IServiceBus {
    virtual ~IServiceBus() = default;

    virtual void publish(const Events::Event &) = 0;

    virtual void subscribe(SpeedUpdateCallback) = 0;

    virtual void subscribe(CarDetectedCallback) = 0;
};

#endif //AUTOBRAKE_ISERVICEBUS_H

#ifndef AUTOBRAKE_MOCKSERVICEBUS_H
#define AUTOBRAKE_MOCKSERVICEBUS_H

#include "IServiceBus.h"
#include "Events.h"

class MockServiceBus : public IServiceBus {
public:
    Events::BrakeCommand last_break_command{0};
    Events::SpeedUpdate last_speed_command{0};
    Events::CarDetected last_detected_command{0,0};
    int break_commands_published{};
    int speed_commands_published{};
    int detected_commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};

    void publish(const Events::Event &cmd) override {
        if (auto breakCmd = dynamic_cast<const Events::BrakeCommand *>(&cmd)) {
            break_commands_published++;
            last_break_command = *breakCmd;
        } else if (auto speedCmd = dynamic_cast<const Events::SpeedUpdate *>(&cmd)) {
            speed_commands_published++;
            last_speed_command = *speedCmd;
        } else if (auto detectedCmd = dynamic_cast<const Events::CarDetected *>(&cmd)) {
            detected_commands_published++;
            last_detected_command = *detectedCmd;
        }
    }

    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    }

    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    }
};

#endif //AUTOBRAKE_MOCKSERVICEBUS_H

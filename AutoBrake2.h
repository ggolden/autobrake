#ifndef AUTOBRAKE_AUTOBRAKE2_H
#define AUTOBRAKE_AUTOBRAKE2_H

#include "IServiceBus.h"
#include "Events.h"

class AutoBrake2 {
    double collision_threshold_s;
    double speed_mps;
public:
    explicit AutoBrake2(IServiceBus &bus) : collision_threshold_s{5}, speed_mps{} {
        bus.subscribe([this](const Events::SpeedUpdate &update) {
            speed_mps = update.velocity_mps;
        });

        bus.subscribe([this, &bus](const Events::CarDetected &detected) {
            const auto relative_velocity_mps = speed_mps - detected.velocity_mps;
            const auto time_to_collision_s = detected.distance_m / relative_velocity_mps;
            if (time_to_collision_s > 0 && time_to_collision_s <= collision_threshold_s) {
                bus.publish(Events::BrakeCommand{time_to_collision_s});
            }

            //bus.publish(Events::SpeedUpdate{100});
        });
    }

    void set_collision_threshold_s(double x) {
        if (x >= 1) {
            collision_threshold_s = x;
        } else {
            collision_threshold_s = 1;
        }
    }

    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }

    double get_speed_mps() const {
        return speed_mps;
    }
};

#endif //AUTOBRAKE_AUTOBRAKE2_H

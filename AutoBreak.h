//
// Created by Glenn R. Golden on 12/27/22.
//

#ifndef AUTOBREAK_AUTOBREAK_H
#define AUTOBREAK_AUTOBREAK_H

#include "Events.h"

class AutoBreak {
public:

    template<typename T>
    struct AutoBrake {
        AutoBrake(const T &publish) : collision_threshold_s{5}, speed_mps{}, publish{publish} {}

        void observe(const Events::SpeedUpdate &cd) {
            speed_mps = cd.velocity_mps;
        }

        void observe(const Events::CarDetected &cd) {
            const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
            const auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
            if (time_to_collision_s > 0 && time_to_collision_s <= collision_threshold_s) {
                publish(Events::BrakeCommand{time_to_collision_s});
            }
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

    private:
        double collision_threshold_s;
        double speed_mps;
        const T &publish;
    };
};


#endif //AUTOBREAK_AUTOBREAK_H

//
// Created by Glenn R. Golden on 12/27/22.
//

#ifndef AUTOBREAK_EVENTS_H
#define AUTOBREAK_EVENTS_H


class Events {
public:

    struct SpeedUpdate {
        double velocity_mps;
    };

    struct CarDetected {
        double distance_m;
        double velocity_mps;
    };

    struct BrakeCommand {
        double time_to_collision_s;
    };

};


#endif //AUTOBREAK_EVENTS_H

#ifndef AUTOBRAKE_EVENTS_H
#define AUTOBRAKE_EVENTS_H

namespace Events {
    class Event {
    public:
        virtual ~Event() = default;
    };

    class SpeedUpdate : public Event {
    public:
        double velocity_mps;
        explicit SpeedUpdate(double velocityMps) : velocity_mps(velocityMps) {}
    };

    class CarDetected : public Event {
    public:
        double distance_m;
        double velocity_mps;
        CarDetected(double distanceM, double velocityMps) : distance_m(distanceM),
                                                            velocity_mps(velocityMps) {}
    };

    class BrakeCommand : public Event {
    public:
        double time_to_collision_s;
        explicit BrakeCommand(double timeToCollisionS) : time_to_collision_s(timeToCollisionS) {}
    };
};

#endif //AUTOBRAKE_EVENTS_H

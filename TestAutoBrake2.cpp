#include <iostream>

#include "TestAutoBrake2.h"

#include "Assert.h"
#include "AutoBrake2.h"
#include "Events.h"
#include "Harness.h"
#include "MockServiceBus.h"

struct TestAutoBrake2::Private {
    static void initial_speed_is_zero() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
    }

    static void initial_threshold_is_5() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        assert_that(auto_brake.get_collision_threshold_s() == 5L, "collision_threshold not equal 5");
    }

    static void threshold_is_not_less_than_1() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        auto_brake.set_collision_threshold_s(0.9);
        assert_that(auto_brake.get_collision_threshold_s() == 1L, "collision_threshold less than 1");
    }

    static void threshold_is_configurable() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        auto_brake.set_collision_threshold_s(1);
        assert_that(auto_brake.get_collision_threshold_s() == 1L, "collision_threshold not configurable to 1");
        auto_brake.set_collision_threshold_s(10.5);
        assert_that(auto_brake.get_collision_threshold_s() == 10.5, "collision_threshold not configurable to 10");
        auto_brake.set_collision_threshold_s(100);
        assert_that(auto_brake.get_collision_threshold_s() == 100L, "collision_threshold not configurable to 10");
    }

    static void speed_is_saved() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        bus.speed_update_callback(Events::SpeedUpdate{100L});
        assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");
        bus.speed_update_callback(Events::SpeedUpdate{50L});
        assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");
        bus.speed_update_callback(Events::SpeedUpdate{0L});
        assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
    }

    static void alert_when_imminent() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        auto_brake.set_collision_threshold_s(10L);
        bus.speed_update_callback(Events::SpeedUpdate{100L});
        bus.car_detected_callback(Events::CarDetected{100L, 0L});
        assert_that(bus.break_commands_published == 1, "expecting 1 break command published");
        assert_that(bus.speed_commands_published == 0, "expecting NO speed commands published");
        assert_that(bus.detected_commands_published == 0, "expecting NO detected commands published");
    }

    static void no_alert_when_not_imminent() {
        MockServiceBus bus{};
        AutoBrake2 auto_brake{bus};
        auto_brake.set_collision_threshold_s(2L);
        bus.speed_update_callback(Events::SpeedUpdate{100L});
        bus.car_detected_callback(Events::CarDetected{1000L, 50L});
        assert_that(bus.break_commands_published == 0, "expecting NO break commands published");
        assert_that(bus.speed_commands_published == 0, "expecting NO speed commands published");
        assert_that(bus.detected_commands_published == 0, "expecting NO detected commands published");
    }
};

void TestAutoBrake2::test() {
    std::cout << "AutoBrake2 Tests:" << std::endl;

    Harness::run_test(Private::initial_speed_is_zero, "initial_speed_is_zero");
    Harness::run_test(Private::initial_threshold_is_5, "initial_threshold_is_5");
    Harness::run_test(Private::threshold_is_configurable, "threshold_is_configurable");
    Harness::run_test(Private::threshold_is_not_less_than_1, "threshold_is_not_less_than_1");
    Harness::run_test(Private::speed_is_saved, "speed_is_saved");
    Harness::run_test(Private::alert_when_imminent, "alert_when_imminent");
    Harness::run_test(Private::no_alert_when_not_imminent, "no_alert_when_not_imminent");
}

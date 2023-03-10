#include <iostream>

#include "TestAutoBrake.h"

#include "Assert.h"
#include "AutoBrake.h"
#include "Events.h"
#include "Harness.h"

struct TestAutoBrake::Private {
    static void initial_speed_is_zero() {
        AutoBrake auto_brake{[](const Events::Event &) {}};
        assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
    }

    static void initial_threshold_is_5() {
        AutoBrake auto_brake{[](const Events::Event &) {}};
        assert_that(auto_brake.get_collision_threshold_s() == 5L, "collision_threshold not equal 5");
    }

    static void threshold_is_not_less_than_1() {
        AutoBrake auto_brake{[](const Events::Event &) {}};
        auto_brake.set_collision_threshold_s(0.9);
        assert_that(auto_brake.get_collision_threshold_s() == 1L, "collision_threshold less than 1");
    }

    static void threshold_is_configurable() {
        AutoBrake auto_brake{[](const Events::Event &) {}};
        auto_brake.set_collision_threshold_s(1);
        assert_that(auto_brake.get_collision_threshold_s() == 1L, "collision_threshold not configurable to 1");
        auto_brake.set_collision_threshold_s(10.5);
        assert_that(auto_brake.get_collision_threshold_s() == 10.5, "collision_threshold not configurable to 10");
        auto_brake.set_collision_threshold_s(100);
        assert_that(auto_brake.get_collision_threshold_s() == 100L, "collision_threshold not configurable to 10");
    }

    static void speed_is_saved() {
        AutoBrake auto_brake{[](const Events::Event &) {}};
        auto_brake.observe(Events::SpeedUpdate{100L});
        assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");
        auto_brake.observe(Events::SpeedUpdate{50L});
        assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");
        auto_brake.observe(Events::SpeedUpdate{0L});
        assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
    }

    static void alert_when_imminent() {
        int brake_commands_published{};
        AutoBrake auto_brake{[&brake_commands_published](const Events::Event &event) {
            if (dynamic_cast<const Events::BrakeCommand *>(&event)) {
                brake_commands_published++;
            } else {
                assert_that(false, "Some other event was published");
            }
        }};
        auto_brake.set_collision_threshold_s(10L);
        auto_brake.observe(Events::SpeedUpdate{100L});
        auto_brake.observe(Events::CarDetected{100L, 0L});
        assert_that(brake_commands_published == 1, "brake commands published not one");
    }

    static void no_alert_when_not_imminent() {
        int brake_commands_published{};
        AutoBrake auto_brake{[&brake_commands_published](const Events::Event &event) {
            if (dynamic_cast<const Events::BrakeCommand *>(&event)) {
                brake_commands_published++;
            } else {
                assert_that(false, "Some other event was published");
            }
        }};
        auto_brake.set_collision_threshold_s(2L);
        auto_brake.observe(Events::SpeedUpdate{100L});
        auto_brake.observe(Events::CarDetected{1000L, 50L});
        assert_that(brake_commands_published == 0, "brake command published");
    }
};

void TestAutoBrake::test() {
    std::cout << "AutoBrake Tests:" << std::endl;

    Harness::run_test(Private::initial_speed_is_zero, "initial_speed_is_zero");
    Harness::run_test(Private::initial_threshold_is_5, "initial_threshold_is_5");
    Harness::run_test(Private::threshold_is_configurable, "threshold_is_configurable");
    Harness::run_test(Private::threshold_is_not_less_than_1, "threshold_is_not_less_than_1");
    Harness::run_test(Private::speed_is_saved, "speed_is_saved");
    Harness::run_test(Private::alert_when_imminent, "alert_when_imminent");
    Harness::run_test(Private::no_alert_when_not_imminent, "no_alert_when_not_imminent");
}


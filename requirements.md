1. AutoBrake will consider the car’s initial speed zero.

1. AutoBrake should have a configurable sensitivity threshold based on how many seconds are forecast until a collision. 

3. The sensitivity must not be less than 1 second.
4. The default sensitivity is 5 seconds.
1. AutoBrake must save the car’s speed in between SpeedUpdate observations.

1. Each time AutoBrake observes a CarDetected event, it must publish a BrakeCommand if a collision is forecasted in less time than the configured sensitivity threshold.

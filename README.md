# husky_codes
ROS packages to control and navigate the Husky UGV from Clearpath

- simple_controller: simple ROS package to move UGV to a target in a straight motion WITHOUT considering obstacle avoidance.
- husky_navigation: customized ROS package to navigate Husky using move_base and amcl. This package provides an obstacle avoidance capability during its navigation based on the global and local path planning.
- comm_ugv: /tf publisher of the detected object after receiving pose values of the object from Jetson TX2 in the case of Jetson TX2 running on a separate ROS Master. The onboard computer of the UGV can be connected to the Jetson TX2 through an Ethernet communication. In this case, first the data from the Jetson TX2 is sent to the UGV computer through the Ethernet communication. Afterwards, /tf is published in the UGV computer based on the data received from the Jetson TX2.

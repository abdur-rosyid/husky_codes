# husky_codes
Packages to control and navigate the Husky UGV from Clearpath

- simple_controller: simple package to move UGV to a target in a straight motion WITHOUT considering obstacle avoidance.
- husky_navigation: customized package to navigate Husky using move_base and amcl.
- comm_ugv: /tf publisher of the detected object after receiving pose values of the object from Jetson TX2 in the case of Jetson TX2 running on a separate ROS Master. The onboard computer of the UGV can be connected to the Jetson TX2 through an Ethernet communication.

[Webots](https://www.cyberbotics.com/#cyberbotics) Version: R2021a

---------------------------------------------------------

Goals:

* Avoid trajectories that would penetrate the ground (avoid high ground reaction forces - GRF);
* Avoid weak contact or loss of contact (avoid slippage);
* Avoid undesired leg internal forces (avoid slippage and waste of energy);
* Reduce disturbances between joint position and trunk attitude controllers;
* Reduce disturbances at the trunk due to poor state estimation (avoid excessive GRF);
* Increase the locomotion robustness with respect to unexpected terrain irregularities (avoid excessive GRF).

An important element of our framework is the horizontal frame which is a reference frame whose xy plane is always horizontal such that the projection of its x axis on the horizontal plane is parallel to the same projection of the x axis of the robot (that is, the horizontal frame has the same yaw angle as the robot, with respect to the world frame). 

![](images/HorizontalFrame.PNG)

In this picture we can see teh horizontal reference frames (in green) and the robot frame (in blue - the parallelepiped represents the robot trunk); horizontal frames share the same yaw angle with respect to the world reference frame (in black).

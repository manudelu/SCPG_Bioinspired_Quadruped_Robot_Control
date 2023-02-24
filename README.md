Implementation of a Spiking Neuronal Network for Quadruped Robot Control
================================

Abstract
----------------------
Biorobotics can be defined as the science and technology of designing and implementing biologically inspired robotic systems. Its goals are:
* Analyze and study how biological systems work and use these models to design new and better robotic systems that mimic the functionality of their biological counterparts;
* Develop physical platforms equivalent to biological systems in order to experimentally test "models" of living systems and their functional principles.

This thesis falls under the first objective and deals, in particular, with the locomotion of a quadruped robot. The control of locomotion is a complex problem in the field of robotics, despite the fact that it appears rather simple in nature. Learning to adapt one's gait to environmental changes plays an essential role in the locomotion of legged robots. 

As a first step toward this goal, this thesis proposes the use of bio-inspired methodologies for the control of the locomotion of a robotic dog. In particular, a Central Pattern Generator, i.e., a small network of neurons capable of autonomously producing rhythmic activity, which biologically plays a key role in animal locomotion. This network is trained, through a stochastic learning algorithm, to reproduce five different gaits typical of quadrupeds.

In addition, a robotic controller was developed that implements the trained network and dynamic oscillators for generating the trajectories of the quadruped robot's legs. The effectiveness of the control strategy proposed is verified in the Webots simulation environment, via the virtual version of the robotic dog Bioloid.

Keywords: Central Pattern Generators (CPG), Locomotion, Quadruped

Introduction
-------------------
Central Pattern Generators (CPGs) are relatively small neural networks found in both vertebrates and invertebrates. Especially, in vertebrates, they are located at the level of the spinal cord. The function they serve mainly concerns the control of repetitive movements, such as locomotion, breathing and chewing, by generating rhythmic patterns for muscle activation. CPGs can perform their function autonomously even in the absence of sensory feedback from the peripheral nervous system (PNS)  or signals from the central nervous system (CNS). However, some higher areas such as the motor cortex, cerebellum and basal ganglia can modulate the action of CPGs according to the environment.

The term "locomotion" refers to an animal's ability to move from point A to point B; locomotion is based on rhythmic and alternating movements of the whole body and its appendages, which must be able to adapt moment by moment according to environmental conditions. The rhythmic contraction and relaxation of muscles, regulated by the CPGs, drive the limbs in a specific order, generating the different gaits that are observed in animal locomotion. Tasks such as avoiding obstacles or approaching prey require locomotion in a particular direction, at a desired speed. CPGs must therefore be able to to generate multiple gaits, switching between them and adjusting their speed based on control signals from higher brain centers.

The study of the mechanisms that regulate animal locomotion also finds application in the development of bio-inspired controllers for robotic locomotion. In this area, the development of mathematical models of CPG is of paramount importance. The main objectives of this thesis are to (i) model a CPG network that governs the quadruped locomotion, capable of generating five gaits such as side walk, diagonal walk, gallop, bound and trot, (ii) implement a supervised learning algorithm to optimize the weights of the CPG network, (iii) develop a quadruped robot controller on the model basis of CPG and (iv) verify its effectiveness in a robotic simulation environment.



Note: This project may be subject to future changes and improvements.

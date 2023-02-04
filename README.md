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
Central Pattern Generators (CPGs) are relatively small neural networks found in both vertebrates and invertebrates [5]. Especially, in vertebrates, they are located at the level of the spinal cord. The function they serve mainly concerns the control of repetitive movements, such as locomotion, breathing and chewing, by generating rhythmic patterns for muscle activation. CPGs can perform their function autonomously even in the absence of sensory feedback from the peripheral nervous system (PNS) [7-5] or signals from the central nervous system (CNS). However, some higher areas such as the motor cortex, cerebellum and basal ganglia can modulate the action of CPGs according to the environment [1-6].

The term "locomotion" refers to an animal's ability to move from point A to point B; locomotion is based on rhythmic and alternating movements of the whole body and its appendages, which must be able to adapt moment by moment according to environmental conditions. The rhythmic contraction and relaxation of muscles, regulated by the CPGs, drive the limbs in a specific order, generating the different gaits that are observed in animal locomotion [1]. Tasks such as avoiding obstacles or approaching prey require locomotion in a particular direction, at a desired speed [1]. CPGs must therefore be able to to generate multiple gaits, switching between them and adjusting their speed based on control signals from higher brain centers.

The study of the mechanisms that regulate animal locomotion also finds application in the development of bio-inspired controllers for robotic locomotion. In this area, the development of mathematical models of CPG is of paramount importance. The main objectives of this thesis are to (i) model a CPG network that governs the quadruped locomotion, capable of generating five gaits such as side walk, diagonal walk, gallop, bound and trot, (ii) implement a supervised learning algorithm to optimize the weights of the CPG network, (iii) develop a quadruped robot controller on the model basis of CPG and (iv) verify its effectiveness in a robotic simulation environment.

State of Art 
-------------

The interaction between biology and robotics can be developed in two directions: robotics takes inspiration from mechanisms to develop innovative control technologies, but, at the same time, an increasing number of projects seek to change perspectives, using robots as scientific tools to validate biological models. The development of CPG-based control of robot locomotion is interesting not only for understanding animal locomotion systems, but also because it can provide agile, robust, and energy-efficient control during movement in complex environments [6].


Spiking Neural Networks
---------------------------

Artificial neural networks that closely mimic natural neural networks are known as spiking neural networks (SNNs). In addition to neuronal and synaptic status, SNNs incorporate time into their working model. The idea is that neurons in the SNN do not transmit information at the end of each propagation cycle, but only when a membrane potential – a neuron’s intrinsic quality related to its membrane electrical charge – reaches a certain value, known as the threshold.

The neuron fires when the membrane potential hits the threshold, sending a signal to neighbouring neurons, which increase or decrease their potentials in response to the signal. A spiking neuron model is a neuron model that fires at the moment of threshold crossing.

Alan Hodgkin and Andrew Huxley created the first scientific model of a Spiking Neural Network in 1952. The model characterized the initialization and propagation of action potentials in biological neurons. Biological neurons, on the other hand, do not transfer impulses directly. In order to communicate, chemicals called neurotransmitters must be exchanged in the synaptic gap. The leaky integrate-and-fire model (or a derivative) is commonly used as it is easier to compute than the Hodgkin–Huxley model.

The general idea is as;

* Each neuron has a value that is equivalent to the electrical potential of biological neurons at any given time.
* The value of a neuron can change according to its mathematical model; for example, if a neuron gets a spike from an upstream neuron, its value may rise or fall.
* If a neuron’s value surpasses a certain threshold, the neuron will send a single impulse to each downstream neuron connected to the first one, and the neuron’s value  will immediately drop below its average.
* As a result, the neuron will go through a refractory period similar to that of a biological neuron. The neuron’s value will gradually return to its average over time.

SNNs can stimulate the central nervous systems of biological animals, such as an insect seeking food in an unfamiliar environment. They can be used to examine the operation of biological brain networks due to their realism. 

Starting with a hypothesis about the topology and function of a real neural circuit, recordings of this circuit can be compared to the output of the appropriate SNN to assess the hypothesis’ plausibility. However, adequate training processes for SNNs are lacking, which can be a hindrance in particular applications.

Supervised Learning
--------------------

In supervised learning, data (the input) is accompanied by labels (the targets), and the learning device’s purpose is to correlate (classes of) inputs with the target outputs (a mapping or regression between inputs and outputs). An error signal is computed between the target and the actual output and utilized to update the network’s weights. 

Supervised learning allows us to use the targets to directly update parameters, whereas reinforcement learning just provides us with a generic error signal (“reward”) that reflects how well the system is functioning. In practice, the line between the two types of supervised learning is blurred.


CPGs - Central Pattern Generators
--------------------------------

In living things, a CPG is a relatively small network of neurons capable of producing rhythmic patterns even in the absence of sensory feedback or signals from the central nervous system (CNS).

Such networks are critical for many vital functions since they generate the signals that mark movements such as locomotion, breathing, chewing and other rhythmic activities.

In vertebrates, CPGs are located at the level of the spine and the control of motor activity depends on both sensory feedback and supraspinal networks, which, based on planning usually linked to visual systems (e.g., changes of rhythm based on the path to be taken) activate the CPGs, determining the animal's gait.

Function of CPGs: selection of which muscles are to be activated (intensity and time): movement patterns characterized by varying forces and velocities.

External signals, in turn, modify CPG behavior based on sensory and vestibular feedback, allowing changes in gait and adaptation to obstacles. Consequently, the CPG must be able to change its dynamics in order to generate different gaits and velocities.

Objective: Quadruped Locomotion (Bioloid Dog)
--------------------------------

The legs of the quadruped robot are controlled by a network of spiking neurons. A typical network consists of four fully connected neurons where the spiking of a neuron causes the corresponding leg to move. Therefore, producing a gait corresponds to tuning the synaptic weights in the network to cause a specific sequence of spiking in the neurons. Execution of specific tasks requires transitioning between gaits to alter the speed and direction of motion. Thus, the objective is to produce multiple gaits on a single CPG each of which can be triggered independently with seamless transitions, depending upon the environment.

This is capable of generating different types of gaits, in this case will be studied:

* Walk 
* Trot 
* Gallop 
* Diagonal Walk 
* Bound 

There will then be 5 gait selection neurons (G_i) each of which will activate a different pattern depending on the leg movement required for that pattern. 

Remark: More details will be described in the README within the folder named Learning.

HCO (Half-Center Oscillator)
------------------------------

![](images/Half-Center_Oscillator.PNG)

Rhythm generation in CPG networks depends on the intrinsic properties of CPG neurons and their synaptic connections.

The circuits that generate this alternating rhythmic activity have been highlighted mainly at the level of the spinal cord and are based on half-center circuits. The role of the inhibitory (red) neurons in the figure is to produce reciprocal inhibition: that is, when N1 is active it excites the inhibitory interneuron, which goes on to inhibit the antagonistic N2 one. Thus, through rhythmic mechanisms, either the neurons controlling the alpha motor neuron of the flexor muscle or those controlling the alpha motor neuron of the extensor muscle are active. (They are never active at the same time!!!) 

One important thing is that the motor neurons generating this activity can modulate their frequency according to the signals coming from the higher center. Normally these circuits generate basal rhythmic activity (associated with a certain frequency of activity). To increase or decrease this frequency requires a signal from the higher centers to go to stimulate these circuits. So these circuits alone cannot change the locomotor rhythmic activity; in order to modulate this activity, a signal from the higher centers is needed.

In this case I have two mutually inhibited neurons: the HCO is in charge of regulating the flexor and extensor muscles of the single leg. Thus, each CPG can be activated independently.

Bibliography
-------------------------------

* Baruzzi V, Lodi M, Storace M, Shilnikov A. Towards more biologically plausible central-pattern-generator models. Phys Rev E. 2021 Dec;104(6-1):064405. doi: 10.1103/PhysRevE.104.064405. PMID: 35030894.
* A. Lele, Y. Fang, J. Ting and A. Raychowdhury, "An End-to-End Spiking Neural Network Platform for Edge Robotics: From Event-Cameras to Central Pattern Generation," in IEEE Transactions on Cognitive and Developmental Systems, vol. 14, no. 3, pp. 1092-1103, Sept. 2022, doi: 10.1109/TCDS.2021.3097675.
* Barasuol, Victor & De Negri, Victor & De Pieri, Edson. (2011). WCPG: A Central Pattern Generator for Legged Robots Based on Workspace Intentions. ASME 2011 Dynamic Systems and Control Conference and Bath/ASME Symposium on Fluid Power and Motion Control, DSCC 2011. 2. 10.1115/DSCC2011-6164. 
* V. Barasuol, J. Buchli, C. Semini, M. Frigerio, E. R. De Pieri and D. G. Caldwell, "A reactive controller framework for quadrupedal locomotion on challenging terrain," 2013 IEEE International Conference on Robotics and Automation, 2013, pp. 2554-2561, doi: 10.1109/ICRA.2013.6630926.




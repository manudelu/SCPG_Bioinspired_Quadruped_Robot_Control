Learning Algorithm
==========================================

Spiking Patterns:
--------------------------------

* Walk: 

|    |t1 |t2 |t3 |t4 |
|----|---|---|---|---|
| N1 | 1 | 0 | 0 | 0 |
| N2 | 0 | 0 | 1 | 0 |
| N3 | 0 | 0 | 0 | 1 |
| N3 | 0 | 1 | 0 | 0 |
   
* Trot:

|    |t1 |t2 |
|----|---|---|
| N1 | 1 | 0 | 
| N2 | 0 | 1 | 
| N3 | 1 | 0 |
| N3 | 0 | 1 | 

* Bound:

|    |t1 |t2 |
|----|---|---|
| N1 | 1 | 0 | 
| N2 | 1 | 0 | 
| N3 | 0 | 1 |
| N3 | 0 | 1 | 
 
* Diagonal Walk:

|    |t1 |t2 |t3 |t4 |
|----|---|---|---|---|
| N1 | 1 | 0 | 0 | 0 |
| N2 | 0 | 0 | 1 | 0 |
| N3 | 0 | 1 | 0 | 0 |
| N3 | 0 | 0 | 0 | 1 |

* Gallop: 

|    |t1 |t2 |t3 |t4 |
|----|---|---|---|---|
| N1 | 1 | 0 | 0 | 0 |
| N2 | 0 | 1 | 0 | 0 |
| N3 | 0 | 0 | 1 | 0 |
| N3 | 0 | 0 | 0 | 1 |

Each gait sequence (Walk, Trot, Bound, Diagonal Walk and Gallop) must be repeated more than once during the learning process, otherwise you'll get a network that cannot stably reproduce gait. So we set a number of repetitions: ```reps = 10```.

Remark: 

* N_i = Neurons
* t_i = Time Instances

All neurons are connected to each other. The leg corresponding to a neuron moves when that neuron fires. So, when the motor neurons driving legs fire with
fixed temporal differences this gives a rhythmic motion of legs causing a gait.

Multi-gait SCPG 

We have five gait selection neurons corresponding to the five gaits. Each ```Gi``` elicits a different spiking pattern corresponding to the motion of the legs required in that gait. The weights are updated using the difference between required and obtained spiking of CPG neurons which determines whether to excite or suppress the spiking of that neuron.

Gaits:

![](images/Gaits.png)



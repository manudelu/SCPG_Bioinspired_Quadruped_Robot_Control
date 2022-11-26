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

* Ni = quadruped legs
* ti = time instances

Gaits:

![](images/Gaits.png)



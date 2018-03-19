# Group-Movement-Sample
### Personal Information
I am [Jaume Suris](https://www.linkedin.com/in/jaume-suris-valhondo-5438a115b/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

## Introduction

This is a repository meant to help those who are trying to add the movement of units as a group like in simple Real-time Strategy (RTS) games to their projects.
The repository, made with SDL2, includes a file with the solution I reached and one with some some parts of the code erased so whoever whats to, can fill them themselves in order to get a better understanding of their work.

## About Gorup Movement

Group movement is a complex issue in most of the games it has any relevance, since the better it is, the more recources it demands. For example, in order to reach from point A to point B, in a perfect world where no optimizations is needed you could calculate individually the paths of all the units, and afterwards make them calculate how to evade the others. 
That would require too many operations that we cannot afford to expend on such similar incomes. But then, **how do we make units move so that they avoid collisions with the environment but maintaining a lower degree of operations?**

There are different ways to approach this problem. For bigger projects, the squads move as a single entity, or as an entity for each of the sizes and terrains they can move on, and have an effect like that of a magnet pulling them together in order to stick close to one another and when a thinner obstacle appears, the units at the back push the ones at the front in order to let them in. Code-wise this way to approach the issue requires a lot of knowledge so I decided to go for a simplier method, that still creates an effect of moving as a group while simplifying the pathfindings to a degree.

The trick I used to unite the squad while simplifying the pathfinding aspect is to create a **leader** for the squad. This leader will always be the nearest unit to the objective. In my case all the entities have the same movement capavilities, in case there were flying entities or faster units the squad should make a leader for each of the cases, so you don't limit the movement of better units or make units try to cross paths they cannot overcome.

Once this leader is selected, the squad should appear in a visual way differenciated from the rest of the units, since my sample doesn't include any kind of HUD, I made them blit a small square around them, with the leader's in a diferent color.

**What is the leaders function?** A leader will be the only unit finding its way to the destination the moment the player clicks somewhere around the map. As you can see on the picture below, most of the units follow a similar path when the group is close together.

![](https://i.imgur.com/uDmRqA9.png)

*The blue squares represent the path a unit follows while the green one is the place the player clicked*

To avoid all those similar operations. the method I decided to use is, as soon as the destination is known, to make the leader find their own individual path to the goal, and for the rest of the squad, to find their way to the leader.
This way of solving the issue reduces the length of the multiple pathfindings to shorter ones, at least for the first frame when the player clicked. From there, once an entity reaches the place where the leader was, you'll make it find it again until it reaches the goal. For further reductions of operations, you can also make the leader change when it reaches the goal to another member of the squad so the flow keeps going on smaller scale.


### Creating the Squad

Creating the squad is the first of the things you will have to do in order to have your functional group movement.
This step is the simpliest of the three although any error made here will greatly affect the result.

![](https://i.gyazo.com/79e977089b62934528f0eb9bf4806306.png)
*Image of a group of entities mixed with some that aren't*

First of all, **what is a squad?**
Well, in this case, a squad is the class where the list of entities is saved and the interactions between them are checked and calculated. For startes, 

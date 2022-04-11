# EcosystemSimulator


# Table of Contents
1. [About](#about)  
2. [Target](#target)  
3. [Technologies](#technologies)  
4. [Design patterns](#design-patterns)  
5. [Bluprint Components link](#blueprint-components)  
    5.1 [Lifetime component](#lifetime-component)  
    5.2 [Metabolism component and Food component](#metabolism-component-and-food-component)  
    5.3 [Reproduction component](#reproduction-component)  
    5.4 [Appearance component](#appearance-component)  
    5.5 [Stamina/Exhaustion component](#staminaexhaustion-component)  
    5.6 [PhysicalParams component](#physicalparams-component)  
    5.7 [UI Data Component](#ui-data-component)  
    5.8 [Statistics Component](#statistics-component)
6. [AI and Behavior Trees](#ai-and-behavior-trees)  
    6.1 [Danger perception](#danger-perception)  
    6.2 [Reproduction](#reproduction)  
    6.3 [Rest](#rest)  
    6.4 [Food seeking behavior](#food-seeking-behavior)  
    6.5 [Herbivore food finding](#herbivore-food-finding)   
    6.6 [Random patrolling](#random-patrolling)  
7. [Flock Behavior](#flock-behavior)  
    7.1 [Flock component](#flock-component)  
    7.2 [Flock manager](#flock-manager)  
    7.3 [Handling flock behavior in BT](#handling-flock-behavior-in-bt)  
8. [UI](#ui)  
    8.1 [Animal hint and UI components](#animal-hint-and-ui-components)  
    8.2 [Message log](#message-log)  
    8.2 [Statistics](#statistics)
9. [Used assets](#used-assets)    


# About
This is a small project about animals and AI programming.
![Screenshot_6](https://user-images.githubusercontent.com/64382796/162788407-358ce1c9-96e1-4045-806e-d88afb96c886.png)


# Target
The target of this project is to create a flexible system that allows us to construct different animals from building blocks (components) and configure their behavior with a few variables. Of Course animals are complicated, so behavior in simulation  will be simplified. 
This behavior includes:
- Feeding behavior / Hunting
- Avoidance behavior
- Sexual behavior
- Rest
- Research behavior
In the ideal case, the user will be able to create any animal that they want. However, due to difficulties in visual and animation there are only few animals which reflect different archetypes, such as 
- Small herbivores (Savannah mini pigs, my fictional species of animal)
- Big predators (lions)
- Scavengers (hyenas)
- Herd herbivores (zebras)
- Big herbivores (elephants)

# Technologies
Unreal Engine 4 is used. Most of the code is written with Blueprints because of fast development and low iteration time. Behavior trees are used to create AI which is common in GameDev and the Environment Query System is used for decision making in complicated cases. Also Animation blueprints and blendspaces are used for animal animation. 
# Design patterns
First of all, all parts of the behavior system must be as flexible as possible. Secondly, the parts must be independent, so arbitrary sets of behavior can be used. Consequently, the main idea is to use blueprint actor components to create divided and flexible logic, and build animals using these components. For flexibility in Behavior Trees, I drive a few main behavior lines which are common for most animals, and add concrete implementations through dynamic subtrees. (Link to AI part)

# Blueprint components
The idea is to create components for each entity’s capability. 

### Lifetime component
This component is responsible for managing an entity’s lifetime and lifecycle. Many other components and systems depend on it. Checking this component on some entity is equivalent to checking if it is alive. 

### Metabolism component and Food component
Metabolism and food components work in pairs, denoting that an entity can eat or be eaten respectively. `Metabolism component` is capable of hunger and calorie consumption. `Food component` is capable of storing calories and decay. The way these components interact is `Gameplay Tags`. `Metabolism component` has all possible food types in `Tag Container`, also `Food component` stores its tag, for example Food.Meat. When the owner of the metabolism component finds food, the component checks if it is possible to eat that concrete type of food. Same works with decay types, which is necessary for creating scavengers. That allows us to specify food preferences really easily and flexibly.

#### Reproduction component
The main purpose of this component is to store information about sexual development, as well as to generate new entities.The main functions of this component is `SpawnNewEntities` and `CanReproduce`. However the logic in this class is really primitive and suitable only for the simplest entities, such as plants. So, for more complicated reproduction cycles there is `AnimalReproductionComponent`, which is inherited from the `Reproduction component`. It implements pregnancy mechanics and more complicated sexual behavior. 

### Appearance component
This component is responsible for changing an entity appearance. It implements such features as scaling depending on the age, changing color, sexual demorfism (allow enttity have 2 different meshes based on 1 skeleton, and changing them depending on the sex).

### Stamina/Exhaustion component
This component handles entity exhaustion (determines when an entity needs to rest) and stamina (for running in critical situations). When `BT` determines that entity needs to run, it applies `Gameplay Effect` to the controlled pawn. While the effect is active, the component handles stamina reduction, as well as increases exhaustion accumulation. After consuming all stamina, the component removes `Gameplay Effect` from the entity.

### PhysicalParams component
It Stores different physical parameters, which are used for calculation of subjective size. Size is used for decision making while hunting.


And some utility components for the final user.

### UI Data Component
It Stores Name and description for usage in UI. Another important purpose of this component is storing Statuses Array that is used in UI for presenting behavior tree state. BTService AddUIStatus adds and removes statuses when executed and aborterd respectively.

### Statistics Component
Interacts with `WorldStatisticsSubsystem` which is used to count entities. UI gets statistics data from the subsystem.

# AI and Behavior Trees
`BT` is a flexible and intuitive instrument. It is easy to debug, extend and develop. The main idea is to create one big tree, where each leaf of behavior can be replaced with a dynamic subtree if needed.

Another important part of the AI system is Perception. Perception is implemented by `AIPerceptionComponent`, which can be added to `AIController`s and belongs to Unreal’s default and out of the box working solution for AI. 

# Parts of BT
![Screenshot_1](https://user-images.githubusercontent.com/64382796/162781121-a72f1f23-78b4-4717-9bcc-761144195fc5.png)
### Danger perception
The main part of this sub behavior is `CalculateDangerLevel` service. It is constantly executed, calculating the danger level. Danger level is based on animal relative sizes and diets. Two different behaviors are executed based on this value. Each Decorator is working in abort self mode, which allows the pawn to switch them easily while driving one of them. Location to run is generated via `Environment Query System (EQS)`. `Query` generating points in the world, then scoring them based on known enemies’ locations, their rotations, etc. Then, the calculated location is used in `MoveTo` task. To solve the problem, when an animal stops to think about the next run location while predators are near, BT Service is used. Service calculating new location every few seconds and updating TargetLocation. This ensures a continuous and responsive movement of animals.

### Reproduction 
This part of behavior is driven only by males. When the male is ready to reproduce, he sends “request’’ to the female reproduction component. Then if the answer is positive male disables the female's AI and calls `StartBreeding` function. Then, he turns the female's AI back on. This system might be slightly clumsy, but works quite well and is more efficient than trying to synchronize 2 animals on equal terms. Possibly, this behavior needs to be reworked, replaced by a more flexible system with dynamic systems or an outer manager.

### Rest
Rest behavior is the simplest behavior of all. All logic is to rest when there are no dangers nearby and the entity is tired. While executing the `Rest` task, `Exhaustion component` is decreasing exhaustion and restoring stamina.

### Food seeking behavior
Food seeking is different for carnivores and herbivores. In order not to duplicate behavior trees, we use `RunBehaviorDynamic` BT task. Also, we create properties for storing proper SubBT for each animal type and setting it in `AIController`. So we have 2 different BTs for herbivores and carnivores.

### Herbivore food finding
That's a simpler version of food finding subtree. The idea is to check all known and perceived food actors, then eat known food. In case no food is known, `Run EQS task` executed, providing location to go while looking for food.

### Hunt
The main difference between common food finding and hunt is chasing prey. When a predator sees prey, it starts chasing it, when the distance is small enough to attack, `BTTaskFight` is executed, applying damage to the target and killing it. After that predator gets the corpse actor and eats it.

### Random patrolling
When animals have satisfied their needs, random patrolling behavior is executed, being a form of research behavior. In case of flock animals special `EQS Query` is used to prevent the flock from staterring too much.

# Flock Behavior
Implementing flock mechanics is an interesting and challenging task. The main question is how to preserve individuality and at the same time make the AI act as a whole. Flock behavior system consists of three parts, `Flock Manager`, `Flock Component` and `Behavior Trees`. 

## Flock component
The main purpose of that component is to create and join flocks (`Flock Manager`) and store information about the entity's flock and state in that flock. When an entity sees relatives, component checks are in the flock. The component calls `AddToFlock` function in flock manager, which also checks special conditions about flock joining. If relatives are flockless, components try to create flock, which is also based on conditions different for species. If all checks are passed, `Flock Manager` spawns and all initial members pass through `ExposeOnSpawn` array.

## Flock manager
`Flock Manager` has many capabilities, such as member management, movement and danger handling. 
The most important functions of the management section are `Add`, `Remove` and `CanBeMember`. The `CanBeMember` function is intended to be overridden for concrete flock behavior. 
Another part of this class is movement. The `MoveFlock` function receives target location, calculates individual locations for each member and then switches all members’ behavior trees to `BT_FlockMemberMoveTo`. 
When `FlockManager` gives orders, it needs some feedback system to correct them and determine next actions. For this, flock notifiers are used. There are a few BT Tasks which call notifiers(just functions) in `Flock Manager`, after that manager handling them depends on its inner state. For example, such notifiers are used for danger handling. That communication might be a little inflexible, but in the current system scale works well. One of the possible ways to fix that is to create a tag-based event system, like `Gameplay Events` from `GAS`.

## Handling flock behavior in BT
To correctly implement flock mechanics small modification of all behavior trees are needed. For example, instead of starting running when animals see danger, we call notify and delegate this logic to the manager. Another example is executing special `EQS` with constraints based on flock bounds.


# UI
I might not be the best UI designer, however, I do enjoy UI programming.
Because of quite complicated behaviors advanced UI is needed.  

![Screenshot_8](https://user-images.githubusercontent.com/64382796/162791154-54698288-c797-4579-9612-83781e2c8f50.png)
## Animal hint and UI components
Information about an animal and its inner state is the most important part of UI. The main Idea is to create a panel widget that procedurally fills itself depending on components of a given entity. To fulfill this task, I created `Blueprint Interface` that returns UI widget class and priority in the widget panel. Each component that needs to be presented in the UI has its own widget class reference. The widget classes have the same interface, which receives references to target pawns, then implements individual data bindings. Example:

## Message log
It’s hard to notice all the events happening, so there is a message log in the UI. Message creating works via Blueprint Function Library AddMessageToLog Node. It's really easy to use in any code.

## Statistics 
Moreover,keeping track of all animals might be hard, so there is a Statistics Subsystem. Every entity with a StatisticsComponent counts in a subsystem, then the Statistics Widget gets data from that subsystem.

# Used assets
- [AFRICAN ANIMALS PACK](https://www.unrealengine.com/marketplace/en-US/product/african-animals-pack)
- [ANIMAL VARIETY PACK](https://www.unrealengine.com/marketplace/en-US/product/17c2d7d545674204a7644c3c0c4c58ba)
- [Modular Lost Ruin Kit](https://marketplace-website-node-launcher-prod.ol.epicgames.com/ue/marketplace/en-US/product/modular-lost-ruins-kit)



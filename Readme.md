# QtPhysics-Unofficial: A wrapper around BulletPhysics for Qt #
 
QtPhysics-Unofficial is an unofficial module that aims at intergrating Bullet physics engine into Qt (>5.5).
Based on the Qt3D 2.x, the module offers:

* QML components to add physics properties to Qt3D Entities;
* An aspect that implements the physic simulation;
* A Qt plugin that works as wrapper around Bullet Physics;

## QML Components ##

Two Qml componets are provided:

* PhysicsBodyInfo
* PhysicsWorldInfo

Both components inherit from Qt3D:QComponent. The first one, PhysicsBodyInfo, allows to specify for an entity properties such as mass, restituition, friction etc;
The entities belonging to the physic world are:
* Object with an abstract mesh and a PhysicsBodyInfo
* Object with a PhysicsBodyInfo that defines the collition shape with the property "ShapeDetails" ->  those are not rendered

The property "ShapeDetails" allows to override the collition shape properties that otherwise would be inferred from the mesh of the entity. 

PhysicsBodyInfo has two property:
* InputTransform. This matrix is used to set the original position of the object or to force the motion state. When the matrix changes the motion state of the object is updated. NB. By "matrix changes" I  mean that a change is notified. For example, if you create button that set a traslation to dz:100, the matrix changes only if the prevoius value of dz was different. 
* OutputTransorm: the matrix coming from the physics simulation

A body can be declered as kinatic using the kinematic flag.
PhysicsBodyInfo emit a signal collided(CollitionEvent*) when a collition happens.



PhysicsWorldInfo defines general setting for the physic world, such as gravity.

##Physic aspect ##

On the backend, the module implements a Qt3D aspect. When  an entity contains a PhysicsBodyInfo component, a QTransform is added to the frontend in order to move the entity according to its motion state from the simulation. More precisely, those entities have two QTransform components:

* Default one, provided in the Qml and used to set the initial position or to input new position. This is generally disabled once the simulation starts.
* The one added by the aspect, named "@MaDeByPhYsIcS@", that gets updated according to the motion state.

The aspect executes sequentially those jobs:

* Visit the scenegraph and update the physic world. For each entry, create a rigid body and/or update its properties;
* Run a simulation step
* Update the transformation of the entities.
* Update the collitions

##Bullet Plugin##
The wrapper around Bullet is implemented as a plugin. It implements the interface PhysicsFactoryInterface, which defines the methods to create 
bodies and worlds (PhysicsAbstractRigidBody and PhysicsAbstractDynamicsWorld).

##What is missing##
;)

#Build it#

In order to build the module, you need to have Qt >5.5 with Qt3D. Bullet should be available otherwise the plugin cannot be built.

##Build and install Bullet for Desktop##

Follow the procedure at 
https://github.com/bulletphysics/bullet3/releases

##Build and install Bullet for Android##

It is required :

* Android NDK 10d
* Android SDK
* android.toolchain.cmake file from Opencv project

Before you compile it, you have to be sure that the shared libraries of Bullet will not have any version number. In fact, Android doesn't support library versioning.
What I suggest is to modify the CMakeList.txt and add the option:

    OPTION(NO_VERSION "remove the version form shared libraries" OFF)

Then for each CMakeList.txt in the subdirs of src/ add a IF:
Example: In BulletSoftBody/CMakeList.txt 

	IF(NOT NO_VERSION)
	SET_TARGET_PROPERTIES(BulletSoftBody PROPERTIES VERSION ${BULLET_VERSION})
	SET_TARGET_PROPERTIES(BulletSoftBody PROPERTIES SOVERSION ${BULLET_VERSION})
	ENDIF(NOT NO_VERSION)


Then in bullet directory:
* mkdir build-android and cd build-android 
* ccmake .. -DANDROID_NDK=[NDK dir] -DCMAKE_TOOLCHAIN_FILE=[android.toolchain.cmake] -DANDROID_TOOLCHAIN_NAME=[TOOLChain name] -DANDROID_NDK_LAYOUT=RELEASE -DANDROID_ABI=[Your ABI]
* Disable everything except BUILD_SHARED_LIBS ,INSTALL_LIBS and NO_VERSION=true. Check also your install directory.
* make and make install 

Do not forget to add your include dirs and libs enviroment if they are not in the default position.



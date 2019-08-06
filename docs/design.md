# Designing a Basic Game Engine

## Engine Start-up

*Hidden from user*.

In charge of ressource allocation and creation of SDL2 UI objects. Takes care of the start-up of all managers.

## Engine Configuration

*User interface*.

Allows to add objects/textures to render, customize physics and display settings.

## Engine Running

*Hidden from user*.

Takes care of user input, rendering, and updating. It is where the main game loop exists.

## Engine Shut-down

*Hidden from user*.

In charge of ressource deallocation, safely and ensures proper order shut-down for the managers. 
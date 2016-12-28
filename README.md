# SWR
A simple wire frame renderer
SWR is a simple wireframe renderer written with the hope that it will be beneficial to the people who
try to understand the modelling, viewing and projection part of the graphics rendering pipeline. 

The reader / developer must be familiar with C++, Windows programming, rendering pipeline, 3D maths and OpenGL 1.x to 
understand this code and will need Visual studio express edition 2008 or later to run this code.

Known issues: 
The project is done using GDI calls. So it will be slow. 
The frustum clipping is yet to be done, therefore the rendered image may get inverted when it is behind the camera.

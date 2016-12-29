# SWR
SWR is a simple wireframe renderer written with the hope that it will be beneficial to the people who
try to understand the modelling, viewing and projection part of the graphics rendering pipeline. The reader will also get an idea of
how low level graphics apis like OpenGL and DirectX works after reading this code.

The reader / developer must be familiar with C++, Windows programming, rendering pipeline, 3D maths and OpenGL 1.x to 
understand this code and will need Visual studio express edition 2008 or later to run this code.

Known issues: 
The project is done using GDI calls. So it will be slow. 
The frustum clipping is yet to be done, therefore the rendered image may get inverted when it is behind the camera.  
  
Features Implemented:  
Right handed coordinate system  
Vector concept  
Matrix concept  
Modelling transformations (Scaling, Rotation and Translation)  
View transformation  (LookAt , View axes )  
Projection transformations (Orthographic, Perspective)  
Perspective division  
Viewport transformation  
Vertex and index buffers  
Loading Wavefront Object file  
Drawing line with depth interpolation  
Backface culling with signed triangle area computation  
Rendering points  
Rendering triangle lists  
Z-buffering  
Copying color buffer to Window  
  
Acknowledgements:  
Mesa3d 3.0 Project (Viewport transformation, Perspective projection)  
Scratchpixel project(Z-buffering)  

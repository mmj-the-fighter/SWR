# SWR
SWR is a simple wireframe renderer written with the hope that it will be beneficial to the people who
try to understand the modelling, viewing and projection part of the graphics rendering pipeline. 
The reader will also get an idea of how low level graphics apis like OpenGL and DirectX works.
It is coded for right handed coordinate system.

Prerequisites:
The reader / developer must be familiar with C++, Windows programming, rendering pipeline, 
3D maths and OpenGL 1.x to understand this code and should have a version of Visual studio.

Known issues: 
The frustum clipping is yet to be done, therefore the rendered image gets inverted when 
it is behind the camera. The rendering slows down when camera is very close to the model.  
  
Features Implemented:  
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
Book:Computer Graphics by F.S. Hill Jr. (View transformation)  
Mesa3d 3.0  (Viewport transformation, Perspective projection, Z-buffering)  
https://www.scratchapixel.com/ (Z-buffering)  

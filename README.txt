1. Benjamin Carlson / bperkins@mines.edu
2. Assignment 3 / To The Arena
3. This program allows you to move a car around. This includes a minimap in the top right, showing the car from a top-
    down view as well as diffuse and specular lighting. To drive the car, use the W and S keys to move backwards and
    forwards, and the S and D keys to turn left and right. The camera will follow the car around. Press the mouse button
    down to pan around the scene. If you are pressing SHIFT while holding the mouse button and moving, it will begin
    to adjust the zoom. I also gave you the option to use the scroll wheel to zoom in and out since that felt more
    natural to me. In order to exit, simply press Q or the ESC key.
4. To compile, enter the A3 directory, and type "cmake ." in the terminal. This will compile the code. To run the program,
   inside the same directory, run "./cmake-build-debug/A3" and you will see the program launch.
5. As mentioned, A few added features are the minimap and the specular lighting. When looking in the vertex shader code,
   you will see an if statement, not adding specular lighting if the "shininess" is 0. This is simply because the
   ground looked too bright to me without that. I also wanted to add a border around the minimap but had issues.
6. 7 hours
7. The lab helped ALOT. 9/10
8. 9/10. I enjoyed it alot and if I had more time I would've been able to make it even better
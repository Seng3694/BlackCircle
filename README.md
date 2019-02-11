# BlackCirlce #

Small visually stimulating project I've created to mess around with [ImGui][1] and [SFML][2]. Also uses [ImGui-SFML][3].

![4]

## Build ##

This project uses [CMake][6] and [SFML 2.5][2].

1. Clone the repository

    ```
    git clone https://github.com/Seng3694/BlackCircle
    ```

2. Generate the build files

    ```
    mkdir bin
    cd bin
    cmake -G "Your Generator" -DSFML_ROOT="PATH_TO_SFML/lib/cmake/SFML" ../BlackCircle
    ```

    Notice the `SFML_ROOT` parameter which must be set here. You could also edit the code locally and set the `SFML_ROOT` in the [CMake file][7] before `find_package` is being called.

3. Build the files

    ```
    cmake --build . --config Release
    ```


## License ##

This Code is licensed under the MIT License. See [LICENSE][5] for more information.


[1]:https://github.com/ocornut/imgui
[2]:https://github.com/sfml/sfml
[3]:https://github.com/eliasdaler/imgui-sfml
[4]:resources/preview.gif
[5]:LICENSE
[6]:https://cmake.org
[7]:https://github.com/Seng3694/BlackCircle/blob/master/ext/imgui/CMakeLists.txt
# RPG

It's little game, it use SFML and other libs.

# New Features!

  - Load textures from UMap and Texture_map


You can also:
  - build ansd test :D !

### Tech

RPG uses a number of open source projects to work properly:

* [SFML] - Graphic lib
* [OpenCV] - Load and image processing !
* [Boost] - Make units tests and others things :)
* [OpenGL] - OpenGL lib.

You can see my [public repository][ben_github] on GitHub, and can see my [public repository][ben_gitlab] on GitLab.

#### Building for source
You need to install SFML, OpenCV, BoostLib, OpenGL lib, before build.
Download RPG asset :
https://bakudas.itch.io/generic-rpg-pack
https://pipoya.itch.io/pipoya-free-rpg-character-sprites-32x32
and unzip it in texture folder.

For production release:
```sh
cd RPG
```
```sh
./make.sh
```

For debug release:
Just change "Release" to "Debug" in make.sh and run it.

### Docker
You must install docker (and docker-compose maybe in later update)

To run docker builder_test :
```sh
./build.sh
```

To export images from docker builder_test (Without builds):

```sh
./export.sh
```

You can see builds on **build_docker/**

### Todos

 - Write MORE Tests
 - Continue dev. :D

License
----

MIT


**Open source Software forever !**

   [OpenCV]: <https://opencv.org>
   [SFML]: <https://www.sfml-dev.org>
   [Boost]: <https://www.boost.org>
   [OpenGL]: <https://www.opengl.org>
   
   [ben_github]: <https://github.com/Bensuperpc>
   [ben_gitlab]: <https://gitlab.com/Bensuperpc>
   
 

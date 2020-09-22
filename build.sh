docker build -t rpg_builder_manjaro_unstable -f config_docker/Dockerfile_manjaro . --build-arg UID=$(id -u) --build-arg GID=$(id -g) --build-arg IMAGE=manjarolinux/build-unstable

docker run --rm -it --name rpg_builder_1 \
--mount type=bind,source="$(pwd)/RPG",destination=/usr/src/app,readonly \
--mount type=bind,source="$(pwd)/build_docker/manjaro",destination=/usr/src/app/build \
rpg_builder_manjaro_unstable


docker build -t rpg_builder_archlinux -f config_docker/Dockerfile_archlinux . --build-arg UID=$(id -u) --build-arg GID=$(id -g) --build-arg IMAGE=archlinux

docker run --rm -it --name rpg_builder_2 \
--mount type=bind,source="$(pwd)/RPG",destination=/usr/src/app,readonly \
--mount type=bind,source="$(pwd)/build_docker/archlinux",destination=/usr/src/app/build \
rpg_builder_archlinux


docker build -t rpg_builder_ubuntu_20.04 -f config_docker/Dockerfile_ubuntu . --build-arg UID=$(id -u) --build-arg GID=$(id -g) --build-arg IMAGE=ubuntu:20.04

docker run --rm -it --name rpg_builder_3 \
--mount type=bind,source="$(pwd)/RPG",destination=/usr/src/app,readonly \
--mount type=bind,source="$(pwd)/build_docker/ubuntu/20.04",destination=/usr/src/app/build \
rpg_builder_ubuntu_20.04


docker build -t rpg_builder_buster -f config_docker/Dockerfile_ubuntu . --build-arg UID=$(id -u) --build-arg GID=$(id -g) --build-arg IMAGE=debian:buster

docker run --rm -it --name rpg_builder_4 \
--mount type=bind,source="$(pwd)/RPG",destination=/usr/src/app,readonly \
--mount type=bind,source="$(pwd)/build_docker/debian",destination=/usr/src/app/build \
rpg_builder_buster

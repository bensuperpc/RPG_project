docker save rpg_builder_manjaro_unstable | 7z a -si -m0=lzma2 -mx=9 -mmt12 -ms=on -aoa rpg_builder_manjaro_unstable.tar.7z
docker save rpg_builder_buster | 7z a -si -m0=lzma2 -mx=9 -mmt12 -ms=on -aoa rpg_builder_buster.tar.7z 
docker save rpg_builder_ubuntu_20.04 | 7z a -si -m0=lzma2 -mx=9 -mmt12 -ms=on -aoa rpg_builder_ubuntu_20.04.tar.7z 
docker save rpg_builder_archlinux | 7z a -si -m0=lzma2 -mx=9 -mmt12 -ms=on -aoa rpg_builder_archlinux.tar.7z 

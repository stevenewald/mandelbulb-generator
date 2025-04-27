#!/bin/bash

PS4='\033[1;34m>>>\033[0m '

set -xeu

pip3 install conan

conan profile detect -f

std=20
profile="$(conan profile path default)"

mv "$profile" "${profile}.bak"
sed 's/^\(compiler\.cppstd=\).\{1,\}$/\1'"$std/" "${profile}.bak" > "$profile"
rm "${profile}.bak"

global_config="$(conan config home)/global.conf"
{
  echo "tools.system.package_manager:mode=install"
  echo "tools.system.package_manager:sudo=True"
} >> "${global_config}"


if [ -f conan_cache_save.tgz ]; then
  conan cache restore conan_cache_save.tgz
fi
conan remove \* --lru=1M -c
conan install . -b missing -o web_build=False
conan cache save '*/*:*' --file=conan_cache_save.tgz

#!/bin/bash

set -e
set -o pipefail

run_in_docker() {
    local wd="/home/user/proj/taller/clases--repo-personal"
    local img=latex-env
    local user="1000:1000"
    sudo docker run                             \
        --device /dev/fuse                      \
        --cap-add SYS_ADMIN                     \
        --security-opt apparmor:unconfined      \
        --rm                                    \
        -u "$user"                              \
        -v "$wd":/mnt                           \
        -w /mnt                                 \
        $EXTRA "$img" "$@"
}

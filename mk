#!/usr/bin/env bash
#
# 2025-03-22 16:21:10 dpw
#

set -eu

export os="$(uname -s)"
export arch="$(uname -m)"

[ $os == "Linux" ] && {
    export CC=/usr/local/bin/gcc
    export CXX=/usr/local/bin/g++
    export FLAGS="-j8"
} || {
    export FLAGS="-j20"
}

# parse the cli
while [[ $# -gt 0 ]]
do
    case $1 in
        init)
            [ -d build ] || mkdir build
            (cd build && cmake ..)

            shift
        ;;
        build)
            clear

            (cd build && time make $FLAGS || exit 1)

            shift
        ;;
        run)
            ./build/PerfTimerDemo

            shift
        ;;
        format)
            clang-format -i include/perftimer/*.hpp src/*.cpp
            git status -s

            shift
        ;;
        clean)
            (cd build && make clean)
        
            shift
        ;;
        clob*)
            /bin/rm -fr build/

            shift
        ;;
        watch)
            watchexec -c -w src/ -w include/ -e h,hpp,cpp ./mk build run

            exit 0
        ;;
        pull)
            git pull

            shift
        ;;

        help)
            echo "Targets:"
            echo ""
            echo "   init     : run the cmake command to create the build folder"
            echo "   build    : compile cryptor to the build folder"
            echo "   run      : runs the web server app"
            echo "   format   : runs clang-format over includes and src"
            echo "   watch    : run watcher over source and include"
            echo "   pull     : pull the latest repo changes"
            echo "   clean    : remove binary builds but leave the build folder"
            echo "   clobber  : remove the entire build folder"
            echo "   verbose  : show a verbose build"
            echo "   help     : show this help"
            
            exit 0
        ;;
        *)
            ./mk help
            exit 0
        ;;

    esac
done



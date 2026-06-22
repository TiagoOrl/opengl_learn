

if [ ! -d "./build" ]; then
    mkdir build
fi

make cl
make 

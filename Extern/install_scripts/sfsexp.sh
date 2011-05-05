#!/bin/bash

if [ "$EXTERN_DIR" == "" ]; then
  echo ".::ERROR::. enviroment variable EXTERN_DIR was not set"
  echo ".::ERROR::. will exit"
  exit -1
fi

if [ ! -d sexpr_1.2.1 ]; then

  tar xvzf ../downloads/sexpr_1.2.1.tar.gz
  cd sexpr_1.2.1/
  ./configure && make
  cp src/*.h $EXTERN_DIR/include/
  cp src/libsexp.a $EXTERN_DIR/lib/libsfsexp.a
  cd ..
fi



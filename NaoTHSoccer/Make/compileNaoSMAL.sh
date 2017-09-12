echo "###### MAKE FILES ######" && \
premake5 --platform=Nao gmake && \
echo "###### C++ ######" && \
cd ../build/ &&
make -R config=optdebug_nao NaoSMAL $@ && \
cd ../Make/ && \
echo "###### FINISH ######" && exit 0 \

echo "!!!! FAILURE !!!!"
exit 100
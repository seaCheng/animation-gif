rcc -binary instance.qrc -o instance.rcc
rm -rf ./../../bin/release/resource
cp -rf ./../resource ./../../bin/release/resource
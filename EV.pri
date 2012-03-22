# Define the path of the source and the binary (lib)
# these two variables need to be changed on difference machines
IDE_SOURCE_TREE = C:/Users/cxc094020/Program/QtCreator-2.4.1

CONFIG(debug,   debug|release): IDE_BUILD_TREE  = $$IDE_SOURCE_TREE-Debug
CONFIG(release, debug|release): IDE_BUILD_TREE  = $$IDE_SOURCE_TREE-Release

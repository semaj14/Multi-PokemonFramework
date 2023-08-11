@echo off
cls
make clean
make -j 8

mkdir luma\plugins\00040000001B5000
echo. > "luma\plugins\00040000001B5000\Ultra Sun"
copy "Multi-PokemonFramework.3gx" "luma\plugins\00040000001B5000"

mkdir luma\plugins\00040000001B5100
echo. > "luma\plugins\00040000001B5100\Ultra Moon"
copy "Multi-PokemonFramework.3gx" "luma\plugins\00040000001B5100"

mkdir luma\plugins\000400000011C400
echo. > "luma\plugins\000400000011C400\Omega Ruby"
copy "Multi-PokemonFramework.3gx" "luma\plugins\000400000011C400"

mkdir luma\plugins\000400000011C500
echo. > "luma\plugins\000400000011C500\Alpha Sapphire"
copy "Multi-PokemonFramework.3gx" "luma\plugins\000400000011C500

mkdir luma\plugins\0004000000055D00
echo. > "luma\plugins\0004000000055D00\X"
copy "Multi-PokemonFramework.3gx" "luma\plugins\0004000000055D00

mkdir luma\plugins\0004000000055E00
echo. > "luma\plugins\0004000000055E00\Y"
copy "Multi-PokemonFramework.3gx" "luma\plugins\0004000000055E00

mkdir luma\plugins\0004000000175E00
echo. > "luma\plugins\0004000000175E00\Moon"
copy "Multi-PokemonFramework.3gx" "luma\plugins\0004000000175E00

mkdir luma\plugins\0004000000164800
echo. > "luma\plugins\0004000000164800\Sun"
copy "Multi-PokemonFramework.3gx" "luma\plugins\0004000000164800

pause

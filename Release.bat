make
rd Release /s /q
mkdir Release\3ds\PKSV
copy output\3ds-arm\PKSV.cia Release
copy output\3ds-arm\3ds\PKSV\PKSV.3dsx Release\3ds\PKSV
cd Release
zip -r PKSV.zip .
cd ..\
pause
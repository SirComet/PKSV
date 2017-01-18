make
rd Release /s /q
mkdir Release\3ds\PKSV
copy output\3ds-arm\PKSV.cia Release
copy output\3ds-arm\3ds\PKSV\PKSV.3dsx Release\3ds\PKSV
@echo ^<targets selectable="true"^>^</targets^> > Release\3ds\PKSV\PKSV.xml
cd Release
zip -r PKSV.zip .
cd ..\
pause
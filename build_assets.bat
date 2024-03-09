@echo off

:: This scripts builds the bme.bsp file containing replacement assets.
:: Requires node.js

pushd r1_modsrc
if not exist ../build/NUL mkdir "../build"
if exist ../build/bme.zip erase "../build/bme.zip"
:: https://fossies.org/windows/misc/zip300xn-x64.zip
..\thirdparty\zip.exe -0 --recurse-paths --no-dir-entries --junk-sfx --filesync -X ../build/bme.zip .
popd

node ./scripts/zip_to_bsp.js

:end

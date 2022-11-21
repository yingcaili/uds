::---------------------------*******************---------------------
::AutoScript to fill Cm4.hex file for Flash  
::
::Author:liyingcai
::History:
::      20221120: V0.1 Initial,configure Address and file Name
::
::
::
::
::Create single Region File  /FA
::Fill Region  /FR
::Specifu fill pattern /FP
::Merge files  /MT
::silent mode /s 
::Usage:
::      
::---------------------------*******************---------------------

::-----------------Fill data config ----------------------
::@set HexFillInfoDataHead="0x5A 0xA5"
::@set HexFillInfoDataHardWare="0x01 0x02 0x03 0x04"
::@set HexFillInfoDataSoftware="0x05 0x06 0x07 0x08"
::@set HexFillInfoDataDate="0x00 0x00 0x00 0x00"
::@set HexFillInfoDataHeadEnd=A55A
::better with CRC if necessary

::@set HexFillInfoData=%HexFillInfoDataHead%%HexFillInfoDataHardWare%%HexFillInfoDataSoftware%%HexFillInfoDataDate%%HexFillInfoDataHeadEnd%
@set HexFillInfoDataHead=0x5A 0xA5 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x00 0x00 0x00 0x00






::-----------------file path and address config----------------------
@set HexHandleExePath="./srecord/srec_cat.exe"
@set HexAPPStart=0x10080000
:: 110K
@set HexAPPSize=0x1B800 
@set HexFillRegionStart=0x1009B800
@set HexFillRegionSize=0x10
@set HexFillRegionInfoStart=0x1009B810
@set HexFillRegionInfoEnd=0x1009C000
@set HexAPPEnd=%HexFillRegionInfoEnd%
@set HexFillByte=FF
@set HexInputName=cm4.hex
@set HexOutputName=full.hex
@set HexInputNameM0=cm0plus.hex

::----------temp file.these files will be deleted when script executed
@set HexRegionName1=test2.hex
@set HexRegionName2=test3.hex
@set HexRegionName3=test4.hex
@set HexRegionName4=test5.hex

::/FA:0x10090000-0x100A0000 /FR:0x10090000-0x100A0000 /FP:FF 
::create an empty file about 1k,use 0xFF

::/FP:%HexFillByte%

%HexHandleExePath%  -Generate %HexFillRegionStart% %HexFillRegionInfoStart%  -repeat-data %HexFillInfoDataHead% -output %HexRegionName1% -Intel 
%HexHandleExePath%  -Generate %HexFillRegionInfoStart% %HexFillRegionInfoEnd%  --constant 0xff -output %HexRegionName2% -Intel 

%HexHandleExePath% %HexRegionName1% -Intel %HexRegionName2% -Intel -o %HexRegionName2% -Intel



%HexHandleExePath%  %HexInputName% -Intel -fill 0xff %HexAPPStart% %HexFillRegionStart%   -output %HexRegionName3%  -Intel
%HexHandleExePath% %HexRegionName2% -Intel %HexRegionName3% -Intel -o %HexRegionName3% -Intel
copy  %HexRegionName3% cm4full.hex
%HexHandleExePath% %HexInputNameM0% -Intel -fill 0xff 0x10000000 0x10080000  -o  %HexRegionName4% 
%HexHandleExePath% %HexRegionName3% -Intel %HexRegionName4% -Intel -o %HexOutputName% -Intel
::-output cm0plus.hex -Intel

::@set FillAddress=-fill 0xff %HexFillRegionStart% %HexFillRegionSize%
::@set FillValidData=/FP:%HexFillInfoData% 
::@set OutputMethod=/s /XI -o
::@%HexHandleExePath%  %FillValidData%  %OutputMethod% %HexRegionName1% 
::@%HexHandleExePath% /FR:%HexFillRegionInfoStart%-%HexFillRegionInfoEnd%  /FP:FF /XI -o %HexRegionName2% /s
::@%HexHandleExePath% %HexRegionName1% /MT:%HexRegionName2% /XI -o %HexRegionName2% /s
::@%HexHandleExePath% %HexInputName% /FR:%HexAPPStart%,%HexAPPSize% /FP:%HexFillByte% /XI -o %HexRegionName3% /s
::@%HexHandleExePath% %HexRegionName3% /MT:%HexRegionName2% /XI -o %HexOutputName% /s
::
::@%HexHandleExePath% %HexInputNameM0% /FR:0x10000000-0x1007ffff /FP:FF /XI -o %HexRegionName4% /s
::@%HexHandleExePath% %HexRegionName4% /MT:%HexOutputName% /XI -o %HexOutputName% /s
::
::
::@%HexHandleExePath% HexFile1.hex -Intel HexFile2.hex -Intel -o MergedHexFile.hex -Intel




@del %HexRegionName1%
@del %HexRegionName2%
@del %HexRegionName3%
@del %HexRegionName4%
pause
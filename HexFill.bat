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
@set HexFillInfoDataHead=5AA5
@set HexFillInfoDataHardWare=01020304
@set HexFillInfoDataSoftware=05060708
@set HexFillInfoDataDate=00000000

::better with CRC if necessary
@set HexFillInfoDataHeadEnd=A55A
@set HexFillInfoData=%HexFillInfoDataHead%%HexFillInfoDataHardWare%%HexFillInfoDataSoftware%%HexFillInfoDataDate%%HexFillInfoDataHeadEnd%



::-----------------file path and address config----------------------
@set HexViewPath="./HexView/HexView.exe"
@set HexAPPStart=0x10080000
:: 110K
@set HexAPPSize=0x1B800 
@set HexFillRegionStart=0x1009B800
@set HexFillRegionSize=0x10
@set HexFillRegionInfoStart=0x1009B810
@set HexFillRegionInfoEnd=0x1009BFFF
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
@%HexViewPath% /FR:%HexFillRegionStart%,%HexFillRegionSize%  /FP:%HexFillInfoData% /XI -o %HexRegionName1% /s
@%HexViewPath% /FR:%HexFillRegionInfoStart%-%HexFillRegionInfoEnd%  /FP:FF /XI -o %HexRegionName2% /s
@%HexViewPath% %HexRegionName1% /MT:%HexRegionName2% /XI -o %HexRegionName2% /s
@%HexViewPath% %HexInputName% /FR:%HexAPPStart%,%HexAPPSize% /FP:%HexFillByte% /XI -o %HexRegionName3% /s
@%HexViewPath% %HexRegionName3% /MT:%HexRegionName2% /XI -o %HexOutputName% /s

@%HexViewPath% %HexInputNameM0% /FR:0x10000000-0x1007ffff /FP:FF /XI -o %HexRegionName4% /s
@%HexViewPath% %HexRegionName4% /MT:%HexOutputName% /XI -o %HexOutputName% /s


@del %HexRegionName1%
@del %HexRegionName2%
@del %HexRegionName3%
@del %HexRegionName4%
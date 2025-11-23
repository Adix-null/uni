:: build app
dotnet publish -c Release -r linux-x64 --self-contained false

:: copy main folder
scp -i C:\Users\Adomas\.ssh\id_ed25519 -P 22 -r bin/Release/net10.0/linux-x64/publish/  adbi1341@uosis.mif.vu.lt:/stud3/2024/adbi1341/Documents/ 
:: Copy sql files
scp -i C:\Users\Adomas\.ssh\id_ed25519 -P 22 -r bin/Release/net10.0/linux-x64/publish/queries adbi1341@uosis.mif.vu.lt:/stud3/2024/adbi1341/Documents/

@echo off
setlocal
title BOTOL - ouverture du projet Unreal Engine 5.8

rem Double-clic sur ce fichier : compile BOTOL puis ouvre l'editeur Unreal.
rem Le projet doit etre dans le meme dossier que ce fichier (BOTOL.uproject).

set "PROJET=%~dp0BOTOL.uproject"
set "UE="

if not exist "%PROJET%" (
  echo BOTOL.uproject introuvable a cote de ce fichier.
  echo Ce fichier doit rester dans le dossier BOTOL.
  pause
  exit /b 1
)

rem Emplacement d'Unreal Engine 5.8 installe par l'Epic Games Launcher.
for /f "tokens=2,*" %%A in ('reg query "HKLM\SOFTWARE\EpicGames\Unreal Engine\5.8" /v InstalledDirectory 2^>nul ^| find /i "InstalledDirectory"') do set "UE=%%B"
if not defined UE if exist "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe" set "UE=C:\Program Files\Epic Games\UE_5.8"

if not defined UE (
  echo Unreal Engine 5.8 introuvable automatiquement.
  echo Ouverture de BOTOL.uproject avec le programme associe : reponds OUI s'il propose de recompiler.
  start "" "%PROJET%"
  exit /b 0
)

echo Unreal Engine 5.8 : %UE%
echo.
echo Compilation de BOTOL. La premiere fois, compte quelques minutes...
echo.
call "%UE%\Engine\Build\BatchFiles\Build.bat" BOTOLEditor Win64 Development -Project="%PROJET%" -WaitMutex
if errorlevel 1 (
  echo.
  echo ===== ECHEC DE LA COMPILATION =====
  echo Copie les premieres lignes contenant "error" ci-dessus et envoie-les a Claude.
  pause
  exit /b 1
)

echo.
echo Compilation reussie. Ouverture de l'editeur...
start "" "%UE%\Engine\Binaries\Win64\UnrealEditor.exe" "%PROJET%"
exit /b 0

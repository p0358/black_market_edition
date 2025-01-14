if ($args.Count -lt 1) {
    Write-Output "Usage: <premake>"
    exit 1
}

$premakeVersion = $args[0]

if ($PSVersionTable.PSVersion.Major -lt 6.0) {
    switch ($([System.Environment]::OSVersion.Platform)) {
        "Win32NT" { 
            New-Variable -Option Constant -Name IsWindows -Value $True -ErrorAction SilentlyContinue
            New-Variable -Option Constant -Name IsLinux -Value $false -ErrorAction SilentlyContinue
            New-Variable -Option Constant -Name IsMacOs -Value $false -ErrorAction SilentlyContinue
        }
    }
}

$destination = "premake.zip"
$premakeBinPath = "premake/premake5.exe"
$premakePath = "premake"

$currentPremakeVersion = ""
if (Test-Path $premakeBinPath) {
    $currentPremakeVersion = ((& $premakeBinPath --version) -join "`n").Replace("premake5 (Premake Build Script Generator) ", "").Trim()
    if ($premakeVersionOutput -eq $premakeVersion) {
        exit
    }
    Write-Output "Premake dependency outdated: $currentPremakeVersion, expected: $premakeVersion"

    #-------------------------------------------------
    Write-Output "Deleting old Premake binary..."
    #-------------------------------------------------
    
    Remove-Item $premakeBinPath -ErrorAction Ignore
}

#-------------------------------------------------
Write-Output "Locating 7-Zip"
#-------------------------------------------------

. $PSScriptRoot\7zip.ps1

#-------------------------------------------------
Write-Output "Downloading Premake..."
#-------------------------------------------------

Add-Type -AssemblyName System.Web
$premakeURLVersion = [uri]::EscapeUriString($premakeVersion) 

$source = "https://github.com/premake/premake-core/releases/download/v$premakeURLVersion/premake-$premakeURLVersion-windows.zip"

# Net.WebClient is much faster than Invoke-WebRequest/Invoke-RestMethod
(New-Object Net.WebClient).DownloadFile($source, $destination)

#-------------------------------------------------
Write-Output "Unpacking Premake..."
#-------------------------------------------------

# Only unpack the files we need
& "$7z" x $destination premake5.exe -aoa -o"$premakePath"

#-------------------------------------------------
Write-Output "Doing cleanup..."
#-------------------------------------------------

Remove-Item $destination

#-------------------------------------------------
Write-Output "Premake download done!"

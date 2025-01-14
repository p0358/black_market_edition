function Get-7zRegistry {
    $reg = [Microsoft.Win32.RegistryKey]::OpenBaseKey([Microsoft.Win32.RegistryHive]::LocalMachine, [Microsoft.Win32.RegistryView]::Registry64)

    if ($null -eq $reg) {
        return $null
    }

    $szKey = $reg.OpenSubKey("SOFTWARE")
    if ($null -eq $szKey) {
        return $null
    }

    $szKey = $szKey.OpenSubKey("7-Zip")
    if ($null -eq $szKey) {
        return $null
    }

    return $szKey.GetValue("Path") + "7z.exe"
}

function Get-7zDefaultPaths {
    if (Get-Command "7z" -ErrorAction SilentlyContinue) {
        return (Get-Command "7z" -ErrorAction SilentlyContinue).Source
    }

    if (Get-Command "7zz" -ErrorAction SilentlyContinue) {
        return (Get-Command "7zz" -ErrorAction SilentlyContinue).Source
    }

    $path = "$env:ProgramFiles\7-Zip\7z.exe"
    if (Test-Path -Path $path -PathType Leaf) { return $path }

    $path = "$env:ProgramW6432\7-Zip\7z.exe"
    if (Test-Path -Path $path -PathType Leaf) { return $path }

    $path = "${env:ProgramFiles(x86)}\7-Zip\7z.exe"
    if (Test-Path -Path $path -PathType Leaf) { return $path }

    $path = "$env:ProgramFiles\7-Zip-Zstandard\7z.exe"
    if (Test-Path -Path $path -PathType Leaf) { return $path }

    $path = "$env:ProgramW6432\7-Zip-Zstandard\7z.exe"
    if (Test-Path -Path $path -PathType Leaf) { return $path }

    return $null
}

if ($IsWindows) {
    $7z = Get-7zRegistry
}

if ($null -eq $7z) {
    $7z = Get-7zDefaultPaths
}

if ($null -eq $7z) {
    Write-Error -Message "Could not locate 7-Zip. Make sure you have 7-Zip installed and try again."
    exit 1
}

param (
    [Parameter(Mandatory=$true)][string]$mode
)



if ($mode -eq "upgrade") {
    $from = "v140"
    $to = "v141"
    Write-Output "Upgrading ..."
} elseif ($mode -eq "downgrade") {
    $from = "v141"
    $to = "v140"
    Write-Output "Downgrading ..."
} else {
    Write-Error "Invalid option. Pass in either 'upgrade' or 'downgrade'"
}



(Get-Content .\CS133Assignment1.vcxproj).Replace($from, $to) | Set-Content .\CS133Assignment1.vcxproj

Write-Output "Done!"
Param(
    [Parameter(Mandatory=$true)]
    [string]$folder
);

$code = Get-ChildItem $folder -Recurse | Where-Object { $_.extension -eq ".h" -or $_.extension -eq ".cpp" }


For ($i = 0; $i -lt $code.Length; $i++) {
    
    # Write-Output $code[$i].FullName;
    $reader = [System.IO.File]::OpenText($code[$i].FullName);
    For ($k = 1;;$k++) {
        $line = $reader.ReadLine();
        if ($line -eq $null) { break }

        if ($line.length -ge 80 -and $line -notmatch "https://") {
            Write-Host -NoNewline $code[$i].FullName "Line" $k "@" $line.Length "|" $line "`n";
        }
    }
    $reader.Close();

}
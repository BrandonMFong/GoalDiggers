<#
.Synopsis
.Notes
#>
Param
(
)

# Get IE object and get content from the link
$global:ie=new-object -com "internetexplorer.application";
$ie.navigate("https://www.airnow.gov/?city=Santa Rosa&state= California (US)"); # Get html content

while ($ie.busy -or $ie.readystate -lt 4){start-sleep -milliseconds 200} # Wait until $ie object is done processing

# Save to file 
$ie.document.body.getElementsByClassName('aqi').InnerTest | Out-File  "temp.txt" -Force | Out-Null;


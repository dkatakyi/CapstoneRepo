/* This program designs a website. This website displays the data values placed in the CSV file and it is updated every 1 mins */
/* capstone project by ESE group 2 */

<!DOCTYPE html>
<html>
<meta charset="UTF-8">
<meta name = "viewport" content ="width=device-width, initial-scale=1">

/* Style for the website */
<style>

* {

 	box-sizing: border-box;
	margin: 0px 

}

body {

	font-family: "Verdana";

}


header {

		background-color: #003300;

		padding: 10px;

		text-align: center;

		font-size: 24px;

		color: white;

		border: 2px black;
		
		margin: 0px;

}
  
tr:nth-child(even){

		background-color: #dddddd;
 
}
  
.mycenter {


		float: center;

		width: 100%;

		font-size: 24px;

		text-align: center;

		background-color:white;

		padding: 8px;

}
  
</style>
<head>
<title>ROMS Dashboard</title>
</head>
<body>
<header>

<h1>Room Occupancy Management System(ROMS) Dashboard </h1>

</header>

<div class="mycenter" >

/* displays the csv file on the website from FTP */
  
<?php 

echo "<html><body><table style = \"border: 1px solid black; border-collapse:collapse; width:100%;\">\n\n";
$f = fopen("0b1.csv", "r");

while (($line = fgetcsv($f)) !== false) {
        echo "<tr>";
        foreach ($line as $cell) {
                echo "<td style = \"border: 1px solid #dddddd; padding:8px;\">" . htmlspecialchars($cell) . "</td>";
        }
        echo "</tr>\n";
}
fclose($f);
echo "\n</table></body></html>";
?>
  
</div>
</body>
</html>


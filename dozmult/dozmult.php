<!-- +AMDG  This document was begun on 23 July 11E5, and it
is humbly dedicated to St. Pantaleon and to the Immaculate
Heart of Mary, for their prayers, and to the Sacred Heart of
Jesus, for His mercy. -->

<html>
<head>
<title>Dozenal Multiplication Table Drills</title>
</head>

<body>

<?php

function simpdoz($number)
{
	if ($number == 10) 
		$number = "X";
	elseif ($number == 11) 
		$number = "E";
	elseif ($number == 12) 
		$number = 10;
	else 
		$number = $number;
return $number;
}

function dozenalize($number)
{
	$doznum = "";
	while ($number >= 12) {
		$nextdig = $number % 12;
		$number /= 12;
		$nextdig = simpdoz($nextdig);
		$doznum .= $nextdig;
	}
	$nextdig = $number % 12;
	$number /= 12;
	$nextdig = simpdoz($nextdig);
	$doznum .= $nextdig;
	$doznum = strrev($doznum);
	return $doznum;
}

function decimalize($number)
{
	$decans = 0;
	$number = strrev($number);
	$length = strlen($number);
	$multip = 1;
	for ($i = 0; $i < $length; ++$i) {
		if ($number[$i] == 'E')
			$newnum = 11;
		elseif ($number[$i] == 'X')
			$newnum = 10;
		else
			$newnum = $number[$i];
		$decans = $decans + ($newnum * $multip);
		$multip *= 12;
	}
	return $decans;
}

if (isset($_POST['answer']))
{
	print "<center>";
	$decimalans = $_POST['decimalans'];
	$answer = $_POST['answer'];
	$dozans = decimalize($answer);
	if ($decimalans == $dozans)
		print "Right!  The answer is $answer!<br />";
	else {
		print "Wrong!  The correct answer is ";
		print dozenalize($decimalans);
		print "!<br />";
	}
	print "</center>";
}

$factor1 = rand(0,12);
$factor2 = rand(0,12);
$dozfact1 = simpdoz($factor1);
$dozfact2 = simpdoz($factor2);
$decimalans = $factor1 * $factor2;

print "<center>";
print "$dozfact1<br />";
print "$dozfact2<br />";
print "______________<br /><br />";
print "<form method=\"post\" action=\"dozmult.php\">";
print "<input type=\"text\" maxlength=\"2\" size=\"3\" ";
print "name=\"answer\"><br />";
print "<input type=\"submit\" value=\"Submit\">";
print "<input type=\"hidden\" value=\"$decimalans\"";
print "name=\"decimalans\">";
print "</form>";
print "</center>";

?>

</body>
</html>

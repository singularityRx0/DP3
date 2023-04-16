<?php

	$datetime1 = date_create("2023-04-18 23:59:58");
	//$datetime1 = date_create(date("Y-m-d H:i:s"));
	$datetime2 = date_create("2023-04-18 24:00:00");
	$diff = date_diff($datetime2,$datetime1);

	$days =  (int)$diff->format("%R%a");
	$days1 = (int)$days;

	echo "difference in days " .$diff->format("%R%a") ."<br>";
	echo "difference in hours " .$diff->format("%R%h") ."<br>";
	echo "difference in minutes " .$diff->format("%R%i") ."<br>";
	echo "difference in seconds " .$diff->format("%R%s")."<br>";

	echo $days ."<br>";
	echo gettype($days) ."<br>";
	echo $days1 ."<br>";
	echo gettype($days1) ."<br>";

	if ($days1 >0) {
		echo "days1 is a positive number";
	}
	else
	echo "days1 is not a positive number";
?>

<?php
/* Database connection settings */
	$servername = "localhost";
    $username = "root";		//put your phpmyadmin username.(default is "root")
    $password = "012862871105232000lzH@";			//if your phpmyadmin has a password put it here.(default is "root")
    $dbname = "login_register";
    
	$con = mysqli_connect($servername, $username, $password, $dbname);

    if($con) {
        echo "Database connection successfull";
    }
    else
    echo "Unable to establish a connection to the database";
?>

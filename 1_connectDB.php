<?php

    $servername = "localhost";
    $username = "root";		//put your phpmyadmin username.(default is "root")
    $password = "012862871105232000lzH@";			//if your phpmyadmin has a password put it here.(default is "root")
    $dbname = "appprototype";
    
	$conn = mysqli_connect($servername, $username, $password, $dbname);

    if($conn -> connect_error) {
        die("Database Connection Failed: ". $conn->connect_error);
    }
    else
    ob_start();
    echo "Database Connection Successes";
    ob_end_clean();
?>

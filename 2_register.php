<?php

    require "1_connectDB.php";

    if(!empty($_POST['name']) && !empty($_POST['username']) && !empty($_POST['email']) 
        && !empty($_POST['ic_no']) && !empty($_POST['password'])) {

        $name = $_POST['name'];
        $username = $_POST['username'];
        $email = $S_POST['email'];
        $ic_num = $S_POST['ic_num'];
        $password = password_hash($S_POST['password'], algo:PASSWORD_DEFAULT);
        $permission = 0;

        $sql = "insert into user_data (name,username,email,ic.no,password,permission) values 
                ('".$name."', '".$username."', '".$email."', '".$ic_num."', '".$password."', '".$permission."') ";

        if(mysqli_query($conn,$sql)==true)
        {
            echo "success";
        }
        else
        echo "Regristration Failed";


    }
    else
    echo "All Fields Are Required";

    $conn->close();
?>
<?php

    require "connectDB.php";

        $name = "test";
        $username = "test";
        $email = "test";
        $ic_num = "test";
        $password = password_hash("test", algo:PASSWORD_DEFAULT);
        $permission = 0;

        $sql = "insert into user_data (name,username,email,ic_num,password,permission) values 
        ('".$name."', '".$username."', '".$email."', '".$ic_num."', '".$password."', '".$permission."')";

        if(mysqli_query($conn,$sql)==true)
        {
            echo "success";
        }
        else
        echo "Regristration Failed";
?>

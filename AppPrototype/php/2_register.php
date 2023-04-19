<<?php

    require "1_connectDB.php";

    if(!empty($_POST['name']) && !empty($_POST['username']) && !empty($_POST['email']) 
        && !empty($_POST['ic_no']) && !empty($_POST['password'])) {

        $name = $_POST['name'];
        //$username = $_POST['username'];
        $email = $_POST['email'];
        $ic_num = $_POST['ic_num'];
        $password = password_hash($S_POST['password'], algo:PASSWORD_DEFAULT);
        $permission = 0;

        //$sql = "insert into user_data (name,username,email,ic.no,password,permission) values 
                //('".$name."', '".$username."', '".$email."', '".$ic_num."', '".$password."', '".$permission."') ";

        $sql = "insert into user_data (name,email,ic_num,password,permission) values 
                ('".$name."', '".$email."', '".$ic_num."', '".$password."', '".$permission."') ";

        if($conn->query($sql))
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

<?php

if(!empty($_POST['name']) && !empty($_POST['email']) && !empty($_POST['password'])) {
    $con = mysqli_connect(hostname:"localhost" , username:"root" , password:"012862871105232000lzH@" ,database:"login_register");
    //require 'connectDB.php';

    $name = $_POST['name'];
    $email = $_POST['email'];
    $password = password_hash($_POST['password'], algo:PASSWORD_DEFAULT) ;

    if($con) {
        $sql = "insert into users(name,email,password) values ('".$name."', '".$email."', '".$password."')";

        if(mysqli_query($con, $sql)) {
            echo "success";
        }
        else echo "Registration failed";

    }
    else echo "Database connection failed";

    mysqli_close($con);

}
else echo "All fields required";


?>
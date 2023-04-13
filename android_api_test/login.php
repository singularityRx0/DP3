<?php

if(!empty($_POST['email']) && !empty($_POST['password'])) {

    $con = mysqli_connect(hostname:"localhost" , username:"root" , password:"012862871105232000lzH@" ,database:"login_register");


    $email = $_POST['email'];
    $password = $_POST['password'];
    $result = array();

    if($con) {
        $sql = "select * from users where email = '".$email."' ";
        $res = mysqli_query($con, $sql);
        
        if(mysqli_num_rows($res) !=0 ) {
            $row = mysqli_fetch_assoc($res);

            if($email == $row['email'] && password_verify($password, $row['password'])) {
                try{
                    $apikey = bin2hex(random_bytes(length:23));
                } 
                catch(Exception $e) {
                    $apikey = bin2hex(uniqid($email, more_entropy:true));
                }

                $sqlUpdate = "update users set apikey = '".$apikey."' where email = '".$email."' ";
                if(mysqli_query($con, $sqlUpdate)) {
                    $result = array("status" => "success", "message" => "Login successful", 
                    "name" => $row['name'], "email" => $row['email'], "apikey" => $apikey);
                }
                else 
                $result = array("status" => "failed", "message" => "Login failed try again");
            }
            else
            $result = array("status" => "failed", "message" => "Retry with correct eamil & password");
        }
        else
        $result = array("status" => "failed", "message" => "Retry with correct email & password");
    }
    else
    $result = array("status" => "failed", "message" => "Database connection failed");

    mysqli_close($con);
}
else
$result = array("status" => "failed", "message" => "All fields are required");

echo json_encode($result, flags:JSON_PRETTY_PRINT);

?>
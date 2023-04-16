<?php

    require '1_connectDB.php';

    if(!empty($_POST['email']) && !empty($_POST['password'])) {
        $email = $_POST['email'];
        $password = $_POST['password'];

        $json = array();

        $sql = "select * from user_data where email = '".$email."' ";
        $res = $conn->query($sql);

        if($res->num_rows != 0) { 
            $row = $res->fetch_assoc();

            if($email == $row['email'] && $row['permission'] == 0 ) {
                $json = array("status" => "failed", "message" => "Account is under verification by admin. 
                Please wait at least 24h for approval");
            } 
            elseif ($email == $row['email'] && $row['permission'] == 1) {
                if(password_verify($password, $row['password'])){
                    try {
                        $apikey = bin2hex(random_bytes(length:23));
                    }
                    catch(Exception $e) {
                        $apikey = bin2hex(uniqid($email, more_entropy:true));
                    }

                    $sqlUpdate = "update user_data set apikey = '".$apikey."' where email = '".$email."' ";
                    
                    $conn->query($sqlUpdate);

                    $json = array("status" => "success", "message" => "Login successful", 
                    "name" => $row['name'], "email" => $row['email'], "apikey" => $apikey);
                }
                else
                $json = array("status" => "failed", "message" => "Retry with correct password");
            }
        }
        else
        $json = array("status" => "failed", "message" => "Retry with correct email");

    }
    else
    $json = array("status" => "failed", "message" => "All fields are required");



    
    echo json_encode($json, flags:JSON_PRETTY_PRINT);

    $conn->close();
?>
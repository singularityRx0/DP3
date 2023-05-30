<?php

if (!empty($_POST['email']) && !empty($_POST['apikey'])) {
    $con = mysqli_connect(hostname:"localhost" , username:"root" , password:"@" ,database:"login_register");

    $email = $_POST['email'];
    $apikey = $_POST['apikey']; 
    $result = array();    

    if($con) {
        $sql = "select * from users where email = '".$email."' and apikey = '".$apikey."' ";
        $res = mysqli_query($con,$sql);

        if (mysqli_num_rows($res) != 0) {
            $row = mysqli_fetch_assoc($res);
            $sqlUpdate = "update users set apikey = '' where email = '".$email."' ";

            if (mysqli_query($con,$sqlUpdate)) {
                echo "success";
            }
            else
            echo "Logout failed";
        }
        else
        echo "Unauthorised access";
    }
    else
    echo "Database connection failed";

    mysqli_close($con);

}
else
echo "All fields required";

?>

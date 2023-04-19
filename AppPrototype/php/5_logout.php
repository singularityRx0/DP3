<?php

    require '1_connectDB.php';

    if (!empty($_POST['email']) && !empty($_POST['apikey'])) {
    

        $email = $_POST['email'];
        $apikey = $_POST['apikey']; 
        $result = array();    

        $sql = "select * from users where email = '".$email."' and apikey = '".$apikey."' ";
        $res = $conn->query($sql);

        if ($res->num_rows != 0) {
            $row = mysqli_fetch_assoc($res);
            $sqlUpdate = "update users set apikey = '' where email = '".$email."' ";

            if ($conn->query($sqlUpdate)) {
                echo "success";
            }
            else
            echo "Logout failed";
        }
        else
        echo "Unauthorised access";    
    }

    $conn->close();

?>
